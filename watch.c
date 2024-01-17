#include "Movie.h"

int score_sum = 0;
int node_sum = 0;

userMovie_t* find_next_leaf(userMovie_t* leaf) {

    if(leaf == NULL){
        return NULL;
    }

    int temp_id = leaf->movieID;

    /* Left child */

    if(leaf->parent->lc == leaf){
        leaf = leaf->parent;

        while(leaf->rc != NULL){
            leaf = leaf->rc;
        }

        node_sum++;
        score_sum += leaf->score;
        return leaf;
    }

    /* Right child */

    if(leaf->parent->rc == leaf){

        leaf = leaf->parent;

        while(leaf->movieID <= temp_id){
            if(leaf->parent == NULL){
                return NULL;
            }

            leaf = leaf->parent;
        }

        

        leaf = leaf->rc; /* Move one right */

        while(leaf->rc != NULL){
            leaf = leaf->lc;
        }

        node_sum++;
        score_sum += leaf->score;
        return leaf;
    }

    return NULL;
}

int find_user_w(int userID){
    
    user_t* find_user = user_hashtable_p[h(userID)]; /* Go to the correct cell */

    while(find_user != NULL){
        if(find_user->userID == userID){
            return 0;
        }
        find_user = find_user->next; 
    }

    printf("User <%d> Not Found\n",userID);
    return 1;
}

int find_movie_w(int movieID, Category_t category){
    movie_t* find_movie = bin_search(categoryArray[category]->movie, movieID);

    if(find_movie->movieID != movieID || find_movie == NULL){
        printf("Movie <%d> Not Found\n",movieID);
        return 1;
    }else{
        return 0;
    }
}

void add_user_movie_to_history(int userID, int movieID, Category_t category, int score){

    /**
     * @warning Sometimes, for some reason it segments with some values... it is almost completely random, I simply cannot
     *          find any logical sequence that the segmentations follow.
     * 
     * @note Whenever both users are at the same chain
    */

    movie_t* find_movie = NULL;

    find_movie = bin_search(categoryArray[category]->movie, movieID); /* Perform Binary Search */

    if (find_movie == NULL) {
        printf("  # Movie not found\n");
        return;
    }

    find_movie->watchedCounter++;
    find_movie->sumScore += score;

    userMovie_t* watched_movie = (userMovie_t*)malloc(sizeof(userMovie_t));

    watched_movie->movieID = find_movie->movieID;
    watched_movie->score = score;
    watched_movie->lc = NULL;
    watched_movie->rc = NULL;
    watched_movie->parent = NULL;

    /**
     * @note It is required for the correct position to be found before inserting the node
    */

    user_t* find_user = user_hashtable_p[h(userID)]; /* Go to the correct cell */

    while(find_user->userID != userID && find_user != NULL){
        printf("  # Checking user <%d>\n", find_user->userID);
        if(find_user->userID == userID){
            printf("  # Checking user <%d>\n", find_user->userID);
            break;
        }
        find_user = find_user->next;
    }

    if(find_user == NULL){
        printf("  # No user <%d> found\n",userID);
        return;
    }

    if(find_user->history == NULL){ /* root */
        find_user->history = watched_movie;
        find_user->history->parent = NULL;
        return;
    }else if(find_user->history != NULL){
        userMovie_t* current = find_user->history;
        userMovie_t* prev = NULL;

        while(current != NULL && current->movieID != movieID){
            prev = current;
            if(current->movieID > movieID){
                current = current->lc;
            }else if(current->movieID < movieID){
                current = current->rc;
            }
        }

        if(prev != NULL){

            userMovie_t* other_child = (userMovie_t*)malloc(sizeof(userMovie_t));

            other_child->category = prev->category;
            other_child->movieID = prev->movieID;
            other_child->score = prev->score;
            other_child->parent = prev;
            other_child->lc = NULL;
            other_child->rc = NULL;

            if(prev->movieID >= movieID){
                prev->lc = watched_movie;
                watched_movie->parent = prev;

                prev->rc = other_child;
            }else if(prev->movieID < movieID){
                prev->rc = watched_movie;
                watched_movie->parent = prev;

                prev->lc = other_child;
            }
        }
    }
    return;
}
