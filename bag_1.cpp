//Kyle Lopez
// 11 Jan. 2021
/*
As we discussed before, Julio Ruiz and I worked very closely together for this
assignment. This was due CPP being a new language for the both of us, a lost class,
on Wednesday of week 1, and our teacher being awesome and allowing us to do so.

This program creates a structure, representing a marble with 4 attributes:
    
    char color[MAX] : an array of characters representing each marbles color
    int size: an integer representing the size of the marble
    int num: an integer representing when the marble was created relative to 
        other marbles.
    struct marble *next: a pointer to the next marble in the chain of marbles, if
        it exists.
        
    The marble structure has 3 methods:
        create_marble: a function to create another marble and attach it to the 
            list of marbles. Returns nothing.
        remove_marble: picks a random number and removes that marble from the bag.
        display_marlbes: starts from the head and displays all marbles to the terminal
        */

#include <iostream>
#include <cstring>
#include <time.h>

using std:: cout;
using std:: endl;
using std:: exception;
using std:: rand;
const int MAX = 15;
int nodes = 0;

//Creates a structure representing a marble.
struct marble
{
    char color[MAX];
    int size;
    int num;
    struct marble *next;
};

//Marble methods
void create_marble(int color, int size);
int remove_marble();
int display_marbles();

//Create the head of the marble chain.
marble *head = NULL;

//A function demonstrating that the structure created works.
int main() {
    
    //Seed our random values where time = now.
    srand(time(NULL));
    
    //First we try to show off marbles that don't exist yet.
    display_marbles();
    
    //Then, we make a few marbles.

    //5 is chosen arbitrarly here as many marbles as wanted can be created.
    //Additionally 'i' could be retrieved from a user to let them choose how many to make.
    for (int i = 0; i < 5; i++){
        create_marble(i, i+1);
    };
    
    //After, we show off our marbles.
    display_marbles();

    //Then, we pull one out and give it to our friend at random.
    remove_marble();

    //Then, we show off the marble bag again. Proving we are missing a marble.
    display_marbles();

    /*
    Realizing that collecting marbles is stupid, we decide to ruin our mothers
    septic tank and flush them all down the drain.
    */
    marble *nxt_head = head;

    while (head != NULL){
        head = head->next;
        free(nxt_head);
        nxt_head = head;
    }

    /*
    Finally, we turn upend our now empty bag over our bed and wonder to ourselves:
    "What am I gonna do now?"
    */
    display_marbles();
    return 0;
};


void create_marble(int color, int size){

    /*
    Because the string type was a little tricky to pass around the first parameter
    that comes in is an int that corresponds to an index on this list to set the color
    up.

    Edit: Because the string type was still too tricky we abandoned strings and 
    made a 2-d char array. I think it's 2-d...yah, it's a 2-d matrix.
    */
    char colors[5][MAX] = {"Red", "Green", "Blue", "Yellow", "Purple"};

    //Reserve space for a marble and create it.
    marble* new_marble;
    new_marble = (marble*)malloc(sizeof(marble));
    
    //Instantiate the new marbles values to the desired ones.
    strcpy(new_marble->color, colors[color % 5]);
    //Modulus on the size to make them appear to be different.
    new_marble->size = (size % 10);
    new_marble->num = nodes;
    new_marble->next = head;
    head = new_marble;
    
    //Increment the node counter.
    nodes += 1;
    };


int remove_marble(){

    //Not 100% if all these heads are needed but this was how we got it to work
    //and I'm not sure how to re-factor into something neater.
    marble *previous = head;
    marble *current = head; 
    marble *new_head = previous;
    
    // Will be a range from (0, nodes-1)
    int random = rand() % nodes;

    //If the marbles number is equal to the number chosen for deletion we do this.
    if (head->num == random){
        
        head = head->next;

        cout << 
            "A number of marbles equal to " << random  << 
            " from the zero marble in the bag has been deleted." << 
            '\n' << endl;

        free(current);
        nodes -= 1;
        return 0;
    }
    //When the marbles number isn't the right number for deletion we do this.
    else{
    for(int i = nodes - 1; i >= 0; i--){
        if(i == random){

            previous->next = current->next;
            cout << 
                "A number of marbles equal to " << random << 
                " from the zero marble in the bag has been deleted." << 
                '\n' << endl;
            free(current);
            nodes -= 1;
        }
        else{
            previous = current;
            current = current->next;
        };
        };

    return 0;

    };
}

int display_marbles(){

    marble *new_head = head;
    
    //Simple loop to print out our marbles. If the bag is empty the user is told.
    if (new_head != NULL) {
        cout << "Marbles in bag." << endl;
        for (int i = 0; i < nodes; i ++){

            cout << 
                "Marble: " << new_head->num << "\tColor: "<< 
                new_head->color << "\tSize: " << 
                new_head->size << endl;
            
            new_head = new_head->next;
            };
        cout << '\n';
    } 
    else cout << "Bag is empty." << '\n' << endl;
    
    return 0;
}