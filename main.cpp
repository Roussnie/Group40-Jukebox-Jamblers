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

	cout << song.count << endl;

	/*
	for (int i = 0; i < song.count; i++) {
		cout << song.artistVect[i] << "    " << song.nameVect[i] << "    " << song.yearVect[i] << " " << song.popularityVect[i] << "\n";

	}
	*/

	return 0;
}

