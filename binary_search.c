#include "Movie.h"

movie_t* bin_search(movie_t* root, int id){
    movie_t* current = root; /* Assign ptr to root */

    while(current->movieID != id){
        if(current->movieID > id){
            current = current->lc;
        }else{
            current = current->rc;
        }
    }
    return current;
}
