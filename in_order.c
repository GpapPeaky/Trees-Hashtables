#include "Movie.h"

int category_count[6] = {0,0,0,0,0,0};

const char* category_names[6] = {
    "HORROR",
	"SCIFI",
	"DRAMA",
	"ROMANCE",
	"DOCUMENTARY",
	"COMEDY"
};

void leaf_in_order(userMovie_t* root){
    if(root == NULL) return;

    leaf_in_order(root->lc);
    leaf_visit(root);
    leaf_in_order(root->rc);
}

void leaf_visit(userMovie_t* leaf){
   if(leaf->lc == NULL && leaf->rc == NULL){
        printf("    Leaf: <%d>, score: <%d>\n",leaf->movieID,leaf->score);
    }
}

void category_in_order(movie_t* root){
    if(root == NULL) return;

    category_in_order(root->lc);
    category_visit(root);
    category_in_order(root->rc);
}

void category_visit(movie_t* node){
    printf("<%d>,",node->movieID);
}

void in_order_copy(new_movie_t* node, Category_t category){

    if(node == NULL) return;

    in_order_copy(node->lc,category);
    visit_copy(node,category);
    in_order_copy(node->rc,category);
}

/*____________Auxillary indexes______________*/

int HORROR_idx = 0;
int SCIFI_idx = 0;
int DRAMA_idx = 0;
int ROMANCE_idx = 0;
int DOCUMENTARY_idx = 0;
int COMEDY_idx = 0;

/*___________________________________________*/

int HORROR_s = 0;
int SCIFI_s = 0;
int DRAMA_s = 0;
int ROMANCE_s = 0;
int DOCUMENTARY_s = 0;
int COMEDY_s = 0;

/*___________________________________________*/

void visit_copy(new_movie_t* node, Category_t category){

        /* WHILE PARSING DATA, PASS THEM ONTO THE ARRAY AS [movie_t*] TYPES */

    movie_t* new_node = (movie_t*)malloc(sizeof(movie_t));
    new_node->movieID = node->movieID;
    new_node->sumScore = node->sumScore;
    new_node->watchedCounter = node->watchedCounter;
    new_node->year = node->year;

    if(node->category == category){
        switch (node->category){
        case 0:
            __HORROR_array[HORROR_idx] = new_node;
            HORROR_s = HORROR_idx + 1;
            HORROR_idx++;
            break;
        case 1:
            __SCIFI_array[SCIFI_idx] = new_node;
            SCIFI_s = SCIFI_idx + 1;
            SCIFI_idx++;
            break;
        case 2:
            __DRAMA_array[DRAMA_idx] = new_node;
            DRAMA_s = DRAMA_idx + 1;
            DRAMA_idx++;
            break;
        case 3:
            __ROMANCE_array[ROMANCE_idx] = new_node;
            ROMANCE_s = ROMANCE_idx + 1;
            ROMANCE_idx++;
            break;
        case 4:
            __DOCUMENTARY_array[DOCUMENTARY_idx] = new_node;
            DOCUMENTARY_s = DOCUMENTARY_idx + 1;
            DOCUMENTARY_idx++;
            break;
        case 5:
            __COMEDY_array[COMEDY_idx] = new_node;
            COMEDY_s = COMEDY_idx + 1;
            COMEDY_idx++;
            break;
        default:
            break;
        }
    }
}

int visit_count(new_movie_t* node, Category_t category){

    if(node->category == category){
        category_count[category]++;
    }

    return category_count[category];
}

void in_order_count(new_movie_t* root, Category_t category){

    if(root == NULL) return;

    in_order_count(root->lc, category);
    visit_count(root, category);
    in_order_count(root->rc, category);
}

void visit_print(new_movie_t* node){
    printf("<%d>, ",node->movieID);
}

void in_order_print(new_movie_t* root){
    
    if(root == NULL) return;

    in_order_print(root->lc);
    visit_print(root);
    in_order_print(root->rc);
}
