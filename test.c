#include <stdio.h>
#include<unistd.h>

int main(void){
    syscall(333,"./1","./newfile");
    printf("copy succesfully!\n");
}
