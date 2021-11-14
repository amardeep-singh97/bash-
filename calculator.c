#include<stdio.h>
#include<unistd.h>
#include<stdlib.h>
#include<sys/signal.h>
#include<fcntl.h>
#include<sys/wait.h>
#include<math.h>
#include<wchar.h>
#include<string.h>

int occurence(char *str, char op){
    int counter = 0;
    int len = strlen(str)-1;
    for(int i=0;str[i];i++){
        if(str[i]==op){
            counter++;
            if(i==0 || i==len-1){
                counter++;
            }
        }
    }
    return counter;
}

void childFunction(char *arg){
    int file;
    double num1=0,num2=0;
    double finalResult;
    int flag = 0;
    char lit[512];
    char *ptr;
    char *str1 = arg;
    int counter;
    printf("%s\n","I am a child working for my Parent");
    file = open("result.txt",O_CREAT | O_WRONLY | O_TRUNC,0700);
    if(strchr(str1,'+')!=NULL){

        if(occurence(str1,'+')>1){
            flag=1;
        }else{
            char *token = strtok(arg, "+");
            num1 = atof(token);
            token = strtok(NULL,"+");
            num2 = atof(token);
            finalResult = num1+num2;
        }
    }else if(strchr(str1,'-')!=NULL){
        if(occurence(str1,'-')>1){
            flag=1;
        }else{
            char *token = strtok(str1, "-");
            num1 = atof(token);
            token = strtok(NULL, "-");
            num2 = atof(token);
            finalResult = num1 - num2;
        }
    }else if(strchr(str1,'*')!=NULL){
        if(occurence(str1,'*')>1){
            flag=1;
        }else{
            char *token = strtok(str1, "*");
            num1 = atof(token);
            token = strtok(NULL,"*");
            num2 = atof(token);
            finalResult = num1*num2;
        }
    }else if(strchr(str1,'/')!=NULL){
        if(occurence(str1,'/')>1){
            flag=1;
        }else{
            char *token = strtok(str1, "/");
            num1 = atof(token);
            token = strtok(NULL,"/");
            num2 = atof(token);
            if(num2!=0){
                finalResult = num1/num2;
            }else{
                flag = 1;
            }
        }
    }else{
        flag = 1;
    }

    if(flag==1){
        close(file);
        exit(55);
    }else{
        sprintf(lit,"%f",finalResult);
        write(file,lit,sizeof(finalResult));
        close(file);
        exit(0);
    }
}

int main(){
    pid_t pid;
    char in[512];
    int status;
    int code;
    int openfile;
    char displayResult[256];
    printf("%s\n","This Program is a simple calculator");
    
    while(1){

        printf("%s\n","Enter an expression, e.g., 134.5+146>");
        read(STDIN_FILENO,in,sizeof(in));
        if((pid=fork())>0){
            printf("%s\n","Created a child to perform task. Waiting....");
            wait(&status);
            code = WEXITSTATUS(status);
        }else if(pid==0){
            childFunction(in);
        }
        
        if(code==55){
            printf("%s\n","Wrong Expression");
        }else{
            openfile = open("result.txt",O_RDONLY);
            read(openfile,displayResult,sizeof(displayResult));
            printf("Parent: File contains value:- %s\n",displayResult);
        }
    }
}