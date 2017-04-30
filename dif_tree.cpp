//
//  main.cpp
//  dif_tree
//
//  Created by Ahan Shabanov on 06.04.16.
//  Copyright © 2016 Ahan Shabanov. All rights reserved.
//

#include <iostream>
#include <string.h>
#include <assert.h>
#include <cstdlib>


#define PLUS new NodeTree(op,'+',
#define MUL new NodeTree(op,'*',
#define DIV new NodeTree(op,'/',
#define SUB new NodeTree(op,'-',
#define COS new NodeTree(op,cos,
#define dL this->left->d()
#define cR this->right->copy()
#define dR this->right->d()
#define cL this->left->copy()
//PLUS MUL dL, cR), MUL cL, dR))

/*#define dL *(this->left->d())
 #define dR *(this->right->d())
 #define cL *this->left->copy()
 #define cR *this->right->copy()*/

////////////  Class NodeTree
class NodeTree
{
private:
    NodeTree* left;
    NodeTree* right;
    char* data;
    char type[5];
public:
    NodeTree();
    NodeTree(char* type,char digit);
    NodeTree(char* type, char deistv, NodeTree* d_left, NodeTree* d_right);
    NodeTree(char* type, char* func_itself, NodeTree* d_left, NodeTree* d_right);
    NodeTree(const NodeTree &obj);
    ~NodeTree();
    void tree_builder(FILE** in);
    void tree_outp_graph (FILE ** out);
    void input_val(FILE** in);
    void tree_print (FILE ** out);
    NodeTree* operator * (NodeTree slag);
    NodeTree* operator + (NodeTree slag);
    void operator = (NodeTree slag);
    NodeTree* copy();
    NodeTree* d();
};

char* str_clean(char* str);

char operators[]="+-/*";
/*
 char val[] = "val";
 char op[] = "op";
 char var[] = "var";*/

//////////// MAIN
int main()
{
    FILE * in = fopen("/Users/Ahan/Documents/Инфа/Dif_tree/Debug/dif_tree/dif_tree/input.txt", "r");
    FILE * out = fopen("/Users/Ahan/Documents/Инфа/Dif_tree/Debug/dif_tree/dif_tree/output.txt", "w");
    if (in == NULL)
    {
        printf("не могу открыть файл input.txt");
        assert(0);
    }
    else fgetc(in);
    
    NodeTree root;
    
    root.tree_builder(&in);
    
    NodeTree* def_tree;
    
    def_tree = root.d();
    
    def_tree->tree_print(&out);
    
    return 0;
}

NodeTree::NodeTree(char* type,char digit)
{
    this->data = new char [10];
    data[0] = digit;
    strcpy(this->type, type);
    left = NULL;
    right = NULL;
}

NodeTree::NodeTree()
{
    this->data = new char [10];
    left = NULL;
    right = NULL;
}

NodeTree::NodeTree(char* type, char deistv, NodeTree* d_left, NodeTree* d_right)
{
    this->data = new char [10];
    data[0] = deistv;
    strcpy(this->type, type);
    left = d_left;
    right = d_right;
}

NodeTree::NodeTree(char* type, char* func_itself, NodeTree* d_left, NodeTree* d_right)
{
    this->data = new char [10];
    strcpy(data, func_itself);
    strcpy(this->type, type);
    left = d_left;
    right = d_right;
}

NodeTree::NodeTree(const NodeTree &obj)
{
    data = new char[10];
    strcpy(data, obj.data);
    strcpy(type, obj.type);
    left = obj.left;
    right = obj.right;
}

NodeTree::~NodeTree()
{
    delete data;
    left = NULL;
    right = NULL;
}

void NodeTree::tree_builder(FILE** in)
{
    char temp;
    while (1)
    {
        fscanf(*in, "%c", &temp);
        if (temp == '(')
        {
            if (this->left == NULL)
            {
                left = new NodeTree;
                left->data = new char [10];
                left->input_val(in);
                left->tree_builder(in);
            }
            else if (this->right == NULL)
            {
                right = new NodeTree;
                right->data = new char [10];
                right->input_val(in);
                right->tree_builder(in);
            }
        }
        
        if (strchr(operators, temp))
        {
            this->data[0]=temp;
            strcpy(this->type, "op");
        }
        if (temp == ')')
        {
            return ;
        }
        if (temp == '=')
        {
            break;
        }
    }
    return;
}

void NodeTree::tree_outp_graph (FILE ** out)  // outputing the tree in the way graph constructer understands
{
    if (this  != NULL)
    {
        this->left->tree_outp_graph(out);
        if (this->left != NULL)
            fprintf(*out, "%s -> %s\n", str_clean(this->data), str_clean(this->left->data));
        
        this->right->tree_outp_graph(out);
        if (this->right != NULL)
            fprintf(*out, "%s -> %s\n", str_clean(this->data), str_clean(this->right->data));
    }
}

char* str_clean(char* str)
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
    
    switch (new_str[0])
    {
        case '+':
            strcpy(new_str, "PLUS");
            break;
        case '-':
            strcpy(new_str, "SUB");
            break;
        case '*':
            strcpy(new_str, "MUL");
            break;
        case '/':
            strcpy(new_str, "DIV");
            break;
        default:
            break;
    }
    return new_str;
}

void NodeTree::input_val(FILE** in)  // puting data between ( and ) to tree->val
{
    int i;
    char val;
    val = getc(*in);
    
    if ((val>='9') || (val<='0'))
    {
        strcpy(this->type,"var");
    } else strcpy(this->type, "val");
    
    for (i=0; (val != ')') && (val != '('); i++ )
    {
        this->data[i] = val;
        val = getc(*in);
    }
    ungetc(val, *in);
}

void NodeTree::tree_print (FILE ** out)
{
    
    fprintf(*out,"(");
    if (this->left != nullptr)
        this->left->tree_print(out);
    
    fprintf(*out,"%s", this->data);
    if (this->right != nullptr)
        this->right->tree_print(out);
    fprintf(*out, ")");
    
}

NodeTree* NodeTree::copy()
{
    NodeTree* temp_node;
    temp_node = new NodeTree;
    temp_node->data = new char [10];
    strcpy(temp_node->data, this->data);
    strcpy(temp_node->type, this->type);
    temp_node->left = this->left;
    temp_node->right = this->right;
    return temp_node;
}

NodeTree* NodeTree::operator * (NodeTree slag)
{
    char op[] = "op";
    //NodeTree* mul_node;
    //mul_node = new NodeTree(op, '*', this, &slag);
    return new NodeTree(op, '*', this, &slag);
}

NodeTree* NodeTree::operator + (NodeTree slag)
{
    char op[] = "op";
    //NodeTree* sum_node;
    //sum_node = new NodeTree(op, '+', this, &slag);
    return new NodeTree(op, '+', this, &slag);
}

void NodeTree::operator = (NodeTree slag)
{
    strcpy(this->data, slag.data);
    strcpy(this->type, slag.type);
    this->left = slag.left;
    this->right = slag.right;
    
}
/*
 NodeTree::NodeTree(char* type, char deistv, NodeTree* d_left, NodeTree* d_right)
 {
 this->data = new char [10];
 data[0] = deistv;
 strcpy(this->type, type);
 left = d_left;
 right = d_right;
 }
 */
NodeTree* NodeTree::d()
{
    char val[] = "val";
    char op[] = "op";
    char var[] = "var";
    /*char func[] = "func";
     char cos[] = "cos";
     char sin[] = "sin";*/
    
    if (strcmp(this->type, val)==0)
    {
        return new NodeTree(val, '0');
    } else
        if (strcmp(this->type, var)==0)
        {
            return new NodeTree(var, '1');
        } else
            if (strcmp(this->type, op)==0)
            {
                switch (this->data[0])
                {
                    case '+':
                        //return  (dL) + (dR);
                        return PLUS dL, dR);
                        break;
                    case '-':
                        return SUB dL, dR);
                        break;
                    case '*':
                        //return (*(dL * cR) + *(cL * dR)) ;
                        return PLUS MUL dL, cR), MUL cL, dR));
                        //return new NodeTree(op,'+',new NodeTree(op,'*',dL,cR),new NodeTree(op,'*',cL, dR));
                        break;
                    case '/':
                        return DIV SUB MUL dL, cR), MUL cL, dR)), MUL cR, cR));
                        break;
                }
            }
    printf("Smth is wrong");
    return 0;
}
/*
 #define dL *(this->left->d())
 #define dR *(this->right->d())
 #define cL *this->left->copy()
 #define cR *this->right->copy()
 */


/*PLUS MUL dL, cR), MUL cL, dR))
 #define PLUS new NodeTree(op,'+',
 #define MUL new NodeTree(op,'*',
 #define COS new NodeTree(op,cos,
 #define dL this->left->d()
 #define cR this->right->copy()
 #define dR this->right->d()
 #define cL this->left->copy()
 */

