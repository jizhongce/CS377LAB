#include <stdio.h>
#include <pthread.h>
#include <stdlib.h>
#include <sys/queue.h>
#include <semaphore.h>
#include <unistd.h>
#include <stdint.h>
#define MAX_QEQUEST 10
#define MAX_total 20

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

//three semaphores
sem_t mutex;
sem_t empty;
sem_t full;


//this is the main function of the simulation of what a consumer
//is doing. It contains a while loop keeping accepting jobs and
//executing them.
void *Consumer_funciton(void* input){

  while (1) {
      sem_wait(&full);//if full = 0(empty), wait
      sem_wait(&mutex);//access to buffer

      //get the id of consumer
      int id = (intptr_t) input;
      //get a request from the queue
      Request *tmp = REQUEST_ARR[count-1];

      //get attributes from the request
      int length = tmp->length;
      int total_length = length;
      int ID = tmp->ID;

      //count minus 1 means the consumer will get next element from the queue
      count--;

      //release the lock for mutex and empty
      sem_post(&mutex);
      sem_post(&empty);

      //get the current local time
      time_t current_time;
      current_time = time(NULL);
      char* string;
      string = ctime(&current_time);

      //When a consumer get a request, print the following line
      printf("Consumer %i: processing request %i, processing for next %i seconds, current time is %s\n", id,ID, length, string);

      //sleep 1 second represents the processing of 1 second
      while(length>0){
          sleep(1);
          curr_time++;
          length--;
      }

      //get the current local time
      time_t current_time2;
      current_time2 = time(NULL);
      char* string2;
      string2 = ctime(&current_time2);

      //When a consumer finishes a request, print the following line
      printf("\n\n----------------------------------------\n");
      printf("Consumer %li, Completed request ID %i, at time %s\n", (long)input,ID, string2);
      printf("----------------------------------------\n\n");
  }
}

//this is main function of simuation of a producer, which contains a
//while loop keeping creating jobs
void* Producer_function(void* input){
  while (1) {

      //access to buffer and check if the queue is full
      sem_wait(&empty);
      sem_wait(&mutex);

      //get sleep_length
      int sleep_length = (intptr_t)input;
      //the length of request is randomly generated from 1 to 10
      int length = (rand() % 10) +1;
      //add the request to the queue
      Request* tmp = REQUEST_ARR[count];
      //set data to the request
      tmp->ID = r_count;
      tmp->length = length;
      curr_time++;

      //get the current local time
      time_t current_time3;
      current_time3 = time(NULL);
      char* string3;
      string3 = ctime(&current_time3);

      //When producer produces a request, print the following line
      printf("Producer: Producing request %i, length %i seconds at time %s\n", tmp->ID,tmp->length,string3);
      count++;
      r_count++;
      //Producer will sleep for one second after producing a request
      printf("Producer: sleeping for %is\n\n",sleep_length);
      sleep(1);

      //release the buffer
      sem_post(&mutex);
      sem_post(&full);
  }
}

//This method is used to create a list of consumer objects and initialise them
//@parameter n, which is the number of consumers
//@parameter input[], is the list if threads to be created
void Consumer(int n, pthread_t input[]){
  for(int i=0; i<n; i++){
    pthread_create(&input[i], NULL, Consumer_funciton, (void*)(intptr_t)i);
  }
  for(int i=0; i<n; i++){
    pthread_join(input[i], NULL);
  }

}

//This method is used to create a producer object,
//producer will sleep for 1 second after producing one request
//@parameter input[], which is a list a p_threads
void Producer(pthread_t input[],int sleep_length){
  pthread_create(&input[0], NULL, Producer_function,(void*)(intptr_t)sleep_length);
}

//free the request queue
void Free(){
  for(int i=0; i<MAX_QEQUEST;i++){
    free(REQUEST_ARR[i]);
  }
}

//Main function
int main(int argc, char const *argv[]) {
  //define semaphores
  sem_init(&mutex,0,1);
  sem_init(&empty,0,MAX_QEQUEST);
  sem_init(&full,0,0);

  //initialize the request queue
  for(int i=0; i<MAX_QEQUEST;i++){
    Request* r = (Request*)malloc(sizeof(Request));
    r->ID = -1;
    r->length = -1;
    REQUEST_ARR[i] = r;
  }

  //initialize the producer, the second input is the sleep length
  pthread_t a[1];
  Producer(a,1);
  //initialize the consumers, the first input is the number of consumers
  pthread_t b[5];
  Consumer(5,b);

  Free();

  return 0;
}
