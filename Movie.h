/*****************************************************
 * @file   Movie.h                                   *
 * @author Paterakis Giorgos <geopat@csd.uoc.gr>     *
 *                                                   *
 * @brief Header File for Data Structures (CS240b)   *
 * Project: Winter 2023						         *
 *****************************************************/

/*___AUXILARY DEFINITIONS___*/

#define FAILURE -1
#define SUCCESS 0

#ifndef MOVIE_FILE
#define MOVIE_FILE

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>
#include <assert.h>
#include <time.h>
#include <math.h> /* for sqrt(), user -lm at the end of the gcc compile command */

/*You can use this enum or you can choose to represent each category as an Integer. Its the same*/
typedef enum {
	HORROR,
	SCIFI,
	DRAMA,
	ROMANCE,
	DOCUMENTARY,
	COMEDY
} Category_t;

/**
* Structure defining a node of a new_realeases binary tree (dendro newvn kykloforiwn)
*/
typedef struct new_movie{
	int category;				/* The category of the movie*/
	int movieID; 				/* The movie identifier*/
	int year;					/* The year movie released*/
	int watchedCounter;	 		/* How many users rate the movie*/
	int sumScore;				/* The sum of the ratings of the movie*/
	struct new_movie *lc;	/* Pointer to the node's left child*/
	struct new_movie *rc;	/* Pointer to the node's right child*/
}new_movie_t;


/**
* Structure defining a node of movie binary tree (dendro tainiwn kathgorias)
*/
typedef struct movie{
	int movieID; 				/* The movie identifier*/
	int year;					/* The year movie released*/
	int watchedCounter;	 		/* How many users rate the movie*/
	int sumScore;				/* The sum of the ratings of the movie*/
	struct movie *lc;	/* Pointer to the node's left child*/
	struct movie *rc;	/* Pointer to the node's right child*/
}movie_t;

/**
* Structure defining movie_category
*/
typedef struct movie_category{
	movie_t *movie;
	movie_t *sentinel;
}movieCategory_t;

/**
* Structure defining a node of user_movie for history doubly linked binary 
* tree (dentro istorikou) 
*/
typedef struct user_movie{
	int movieID; 					/* The movie identifier*/
	int category;					/* The category of the movie*/
	int score;						/* The score of the movie*/
	struct user_movie *parent;		/* Pointer to the node's parent*/
	struct user_movie *lc;	/* Pointer to the node's left child*/
	struct user_movie *rc;	/* Pointer to the node's right child*/
}userMovie_t;

/**
* Structure defining a node of users' hashtable (pinakas katakermatismou
* xrhstwn)
*/
typedef struct user {
	int userID; 			/* The user's identifier*/
	userMovie_t *history;	/* A doubly linked binary tree with the movies watched by the user*/
	struct user *next;		/* Pointer to the next node of the chain*/	
}user_t;

extern movieCategory_t *categoryArray[6];  /* The categories array (pinakas kathgoriwn)*/
extern new_movie_t *new_releases;    		   /* New releases simply-linked binary tree*/
extern user_t **user_hashtable_p;		   /* The users hashtable. This is an array of chains (pinakas katakermatismoy xrhstwn)*/
extern int hashtable_size;				   /* The size of the users hashtable, parsed from the command line (>0)*/
extern int max_users;					   /* The maximum number of registrations (users)*/			
extern int max_id;   			   /* The maximum account ID */
extern int primes_g[170];

/*_______________________________________________________________________________________________*/

										/* Hashtable */

extern int a_constant; /* For the generation of a random hash function (1 ... p - 1) */ 
extern int b_constant; /* For the generation of a random hash function (0 ... p - 1) */ 
extern int p_constant; /* For the generation of a random hash function */

/*_______________________________________________________________________________________________*/

								/* Distribute extern variables */

extern const char* category_names[6];
extern int category_count[6]; /* Each cell has the number of movies of the corresponding category exist */

extern movie_t* sentinel;

/* Categorised movie arrays type [movie_t*] */

extern movie_t** __HORROR_array;	
extern movie_t** __SCIFI_array;
extern movie_t** __DRAMA_array;
extern movie_t** __ROMANCE_array;
extern movie_t** __DOCUMENTARY_array;
extern movie_t** __COMEDY_array;

/* Movie category indexes (could have used an array, too much of a hussle) */

extern int HORROR_idx;
extern int SCIFI_idx;
extern int DRAMA_idx;
extern int ROMANCE_idx;
extern int DOCUMENTARY_idx;
extern int COMEDY_idx;

/* Category array size */

extern int HORROR_s;
extern int SCIFI_s;
extern int DRAMA_s;
extern int ROMANCE_s;
extern int DOCUMENTARY_s;
extern int COMEDY_s;

/**
 * @note Category array nodes are all movie_t* type, no pre-BST isnertion conversion required
*/

/*___________________________________________SCORE_______________________________________________*/

userMovie_t* find_next_leaf(userMovie_t* root);

extern int score_sum;
extern int node_sum;

/**
 * @brief Finds the next leaf of in the leaf-oriented BST (user history)
 * 
 * @param node Node to find the next leaf
 * 
 * @returns The next leaf of the node
*/
userMovie_t* find_next_leaf(userMovie_t* node);
/*_______________________________________________________________________________________________*/

extern int filter_count;
extern int filter_s;

/*__________________________________________HEAP_________________________________________________*/

/**
 * @brief Swaps 2 nodes with eachother
 * 
 * @param a Node a to swap
 * @param b Node b to swap
*/
void swap(movie_t** a , movie_t** b);

/**
 * @brief Heapifies an array
 * 
 * @param table Array to heapify
 * @param i Start of the array section to heapify
 * @param j End of the array section to heapify
 * @param size Table size
*/
void heapify(movie_t** table,int size, int i, int j);

/**
 * @brief Initialises the heap
 * 
 * @param table Table to convert into a heap
 * @param size Table size
*/
void init_heap(movie_t** table, int size);

/**
 * @brief Heap sort
 * 
 * @param table Array to sort
*/
void heap_sort(movie_t** table, int size);

/*_________________________________________Copying Nodes_________________________________________*/

/**
 * @brief Filters All categories and copies he correct notes
 * 
 * @param score Node score
 * @param table Where to copy the nodes
*/
void filter_category_copy(movie_t** table, int score);

/**
 * @brief Special in_order to copy the nodes of the requested average exist
 * 
 * @param table Where to copy the nodes
 * @param root Node to visit
 * @param score Score average
*/
void filter_in_order_copy(movie_t** table, movie_t* root, int score);

/**
 * @brief Special visit to count how many nodes of the requested average exist
 * 
 * @param node Node to visit
 * @param score Score average
 * @param table Where to copy the nodes
*/
void filter_visit_copy(movie_t** table, movie_t* node, int score);

/*_______________________________________________________________________________________________*/

/**
 * @brief Filters All categories to check for valid movies
 * 
 * @param score Node score
 * 
 * @returns the count of valid movies
*/
int filter_category(int score);

/**
 * @brief Special in_order to count how many nodes of the requested average exist
 * 
 * @param node Node to visit
 * @param score Score average
*/
void filter_in_order(movie_t* root, int score);

/**
 * @brief Special visit to count how many nodes of the requested average exist
 * 
 * @param node Node to visit
 * @param score Score average
*/
void filter_visit(movie_t* node, int score);

/*_______________________________________________________________________________________________*/

/**
 * @brief Prints the leafs of a leaf-oriented BST
 * 
 * @param root The root of the tree
*/
void leaf_in_order(userMovie_t* root);

/**
 * @brief Prints the leaf's id
 * 
 * @param leaf The leaf we are visiting
*/
void leaf_visit(userMovie_t* leaf);

/**
 * @brief Add the movie to the double linked BST
 * 
 * @param userID User who watched the movie
 * @param movieID Movie to be watched 
 * @param category Category of the movie 
 * @param score User score
*/
void add_user_movie_to_history(int userID, int movieID, Category_t category, int score);

/**
 * @brief Finds the correct movie
 * 
 * @param movieID Movie id
 * @param category Category on which we search
 * 
 * @returns 1 On failure
 * @returns 0 On success
*/
int find_movie_w(int movieID, Category_t category);

/**
 * @brief Finds the correct user
 * 
 * @param userID User id
 * 
 * @returns 1 On failure
 * @returns 0 On success
*/
int find_user_w(int userID);

/*_______________________________________________________________________________________________*/

/**
 * @brief Special in order, for the category tree prints
 * 
 * @param root Root to the category tree
*/
void category_in_order(movie_t* root);

/**
 * @brief Special visit for the category tree prints
 * 
 * @param node Node to be printed
*/
void category_visit(movie_t* node);

/**
 * @brief Maps the array to a tree, with height of O(log(n))
 * 
 * @param array Array from which we map the elements
 * @param start Start index
 * @param end Ending index
 * @param root Category array/root of specfied tree
 * @param category Category root/array we want to map
*/
void array_to_tree(movie_t** array, int start, int end, movie_t** root, Category_t category);

/**
 * @brief Prints the nodes of each category array 
*/
void print_categories_arrays(void);

/**
 * @brief Copies all categorised movies to a category array
*/
void category_array_copy(void);

/**
 * @brief In-order traversal of a bst root to copy the movies to the specific category
 * 
 * @param root BST root
 * @param category Movie category 
*/
void in_order_copy(new_movie_t* root, Category_t category);

/**
 * @brief Copies the specific category movies, onto the relative category array
 * 
 * @param node Node we currently visiting
 * @param category Category type
 * 
*/
void visit_copy(new_movie_t* node, Category_t category);

/**
 * @brief Allocates the correct amount of memory blocks to map the new releases tree to an array
*/
void category_array_memory_allocation(void);

/**
 * @brief Counts the movies for each category
*/
void count_movies(void);

/**
 * @brief Performs a binary search (of type new_movie) to find a specific key
 * 
 * @param id Key id to be found
 * @param root BST root
 * 
 * @returns The node in which the id is
*/
movie_t* bin_search(movie_t* root,int id);

/**
 * @brief In-order traversal of a bst root to count up how many movies of a specific category exist
 * 
 * @param root BST root
 * @param category Movie category 
*/
void in_order_count(new_movie_t* root, Category_t category);

/**
 * @brief Counts how many nodes of a specific category exist in th new releases tree
 * 
 * @param node Node we currently visiting
 * @param category Category type
 * 
 * @returns The movie count
*/
int visit_count(new_movie_t* node, Category_t category);

/*_______________________________________________________________________________________________*/

/**
 * @brief Performs a print of the data, in a tree node
 * 
 * @param node The tree node to be printed
*/
void visit_print(new_movie_t* node);

/**
 * @brief In-order traversal of a BST 
 * 
 * @param root The root of the binary search tree
*/
void in_order_print(new_movie_t* root);

/*_______________________________________________________________________________________________*/

/**
 * @brief Selects the next bigger prime of the max_user_id
 * 
 * @param max_user_id Max id of the users
 * 
 * @returns The next bigger prime
*/
int prime_selection(int max_user_id);

/**
 * @brief Checks if the user is unique
 * 
 * @param user_id User ID
 * 
 * @returns 0 Is unique
 * 			1 Not unique
*/
int is_unique(int user_id);

/**
 * Initialises the random numbers to be chosen for the has table
 * 
 * @param max_users Max User Count
 * @param p_constant Prime Product From The Maximum User ID input
*/
void init(int max_users, int p_constant);

/** 
 * int h( int user_id ){
 *		return (((( a * user_id ) + b ) % p) % m );
 *  } 
 *
 *	Generates a "hash - cell" to choose where in the table, the user will be put, based on his id
 *
 *	O(n) -> O(1)
 *
 * @param user_id User id
 * 
 * @return The product cell of the user hash table
*/
int h(int user_id);

/**
 * @brief Creates a new user.
 * Creates a new user with userID as its identification.
 *
 * @param userID The new user's identification
 *
 * @return 1 on success
 *         0 on failure
 */
 int register_user(int userID);
 
/**
 * @brief Deletes a user.
 * Deletes a user with userID from the system, along with users' history tree.
 *
 * @param userID The new user's identification
 *
 * @return 1 on success
 *         0 on failure
 */
 int unregister_user(int userID);
 
 /**
 * @brief Add new movie to new release binary tree.
 * Create a node movie and insert it in 'new release' binary tree.
 *
 * @param movieID The new movie identifier
 * @param category The category of the movie
 * @param year The year movie released
 *
 * @return 1 on success
 *         0 on failure
 */
 int add_new_movie(int movieID, int category, int year);
 
 /**
 * @brief Distribute the movies from new release binary tree to the array of categories.
 *
 * @return 1 on success
 *         0 on failure
 */
 int distribute_movies(void);
 
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
 int watch_movie(int userID, int category,int movieID, int score);
 
/**
 * @brief Identify the best rating score movie and cluster all the movies of a category.
 *
 * @param userID The identifier of the user
 * @param score The minimum score of a movie
 *
 * @return 1 on success
 *         0 on failure
 */
 int filter_movies(int userID, int score);
 
/**
 * @brief Find the median score that user rates movies.
 *
 * @param userID The identifier of the user
 *
 * @return 1 on success
 *         0 on failure
 */
 int user_stats(int userID);
 
/**
 * @brief Search for a movie with identification movieID in a specific category.
 *
 * @param movieID The identifier of the movie
 * @param category The category of the movie
 *
 * @return 1 on success
 *         0 on failure
 */
 int search_movie(int movieID, int category);
 
 /**
 * @brief Prints the movies in movies categories array.
 * @return 1 on success
 *         0 on failure
 */
 int print_movies(void);
 
  /**
 * @brief Prints the users hashtable.
 * @return 1 on success
 *         0 on failure
 */
 int print_users(void);

 /**
 * @brief Debug message
 */
 void ___DEBUG(void);

/**
 * @brief Cleaner Prints
*/
 void ___NEWSCOPE(void);
  
 #endif
