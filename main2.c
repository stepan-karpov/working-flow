#include <stdio.h>
#include <stdint.h>
#include <pthread.h>
#include <unistd.h>
#include <stdlib.h>
#include <math.h>


_Atomic int counter = 0;

typedef struct {
  int value;
  int executing;
} info;


void* routine(void* arg) {
  info* inf = (info*)arg;

  printf("I am here with counter = %d!\n", counter);
  counter += 1;
}

void call(pthread_t* thread, info* new_info) {
  
}

int main () {

  pthread_t thread;

  info* new_info = (info*) malloc(sizeof(info));
  new_info->executing = 0;

  pthread_create(&thread, NULL, routine, new_info);

  for (int i = 0; i < 4; ++i) {
    call(&thread, new_info);
  }

  pthread_join(thread, NULL);

  free(new_info);
  printf("Final answers is %d\n", counter);
}