#include<stdio.h>
#include<unistd.h>
#include<sys/types.h>
#include<fcntl.h>
#include<stdlib.h>
#include<ctype.h>
#include<string.h>

typedef struct ImageDetail {
    char pgmType[3];
    unsigned char** data;
    unsigned int width;
    unsigned int height;
    unsigned int maxValue;
} ImageDetail;

void flipImage(char *input,char *output){

    int Initpgm, finalImage;
    int offset;
    char imageHeader[100];
    unsigned char** data;

    ImageDetail* pgm = malloc(sizeof(ImageDetail));

    FILE* Initialpgm = fopen(input,"rb");
    FILE* Filppedpgm = fopen(output,"wb");

    if(Initialpgm==NULL){
        printf("File doesn't exist.");
    }
    else{ 
    //Reading details from old PGM like width, height, pgmType and maxvalue
    fscanf(Initialpgm,"%s",pgm->pgmType);
    fscanf(Initialpgm,"%d %d",&(pgm->width),&(pgm->height));
    fscanf(Initialpgm,"%d",&(pgm->maxValue));
    printf("PGM File Type : %s\n",pgm->pgmType);
    printf("PGM height and width : %d & %d\n",pgm->width,pgm->height);

    //Writing details to new PGM
    fprintf(Filppedpgm, "%s\n", pgm->pgmType);
    fprintf(Filppedpgm, "%d %d\n",pgm->width,pgm->height);
    fprintf(Filppedpgm,"%d\n",pgm->maxValue);


    pgm->data
		= malloc(pgm->height
				* sizeof(unsigned char*));

	if (pgm->pgmType[1] == '5') {

		fgetc(Initialpgm);
        
		for (int i = 0;
			i < pgm->height; i++) {
			pgm->data[i]
				= malloc(pgm->width
						* sizeof(unsigned char));

			if (pgm->data[i] == NULL) {
				fprintf(stderr,
						"malloc allocation failed\n");
				exit(1);
			}

			fread(pgm->data[i],
				sizeof(unsigned char),
				pgm->width, Initialpgm);
		}
        for(int j = pgm->height-1; j>=0; j--){
             fwrite(pgm->data[j],sizeof(unsigned char),pgm->width,Filppedpgm);
        }
	}

    fclose(Initialpgm);
    fclose(Filppedpgm);  
    printf("%s\n","Task Completed.");
  }
}

void reverseImage(char *input,char *output){
    int length,i; 
    ImageDetail* pgm = malloc(sizeof(ImageDetail));

    FILE* Initialpgm = fopen(input,"rb");
    FILE* Filppedpgm = fopen(output,"wb");

    fscanf(Initialpgm,"%s",pgm->pgmType);
    fscanf(Initialpgm,"%d %d",&(pgm->width),&(pgm->height));
    fscanf(Initialpgm,"%d",&(pgm->maxValue));
    printf("PGM File Type : %s\n",pgm->pgmType);
    printf("PGM height and width : %d & %d\n",pgm->width,pgm->height);

    //Writing details to new PGM
    fprintf(Filppedpgm, "%s\n", pgm->pgmType);
    fprintf(Filppedpgm, "%d %d\n",pgm->width,pgm->height);
    fprintf(Filppedpgm,"%d\n",pgm->maxValue);

    fseek(Filppedpgm, 15, SEEK_CUR);

    fseek(Initialpgm, 0, SEEK_END);
    length=ftell(Initialpgm);

    while(i<length){
        i++;
        fseek(Initialpgm,-i,SEEK_END); 
        int c=fgetc(Initialpgm); 
        fputc(c,Filppedpgm); 
    }
    fclose(Initialpgm);
    fclose(Filppedpgm);
}

int main(int argc, char *argv[])
{   int userInput;
    if(argc<2){
        printf("%s\n","You can also use the syntax reverseImage <InputPGM Name> {OutputPGM Name}");
        while(1){
            printf("%s\n","Do you want Flipped Image(1) or Reversed Image(2)? Enter 1 or 2");
            scanf("%d",&userInput);
            if(userInput==1 || userInput==2){
                break;
            }else{
                printf("%s\n","Please Enter correct Input");
            }
        }
        if(userInput==1){
            flipImage("m1.pgm","rm1.pgm");
        }else{
            reverseImage("m1.pgm","rm2.pgm");
        }
    }
    else{
        while(1){
            printf("%s\n","Do you want Flipped Image(1) or Reversed Image(2)? Enter 1 or 2");
            scanf("%d",&userInput);
            if(userInput==1 || userInput==2){
                break;
            }else{
                printf("%s\n","Please Enter correct Input");
            }
        }

        if(userInput==1){
            flipImage(argv[1],argv[2]);
        }else{
            reverseImage(argv[1],argv[2]);
        }
    }
    return 0;
}