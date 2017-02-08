#include "brick.h"

@@VARIABLES@@
Brick brick;

@@SUBPROGRAMS_FORWARDING@@

@@THREADS_FORWARDING@@

@@SUBPROGRAMS@@

@@THREADS@@

void genMain(void)
{
@@MAIN_CODE@@
}

int main(void)
{
    genMain();
    return 0;
}
