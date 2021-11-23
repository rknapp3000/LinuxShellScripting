#include <stdio.h>
#include <dirent.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include <string.h>
#include <stdlib.h>

int fileSize = 0, fileCount = 0, count = 0; 

    int displayDirectory (const char *argv, int count) {
        struct dirent *pDirent;
        DIR *pDir;

        pDir = opendir(argv);     //testing if the directory will open
        if (pDir == NULL) {
            printf("This directory will not open: '%s'\n", argv);
            return 1;
        
        } else {

        while ((pDirent = readdir(pDir)) != NULL) { // testing if there is content in the file
            
            for (int i = 0; i < count; i++ ){  printf(" ");} 
        struct stat fileStatistics;
        fstatat(dirfd(pDir), pDirent->d_name, &fileStatistics, 0);
        
            if(pDirent->d_type == DT_REG){   // if it is a regular file print the name and size
                printf ("%s %d\n", pDirent->d_name, fileStatistics.st_size);
                
                fileSize = fileSize + fileStatistics.st_size;

                fileCount++; //incrementing the file count

          } else {

            printf("%s /\n", pDirent->d_name);
           
            if(strlen(pDirent->d_name) > 2){
            char stringVars[750];
            
            strcpy(stringVars, argv);
            strcat(stringVars, "/");
            strcat(stringVars, pDirent->d_name);

            displayDirectory(argv[1], count++);
            }
          } 
        }

        closedir(pDir);
        return 0;
        }
    }

int main(int argc, char *argv[]){
    int errorNumber = 1;
    if (argc < 2) {
            fprintf(stderr, "%s.\n", strerror(errorNumber));
            return 0;
       
    } else {
        
        printf("List of all directories %s\n", argv);
        
        displayDirectory(argv[1], 0); //calling method for printing directory
        
        //print functions 
        printf("Total space used to support files: %d\n", fileSize);
        printf("Total count of files: %d\n", fileCount);
        printf("\nEnd.");
    }
}
