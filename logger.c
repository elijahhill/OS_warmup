#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int check_args(int argc, char *argv[]);
int read_file();
int determine_multithreading(char * state);
char * toStatToken();

int main(int argc, char *argv[]){
    int checkNum = check_args(argc, argv);
    if(checkNum == 0){
        int sys_check = system("ps augx > ps.log");
        if(sys_check == 0){
            read_file();
        }
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

// Using this site to help with reading and writing
// https://www.thegeekstuff.com/2012/07/c-file-handling/
// ...and this https://www.tutorialspoint.com/cprogramming/c_file_io.htm
// settled on this approach http://www.cplusplus.com/reference/cstdio/fgets/
int read_file(){
    char * compareChar = "a";
	char * stringCpy = NULL;
	int buffSize = 3000; // Some chrome rendering processes were over 2000 characters
	char arrBuff[buffSize];
	char arrCpy[buffSize];
	char * individual;
    FILE * file = fopen("./ps.log", "r");
    
    while(compareChar != NULL){
		compareChar = fgets(arrBuff, buffSize, file);

		strcpy(arrCpy, arrBuff);
		
		// Breaks off the first piece from the original string
		individual = strtok(arrCpy, " ");
        individual = toStatToken();
        if(individual != NULL){
            printf("%s\n", individual);
        }
        printf("\n");
        
	}
	return 0;
}

char * toStatToken(){
    int i = 0;
	char * individual;
    
    while(i < 7){
        individual = strtok(NULL, " ");
        i = i + 1;
    }
	return individual;
}

int determine_multithreading(char * state){
    
    return -1;
}