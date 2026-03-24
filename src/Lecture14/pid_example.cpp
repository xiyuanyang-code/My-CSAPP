#include "iostream"
#include <sys/types.h>
#include <unistd.h>

void show_process_usage_demo() {
  pid_t current_pid = getpid();
  std::cout << "Current PID:" << current_pid << std::endl;
  pid_t parent_pid = getppid();
  std::cout << "Parent PID:" << parent_pid << std::endl;
}

int main(){
    show_process_usage_demo();
    return 0;
}