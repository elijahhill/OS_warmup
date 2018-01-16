#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <errno.h>

int check_args(int argc, char *argv[]);
int read_file();
int determine_multithreading(char * state);
char * toStatToken();

int main(int argc, char *argv[]){
    int checkNum = check_args(argc, argv);
    if(checkNum >= 1){
        int sys_check = system("ps augx > ps.log");
        if(sys_check == 0){
            while(1){
                read_file();
                sleep(checkNum);
            }
            
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
//Used this https://www.techonthenet.com/c_language/standard_library_functions/stdlib_h/strtol.php
int check_args(int argc, char *argv[]){
    if(argc != 2){
        printf("Usage: ps-logger <sleep interval (seconds)>\n");
        return 1;
    }
    else{
        if(!(*argv[1] >= 1)){
            printf("Seconds must be at least 1");
            return 1;
        }
        else{
            // char * eptr
            long sleepTime = strtol(argv[1], NULL, 10);
            printf("ps-logger: using a default time of %ld seconds.\n", sleepTime);
            return sleepTime;
        }
    }
}

// Using this site to help with reading and writing
// https://www.thegeekstuff.com/2012/07/c-file-handling/
// ...and this https://www.tutorialspoint.com/cprogramming/c_file_io.htm
// settled on this approach http://www.cplusplus.com/reference/cstdio/fgets/
int read_file(){
    char * compareChar = NULL;
	char * stringCpy = NULL;
	int buffSize = 3000; // Some chrome rendering processes were over 2000 characters
	char arrBuff[buffSize];
	char arrCpy[buffSize];
	char * individual; // Are the individual words that string tokenizer gets

    int result = 0;
    int multiTotal = 0;
    int total = 0;
    FILE * file = fopen("./ps.log", "r");
    
    while(1){ // This while loop will be broken out of
		compareChar = fgets(arrBuff, buffSize, file);

        if(compareChar == NULL){
            break;
        }

		strcpy(arrCpy, arrBuff);
		
		// Breaks off the first piece from the original string
		individual = strtok(arrCpy, " ");
        individual = toStatToken();
        if(individual != NULL){
            // printf("%s\n", individual);
        }
        if(strcmp(individual, "STAT") != 0){
            result = determine_multithreading(individual);
        }
        multiTotal = multiTotal + result;
        total = total + 1;
        
	}
    fclose(file);
    double percentage = ((double)multiTotal/total) * 100;
    printf("ps-logger: %d/%d processes are multithreaded. [%f%%]\n", multiTotal, total, percentage);
	return 0;
}

/**
 * Because the stat token is always the 6th token in the ps augx listing,
 * it's the only "individual" token that matters. Thus, we loop to it, and
 * discard everything else.
*/ 
char * toStatToken(){
    int i = 0;
	char * individual;
    
    while(i < 7){
        individual = strtok(NULL, " ");
        i = i + 1;
    }
	return individual;
}

/**
 * Determines whether the element passed in contains a lowercase l, and thus whether
 * that process is considered multithreaded. 
*/
int determine_multithreading(char * state){
    char * result;
    int multiThreadedCount = 0;

    result = strchr(state, 'l');

    if(result != NULL){
        return 1;
    }

    // printf("result is: %s\n\n", result);

    return 0;
}