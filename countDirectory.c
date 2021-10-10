#include<stdio.h>
#include<stdlib.h>
#include<ftw.h>
#include<sys/types.h>
#include<dirent.h>
#include<string.h>

int iteration = 0;

int countDirectory(const char *pathName, const struct stat *statptr, 
	int flag, struct FTW *f)
{	
	if(flag == FTW_D){
		iteration++;
	}
	return 0;
}

int main(int argc, const char *argv[]){
	int returnval;
	DIR *dp;
	struct dirent *dirp;
	char str[50];


	if(argc == 1){
		dp = opendir("./");
		
		dirp = readdir(dp);
		returnval = nftw(dirp->d_name,countDirectory,500,FTW_D);
	}else {
		dp = opendir("./");
		if(strchr(argv[1],'/')!=NULL){
			memmove(&argv[1][0], &argv[1][0 + 1], strlen(argv[1]) - 0);
		}
		while((dirp=readdir(dp))!= NULL){
			if(strcmp(dirp->d_name,argv[1])==0){
				char* path = NULL;
				int argvLen = strlen( argv[1] );
				path = malloc( 9 + argvLen + 4 + 1 );
				strcpy( path, "./" );
				strcat( path, argv[1] );
		 		nftw(path,countDirectory,500,FTW_D);
		 	}
		}
	}


	if(returnval == -1){

	printf(stderr,"Error Ocuured!");

	}else{

	printf("Number of sub directories: %d",iteration-1);

	}

    closedir(0);
    exit(0);

}