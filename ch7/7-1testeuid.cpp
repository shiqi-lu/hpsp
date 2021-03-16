#include <unistd.h>
#include <stdio.h>

int main()
{
    printf("uid:%d, euid:%d\n", getuid(), geteuid());
    return 0;
}
