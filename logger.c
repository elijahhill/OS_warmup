#include <stdio.h>
#include <stdlib.h>

int check_args(int argc, char *argv[]);

int main(int argc, char *argv[]){
    int checkNum = check_args(argc, argv);
    if(checkNum == 0){
        int sys_check = system("ps augx > ps.log");
    }
}

/**
* Checks to make sure that the correct # of arguments are used
* if not returns 1
* if so, continues
* Checks to make sure that a valid # of seconds are used
* if not, returns 1
* if so, returns 0
*/
int check_args(int argc, char *argv[]){
    if(argc != 2){
        printf("Usage: ps-logger <sleep interval (seconds)>\n");
        return 1;
    }
    else{
        if(!(*argv[0] >= 1)){
            printf("Seconds must be at least 1");
            return 1;
        }
        else{
            return 0;
        }
    }
}