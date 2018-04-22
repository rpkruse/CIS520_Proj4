#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/time.h>

#define MAX(x, y) (((x) > (y)) ? (x) : (y))
#define WIKI_SIZE 1000000 //The number of lines in the wiki file
#define WIKI_LINE_SIZE 2003 //The number of characters in each line
#define num_threads 32

pthread_mutex_t wiki_lock;

int wiki_index = -1;

char wiki_lines[WIKI_SIZE][WIKI_LINE_SIZE];
char solution[WIKI_SIZE][WIKI_LINE_SIZE];

//int num_threads = 32;

struct thread_data {
   char *first;
   char *last;
   int m;
   int n;
   int index;
};

struct thread_data thread_data_array[num_threads];


//void LCS (char *first, char *second, int m, int n, int index){
void LCS(int myID){ 
   /*pthread_mutex_lock (&wiki_lock);
       int index = ++wiki_index;
   pthread_mutex_unlock (&wiki_lock);
 
   if(index >= WIKI_SIZE-1) return;
   printf("index: %d\n", index);*/

   int startPos = ((int) myID) * (WIKI_SIZE / num_threads);
   int endPos = startPos + (WIKI_SIZE / num_threads);


   int index;
 
   //printf("start: %d end: %d\n", startPos, endPos); 
   for(index = startPos; index < endPos; index++){

   char *first = wiki_lines[index];
   char *second = wiki_lines[index+1];
   int m = strlen(first);
   int n = strlen(second);
   int i,j;
   
   //printf("First: %s\n\n Second: %s\n\n", first, second);
      
   int (*L)[n+1] = malloc(sizeof(int[m+1][n+1]));
   int len = 0;
   
   int row, col;

   char *results;

   
  
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

   //if(len == 0){
   //   printf("No common substring\n");
   //   return;
   //}

      results = (char*)malloc((len + 1) * sizeof(char));

      while (L[row][col] != 0){
         results[--len] = first[row - 1];

         row--;
         col--;
      }

      free(L);
      //printf("%s\n", results); 
      //solution[index] = results;
      
      //printf("printing: \n%s\n  at: %d\n", results, index);
      strcpy(solution[index], results);
   }
}

void output_final_results(){
   int i;
   for(i = 0; i<WIKI_SIZE; i++){
      printf("%s\n", solution[i]);
   }
}

void compare_wiki_pages(){
   int i, rc;
   void *status;

   pthread_t threads[num_threads];
   pthread_attr_t attr;

   pthread_attr_init(&attr);
   pthread_attr_setdetachstate(&attr, PTHREAD_CREATE_JOINABLE);

   
   for(i=0; i < num_threads; i++){
      rc = pthread_create(&threads[i], &attr, LCS, (void *)i);
      if(rc) {
         printf("Error; return code from pthreads_create() is %d\n", rc);
         exit(-1);
      }
   } 

   pthread_attr_destroy(&attr);
   for(i=0; i<num_threads; i++){
      rc = pthread_join(threads[i], &status);
      if(rc){
         printf("Error; return code from pthreads_join() is %d\n", rc);
         exit(-1);
      }
   }


   //for(i = 0; i<WIKI_SIZE - 1; i++){
   //   LCS(wiki_lines[i], wiki_lines[i+1], strlen(wiki_lines[i]), strlen(wiki_lines[i+1]), i); 
  // }

   //output_final_results();

}

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

   pthread_mutex_init(&wiki_lock, NULL);

   fclose(fp);
}

int main(){
   struct timeval t1, t2, t3, t4, t5;
   double elapsedTime;
   int numSlots, myVersion = 3; //base = 1, openmp = 2, pthreads = 3, mpi = 4

   
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
   printf("DATA, %d, %s, %f\n", myVersion, getenv("NSLOTS"), elapsedTime);

   pthread_mutex_destroy(&wiki_lock);
   pthread_exit(NULL);
   exit(EXIT_SUCCESS);
} 
