#ifndef __MOVIE_H__
#define __MOVIE_H__
#include <iostream>
#include <fstream>
#include <algorithm>
#include <windows.h>
#include "Flavor.h"
using namespace std;

class Movie {
private:
  string title;
  int year;
  int runtime;
  string *tags;
	int tagSize;
  string era;
  string *distributedBy;
	int distributorCount;
  string folderLocation;
public:
  Movie();
	~Movie();
	void setTitle(string);
	void setFolderLocation(string);
	void setYear();
	void setRuntime();
	void setDistributedBy();
	void setTags();
	void setEra(int);
	string getTitle() const;
	string getFolderLocation() const;
	string getEra() const;
	string* getTags() const;
	string* getDistributedBy() const;
	int getYear() const;
	int getRuntime() const;
	int getTagSize() const;
	int getDistributorCount() const;
	void playMovie();
  
  friend ifstream& operator >> (ifstream&, Movie&);
	friend ofstream& operator << (ofstream&, Movie&);
	friend ostream& operator << (ostream&, Movie&);
	friend bool operator == (Movie&, Movie&);
};

#endif