#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void editDist();
void printArray();
int min3();

//typedef enum action {DELETE, ADD, REPLACE};
typedef enum {ON, OFF} Debug;
Debug debugger = OFF;

/*
 * Set first argument to "-d" to enable debugging text to be shown.
 */
int main(int argc, char* argv[]) {
    char buffer[1024];
    char* string1; 
    char* string2;
    char* pos;

    if (argc > 1) {
        if (strlen(argv[1]) == 2) {
            if (argv[1][0] == '-' && argv[1][1] == 'd') {
                debugger = ON;
            }
        }
    }
    
    while (printf("Press Ctrl-d to exit, press enter to continue...") && fgets(buffer, 1024, stdin) != NULL) {
        printf("Enter string 1\n");
        fgets(buffer, 1024, stdin);
        if ((pos = strchr(buffer, '\n')) != NULL) {
            *pos = '\0';
        }
        string1 = malloc(sizeof(char) * strlen(buffer));
        strcpy(string1, buffer);
        printf("Enter string 2\n");
        fgets(buffer, 1024, stdin);
        if ((pos = strchr(buffer, '\n')) != NULL) {
            *pos = '\0';
        }
        string2 = malloc(sizeof(char) * strlen(buffer));
        strcpy(string2, buffer);

        editDist(string1, string2);
    }
    printf("\n");
    return 0;
}

/**
* Uses a m by n int array. Think of src as vertical and dest as horizontal.
*/
void editDist(char* src, char* dest) {
    // might need to make dest and src 1 character bigger. malloc new array?
    int** array;
    int srclen = strlen(src);
    int destlen = strlen(dest);
    int i, j;
    
    // initialise rows 
    array = malloc(sizeof(int*) * (srclen + 1));

    // +1 to allow for empty string 
    for (i = 0; i < srclen + 1; i++) {
       array[i] = malloc(sizeof(int) * (destlen + 1));   
    }

    for (i = 0; i < destlen + 1; i++) {
        array[0][i] = i;
        //printf("test:%d ", i);
    } 
    printf("\n");
    for (i = 0; i < srclen + 1; i++) {
        array[i][0] = i;
    }
    
    // Edit Distance Algorithm
    int subcost;
    for (i = 1; i < srclen + 1; i++) {
        for (j = 1; j < destlen + 1; j++) {
            if (dest[j-1] == src[i-1]) {
                subcost = 0;
            } else {
                subcost = 1;
            }
            array[i][j] = min3(array[i-1][j] + 1, array[i][j-1] + 1, array[i-1][j-1] + subcost);
        }
    }

    printArray(array, src, dest);
    /**
     * Free up memory when done.
     */
    for (i = 0; i < srclen + 1; i++) {
        free(array[i]);
    }
    free(array);
}

void printArray(int** a, char* s1, char* s2) {
    int i, j;
    
    if (debugger == ON) {
        printf("length of s1(%s) is: %zu\n", s1, strlen(s1));
        for (i = 0; i<strlen(s1); i++) {
            printf("s1[%d]=%c ", i, s1[i]);
        }
        printf("\n");
        printf("length of s2(%s) is: %zu\n", s2, strlen(s2));
        for (i = 0; i<strlen(s2); i++) {
            printf("s2[%d]=%c ", i, s2[i]);
        }
        printf("\n");
    }

    /**
     * Actual printing of the table.
     */
    printf("%3c%3c", ' ','.');
    //print string s2 along the top
    for (i = 0; i < strlen(s2); i++) {
        printf("%3c", s2[i]);
    }
    printf("\n");
    for(i = 0; i < strlen(s1) + 1; i++) {
        if (i > 0) {
            printf("%3c", s1[i-1]);
        } else {
            printf("%3c", '.');
        }
        for(j = 0; j < strlen(s2) + 1; j++) {
            printf("%3d", a[i][j]);
        }
        printf("\n");
    }
    printf("The minimum edit distance is %d.\n", a[i-1][j-1]);
}

int min3(int a, int b, int c) {
    int temp;
    temp = a;
    if (b < temp) {
        temp = b;
    }
    if (c < temp) {
        temp = c;
    }
    return temp;
}
