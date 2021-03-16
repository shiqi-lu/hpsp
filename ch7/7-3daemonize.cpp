#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>

bool daemonize()
{
    // 创建子进程，关闭父进程，可使程序在后台运行
    pid_t pid = fork();
    if (pid < 0) {
        return false;
    } else if (pid > 0) {
        exit(0);
    }

    // 设置文件权限掩码。当进程创建新文件(open系统调用)时，
    // 文件的权限将是mode & 0777
    umask(0);

    // 创建新的会话，设置本进程为进程组的首领
    pid_t sid = setsid();
    if (sid < 0) {
        return false;
    }

    // 切换工作目录
    if ((chdir("/")) < 0) {
        return false;
    }

    // 关闭标准输入设备、标准输出设备和标准错误输出设备
    close(STDIN_FILENO);
    close(STDOUT_FILENO);
    close(STDERR_FILENO);

    // 关闭其它已经打开的文件描述符，此处代码省略
    // 将标准输入、标准输出和标准错误输出都重定向到/dev/null
    open("/dev/null", O_RDONLY);
    open("/dev/null", O_RDWR);
    open("/dev/null", O_RDWR);

    return true;
}

int main()
{
    if (daemonize()) {
        printf("daemonize success\n");
    } else {
        printf("daemonize failed\n");
    }
    while (true) {
        printf("I'm daemon\n");
        sleep(3);
    }

    return 0;
}