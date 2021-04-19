#include <iostream>
#include <string>
#include <vector>
#include <map>
#include <set>
#include <fstream>
#include <sstream>

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
    
    Song(){ //Default Constructor//
        
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
    
    Song(const Song &d){ //Copy constructor//
        
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
    
    Song &operator=(const Song &d){ //Copy assignment operator//
        
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

set<Song> CreateSet(Song song, vector<int> index){
    
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

    //cout << song.count << endl;
    
    //*********Interface*********//
    cout << "Welcome to the Jukebox Jambler!" << endl;
    
    //user enters word to search for
    string wordInput = "";
    cout << "Enter a word: \n";
    cout << "" << endl;
    getline(cin, wordInput);
    
    //user chooses data structure
    cout << "Which Data Stucture would you like to use?" << endl;
    cout << "1. Set" << endl;
    cout << "2. Tree" << endl;
    cout << "" << endl;
    cout << "Selection: " << endl;
    cout << "" << endl;
    string input1 = "";
    getline(cin, input1);
    
    
    vector<int> index;
    
    string word = "";

    for (int i = 0; i < song.count; i++) {
        
        for (auto x : song.nameVect[i]) {
            
            if (x == ' ') {
                
                if (wordInput == word) {
                    index.push_back(i);
                }
                word = "";
            }
            else {
                
                word += x;
            }
        }
        word = "";
    }
    
    if (input1 == "1"){
        
        set<Song> songSet = CreateSet(song, index); //creates the set
        
        cout << "Songs similar to '" << wordInput << "':" << endl;
        cout << "" << endl;
        
        for(const auto& s : songSet){ //prints set
            
            cout << "Title: " << s.name << endl;
            cout << "Artist: " << s.artist << endl;
            cout << "Year of Release: " << s.releaseYear << endl;
            cout << "Popularity: " << s.popularity << endl;
            cout << "" << endl;
        }
        
        
    } else if(input1 == "2"){
        
        //create tree
    }
    

    return 0;
}

//https://www.geeksforgeeks.org/split-a-sentence-into-words-in-cpp/
