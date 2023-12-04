#include <stdio.h>
#include <stdint.h>
#include <pthread.h>
#include <unistd.h>

int counter = 0;
pthread_mutex_t mutex;

void* routine() {
  for (int i = 0; i < 1e8; ++i) {
    pthread_mutex_lock(&mutex);
    ++counter;
    pthread_mutex_unlock(&mutex);
  }
}

int main () {
  pthread_t threads[8];

  pthread_mutex_init(&mutex, NULL);

  for (int i = 0; i < 8; ++i) {
    pthread_create(&threads[i], NULL, routine, NULL);
    printf("Thread %d starts\n", i);
  }
  for (int i = 0; i < 8; ++i) {
    pthread_join(threads[i], NULL);
    printf("Thread %d ends\n", i);
  }
  
  pthread_mutex_destroy(&mutex);

  printf("%d", counter);
  return 0;
}