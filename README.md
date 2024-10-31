## IMDB Movies Database Project

This project is a simple implementation of a movie database using C++ and two data structures: a hash table and a skip list.

## Requirements

1. C++ compiler 
2. A CSV file containing movie data (e.g. IMDB-Movie-Data.csv)

## Installation

1. Clone the repository
2. Compile the code : `g++ -std=c++11 driver.cpp MovieHashTable.cpp DirectorSkipList.cpp -o movie-db`
3. Run the program: `./movie-db IMDB-Movie-Data.csv 2000 2000`
4. Follow the on-screen (terminal) menu to perform different operations on the movie database.

## Data Structures

This project uses two data structures to store and retrieve movie data: a hash table and a skip list.

### Hash Table
The hash table is used to map movie titles to `MovieNode` objects. 
The hash function used is a custom function that takes the sum of the ASCII codes of all characters in the title string and calculates the modulo of the sum by the hash table size.

### Skip List
The skip list is used to map director names to `DirectorSLNode` objects, which contain a vector of `MovieNode` pointers. The skip list is a probabilistic data structure that allows for efficient search, insertion, and deletion of elements. It is implemented using a linked list with multiple levels, where each level has fewer nodes than the level below it. The skip list used in this project has a fixed number of levels (10) and a fixed capacity (2000).

I decided to use chaining as my collision resolution method. I feel like I have the best understanding of chaining when it comes to hashing. I had a decent idea of how to work with a linked list in this case and found it to be the easiest implementation. 

My hash function uses a helper to sum the ascii values in my identikey "Jahu8701" and the title of movie that is passed in. Then I added in another calculation depending on the title length of the movie passed in. This was to add more uniqueness to my hashing function and reduce the number of collisions. I think I got it down to a good spot with only 247 collisions.
