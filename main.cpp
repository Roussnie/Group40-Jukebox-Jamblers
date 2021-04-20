#include <iostream>
#include <string>
#include <vector>
#include <set>
#include <fstream>
#include <sstream>
#include "Tree.h"
using namespace std;

struct Song {

    string artist;
    string name;
    int popularity = 0;
    int releaseYear = 0;

    int count = 0;
    string lines;

    vector<string> artistVect;
    vector<string> nameVect;
    vector<int> popularityVect;
    vector<int> yearVect;

    Song() { //Default Constructor//

        artist = "";
        name = "";
        popularity = 0;
        releaseYear = 0;

        count = 0;
        lines = "";

        artistVect = {};
        nameVect = {};
        popularityVect = {};
        yearVect = {};
    }

    Song(const Song& d) { //Copy constructor//

        this->artist = d.artist;
        this->name = d.name;
        this->popularity = d.popularity;
        this->releaseYear = d.releaseYear;

        this->count = d.count;
        this->lines = d.lines;

        this->artistVect = d.artistVect;
        this->nameVect = d.nameVect;
        this->popularityVect = d.popularityVect;
        this->yearVect = d.yearVect;
    }

    Song& operator=(const Song& d) { //Copy assignment operator//

        this->artist = d.artist;
        this->name = d.name;
        this->popularity = d.popularity;
        this->releaseYear = d.releaseYear;

        this->count = d.count;
        this->lines = d.lines;

        this->artistVect = d.artistVect;
        this->nameVect = d.nameVect;
        this->popularityVect = d.popularityVect;
        this->yearVect = d.yearVect;

        return *this;
    }

    bool operator < (const Song& rhs) const { //organize set based off name in ascending order
        return name < rhs.name;
    }
};

set<Song> CreateSet(Song song, vector<int> index) {

    set<Song> songSet;

    for (int i = 0; i < index.size(); i++) {

        Song temp; //make a temporary song

        temp.artist = song.artistVect[index[i]];
        temp.name = song.nameVect[index[i]];
        temp.popularity = song.popularityVect[index[i]];
        temp.releaseYear = song.yearVect[index[i]];

        songSet.insert(temp); //insert it into the set
    }

    return songSet;
}


int main()
{
    Song song;

    set<Song> songSet;

    JJTree tree;
    TreeNode* root = nullptr;

    /*======= Load data from file(s) =======*/
    ifstream file("P3_song_data csv.csv");

    if (file.is_open()) {

        file.get();

        getline(file, song.lines); //header line

        while (getline(file, song.lines)) { //while there are lines to read
            istringstream stream(song.lines);

            getline(stream, song.artist, ',');
            song.artistVect.push_back(song.artist);

            getline(stream, song.name, ',');
            song.nameVect.push_back(song.name);

            string tempPopu;
            getline(stream, tempPopu, ',');
            song.popularity = stoi(tempPopu);
            song.popularityVect.push_back(song.popularity);

            string tempYear;
            getline(stream, tempYear, ',');
            song.releaseYear = stoi(tempYear);
            song.yearVect.push_back(song.releaseYear);

            song.count++;
        }
    }
    file.close();

    //*********Interface*********//
    cout << "Welcome to the Jukebox Jambler!" << endl;

    //user enters word to search for
    string wordInput = "";
    cout << "Enter a word based on what you would like to hear: ";
    getline(cin, wordInput);
    cout << endl;

    vector<int>index;

    string word = "";

    for (int i = 0; i < song.count; i++) {  
        size_t found = song.nameVect[i].find(wordInput);
        if (found != string::npos) { 
            index.push_back(i);
        }
    }

    if (index.size() == 0) {
        cout << "Sorry, we dont have any songs matching " << wordInput << ". Goodbye\n";
        return 0;
    }

    //user chooses data structure
    cout << "Which Data Stucture would you like to use?\n";
    cout << "1. Set\n";
    cout << "2. Tree\n";
    cout << "Selection: ";

    string input1 = "";
    getline(cin, input1);
    cout << endl;

    cout << "We have " << index.size() << " song(s) similar to '" << wordInput << "':\n" << endl;

    if (input1 == "1") {

        songSet = CreateSet(song, index); //creates the set

        for (const auto& s : songSet) { //prints set

            cout << "Title: " << s.name << endl;
            cout << "Artist: " << s.artist << endl;
            cout << "Year of Release: " << s.releaseYear << endl;
            cout << "Popularity: " << s.popularity << endl;
            cout << endl;
        }
    }
    else if (input1 == "2") {

        for (int i = 0; i < index.size(); i++) {  //creates the tree
            tree.Insert(root, index[i], song.artistVect[index[i]], song.nameVect[index[i]], song.popularityVect[index[i]], song.yearVect[index[i]]);
        }
        tree.PrintInorder(root, root->artist, root->name, root->popularity, root->releaseYear);

    }
    else {
        cout << "Invalid entry!\n";
    }
    return 0;
}


//Sources:
//https://www.geeksforgeeks.org/string-find-in-cpp/
//Roussnie Project 1 Implementation
