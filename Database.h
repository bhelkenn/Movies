#ifndef __DATABASE_H__
#define __DATABASE_H__
#include <string>
#include <fstream>
#include "Movie.h"

using namespace std;

class Database {
private:
  Movie *movies;
  int size;
  int capacity;
	string path;
	Movie *results;
	int resultsSize;
	void collectMetaResults(string);
	int applyMetaResults(string, int);
public:
  Database();
  ~Database();
  int getSize() const;
	Movie* getMovies();
	Movie* getResults();
	int getResultsSize() const;
	void listMovies();
	bool searchMoviesResults(string);
	bool searchMetaResults(string);
	//bool searchMetaResults(string*, int);
	bool saveChanges();
  friend ifstream& operator >> (ifstream&, Database&);
};


#endif