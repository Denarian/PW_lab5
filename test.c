
#include  <stdio.h>
#include <semaphore.h>
#include <pthread.h>

sem_t lock;

void * test (void * a)
{
    sleep(5);
    sem_post(&lock);
    return NULL;
}

int main(void)
{
    sem_init(&lock, 0 ,1);
    pthread_t tid;
    pthread_create(&tid, NULL, test, NULL);
    printf("1\n");
    sem_wait(&lock);
    printf("2\n");
    sem_wait(&lock);
    printf("3\n");
    printf("%d %d\n", NULL, 0);
    return 0;
}