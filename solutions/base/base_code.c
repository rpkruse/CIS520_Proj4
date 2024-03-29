#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/time.h>

#define MAX(x, y) (((x) > (y)) ? (x) : (y))
#define WIKI_SIZE 100000//1000000 //The number of lines in the wiki file
#define WIKI_LINE_SIZE 2003 //The number of characters in each line

char wiki_lines[WIKI_SIZE][WIKI_LINE_SIZE];
char solution[WIKI_SIZE][WIKI_LINE_SIZE];

/*
 * This method finds the LCS of two given strings and adds it to a global array "solution"
 * @param char *first: - The first string to compare
 * @param char *second:- The second string to compare
 * @param int m:- The length of the first string
 * @param int n:- The length of the second string
 * @param int index:- The index we are currently on in the solution array
 */
void LCS (char *first, char *second, int m, int n, int index){
   int i,j;
         
   int (*L)[n+1] = malloc(sizeof(int[m+1][n+1]));
   int len = 0;
   
   int row, col;

   char *results;

   //Compute LCS store in local matrix
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

   results = (char*)malloc((len + 1) * sizeof(char));

   //Pull the LCS from the local matrix
   while (L[row][col] != 0){
      results[--len] = first[row - 1];
      row--;
      col--;
   }

   free(L);

   //Save the solution into our solution array at index index
   strcpy(solution[index], results);
}

/*
 * This method is called at the end, it outputs the results stored in
 * the solution array
 */
void output_final_results(){
   int i;
   for(i = 0; i<WIKI_SIZE; i++){
      printf("%s\n", solution[i]);
   }
}

/*
 * This method is called when we have read the wiki pages into our global array, it will compare the i and i+1 lines
 */
void compare_wiki_pages(){
   int i;
      
   for(i = 0; i<WIKI_SIZE - 1; i++){
      LCS(wiki_lines[i], wiki_lines[i+1], strlen(wiki_lines[i]), strlen(wiki_lines[i+1]), i); 
   }
}

/*
 * This method reads the file and stores the results into our global array
 */
void init_wiki_page(){
   FILE *fp;

   char line[WIKI_LINE_SIZE];
   int count = 0;
   int i;

   fp = fopen("/homes/dan/625/wiki_dump.txt", "r");
   
   if(fp == NULL){
      perror("UNABLE TO FIND FILE\n");
      exit("EXIT_FAILURE");
   }
 
   while( fgets(line, WIKI_LINE_SIZE, fp) != NULL && count < WIKI_SIZE){
      strcpy(wiki_lines[count], line);
      count++; 
   }

   fclose(fp);
}

int main(){
   struct timeval t1, t2, t3, t4, t5;
   double elapsedTime;
   int numSlots, myVersion = 1; //base = 1, openmp = 2, pthreads = 3, mpi = 4

   gettimeofday(&t5, NULL); 
   init_wiki_page();
   gettimeofday(&t1, NULL);
   elapsedTime = (t1.tv_sec - t5.tv_sec) * 1000.0; //sec to ms
   elapsedTime += (t1.tv_usec - t5.tv_usec) / 1000.0; //us to ms
   printf("Time to load wiki page: %f\n", elapsedTime);

   gettimeofday(&t2, NULL);
   compare_wiki_pages();   
   
   gettimeofday(&t3, NULL);
   elapsedTime = (t3.tv_sec - t2.tv_sec) * 1000.0; //sec to ms
   elapsedTime += (t3.tv_usec - t2.tv_usec) / 1000.0; //us to ms
   printf("Time to get LCS: %f\n", elapsedTime);

   gettimeofday(&t4, NULL);
   output_final_results();   

   elapsedTime = (t4.tv_sec - t1.tv_sec) * 1000.0; //sec to ms
   elapsedTime += (t4.tv_usec - t1.tv_usec) / 1000.0; //us to ms
   printf("DATA, %d, %d, %d, %s, %f\n", myVersion, 1, WIKI_SIZE, getenv("NSLOTS"), elapsedTime);
   exit(EXIT_SUCCESS);
} 
