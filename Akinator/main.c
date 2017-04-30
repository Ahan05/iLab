//
//  main.c
//  TREE
//
//  Created by Ahan Shabanov on 01.12.15.
//  Copyright © 2015 Ahan Shabanov. All rights reserved.
// 1) созадние дерева из считанного файла (символы) +
// 2) созадние дерева из считанного файла (строки) +
// 3) вопросно-ответная форма (вроде сделано, но не полностью выводит все вопросы, нужна отладка) +
// 4) добавление новой ветки +
// 5) вывод дерева с добавленной веткой +
// 6) улучшить ввод с файла+
// 7) менять имя файлов ввода и ввывода+

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>

typedef char* Data;

struct Node {
    Data val;            // data in a node
    struct Node * left;  // left child
    struct Node * right; // right child
    struct Node * prev; // previous node
};

struct Node* root;  // root of my tree

struct Node * tree_add (struct Node * tree, Data x);
void tree_print (struct Node * tree);
void child(struct Node * tree);
void tree_destroy (struct Node * tree);
void tree_outp_graph (struct Node * tree, FILE **);
struct Node * tree_constr(struct Node * tree, FILE** in);
void tree_search(struct Node * tree);
void my_scanf(char*);
void tree_search_plus(struct Node * tree);
void new_tree_outp (struct Node * tree, FILE **);
char* str_clean(char*);
void input_val(FILE** in, struct Node * tree );


int main()
{
    FILE * in = fopen("data.txt", "r");
    FILE * out_graph = fopen ("output.txt", "w");
    FILE * out_new_tree = fopen ("input_new_tree.txt", "w");

    if (in == NULL)
    {
        printf("не могу открыть файл input.txt");
        assert(0);
    }

    printf("Hi, Think of a character from Star Wars, and I will try to guess him\n");
    printf("You should answer the folowing questions by writing + (YES) or - (NO) \n");
    printf("If I missed, help me to improve the program by writing the question and the right answer\n");

    root = (struct Node*)calloc(sizeof(struct Node), 1);
    root->val = (char*)calloc(sizeof(char), 30);

    tree_constr (root, &in);

    tree_search(root);

    new_tree_outp(root, &out_new_tree);

    fprintf(out_graph, "digraph tree {\n");
    tree_outp_graph(root, &out_graph);
    fprintf(out_graph, "}");

    tree_destroy(root);
    return 0;
}

void new_tree_outp (struct Node * tree, FILE ** out)  // outputs the new tree, after answering questions
{
    if (tree == NULL)
        return;
    fprintf(*out,"( %s ", tree->val);
    new_tree_outp(tree->left, out);
    new_tree_outp(tree->right, out);
    fprintf(*out, ") ");
    fflush(*out);
}


void wrong_answ(struct Node * tree)
{
    struct Node * tree_quest, * tree_answ;
    char quest[30], answ[30];

    printf("What question is missed?\n");
    fgets(quest, 30, stdin);
    quest[strlen(quest)-1] = '\0';
    if (strcmp(quest, "") == 0)
    {
        printf("Nothing was added\n");
        assert(0);
    }

    printf("What is the right answer?\n");
    fgets(answ, 30, stdin);
    if (strcmp(answ, "") == 0) assert(0);
    answ[strlen(answ)-1] = '_';

    tree_answ = (struct Node*)calloc(sizeof(struct Node), 1);
    tree_quest = (struct Node*)calloc(sizeof(struct Node), 1);


    tree_answ->val = (char*)calloc(sizeof(char), 20);
    strcpy(tree_answ->val, answ);
    tree_answ->prev = tree_quest;


    tree_quest->val = (char*)calloc(sizeof(char), 20);
    strcpy(tree_quest->val, quest);
    tree_quest->left = tree_answ;
    tree_quest->right = tree;
    tree_quest->prev = tree->prev;


    if (tree->prev->left == tree) tree->prev->left = tree_quest;
    else tree->prev->right = tree_quest;

    tree->prev = tree_quest;

}


void tree_search(struct Node * tree)  // searching the right answer
{
    char answ;


    if (tree != NULL)
    {
        if ( tree->val[strlen(tree->val)-1] == '_' )  // the end of the tree is signed as _
        {
            tree->val[strlen(tree->val)-1] = '\0';
            printf("%s\n", tree->val);
            tree->val[strlen(tree->val)] = '_';
            printf("Right?\n");
            answ = getchar();
            getchar();
            if (answ == '-') wrong_answ(tree);  // if answer is wrong, use the function wrong_answ
        }
        else
        {
            printf("%s\n", tree->val);     // outputing the question
            answ = getchar();               // inputing the answer
            getchar();

            if (answ == '+') tree_search(tree->left);
            else if (answ == '-') tree_search(tree->right);
            else printf("Wrong input\n");
        }
    }

}

void input_val(FILE** in, struct Node * tree )  // puting data between ( and ) to tree->val
{
    int i;
    char val;
    val = getc(*in);
    val = getc(*in);
    for (i=0; (val != ')') && (val != '('); i++ )
    {
        tree->val[i] = val;
        val = getc(*in);
    }
    tree->val[strlen(tree->val)-1] = '\0';
    ungetc(val, *in);
}


struct Node * tree_constr(struct Node * tree, FILE** in)  // creates a tree from the input.txt file
{
    char temp[20], sup_temp[20];  // 2 temprorary variables

    fscanf(*in,"%s", temp);

    if (feof(*in)!=0)
        return tree;
    else
    {
        if (strcmp(temp, "(") == 0)  // ( - means creating a new node in my tree; ) - means going to the previous node
        {
            if (tree == NULL)   // creating a new node
            {
                tree = (struct Node*)calloc(sizeof(struct Node), 1);
                tree->val = (char*)calloc(sizeof(char), 30);
            }

            input_val(in, tree);  // a function that puts data from the file to the tree->val

            fscanf(*in,"%s", sup_temp);
            if ( strcmp(sup_temp, ")") == 0 )   // checking, if the next symbol is );
            {
                return tree;
            }
            fseek(*in, -2, SEEK_CUR);   // going backwards after checking
            if (tree->left == NULL) tree->left = tree_constr(tree->left, in);    // going to the left child
            tree->left->prev = tree;
            if (tree->right == NULL) tree->right = tree_constr(tree->right, in); // going to the right child
            tree->right->prev = tree;
        }
        fscanf(*in,"%s", temp);
    };
    return tree;
}



void tree_destroy (struct Node * tree)
{
    if (tree != NULL)
    {
        tree_destroy(tree->left);
        tree_destroy(tree->right);
        free(tree);
    }
}

char* str_clean(char* str)  // function that changes the data so that graph constructer undestands
{
    int i;
    char * new_str;

    new_str = (char*) calloc(sizeof(char)*strlen(str)+1, 1);
    strcpy(new_str, str);

    for (i=0; i < strlen(new_str); i++)
    {
        if (new_str[i] == ' ') new_str[i] = '_';
        if (new_str[i] == '?') new_str[i] = '\0';
    }
    return new_str;
}



void tree_outp_graph (struct Node * tree, FILE ** out)  // outputing the tree in the way that graph constructer understands
{
    if (tree != NULL)
    {
        tree_outp_graph(tree->left, out);
        if (tree->left != NULL)
            fprintf(*out, "%s -> %s\n", str_clean(tree->val), str_clean(tree->left->val));

        tree_outp_graph(tree->right, out);
        if (tree->right != NULL)
            fprintf(*out, "%s -> %s\n", str_clean(tree->val), str_clean(tree->right->val));
    }
}
