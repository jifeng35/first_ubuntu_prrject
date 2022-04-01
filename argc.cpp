//
// Created by j1feng on 2022/4/1.
//

#include<stdio.h>
int main(int argc, char* argv[]){
    if(argc == 2){
        printf("Your IP is: %s\n", argv[1]);
    }
    else{
        printf("Your input is illegal!\n");
        printf("Your input is listed as follows: ");
        for(int i=0;i<argc;i++){
            printf("%s ", argv[i]);
        }
        printf("\n");
        printf("Your need to run belike that!\n");
        printf("./argc {Your IP}\n");
    }
    return 0;
}