// Programmer : Jiaxuan Chen
// Created : Jiaxuan Chen at 5/11/2021
// Purpose:
// Parse the command line input 
//
// Modifications:
// Initial Date Short Description 
// <none>

#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<dirent.h>
#include"main.h"
#include"parser.h"

char *valid_modes[MODENUM]={"-help", "-ssf", "-nodoc", "-notest", "-novars"};

int is_mode_valid(char *mode){
    // ---------------------------------------------------
    // Created : 5/11/2021
    // Purpose:
    // check if a mode that user entered is valid
    //
    // Parameters : the mode string
    // Returns : if the mode is valid, return the index in valid_modes list. if not valid, return -1
    // Side-effects : NULL

    for(int j=0; j<MODENUM; j++){
        if(strcmp(mode, valid_modes[j])==0){
            return j;
        }
    }
    return -1;
}

int mode_parser(int* modes, char **arguments, int argc){
    // ---------------------------------------------------
    // Created : 5/11/2021
    // Purpose:
    // from the command line arguments, parse all the modes and check validation
    //
    // Parameters : 1. a list that will be filled with 1 or 0 to show if the mode in valid_mode list is on.  2.command line arguments
    // Returns : 1 for normal
    // Side-effects : mode should not be duplicated

    int index;

    for(int i=0; i<MODENUM; i++) modes[i]=0;

    for(int i=1; i<argc; i++){
        if(arguments[i][0]=='-'){
            index=is_mode_valid(arguments[i]);
            if(index>=0){
                if(modes[index]==1){
                    printf("Error: mode %s duplicated\n", valid_modes[index]);
                    error_dealer(-1);
                }
                else modes[index]=1;
            }
            else{
                printf("Error: command %s is not valid\n", arguments[i]);
                error_dealer(-1);
            }
        }
        else break;
    }
    return 1;
}

int is_filename_valid(char *filename){
    // ---------------------------------------------------
    // Created : 5/11/2021
    // Purpose:
    // check if the user entered filename really exists
    //
    // Parameters : given filename
    // Returns : 1 for exist, 0 for not
    // Side-effects : NULL

    FILE *f = fopen(filename, "r");
    if(f==NULL) return 0;
    fclose(f);
    return 1;
}

char **all_c_files_list(int *file_num){
    // ---------------------------------------------------
    // Created : 5/11/2021
    // Purpose:
    // get all c files in the current directory
    //
    // Parameters : the address of the number of files that will be rated
    // Returns : the filenames of all c files, if no file exists, return NULL
    // Side-effects : NULL

    DIR *dr;
    int num=0;
    int length;
    struct dirent *en;
    dr = opendir("."); 
    while ((en = readdir(dr)) != NULL) {
        length = strlen(en->d_name);
        if(length>=2 && en->d_name[length-1]=='c' && en->d_name[length-2]=='.') num++;
    }
    if(num==0) {
        printf("Error: no c-extension file exists\n");
        return NULL;
    }
    closedir(dr); 
    char **filenames=malloc(num*sizeof(char*));
    num=0;
    dr = opendir("."); 
    while ((en = readdir(dr)) != NULL) {
        length = strlen(en->d_name);
        if(length>=2 && en->d_name[length-1]=='c' && en->d_name[length-2]=='.'){
            filenames[num]=strdup(en->d_name);
            num++;
        }
    }
    closedir(dr); 
    *file_num=num;
    return filenames;
}

char **filenames_parser(int *file_num, char **arguments, int argc, int index){
    // ---------------------------------------------------
    // Created : 5/11/2021
    // Purpose:
    // get all the filename that user want to check and check whether the names are valid
    //
    // Parameters : the address of the number of files that will be rated, command line arguments and the index where the filename starts
    // Returns : the filenames wanted 
    // Side-effects : NULL

    if(argc==index){
        printf("Error: filenames missing\n");
        error_dealer(-1);
    }
    for(int i=0; i<argc-index; i++){
        if(strcmp(arguments[index+i], "*.c")==0){
            return all_c_files_list(file_num);
        }
    }
    int num=0;
    char **filenames=malloc((argc-index)*sizeof(char*));
    for(int i=0; i<argc-index; i++){
        if(is_filename_valid(arguments[index+i])){
            filenames[i]=strdup(arguments[index+i]);
            num++;
        }
        else{
            printf("Error: file %s does not exist\n", arguments[index+i]);
            error_dealer(-1);
        }
    }
    *file_num=num;
    return filenames;
}

int help_command(){
    // ---------------------------------------------------
    // Created : 5/11/2021
    // Purpose:
    // the help command
    //
    // Parameters : NULL
    // Returns : 1 for normal
    // Side-effects : NULL

    printf("\nThis is the help command, put description later here\n\n");
    return 1;
}
