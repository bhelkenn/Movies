#include <string>
#include <Windows.h>
#include <iostream>
#include "Database.h"

void Database::collectMetaResults(string search) {
	for (int loop_count = 0; loop_count < size; loop_count++) {
		if (atoi(search.c_str()) > 0 && movies[loop_count].getYear() == atoi(search.c_str())) {
			cout << "year result found in " << movies[loop_count].getTitle() << endl;
			resultsSize++;
		}
		else if (atoi(search.c_str()) > 0 && movies[loop_count].getRuntime() == atoi(search.c_str())) {
			cout << "runtime result found in " << movies[loop_count].getTitle() << endl;
			resultsSize++;
		}
		else if (movies[loop_count].getEra().find(search) != string::npos) {
			cout << "era result found in " << movies[loop_count].getTitle() << endl;
			resultsSize++;
		}
		else if (search == "UNKNOWN" &&
		(movies[loop_count].getYear() == 0 ||
		movies[loop_count].getRuntime() == 0 ||
		movies[loop_count].getTagSize() == 0 ||
		movies[loop_count].getEra().size() == 0 ||
		movies[loop_count].getDistributorCount() == 0)) {
			cout << "empty result found in " << movies[loop_count].getTitle() << endl;
			resultsSize++;
		}
		else {
			for (int tag_loop_count = 0; tag_loop_count < movies[loop_count].getTagSize(); tag_loop_count++) {
				if (movies[loop_count].getTags()[tag_loop_count].find(search) != string::npos) {
					cout << "tag result found in " << movies[loop_count].getTitle() << endl;
					resultsSize++;
					break;
				}
			}
			for (int distr_loop_count = 0; distr_loop_count < movies[loop_count].getDistributorCount(); distr_loop_count++) {
				if (movies[loop_count].getDistributedBy()[distr_loop_count].find(search) != string::npos) {
					cout << "distributedBy result found in " << movies[loop_count].getTitle() << endl;
					resultsSize++;
					break;
				}
			}
		}
	}
}
int Database::applyMetaResults(string search, int position) {
	for (int loop_count = 0; loop_count < size; loop_count++) {
		if (atoi(search.c_str()) > 0 && movies[loop_count].getYear() == atoi(search.c_str())) {
			results[position] = movies[loop_count];
			position++;
		}
		else if (atoi(search.c_str()) > 0 && movies[loop_count].getRuntime() == atoi(search.c_str())) {
			results[position] = movies[loop_count];
			position++;
		}
		else if (movies[loop_count].getEra().find(search) != string::npos) {
			results[position] = movies[loop_count];
			position++;
		}
		else if (search == "UNKNOWN" &&
		(movies[loop_count].getYear() == 0 ||
		movies[loop_count].getRuntime() == 0 ||
		movies[loop_count].getTagSize() == 0 ||
		movies[loop_count].getEra().size() == 0 ||
		movies[loop_count].getDistributorCount() == 0)) {
			results[position] = movies[loop_count];
			position++;
		}
		else {
			for (int tag_loop_count = 0; tag_loop_count < movies[loop_count].getTagSize(); tag_loop_count++) {
				if (movies[loop_count].getTags()[tag_loop_count].find(search) != string::npos) {
					results[position] = movies[loop_count];
					position++;
					break;
				}
			}
			for (int distr_loop_count = 0; distr_loop_count < movies[loop_count].getDistributorCount(); distr_loop_count++) {
				if (movies[loop_count].getDistributedBy()[distr_loop_count].find(search) != string::npos) {
					results[position] = movies[loop_count];
					position++;
					break;
				}
			}
		}
	}
	return position;
}

Database::Database() {
  movies = NULL;
  size = 0;
  capacity = 500;
	path = "M:\\Movies\\Movies";
	results = NULL;
	resultsSize = 0;
}
Database::~Database() {
	if (Database::saveChanges()) {
		cout << "Database data saved" << endl;
	}
	delete [] movies;
}

int Database::getSize() const {
	return size;
}
Movie* Database::getMovies() {
	return movies;
}
Movie* Database::getResults() {
	return results;
}
int Database::getResultsSize() const {
	return resultsSize;
}

void Database::listMovies() {
	cout << "---- MOVIES IN DATABASE ----" << endl;
	for (int loop_count = 0; loop_count < size; loop_count++) {
		cout << loop_count + 1 << ". " << movies[loop_count].getTitle() << endl;
	}
}

bool Database::searchMoviesResults(string search) {
	//zeros out previous search results
	resultsSize = 0;
	delete [] results;
	
	
	for (int loop_count = 0; loop_count < size; loop_count++) {
		if (movies[loop_count].getTitle().find(search) != string::npos) {
			resultsSize++;
		}
	}
	if (resultsSize == 0)
		return false;
	else {
		results = new Movie[resultsSize];
		int index = 0;
		for (int loop_count = 0; loop_count < size; loop_count++) {
			if (movies[loop_count].getTitle().find(search) != string::npos) {
				results[index] = movies[loop_count];
				index++;
			}
		}
		return true;
	}
}
bool Database::searchMetaResults(string search) {
	//zeros out previous search results
	resultsSize = 0;
	delete [] results;
	
	Database::collectMetaResults(search);
	cout << "resultsSize == " << resultsSize << endl;
	
	if (resultsSize == 0)
		return false;
	else {
		results = new Movie[resultsSize];
		int index = 0;
		index = Database::applyMetaResults(search, index);
		return true;
	}
}
/*
bool Database::searchMetaResults(string *tags, int tagSize) {
	//zeros out previous search results
	resultsSize = 0;
	delete [] results;
	
	if (tagSize > 0) {
		for (int loop_count = 0; loop_count < tagSize; loop_count++) {
			cout << "collecting results for " << tags[loop_count] << " movies..." << endl;
			Database::collectMetaResults(tags[loop_count]);
			cout << "finished collecting " << tags[loop_count] << " results..." << endl;
			cout << "resultsSize == " << resultsSize << endl;
		}
		results = new Movie[resultsSize];
		for (int loop_count = 0; loop_count < tagSize; loop_count++) {
			int index = 0;
			cout << "writing results for " << tags[loop_count] << " movies to array..." << endl;
			index = Database::applyMetaResults(tags[loop_count], index);
			cout << "finished writing results for " << tags[loop_count] << " results to array..." << endl;
		}
		return true;
	}
	else
		return false;
}
*/
bool Database::saveChanges() {
	bool changesSaved = false;
	for (int loop_count = 0; loop_count < size; loop_count++) {
		if (movies[loop_count].getFolderLocation() != "") {
			ofstream file;
			file << movies[loop_count];
			changesSaved = true;
		}
	}
	return changesSaved;
}

ifstream& operator >> (ifstream& file, Database &db) {
	string location = db.path + "\\MOVIELIST";
  
	file.open(location.c_str());
	
	db.movies = new Movie[db.capacity];
	
	int index;
	string tmp;
	while (!file.eof()) {
		getline(file, tmp);
		db.movies[index].setTitle(tmp);
		db.movies[index].setFolderLocation(db.path + "\\" + tmp);
		index++;
	}
	file.close();
	db.size = index - 1;
	
  return file;
}