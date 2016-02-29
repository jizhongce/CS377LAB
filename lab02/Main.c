#include <stdio.h>
#include <pthread.h>
#include <stdlib.h>
#include <sys/queue.h>
#include <semaphore.h>
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

//running time
int curr_time = 0;

sem_t mutax;
sem_t empty;
sem_t full;


void *Consumer_funciton(void* input){
  //printf("I'm Consumer %i\n", );
  //
  while (1) {

      sem_wait(&full);//if full = 0(empty), wait
      sem_wait(&mutax);//access to buffer
      Request *tmp = REQUEST_ARR[count-1];
      int length = tmp->length;

      while(length> 0){
        length--;
        curr_time++;
        printf("I'm Consumer %i, processing request %i, processing for next %i seconds, current time is %i\n", (int)input,tmp->ID, length, curr_time);
      }
      printf("---------------------------------\n");
      printf("I'm Consumer %i, done processing request %i, processed for %i seconds, current time is %i\n", (int)input,tmp->ID, tmp->length, curr_time);
      count--;
      sem_post(&mutax);
      sem_post(&empty);
  }

}

void* Producer_function(void* input){


  while (count <= MAX_QEQUEST) {
    //access to buffer
    sem_wait(&empty);//
    sem_wait(&mutax);

      curr_time++;
      int length = (rand() % 100) +1;
      Request* tmp = REQUEST_ARR[count];
      tmp->ID = count;
      tmp->length = length;
      count++;
      printf("Producing request %i, current time is %i\n", count,curr_time);

      sem_post(&mutax);
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


void Producer(pthread_t input[]){
  pthread_create(&input[0], NULL, Producer_function, NULL);
}


int main(int argc, char const *argv[]) {
  //define semaphores
  sem_init(&mutax,0,1);
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
Producer(a);



  pthread_t b[5];
  Consumer(5,b);





  return 0;
}
