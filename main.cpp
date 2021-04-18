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

	int  count = 0;
	string lines;

	vector<string> artistVect;
	vector<string> nameVect;
	vector<int> popularityVect;
	vector<int> yearVect;
};


int main()
{
	Song song;

	/*======= Load data from file(s) =======*/
	ifstream file("P3_song_data csv.csv");

	if (file.is_open()) {

		file.get();

		getline(file, song.lines);   //header line

		while (getline(file, song.lines)) {  //while there are lines to read
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

	string input = "";
	cout << "Enter a word: \n";
	getline(cin, input);

	vector<int>index;
	
	string word = "";

	for (int i = 0; i < song.count; i++) {
		for (auto x : song.nameVect[i]) {
			if (x == ' ') {
				if (input == word) {
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

	for (int i = 0; i < index.size(); i++) {
		cout << song.artistVect[index[i]] << ", " << song.nameVect[index[i]] << ", " <<
			song.yearVect[index[i]] << ", " << song.popularityVect[index[i]] << "\n";
	}
	

	return 0;
}

//https://www.geeksforgeeks.org/split-a-sentence-into-words-in-cpp/
