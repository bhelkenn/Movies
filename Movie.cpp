#include "Movie.h"

Movie::Movie() {
  title = "";
  year = 0;
  runtime = 0;
  tags = NULL;
	tagSize = 0;
  era = "";
  distributedBy = NULL;
	distributorCount = 0;
  folderLocation = "";
}
Movie::~Movie() {
	delete [] tags;
	delete [] distributedBy;
}

void Movie::setTitle(string title) {
	this->title = title;
}
void Movie::setFolderLocation(string folderLocation) {
	this->folderLocation = folderLocation;
}
void Movie::setYear() {
	int year = GetInt();
	while (year / 1000 == 0 || year / 10000 > 0) {
		cout << "Must be 4 digits, try again: ";
		year = GetInt();
	}	
	this->year = year;
	Movie::setEra(year);
}
void Movie::setRuntime() {
	string input = GetString();
	if (IsInt(input)) {
		int runtime = atoi(input.c_str());
		while (runtime / 1000 > 0) {
			cout << "Must be at most 3 digits, try again: ";
			runtime = GetInt();
		}
		this->runtime = runtime;
	}
	else {
		while (input[1] != ':' || input.size() != 4) {
			cout << "Must be in x:xx format only, try again: ";
			input = GetString();
		}
		int hours = atoi(input.substr(0, 1).c_str());
		int minutes = atoi(input.substr(2).c_str());
		this->runtime = hours * 60 + minutes;
	}
}
void Movie::setDistributedBy() {
	cout << "How many distributors are there? ";
	distributorCount = GetInt();
	distributedBy = new string[distributorCount];
	for (int loop_count = 0; loop_count < distributorCount; loop_count++) {
		cout << loop_count + 1 << " of " << distributorCount << ": ";
		distributedBy[loop_count] = GetString();
	}
}
void Movie::setTags() {
	cout << "How many tags would you like to add? ";
	tagSize = GetInt();
	tags = new string[tagSize];
	for (int loop_count = 0; loop_count < tagSize; loop_count++) {
		cout << loop_count + 1 << " of " << tagSize << ": ";
		tags[loop_count] = GetString();
	}
}
void Movie::setEra(int year) {
	int decade = year / 10;
	decade *= 10;
	this->era = static_cast<ostringstream*>(&(ostringstream() << decade))->str() + "s";
}
string Movie::getTitle() const {
	return title;
}
string Movie::getFolderLocation() const {
	return folderLocation;
}
string Movie::getEra() const {
	return era;
}
string* Movie::getTags() const {
	return tags;
}
string* Movie::getDistributedBy() const {
	return distributedBy;
}
int Movie::getYear() const {
	return year;
}
int Movie::getRuntime() const {
	return runtime;
}
int Movie::getTagSize() const {
	return tagSize;
}
int Movie::getDistributorCount() const {
	return distributorCount;
}

void Movie::playMovie() {
	string mpchc = "C:\\Program Files (x86)\\MPC-HC\\mpc-hc.exe";
	
	string cmd = "\"" + folderLocation + "\"" + " /new";
	
	ShellExecute(NULL, "open", mpchc.c_str(), cmd.c_str(), NULL, SW_SHOWNORMAL);
	Pause();
}

/* used to pull from desktop.ini, shouldn't be needed anymore, but you never know
ifstream& operator >> (ifstream& file, Movie &movie) {
	string location = movie.folderLocation + "\\Desktop.ini";
	file.open(location.c_str(), ios::in);
	string tmp;
	if (!file) {
		cout << movie.title << " failed to open desktop.ini file" << endl;
	}
	while (!file.eof()) {
		getline(file, tmp);
		if (tmp.find("Prop3=31,") != string::npos) {
			movie.year = atoi((tmp.substr(tmp.find(",") + 1)).c_str());
			int decade = (movie.year / 10);
			decade *= 10;
			movie.era = static_cast<ostringstream*>(&(ostringstream() << decade))->str() + "s";
		}
		if (tmp.find("Prop4=31,") != string::npos) {
			movie.distributorCount = count(tmp.begin(), tmp.end(), ';') + 1;
			string *distributedBy = new string[movie.distributorCount];
			stringstream ss(tmp);
			
			getline(ss, tmp, ',');
			for (int loop_count = 0; loop_count < movie.distributorCount; loop_count++) {
				getline(ss, tmp, ';');
				distributedBy[loop_count] = tmp;
			}
			
			movie.distributedBy = new string[movie.distributorCount];
			int indexOfDistributedBy = 0;
			for (int loop_count = 0; loop_count < movie.distributorCount; loop_count++) {
				if (distributedBy[loop_count] != "") {
					movie.distributedBy[indexOfDistributedBy] = distributedBy[loop_count];
					indexOfDistributedBy++;
				}
			}
		}
		if (tmp.find("Prop5=31,") != string::npos) {
			movie.tagSize = count(tmp.begin(), tmp.end(), ';') + 1;
			string *tags = new string[movie.tagSize];
			stringstream ss(tmp);
			
			getline(ss, tmp, ',');
			for (int loop_count = 0; loop_count < movie.tagSize; loop_count++) {
				getline(ss, tmp, ';');
				tags[loop_count] = tmp;
			}
			for (int loop_count = 0; loop_count < movie.tagSize; loop_count++) {
				if (tags[loop_count].size() == 5 && tags[loop_count][4] == 's') {
					tags[loop_count] = "";
					movie.tagSize--;
				}
			}
			movie.tags = new string[movie.tagSize];
			int indexOfMovieTags = 0;
			for (int loop_count = 0; loop_count < movie.tagSize; loop_count++) {
				if (tags[loop_count] != "") {
					movie.tags[indexOfMovieTags] = tags[loop_count];
					indexOfMovieTags++;
				}
			}
		}
		if (tmp.find("InfoTip=") != string::npos) {
			int hours = atoi((tmp.substr(tmp.find("=") + 1, tmp.find(":"))).c_str());
			int minutes = atoi((tmp.substr(tmp.find(":") + 1)).c_str());
			movie.runtime = hours * 60 + minutes;
		}
	}

	file.close();
	return file;
}
*/
// best to use this if possible to reduce dependence on desktop.ini
ifstream& operator >> (ifstream& file, Movie &movie) {
	string location = movie.folderLocation + "\\METADATA";
	file.open(location.c_str());
	string tmp;
	
	getline(file, tmp);
	movie.title = tmp;
	
	getline(file, tmp);
	movie.year = atoi(tmp.c_str());
	
	getline(file, tmp);
	movie.runtime = atoi(tmp.c_str());
	
	//collect total tags from file
	getline(file, tmp);
	movie.tagSize = count(tmp.begin(), tmp.end(), ';');
	movie.tags = new string[movie.tagSize];
	
	stringstream ssTags(tmp);
	for (int loop_count = 0; loop_count < movie.tagSize; loop_count++) {
		getline(ssTags, tmp, ';');
		movie.tags[loop_count] = tmp;
	}
	
	getline(file, tmp);
	movie.era = tmp;
	
	//collect total distributedBy from file
	getline(file, tmp);
	movie.distributorCount = count(tmp.begin(), tmp.end(), ';');
	movie.distributedBy = new string[movie.distributorCount];
	
	stringstream ssDistr(tmp);
	for (int loop_count = 0; loop_count < movie.distributorCount; loop_count++) {
		getline(ssDistr, tmp, ';');
		movie.distributedBy[loop_count] = tmp;
	}
	
	file.close();
	return file;
}

ofstream& operator << (ofstream& file, Movie &movie) {
	string location = movie.folderLocation + "\\METADATA";
	file.open(location.c_str(), ios::trunc | ios::out);
	file << movie.title << endl;
	file << movie.year << endl;
	file << movie.runtime << endl;
	
	for (int loop_count = 0; loop_count < movie.tagSize; loop_count++) {
		file << movie.tags[loop_count] << ";";
	}
	file << endl;
	
	file << movie.era << endl;
	
	for (int loop_count = 0; loop_count < movie.distributorCount; loop_count++) {
		file << movie.distributedBy[loop_count] << ";";
	}
	file << endl;
	
	file.close();
	return file;
}
ostream& operator << (ostream& stream, Movie &movie) {
	stream << "-----Showing detailed information on " << movie.title << "-----" << endl;
	stream << "Year released: ";
	if (movie.year == 0)
		stream << "UNKNOWN" << endl;
	else
		stream << movie.year << endl;
	
	stream << "Runtime: ";
	if (movie.runtime == 0)
		stream << "UNKNOWN" << endl;
	else {
		stream << movie.runtime / 60 << ":";
		int minutes = movie.runtime % 60;
		if (minutes < 10)
			stream << "0";
		stream << minutes << endl;
	}
	
	stream << "Era (decade released): ";
	if (movie.era == "")
		stream << "UNKNOWN" << endl;
	else
		stream << movie.era << endl;
	
	stream << "Distributed by: ";
	if (movie.distributorCount > 0) {
		stream << movie.distributedBy[0];
		for (int loop_count = 1; loop_count < movie.distributorCount; loop_count++) {
			stream << ", " << movie.distributedBy[loop_count];
		}
		stream << endl;
	}
	else {
		stream << "UNKNOWN" << endl;
	}
	
	stream << "Tags: ";
	if (movie.tagSize > 0) {
		stream << movie.tags[0];
		for (int loop_count = 1; loop_count < movie.tagSize; loop_count++) {
			stream << ", " << movie.tags[loop_count];
		}
		stream << endl;
	}
	else {
		stream << "NONE" << endl;
	}
	
	return stream;
}
bool operator == (Movie& movie1, Movie& movie2) {
	return (movie1.title == movie2.title);
}