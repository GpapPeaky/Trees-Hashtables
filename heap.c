#include "Movie.h"

void swap(movie_t** a , movie_t** b){
    movie_t* tmp = *a;
    *a = *b;
    *b = tmp;

    return;
}

void heapify(movie_t** table, int size, int j, int i){

    int m = j;
    int p;

    while(((2 * m - size) >= i && ((double)table[2 * m - size]->sumScore / table[2 * m - size]->watchedCounter) < ((double)table[m]->sumScore / table[m]->watchedCounter)) ||
          ((2 * m - size - 1) >= i &&((double)table[2 * m - size - 1]->sumScore / table[2 * m - size - 1]->watchedCounter) < ((double)table[m]->sumScore / table[m]->watchedCounter))){

        if(2 * m - size >= i){
            if(((double)table[2 * m - size]->sumScore / table[2 * m - size]->watchedCounter) < ((double)table[2 * m - size - 1]->sumScore / table[2 * m - size - 1]->watchedCounter)){
                p = 2 * m - size;
            }else{
                p = 2 * m - size - 1;
            }
        }else{
            p = i;

            swap(&table[m], &table[p]);

            m = p;
        }
    } 
}

void init_heap(movie_t** table,int size){

    int i = 0;

    for(i = size / 2 -1  ; i >= 0 ; i--){
        heapify(table,size,0,i);
    }
}

void heap_sort(movie_t** table, int size){

    init_heap(table,size);

    int i = 0;

    for(i = 0 ; i < size - 1; i++){        
        swap(&table[i],&table[size - 1]);
        
        heapify(table, size, i + 1, size - 1);
    }
}
