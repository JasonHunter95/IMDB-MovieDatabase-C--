#include <iostream>
#include <vector>
#include "MovieHashTable.hpp"
#include "MovieNode.hpp"
using namespace std;

/**
* Constructor for MovieHashTable with default size
* @param (no parameters / default constructor)
* @return (no return / constructor)
*/
MovieHashTable::MovieHashTable() 
{
    int table_size = DEFAULT_HTABLE_CAPACITY; // table size is set to default capacity 2000
    table = new MovieNode*[table_size]; // create new array of MovieNode pointers
    for(int i = 0; i < table_size; i++) // loop through and initialize all pointers to null
    {
        table[i] = nullptr;
    }
    int n_collisions = 0;
}

/**
* Parametrized constructor for MovieHashTable with given size
* @param (size of hash table)
* @return (no return / constructor)
*/
MovieHashTable::MovieHashTable(int size) 
{
    int table_size = size;
    table = new MovieNode*[table_size];
    for(int i = 0; i < table_size; i++)
    {
        table[i] = nullptr;
    }
    int n_collisions = 0;
}

/**
* Destructor for MovieHashTable that deletes all nodes in the hash table and the linked lists at each shared index
* @param (no parameters / destructor)
* @return (no return / destructor)
*/
MovieHashTable::~MovieHashTable() 
{
    for(int i = 0; i < table_size; i++) // loop through each index in the table
    {
        MovieNode* curr = table[i]; // set curr to the head of the list at the current index
        while(curr != nullptr) // delete all nodes in this list
        {
            // update pointers and delete
            MovieNode* temp = curr; // set temp to curr
            curr = curr->next; // set curr to the next node in the list
            delete temp; // delete temp
        }
    }
    delete[] table; 
}

/**
* Helper function for hashing to sum the ASCII values of the characters in an input string
* @param (string)
* @return (int (sum of ASCII values of the input string))
*/
int sumASCII(string &input) 
{
    int sum = 0;
    for(int i = 0; i < input.length(); i++)
    {
        sum += input[i];
    }
    return sum;
}

/**
* Hash function for MovieHashTable that returns an index in the hash table for a given movie title.
* @param (string (movie title))
* @return (int (index in the hash table at which to insert the movie))
*/
int MovieHashTable::hash(string title) 
{
    // TODO
    string identikey = "Jahu8701";
    int ASCII_title = sumASCII(title);
    int ASCII_identikey = sumASCII(identikey);
    int title_length = title.length();
    int sum = ASCII_identikey + ASCII_title;  
    int hash_value = sum; // hash value to be returned

    // This is simply to make the hash function have a better distribution
    if (title_length >= 4) 
    {
        // Compute hash value using the first two and last two characters of the movie title
        hash_value += (title[0] + title[1] + title[title_length - 2] + title[title_length - 1]);
    } 
    else 
    {
        // If the movie title is less than four characters, use the ASCII value of the title as the hash value
        for (int i = 0; i < title_length; i++) 
        {
            hash_value += (title[i]);
        }
    } 
    return hash_value % DEFAULT_HTABLE_CAPACITY; 
}

/**
* Inserts a movie node into the hash table with the specified title 
* @param (string (movie title), MovieNode* (pointer to the movie node to insert))
* @return (void / inserts the movie node into the hash table)
*/
void MovieHashTable::insert(string title, MovieNode* movie) 
{
    int index = hash(title); // get index to place movie

    // If the hash table slot is empty, insert the movie as the head of the linked list
    if (table[index] == nullptr) 
    {
        table[index] = movie;
    } 
    else 
    {
        // Otherwise, traverse the list until the end and insert the movie at the tail
        MovieNode* temp = table[index]; // set temp to head
        while (temp->next != nullptr) // traverse to end of list
        {
            temp = temp->next; // update temp to next
        }
        temp->next = movie; // insert the movie at the end of list
        setCollisions(); // update collisions
    }
    // cout << "Inserted " << title << " at index " << index << endl;
}


/**
* Searches for a node in the hash table with the specified title and returns a pointer to that node
* @param (string (movie title to search for))
* @return (MovieNode* (pointer to the movie node with the title passed in))
*/
MovieNode* MovieHashTable::search(string title) 
{
    int index = hash(title); // get index to search
    MovieNode* node = table[index]; // set node to head of list at index calculated
    while(node != nullptr && node->title != title) // traverse list (if there is one) until either the node is found or end of list is reached
    {
        node = node->next;
    }
    return node; 
}

/**
* Returns the number of collisions that have occurred during insertion into the hash table
* @param (no parameters / getter)
* @return (int (number of collisions)
*/
int MovieHashTable::getCollisions() 
{
    return n_collisions;
}

/**
* Increments the number of collisions that have occurred during insertion into the hash table (called each time a collision occurs)
* @param (no parameters / setter)
* @return (void / setter)
*/
void MovieHashTable::setCollisions() 
{
    n_collisions++;
}
