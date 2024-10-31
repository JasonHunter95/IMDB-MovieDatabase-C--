#include <cstddef>
#include <iostream>
#include <vector>
#include "DirectorSkipList.hpp"
#include "MovieNode.hpp"
#include <random>
#include <time.h>
#include <math.h>

using namespace std;
 
/**
* Constructor for DirectorSkipList with default capacity and levels
* @param (no parameters / default constructor)
* @return (no return / constructor)
*/
DirectorSkipList::DirectorSkipList() 
{
    levels = DEFAULT_LEVELS; // set levels to default levels
    capacity = DEFAULT_CAPACITY; // set capacity to default capacity
    head = new DirectorSLNode(); // set head to a new DirectorSLNode
    head->next = vector<DirectorSLNode*>(levels, nullptr); // connect head to a vector of DirectorSLNodes of size levels and set the pointers to null
    size = 0;
}

/**
* Parametrized constructor for DirectorSkipList with given capacity and levels
* @param (capacity, levels / parametrized constructor)
* @return (no return / constructor)
*/
DirectorSkipList::DirectorSkipList(int _cap, int _levels) 
{
    levels = _levels;
    capacity = _cap;
    head = new DirectorSLNode();
    head->next = vector<DirectorSLNode*>(levels, nullptr);
    size = 0;
}

/**
* Destructor for DirectorSkipList that deletes all nodes in the skip list (but not the MovieNodes, which are shared with other data structures)
* @param (no parameters / destructor)
* @return (no return / destructor)
*/
DirectorSkipList::~DirectorSkipList() 
{
    DirectorSLNode* curr = head; // set curr to head
    DirectorSLNode* next = nullptr; // set next to null
    while(curr != nullptr)
    {
        next = curr->next[0]; // set next to curr's next node at level 0
        delete curr; // delete curr
        curr = next; // set curr to next
    }
    head = NULL; // set head to null (not sure if this is necessary)
}

void DirectorSkipList::insert(string director, MovieNode* _movie) 
{
    // create a vector to track nodes before the insertion point at each level
    vector<DirectorSLNode*> prev(levels, nullptr);
    DirectorSLNode* curr = head;

    // traverse each level from top down to find the insertion points
    for (int i = levels - 1; i >= 0; i--) 
    {
        while (curr->next[i] != nullptr && curr->next[i]->director < director) 
        {
            curr = curr->next[i];
        }
        prev[i] = curr;  // Store the last node visited at this level
    }

    // check if director already exists to avoid duplicate insertions
    curr = curr->next[0];
    if (curr != nullptr && curr->director == director) 
    {
        curr->addMovie(_movie);  // Add movie if director node exists
        return;
    }

    // determine levels for the new node using a random level generator
    int n_levels = 1;
    while (n_levels < levels && rand() % 2 == 0) 
    {
        n_levels++;
    }

    // create the new node with `n_levels` levels
    DirectorSLNode* newNode = new DirectorSLNode(director, n_levels);

    // insert the new node by updating pointers in `prev` at each level
    for (int i = 0; i < n_levels; i++) 
    {
        newNode->next[i] = prev[i]->next[i];
        prev[i]->next[i] = newNode;
    }

    // add the movie to the new node's movie list
    newNode->addMovie(_movie);

    // increase size counter if you’re keeping track of the size of the skiplist
    size++;
}

// Searches for a node in the skip list with the specified director
// 1. Set curr to head
// 2. For i from maxlevels - 1 down to 0, do the following:
// a. While curr’s next node at level i is not null and its key is less
// than search key:
// i. Set curr to curr’s next node at level i
// b. Set prev[i] to curr
// 3. Set curr to curr’s next node at level 0 // Why is this important?
// 4. If curr is not null and its key equals key, then return curr
// 5. Otherwise, return null
// I followed the above pseudocode from the slides for this function and I'm pretty sure it's not right. 
// I couldn't figure out how to find the previous node in the skip list.
DirectorSLNode *DirectorSkipList::search(string director) 
{
    // Set curr to head
    DirectorSLNode* curr = head;
    
    // For i from maxlevels - 1 down to 0, do the following:
    for(int i = levels - 1; i >= 0; i--)
    {
        // While curr’s next node at level i is not null and its key is less than the search key, set curr to its next node at level i
        while(curr->next[i] != NULL && curr->next[i]->director < director)
        {
            curr = curr->next[i];
        }
        // prev[i] = curr;
    }
        // 3. Set curr to curr’s next node at level 0
        curr = curr->next[0];
        // 4. If curr is not null and its key equals key, then return curr
        if(curr != NULL && curr->director == director)
        {
            return curr;
        }
        // 5. Otherwise, return null
    return nullptr;
}

// Pretty-prints the skip list
void DirectorSkipList::prettyPrint() 
{
}
