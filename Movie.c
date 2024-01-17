/*****************************************************
 * @file   Movie.c                                   *
 * @author Paterakis Giorgos <geopat@csd.uoc.gr>     *
 *                                                   *
 * @brief Implementation for Movie.h 				 *
 * Project: Winter 2023						         *
 *****************************************************/ 

#include "Movie.h"

/*_________Hashing__________*/

int hashtable_s; /* constant m */
int max_u;

int p_constant;
int a_constant;
int b_constant;

user_t **user_hashtable_p;	/* The users hashtable. This is an array of chains (pinakas katakermatismoy xrhstwn)*/

/*_____New Rlkeases Tree____*/

new_movie_t *new_releases = NULL;     /* New releases simply-linked binary tree*/

/*__________________________*/

movieCategory_t *categoryArray[6];  /* The categories array (pinakas kathgoriwn)*/

/*__________________________*/

movie_t* sentinel;

int prime_selection(int max_user_id){

	int p;

	for(int i = 0 ; i < 170 ; i++){
		if(primes_g[i] > max_user_id){
			p = primes_g[i];
			return p;
		}
	}
}

int is_unique(int user_id){

	int i = 0;

	for(i = 0 ; i < hashtable_s ; i++){

		user_t* current = user_hashtable_p[i];

		while(current != NULL){
			if(current->userID == user_id){
				printf("User with ID <%d> already exists.\n",user_id);
				return FAILURE; /* Is Not Unique */
			}
			current = current->next;
		}
	}

	return SUCCESS; /* Is Unique */
}

void init(int max_u, int p_c){

	srand(time(NULL));

	printf("- Prime selected: %d\n",p_c);

	a_constant = rand() % (p_c - 1) + 1;
	printf("- a constant selected (1 -> p - 1): %d\n",a_constant);

	b_constant = rand() % (p_c - 1); /* rand() selects a value from 0 to MAX_VALUE */
	printf("- b constant selected (0 -> p - 1 ): %d\n",b_constant);

	hashtable_s = (int) sqrt(max_u) + 2; /* Think of the chains and cells as a 2D array / box */

	user_hashtable_p = (user_t**) malloc(hashtable_s * sizeof(user_t*)); /* Allocate The Correct Memory For The Hash Table */
	
	int i = 0;

	for (i = 0 ; i < hashtable_s ; i++) {
		user_hashtable_p[i] = NULL; /* NULL-ify the array */
	}

	int k = 0;

	for(k = 0 ; k < 6 ; k++){
		categoryArray[k] = NULL;
	}

	/*_____________________________________*/

	movie_t* sentinel = (movie_t*)malloc(sizeof(movie_t));

	sentinel->movieID = -1;
	sentinel->lc = NULL;
	sentinel->rc = NULL;
	sentinel->sumScore = 0;
	sentinel->watchedCounter = 0;
	sentinel->year = 0;

	/*_____________________________________*/

	for (int i = 0; i < 6; i++) {
    	categoryArray[i] = (movieCategory_t*)malloc(sizeof(movieCategory_t)); /* Allocate memory for each root*/
    	categoryArray[i]->movie = NULL; /* Access and NULL-ify the movie pointers */
		categoryArray[i]->sentinel = (movie_t*)malloc(sizeof(movie_t));
		categoryArray[i]->sentinel = sentinel;
	}

	return;
}

int h(int user_id){
	int h_value;
	h_value = ((((a_constant * user_id) + b_constant) % p_constant) % hashtable_s);
	return h_value;
}

	int register_user(int userID){

		if(is_unique(userID) == FAILURE){
			return 0;
		}

		user_t* new_user = (user_t*)malloc(sizeof(user_t));

		
		new_user->history = NULL;
		new_user->userID = userID;

		/* User cell is empty, no chain exists there yet */
		if(!user_hashtable_p[h(userID)]){
			user_hashtable_p[h(userID)] = new_user;
			new_user->next = NULL;
		}else{
			new_user->next = user_hashtable_p[h(new_user->userID)];
			user_hashtable_p[h(new_user->userID)] = new_user;
		}

		int i = 0;

		for(i = 0 ; i < hashtable_s ; i++){

			printf("Chain <%d> of Users:\n",i);

			user_t* current = user_hashtable_p[i];

			while(current != NULL){
				printf("	<%d>\n",current->userID);
				current = current->next;
			}
		}
		printf("DONE\n");

		return 1;
	}
 
 int unregister_user(int userID){

	user_t* prev = NULL;

	user_t* current = user_hashtable_p[h(userID)];
	
	if(current == NULL){
		printf("Empty <%d> Chain\n",h(userID));
		return 0;
	}

	if(current->userID == userID){
		/* If the node to be removed is the first one */
		user_hashtable_p[h(userID)] = user_hashtable_p[h(userID)]->next; /* Move the "header" to the next node */
	}else{
		while(current != NULL){
			if(current->userID == userID){
				prev->next = current->next; /* Link */
				current->next = NULL; /* Delink */
				free(current); /* Free allocated memory */
			}
			prev = current;
			current = current->next;
		}
	}

	int i = 0;

	for(i = 0 ; i < hashtable_s ; i++){

		printf("Chain <%d> of Users:\n",i);

		user_t* current = user_hashtable_p[i];

		while(current != NULL){
			printf("	<%d>\n",current->userID);
			current = current->next;
		}
	}
	printf("DONE\n");
 }
 
 int add_new_movie(int movieID, int category, int year){

	new_movie_t* new_movie = (new_movie_t*)malloc(sizeof(new_movie_t));

	new_movie->movieID = movieID;
	new_movie->category = category;
	new_movie->year = year;
	new_movie->sumScore = 0;
	new_movie->watchedCounter = 0;
	new_movie->lc = NULL;
	new_movie->rc = NULL;

	new_movie_t* current = new_releases; /* Perform Binary Search */
	new_movie_t* prev = NULL; /* To mark the parent of the node we want to insert */

	if(new_releases == NULL){ /* If empty leave it here */
		new_releases = new_movie; /* Assign node to root */
	}else{

		current = new_releases; /* Assign to the previosuly created root */

		while(current != NULL){
			prev = current;
			if(current->movieID > movieID){
				current = current->lc;
			}else{
				current = current->rc;
			}
		}

		if(prev->movieID > new_movie->movieID){
			prev->lc = new_movie;
		}else{
			prev->rc = new_movie;
		}
	}

	printf("New releases tree:\n\n	");
	printf("<new releases>: ");

	new_movie_t* print = new_releases;

	in_order_print(print);
	printf("\n\n");

	printf("DONE\n");

	return 1;
 }
 
 /**
 * @brief Distribute the movies from new release binary tree to the array of categories.
 *
 * @return 0 on success
 *         1 on failure
 */
 int distribute_movies(void){
	/* Search BST, Find how many movies of each category we have */
	/* Allocate memory for dynamic array */
	/* pass all elements, sorted in each category array, using in-order traversal */

	count_movies();
	category_array_memory_allocation();
	category_array_copy();

	/* All array mapped to trees */

	array_to_tree(__HORROR_array, 0,HORROR_s - 1, &categoryArray[HORROR]->movie, HORROR);
	array_to_tree(__SCIFI_array, 0,SCIFI_s - 1, &categoryArray[SCIFI]->movie, SCIFI);
	array_to_tree(__DRAMA_array, 0,DRAMA_s - 1, &categoryArray[DRAMA]->movie, DRAMA);
	array_to_tree(__ROMANCE_array, 0,ROMANCE_s - 1, &categoryArray[ROMANCE]->movie, ROMANCE);
	array_to_tree(__DOCUMENTARY_array, 0,DOCUMENTARY_s - 1, &categoryArray[DOCUMENTARY]->movie, DOCUMENTARY);
	array_to_tree(__COMEDY_array, 0,COMEDY_s - 1, &categoryArray[COMEDY]->movie, COMEDY);

	printf("Movie category array:\n\n");

	int i = 0;

	for(i = 0 ; i < 6 ; i++){

		movie_t* current = categoryArray[i]->movie;

		printf("	<%s>: ",category_names[i]);

		category_in_order(current);
		printf("\n");
	}

	printf("DONE\n");

	return 1;
 }
 
 /**
 * @brief User rates the movie with identification movieID with score
 *
 * @param userID The identifier of the user
 * @param category The Category of the movie
 * @param movieID The identifier of the movie
 * @param score The score that user rates the movie with id movieID
 *
 * @return 1 on success
 *         0 on failure
 */
 int watch_movie(int userID,int category, int movieID, int score){

	/**
	 * @note We first find the user and the movie, we access the watch history of the user, copy the movie there, change the score to the specified amount.
	 * 
	 * @warning In random sequences of numbers, the program segments.
	*/

	add_user_movie_to_history(userID,movieID,category,score);

	user_t* current = user_hashtable_p[h(userID)]; /* Go to the correct cell */

    while(current != NULL){
        if(current->userID == userID){
            break;            
        }
		current = current->next;
    }

	printf("History tree of user <%d>:\n\n",current->userID);

    leaf_in_order(current->history);

	printf("DONE\n");
	return 1;
 }
 
/**
 * @brief Identify the best rating score movie and cluster all the movies of a category.
 *
 * @param userID The identifier of the user
 * @param score The minimum score of a movie
 *
 * @return 1 on success
 *         0 on failure
 */
 int filter_movies(int userID, int score){
	
	/**************************************************/
	/*note: Find how many nodes of avg > score exist  */
	/* 		pass them onto a dynamicly allocated array*/
	/* 		heap sort it and print it                 */
	/**************************************************/

	/**
	 * @note Prints all movie data that have an avg > score (change the visit to copy the data)
	 * 		 count, allocate, pass onto array, then print
	*/



	int size = filter_category(score);

	/* Allocating memory */

	movie_t** __FILTERED_array = (movie_t**)malloc(size * sizeof(movie_t*));

	filter_category_copy(__FILTERED_array,score); /* Copies the nodes to the array */

	heap_sort(__FILTERED_array,filter_s);

	int i = 0;

	for(i = 0 ; i < filter_s; i++){
		double avg =(double)__FILTERED_array[i]->sumScore / __FILTERED_array[i]->watchedCounter;

		printf("  <%d> <AVG: %.2f>",__FILTERED_array[i]->movieID,avg);
	}

	printf("\nDONE\n");

	/* Value reset */
	filter_count = 0;
	filter_s = 0;

	return 1;
 }
 
/**
 * @brief Find movies from categories withn median_score >= score t
 *
 * @param userID The identifier of the user
 * @param category Array with the categories to search.
 * @param score The minimum score the movies we want to have
 *
 * @return 1 on success
 *         0 on failure
 */
 int user_stats(int userID){

	score_sum = 0; /* Defaultvalues */
	node_sum = 1; /* For the leftmost leaf */

	user_t* current = user_hashtable_p[h(userID)];

	while(current != NULL){
		if(current->userID == userID){
			break;
		}
		current = current->next;
	}

	/* Pointer set correctly */

	userMovie_t* watch_history = current->history;

	while(watch_history != NULL && watch_history->lc != NULL){
        watch_history = watch_history->lc; /* Go to the leftmost node */
    }

	score_sum += watch_history->score;

	userMovie_t* trace = find_next_leaf(watch_history);

	while(trace != NULL){
		trace = find_next_leaf(trace);
	}

	printf("<%d> <%d/%d> = <%.2f>\n",userID,score_sum,node_sum,(double) score_sum / node_sum );

	return 1;
 }
 
/**
 * @brief Search for a movie with identification movieID in a specific category.
 *
 * @param movieID The identifier of the movie
 * @param category The category of the movie
 *
 * @return 1 on success
 *         0 on failure
 */
 int search_movie(int movieID, int category){
	
	movie_t* current = categoryArray[category]->movie;

	while(current != sentinel){
		if(current->movieID > movieID){
			current = current->lc;
		}else if(current->movieID < movieID){
			current = current->rc;
		}else if( current->movieID == movieID){
			printf("Movie <%d> found\n",current->movieID);
			printf("DONE\n");
			return 1;
		}else if(current == sentinel){
			printf("Movie Not Found\n");
			return 0;
		}
	}

	return 0;
 }
 
 /**
 * @brief Prints the movies in movies categories array.
 * @return 1 on success
 *         0 on failure
 */
 int print_movies(void){
	printf("Movie category array:\n\n");

	int i = 0;

	for(i = 0 ; i < 6 ; i++){

		movie_t* current = categoryArray[i]->movie;

		printf("	<%s>: ",category_names[i]);

		category_in_order(current);
		printf("\n");
	}

	printf("DONE\n");
	return 1;
 }
 
/**
 * @brief Prints the users hashtable.
 * @return 1 on success
 *         0 on failure
 */
int print_users(void){

	int i = 0;

	for(i = 0 ; i < hashtable_s ; i++){

		printf("Chain <%d> of Users:\n",i);

		user_t* current = user_hashtable_p[i];

		while(current != NULL){
			printf("	<%d>\n",current->userID);
			current = current->next;
		}
	}
	printf("DONE\n");

	return 1;
}
