#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

int main(int argc, char **argv) {
    char symb=NULL;
    size_t symbQuan=0;
    size_t stringQuan=0;
    size_t wordQuan=0;
    int err;
    int spaceFlag=1;
    FILE *curFile;
    if(argc>1){
        for(int j=1;j<argc;j++){
            curFile=fopen(argv[j],"r");
            err=ferror(curFile);
            if(err==0){
                while(1>0){
                    symb=getc(curFile);
                    if(symb==EOF){
                        break;
                    }
                    symbQuan++;
                    if(symb=='\n'){
                        stringQuan++;
                    }
                    if(isspace(symb)){
                        if(spaceFlag==0){
                            wordQuan++;
                        }
                        spaceFlag=1;
                    }
                    else{
                        spaceFlag=0;
                    }
                }
                if(spaceFlag==0){
                    wordQuan++;
                }
                printf("%s\n",argv[j]);
                printf("%d %d %d\n",stringQuan,wordQuan,symbQuan);
            }
        }
    }
    else{
        while(1>0){
            symb=getchar();
            if(symb==EOF){
                break;
            }
            symbQuan++;
            if(symb=='\n'){
                stringQuan++;
            }
            if(isspace(symb)){
                if(spaceFlag==0){
                    wordQuan++;
                }
                spaceFlag=1;
            }
            else{
                spaceFlag=0;
            }
        }
        if(spaceFlag==0){
            wordQuan++;
        }
        printf("%d %d %d\n",stringQuan,wordQuan,symbQuan);
    }
    return 0;
}