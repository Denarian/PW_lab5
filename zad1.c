#include<stdio.h>
#include<stdlib.h> 
#include<pthread.h>


void * merge_sort(void *);
void * merge(void *);


void print_tab(int tab[], int n);

typedef struct 
{
    int l;
    int r;
    int * tab;
}merge_sort_io;

typedef struct 
{
    int l;
    int r;
    int m;
    int * tab;
}merge_io;


int main()
{
    int tab[] = {5,10,31,55,44,1,9,4,66,3,5};
    int tab_size = sizeof(tab)/sizeof(tab[0]);
    merge_sort_io io = {0, tab_size - 1,tab};

    print_tab(tab, tab_size);
    merge_sort(&io);
    print_tab(tab, tab_size);
 

return 0;
}
void * merge_sort(void * arg)
{
    merge_sort_io io = *(merge_sort_io *)arg;
    if(io.l < io.r)
    {
        int m = io.l+(io.r-io.l)/2;  
        merge_sort_io io_1 = io;
        merge_sort_io io_2 = io;
        io_1.r = m;
        io_2.l = m+1;

        pthread_t tid[2];
        pthread_create(&tid[0], NULL, merge_sort, &io_1);
        pthread_create(&tid[1], NULL, merge_sort, &io_2);
        
        pthread_join(tid[0],NULL);
        pthread_join(tid[1],NULL);    

        merge_io io_m = {io.l,io.r,m,io.tab};
        
        merge(&io_m);
    }

    return NULL;
}

void * merge(void * arg)
{
    merge_io io = *(merge_io *)arg;
    int n1 = io.m - io.l + 1;
    int n2 = io.r - io.m;

    int L[n1],R[n2];

    for(int i = 0; i < n1; i++)
        L[i] = io.tab[io.l + i]; 
    for(int i = 0; i < n2; i++)
        R[i] = io.tab[io.m + 1 + i]; 
        
    int i = 0, j = 0, k = io.l;
    for(; i < n1 && j < n2; k++)
    {
        if(L[i] <= R[j])
        {
            io.tab[k] = L[i];
            i++;
        }
        else
        {
            io.tab[k] = R[j];
            j++;
        }
    }
    for(;i < n1; i++, k++)
        io.tab[k]=L[i];

    for(;j < n2; j++, k++)
        io.tab[k]=R[j];

    return NULL;
}


void print_tab(int tab[], int n)
{
    for(int i = 0; i < n; i++)
    {
        printf("%d | ", tab[i]);
    }
    printf("\n");
}