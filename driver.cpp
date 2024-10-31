#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include "MovieHashTable.hpp"
#include "DirectorSkipList.hpp"
#include "MovieNode.hpp"

using namespace std;

// Function prototypes
MovieNode* parseMovieLine(string line);
void readMovieCSV(string filename,  MovieHashTable &movieTable, DirectorSkipList &directorList);
void display_menu();


// Main function
int main(int argc, char* argv[]) 
{
    // Argument check
    if(argc != 4)
    {
        cout << "Invalid number of arguments." << endl;
        cout << "Usage: ./<program name> <csv file> <hashTable size> <skipList size>" << endl;
        return 0;
    }
    string filename = argv[1];
    int hash_table_size = stoi(argv[2]);
    int skip_list_size = stoi(argv[3]);
    MovieHashTable movieTable(hash_table_size);
    DirectorSkipList directorList(skip_list_size, 10);
    readMovieCSV(filename, movieTable, directorList);
    bool quit = false;
    string input = "";

    cout << "Number of collisions: " << movieTable.getCollisions() << endl;

    while(!quit)
    {
        display_menu();
        getline(cin, input);
        int choice = stoi(input);

        switch(choice)
        {
            case 1: // 1. Find the director of a movie
            {
                cout << "Enter movie name: ";
                string title;
                getline(cin, title);
                MovieNode* movie = movieTable.search(title);
                if(movie == nullptr)
                {
                    cout << "Movie not found." << endl;
                    break;
                }
                cout << "Movie found: " << movie->title << endl;
                cout << "The director of: " << movie->title << " is " << movie->director << endl;
                break;
            }
            case 2: // 2. Find the number of movies by a director
            {

                cout << "Enter director name: ";
                string director;
                getline(cin, director);
                // TODO: Find the number of movies by the director
                // Damien Chazelle directed 2 movies.
                vector <DirectorSLNode*> prev = vector<DirectorSLNode*>(skip_list_size, nullptr);
                DirectorSLNode* node = directorList.search(director);
                if(node)
                {
                    cout << node->director << " directed " << node->movies.size() << " movies." << endl;
                }
                else
                {
                    cout << "Director not found." << endl;
                }
                break;
            }
            case 3: // 3. Find the description of a movie
            {
                cout << "Enter movie name: ";
                string title;
                getline(cin, title);
                MovieNode *movie = movieTable.search(title);
                if(movie == nullptr)
                {
                    cout << "Movie not found." << endl;
                    break;
                }
                cout << "Movie found: " << movie->title << endl;
                cout << "Summary: " << movie->title << " is a " << movie->year << " (" << movie->genre << ") " << "film featuring the following actors: " << movie->actors << endl;
                cout << "Plot: " << movie->description << endl;
                break;
            }
            case 4: // 4. List the movies by a director
            {
                cout << "Enter director name: ";
                string director;
                getline(cin, director);
                // Damien Chazelle directed the following movies:
                // 0: La La Land
                // 1: Whiplash
                vector <DirectorSLNode*> prev = vector<DirectorSLNode*>(skip_list_size, nullptr);
                DirectorSLNode* node = directorList.search(director);
                if(node)
                {
                    cout << node->director << " directed the following movies:" << endl;
                    for(MovieNode* movie : node->movies)
                    {
                        cout << "\t" << movie->title << endl;
                    }
                }
                else
                {
                    cout << "Director not found." << endl;
                }
                break;
            }
            case 5: // 5. Quit
            {
                cout << "Quitting..." << endl;
                quit = true;
                break;
            }
            default:
            {
                cout << "INVALID INPUT" << endl;
                cout << "Please enter an integer between 1 and 5." << endl;
                break;
            }
        }
    }
    return 0;
}

// Function to parse a CSV line into a MovieNode object
MovieNode* parseMovieLine(string line) 
{
    stringstream ss(line);
    vector<string> fields;
    string field;

    // Loop through the characters in the line
    bool in_quotes = false;
    for (size_t i = 0; i < line.length(); ++i)
    {
        char c = line[i];
        if (c == '\"') 
        {
            in_quotes = !in_quotes;
        } 
        else if (c == ',' && !in_quotes) 
        {
            // add field to vector and reset for next field
            fields.push_back(field);
            field.clear();
        } 
        else 
        {
            field += c;
            // handle double quotes inside a quoted field
            if (in_quotes && c == '\"' && i < line.length() - 1 && line[i+1] == '\"') 
            {
                field += '\"'; // add the second double quote and skip it
                ++i;
            }
        }
    }
    fields.push_back(field);

    if (fields.size() != 12) 
    {
        cerr << "Error: Invalid movie line format" << line << endl;
        return nullptr;
    }

    int rank = stoi(fields[0]);
    string title = fields[1];
    string genre = fields[2];
    string description = fields[3];
    string director = fields[4];
    string actors = fields[5];
    int year = stoi(fields[6]);
    int runtime = stoi(fields[7]);
    float rating = stof(fields[8]);
    int votes = stoi(fields[9]);
    float revenue = stof(fields[10]);
    int metascore = stoi(fields[11]);

    // Create a new MovieNode object with the parsed fields
    MovieNode* movie = new MovieNode(rank, title, genre, description, director, actors, year, runtime, rating, votes, revenue, metascore);
    return movie;
}

/**
* reads a CSV file into a vector of MovieNode objects
* @param - takes in a CSV file, and both movieTable and directorList objects
* @return - void (function calls insert on movieTable and directorList objects to populate with data from the CSV) 
*/
void readMovieCSV(string filename,  MovieHashTable &movieTable, DirectorSkipList &directorList) 
{
    ifstream file;
    string line;

    file.open(filename);

    if(!file.is_open())
    {
        cout << "Error opening file." << endl;
    }
    else
    {
        // cout << "File opened successfully." << endl;
        getline(file, line); // skips 1 line to ignore headers
        while(getline(file, line))
        {
            MovieNode* movie = parseMovieLine(line);
            movieTable.insert(movie->title, movie);
            directorList.insert(movie->director, movie);
        }
    }
    file.close();
}

// Function to display the menu options 
void display_menu()
{
    cout << endl;
    cout << "Please select an option: " << endl;
    cout << "1. Find the director of a movie" << endl;
    cout << "2. Find the number of movies by a director" << endl;
    cout << "3. Find the description of a movie" << endl;
    cout << "4. List the movies by a director" << endl;
    cout << "5. Quit" << endl << endl;
    cout << "Enter an Option: ";
}
