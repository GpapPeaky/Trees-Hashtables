#include "Movie.h"

int filter_count = 0;
int filter_s = 0;


void filter_category_copy(movie_t** table, int score){

    filter_s = 0;

    int i = 0;

    for(i = 0 ; i < 6 ; i++){

        filter_in_order_copy(table,categoryArray[i]->movie,score);
    }
}

void filter_in_order_copy(movie_t** table, movie_t* root, int score){
    if(root == NULL) return;

    filter_in_order_copy(table, root->lc, score);
    filter_visit_copy(table, root,score);
    filter_in_order_copy(table, root->rc,score);
}

void filter_visit_copy(movie_t** table, movie_t* node, int score){

    double avg = 0.0;

    if(node->watchedCounter != 0){
        avg = (double)(node->sumScore / node->watchedCounter);
    }

    if(avg > score){
        table[filter_s] = node; /* copying data */
        filter_s++;
    }

    return;
}

/*_______________________________________________________________________________________________*/

int filter_category(int score){

    filter_count = 0;

    int i = 0;

    for(i = 0 ; i < 6 ; i++){

        filter_in_order(categoryArray[i]->movie,score);
    }

    return filter_count;
}

void filter_in_order(movie_t* root, int score){
    if(root == NULL) return;

    filter_in_order(root->lc, score);
    filter_visit(root,score);
    filter_in_order(root->rc,score);
}

void filter_visit(movie_t* node, int score){

    double avg = 0.0;

    if(node->watchedCounter != 0){
        avg = (double)(node->sumScore / node->watchedCounter);
    }

    if(avg > score){
        filter_count++;
    }

    return;
}
