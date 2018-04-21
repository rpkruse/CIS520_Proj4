#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/time.h>

#define MAX(x, y) (((x) > (y)) ? (x) : (y))
#define WIKI_SIZE 1000000 //The number of lines in the wiki file
#define WIKI_LINE_SIZE 2003 //The number of characters in each line

char wiki_lines[WIKI_SIZE][WIKI_LINE_SIZE];

void LCS (char *first, char *second, int m, int n){
   int i,j;
         
   int (*L)[n+1] = malloc(sizeof(int[m+1][n+1]));
   int len = 0;
   
   int row, col;
 
   for(i = 0; i <= m; i++){
      for(j = 0; j <= n; j++){ 
         if(i == 0 || j == 0)
            L[i][j] = 0;
         else if (first[i-1] == second[j-1]){
            L[i][j] = L[i-1][j-1] + 1;
            if(len < L[i][j]){
               len = L[i][j];
               row = i;
               col = j;
            }
         }else{
            L[i][j] = 0;
         }
      }
   }

   if(len == 0){
      printf("No common substring\n");
      return;
   }

   char *results = (char*)malloc((len + 1) * sizeof(char));

   while (L[row][col] != 0){
      results[--len] = first[row - 1];

      row--;
      col--;
   }

   free(L);
   printf("%s\n", results);
}

int main(){
   FILE *fp;
 
   char line1[WIKI_LINE_SIZE];
   char line2[WIKI_LINE_SIZE];

  
   char line [WIKI_LINE_SIZE];
   size_t len1 = 0;
   size_t len2 = 0;

   ssize_t read;
   
   fp = fopen("/homes/dan/625/wiki_dump.txt", "r");
   
   if(fp == NULL){
      perror("UNABLE TO FIND FILE!\n");
      exit(EXIT_FAILURE);
   }

   int readingLines = 1;
   int lineCount = 0;

  

   //Copy in the wiki file
   int count = 0;
   while( fgets(line, WIKI_LINE_SIZE, fp) != NULL){
      strcpy(wiki_lines[count], line);
      count++;
   }

   fclose(fp);

   //int onLine = 0;
   int i;
   for(i = 0; i<WIKI_SIZE - 1; i++){
      LCS(wiki_lines[i], wiki_lines[i+1], strlen(wiki_lines[i]), strlen(wiki_lines[i+1])); 
   }
   




   if(line1)
      //free(line1);
   exit(EXIT_SUCCESS);
} 
