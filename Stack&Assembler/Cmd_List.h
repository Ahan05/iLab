enum Comands
{
    cmd_PUSH=2,
    cmd_POP=1,
    cmd_ADD=3,
    // функции без аргрументов должны иметь нечетные числа!!!!
    // пока реализованы 3 функции
};

struct MassOfCmd
{
    int num;
    const char *name;
};

struct MassOfCmd Mass[] =
{
    {cmd_PUSH, "PUSH"},
    {cmd_POP, "POP"},
    {cmd_ADD, "ADD"},
};
