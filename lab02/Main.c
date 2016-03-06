#include <stdio.h>
#include <pthread.h>
#include <stdlib.h>
#include <sys/queue.h>
#include <semaphore.h>
#include <unistd.h>
#define MAX_QEQUEST 10




//struct for Request
typedef struct Request{
  int ID;
  int length;
}Request;

//Request array
Request* REQUEST_ARR[MAX_QEQUEST];

//count for elements
int count = 0;

//count for requests
int r_count = 0;

//running time
int curr_time = 0;

sem_t mutex;
sem_t empty;
sem_t full;



void *Consumer_funciton(void* input){
  //printf("I'm Consumer %i\n", );
  //
  while (1) {
      sem_wait(&full);//if full = 0(empty), wait
      sem_wait(&mutex);//access to buffer
      Request *tmp = REQUEST_ARR[count-1];
      int length = tmp->length;
      int total_length = length;
      int ID = tmp->ID;

      count--;
      sem_post(&mutex);
      sem_post(&empty);

      printf("Consumer %li: , processing request %i, processing for next %i seconds, current time is %i\n", (long)input,ID, length, curr_time);

      //processing
      while(length>0){
          curr_time++;
          length--;
      }



      printf("\n\n---------------------------------\n");
      printf("Consumer %li, Completed request ID %i, at time %i\n", (long)input,ID, curr_time);
      printf("---------------------------------\n\n");

  }

}

void* Producer_function(void* input){


  while (count <= MAX_QEQUEST) {
    //access to buffer

      sem_wait(&empty);
      sem_wait(&mutex);

      curr_time++;
      int length = (rand() % 10) +1;
      Request* tmp = REQUEST_ARR[count];
      tmp->ID = r_count;
      tmp->length = length;
      printf("Producer: Producing request %i, length %i seconds at time %i\n", tmp->ID,tmp->length,curr_time);
      count++;
      r_count++;
      printf("\n-----------------------------------------Producer: sleeping for %li s\n\n",(long)input);
      sleep(1);

      sem_post(&mutex);
      sem_post(&full);


  }


}

void Consumer(int n, pthread_t input[]){
  for(int i=0; i<n; i++){
    pthread_create(&input[i], NULL, Consumer_funciton, (void*)i);
  }
  for(int i=0; i<n; i++){
    pthread_join(input[i], NULL);
  }

}


void Producer(pthread_t input[], int sleep_length){
  pthread_create(&input[0], NULL, Producer_function, (void*)sleep_length);
}


void Free(){
  for(int i=0; i<MAX_QEQUEST;i++){
    free(REQUEST_ARR[i]);
  }
}


int main(int argc, char const *argv[]) {
  //define semaphores
  sem_init(&mutex,0,1);
  sem_init(&empty,0,MAX_QEQUEST);
  sem_init(&full,0,0);

  for(int i=0; i<MAX_QEQUEST;i++){
    Request* r = (Request*)malloc(sizeof(Request));
    r->ID = -1;
    r->length = -1;
    REQUEST_ARR[i] = r;
  }




  // producer

pthread_t a[1];
Producer(a,1);



  pthread_t b[5];
  Consumer(5,b);



  Free();


  return 0;
}
