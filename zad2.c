#include<stdio.h>
#include<stdlib.h> 
#include<pthread.h>
#include<semaphore.h>
#include<limits.h>

//#define SIZE 2147483
#define SIZE 100
typedef struct
{
    unsigned int prime;
    unsigned int size;
    unsigned int * tab;
}del_io;

void * deleter(void *);

sem_t lock;

int main()
{
    pthread_t tid;
    unsigned int tab[SIZE];

    sem_init(&lock, 0, 0);

    int primes_count = 0;

    for(unsigned int i = 0 ; i < SIZE; i++)
        tab[i] = i;
    
    unsigned int i = 2; //index startowy
    del_io io = {i, SIZE, tab};
    while(i < SIZE)
    {
        
        io.prime = tab[i];
       // fprintf(stderr , "%d\r", i);// wyświetlenie aktualnej liczby

        pthread_create(&tid, NULL, deleter, &io);

        sem_wait(&lock);// czekaj aby watek usuwajacy zdazyl cos usunac
       

        while(tab[++i] == 0);//znajdz pierwsza nie usunieta liczbe
        primes_count++;
    }
    pthread_join(tid,NULL); // czekaj az ostatni watek zakonczy dzialanie 

    sem_destroy(&lock);
    
    fprintf(stderr, "\n");
    fprintf(stderr,"%d\n",primes_count );// wyświetlenie liczby znalezionych liczb pierwszych.
    
    for(unsigned int i = 0 ; i < SIZE; i++)
        if(tab[i])//pomin 0 przy wyswietlaniu
            printf("%ld | ", tab[i]);
    printf("\n");

return 0;
}

void * deleter(void * arg_p) // watek usuwajacy wielokrotnosci
{
    del_io arg = *(del_io *)arg_p;
    del_io io = arg;
    int once = 1;
    for(unsigned int i = io.prime + 1; i < io.size ; i++)
    {
        if(io.tab[i] % io.prime == 0)// jesli znajdzie wielokrotnosc
            io.tab[i] = 0;// wstaw 0
        else if(once)
        {
            sem_post(&lock);//gdy nie usunie odblokuj watek głowny
            once = 0;
        }
    }
    if(once)// zabezpieczenie gdyby wątek nic nie usunal, aby nie zablokwac watku glownego
        sem_post(&lock); //gdy nie usunie odblokuj watek głowny
    return NULL;
}