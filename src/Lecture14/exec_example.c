#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <errno.h>
#include <string.h>

int main() {
    pid_t pid;
    int status;
    
    // 1. 创建子进程
    pid = fork();
    
    if (pid < 0) {
        // fork 失败
        fprintf(stderr, "Fork failed: %s\n", strerror(errno));
        exit(1);
    }
    else if (pid == 0) {
        // ============================================
        // 子进程代码
        // ============================================
        printf("[Child %d] Starting...\n", getpid());
        printf("[Child %d] Current directory: ", getpid());
        
        // 获取并打印当前工作目录
        char cwd[1024];
        if (getcwd(cwd, sizeof(cwd)) != NULL) {
            printf("%s\n", cwd);
        }
        
        // 准备 execve 的参数
        // 相当于执行：ls -l
        char *filename = "/bin/ls";
        char *argv[] = { "ls", "-l", NULL };  // argv[0] 约定为程序名
        char *envp[] = { NULL };               
        
        printf("[Child %d] Executing: %s\n", getpid(), filename);
        
        execve(filename, argv, envp);
        
        fprintf(stderr, "[Child %d] execve failed: %s\n", getpid(), strerror(errno));
        exit(127);  
    }
    else {
        printf("[Parent %d] Child created with PID %d\n", getpid(), pid);
        printf("[Parent %d] Waiting for child to complete...\n", getpid());
        
        // 4. 等待子进程结束并回收资源
        pid_t wpid = wait(&status);
        
        // 5. 检查子进程退出状态
        if (WIFEXITED(status)) {
            int exit_code = WEXITSTATUS(status);
            printf("[Parent %d] Child %d exited normally with status %d\n", 
                   getpid(), wpid, exit_code);
            
            if (exit_code == 0) {
                printf("[Parent %d] ✅ Child completed successfully!\n", getpid());
            } else {
                printf("[Parent %d] ⚠️  Child completed with error code %d\n", 
                       getpid(), exit_code);
            }
        }
        else if (WIFSIGNALED(status)) {
            printf("[Parent %d] Child %d was killed by signal %d\n", 
                   getpid(), wpid, WTERMSIG(status));
        }
        
        printf("[Parent %d] All done, exiting.\n", getpid());
    }
    
    return 0;
}