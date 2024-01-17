#include "Movie.h"

movie_t** __HORROR_array = NULL;
movie_t** __SCIFI_array = NULL;
movie_t** __DRAMA_array = NULL;
movie_t** __ROMANCE_array = NULL;
movie_t** __DOCUMENTARY_array = NULL;
movie_t** __COMEDY_array = NULL;

void array_to_tree(movie_t** array, int start, int end, movie_t** root, Category_t category){
	/* The elements of the array are already type movie_t*, so we might be able to just move them, instead of copying their data */

	if(start > end){

		*root = sentinel;
		return;
	}

	int mid_idx = (start + end) / 2;

	if(*root == NULL){
		*root = array[mid_idx]; /* If empty, the first one becomes the root */
	}

	array_to_tree(array, start, mid_idx -1, &(*root)->lc, category); /* Moving left */
	array_to_tree(array, mid_idx + 1, end, &(*root)->rc, category); /* Moving right */
}

void count_movies(void){
	int i = 0;

	for(i = 0 ; i < 6 ; i++){
		in_order_count(new_releases,i);
	}
}

void category_array_memory_allocation(void){
	
    __HORROR_array = (movie_t**) malloc(category_count[HORROR] * sizeof(movie_t*));

    __SCIFI_array = (movie_t**) malloc(category_count[SCIFI] * sizeof(movie_t*));

    __DRAMA_array = (movie_t**) malloc(category_count[DRAMA] * sizeof(movie_t*));

    __ROMANCE_array = (movie_t**) malloc(category_count[ROMANCE] * sizeof(movie_t*));

    __DOCUMENTARY_array = (movie_t**) malloc(category_count[DOCUMENTARY] * sizeof(movie_t*));

    __COMEDY_array = (movie_t**) malloc(category_count[COMEDY] * sizeof(movie_t*));
}

void category_array_copy(void){
    int i = 0 ;

    for( i = 0 ; i < 6; i++){
        in_order_copy(new_releases,i);
    }
}

void print_categories_arrays(void){
    
	int i = 0;
	int o = 0;
	int p = 0;
	int j = 0;
	int k = 0;
	int l = 0;

	printf("%s Category array:\n",category_names[HORROR]);
	for(i = 0; i < category_count[HORROR] ; i++){
		printf("--- <%d>\n",__HORROR_array[i]->movieID);
	}

	printf("%s Category array:\n",category_names[SCIFI]);
	for(o = 0; o < category_count[SCIFI] ; o++){
		printf("--- <%d>\n",__SCIFI_array[o]->movieID);
	}

	printf("%s Category array:\n",category_names[DRAMA]);
	for(p = 0; p < category_count[DRAMA] ; p++){
		printf("--- <%d>\n",__DRAMA_array[p]->movieID);
	}

	printf("%s Category array:\n",category_names[ROMANCE]);
	for(j = 0; j < category_count[ROMANCE] ; j++){
		printf("--- <%d>\n",__ROMANCE_array[j]->movieID);
	}

	printf("%s Category array:\n",category_names[DOCUMENTARY]);
	for(k = 0; k < category_count[DOCUMENTARY] ; k++){
		printf("--- <%d>\n",__DOCUMENTARY_array[k]->movieID);
	}

	printf("%s Category array:\n",category_names[COMEDY]);
	for(l = 0; l < category_count[COMEDY] ; l++){
		printf("--- <%d>\n",__COMEDY_array[l]->movieID);
	}
}
