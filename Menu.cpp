#include "Menu.h"

enum RootSelection {
  EXIT,
  LIST_MOVIES,
  SELECT_MOVIE,
	FIND_METADATA,
	ROOT_SELECTION_MAX = FIND_METADATA
};
enum MovieSelection {
	BACK,
	LIST,
	SEARCH,
	MOVIE_SELECTION_MAX = SEARCH
};
enum MovieRoot {
	BACK_FROM_MOVIE_ROOT,
	PLAY,
	INFO,
	METADATA,
	SIMILAR_TAGS,
	MOVIE_ROOT_MAX = SIMILAR_TAGS
};
enum EditMetadata {
	BACK_FROM_EDIT_METADATA,
	YEAR,
	RUNTIME,
	DISTRIBUTEDBY,
	TAGS,
	EDIT_METADATA_MAX = TAGS
};

Menu::Menu() {
	selection = -1;
}

//root menu
void Menu::showRoot() {
	Clear();
	cout << "----- MAIN MENU -----" << endl;
	cout << LIST_MOVIES << ". List movies" << endl;
	cout << SELECT_MOVIE << ". Select a movie" << endl;
	cout << FIND_METADATA << ". Find movies based on metadata" << endl;
	cout << EXIT << ". EXIT" << endl;
}
void Menu::inputPromptRoot() {
	selection = validatedInput(EXIT, MOVIE_ROOT_MAX);
}
void Menu::processRoot(Database &db) {
	RootSelection choice = static_cast<RootSelection>(selection);
	switch (choice) {
		case LIST_MOVIES:
			db.listMovies();
			Pause();
			break;
		case SELECT_MOVIE:
			Menu::movieSelection();
			Menu::inputPromptMovieSelection();
			Menu::processMovieSelection(db);
			break;
		case FIND_METADATA:
			Menu::searchMetaResults(db, db.searchMetaResults(Menu::collectMetaSearchParamaters()));
			Menu::inputSearchResults(db.getResultsSize());
			Menu::processSearchResults(db, selection - 1);
			selection = -1; //prevents from quitting completely
			break;
		case EXIT:
			break;
		default:
			cout << "Something horrible has happened!" << endl;
	}
}

//used for both metadata and title searches
void Menu::inputSearchResults(int size) {
	selection = validatedInput(0, size);
}
void Menu::processSearchResults(Database& db, int index) {
	for (int loop_count = 0; loop_count < db.getSize(); loop_count++) {
		if (db.getResults()[index] == db.getMovies()[loop_count]) {
			Menu::processMovieChoiceFromList(db, loop_count);
			break;
		}
	}
}

//search for a movie by metadata string
string Menu::collectMetaSearchParamaters() {
	cout << "Enter metadata details you'd like to find a list of movies for (case-sensitive): ";
	return GetString();
}
void Menu::searchMetaResults(Database& db, bool found) {
	while (!found) {
		cout << "-----NO RESULTS FOUND, TRY AGAIN-----" << endl;
		found = db.searchMetaResults(Menu::collectMetaSearchParamaters());
	}
	cout << "-----Here's a list of movies that match your request-----" << endl;
	for (int loop_count = 0; loop_count < db.getResultsSize(); loop_count++) {
		cout << loop_count + 1 << ". " << db.getResults()[loop_count].getTitle() << endl;
	}
	cout << "0. Go back to the main menu" << endl;
}

//select a movie section
void Menu::movieSelection() {
	cout << "How would you like to select a movie?" << endl;
	cout << LIST << ". By number from the listed movies" << endl;
	cout << SEARCH << ". By string search" << endl;
	cout << BACK << ". Go back to the main menu" << endl;
}
void Menu::inputPromptMovieSelection() {
	selection = validatedInput(BACK, MOVIE_SELECTION_MAX);
}
void Menu::processMovieSelection(Database &db) {
	MovieSelection choice = static_cast<MovieSelection>(selection);
	switch (choice) {
		case LIST:
			db.listMovies();
			cout << "0. Go back to the main menu" << endl;
			Menu::inputChooseMovieFromList(db.getSize());
			Menu::processMovieChoiceFromList(db, selection - 1);
			selection = -1; //prevents from quitting completely
			break;
		case SEARCH:
			Menu::searchMoviesResults(db, db.searchMoviesResults(Menu::collectMovieSearchParameters()));
			Menu::inputSearchResults(db.getResultsSize());
			Menu::processSearchResults(db, selection - 1);
			selection = -1; //prevents from quitting completely
			break;
		case BACK:
			selection = -1; //prevents from quitting completely
			break;
		default:
			cout << "Something horrible has happened!" << endl;
	}
}
void Menu::inputChooseMovieFromList(int size) {
	selection = validatedInput(0, size);
}
void Menu::processMovieChoiceFromList(Database& db, int index) {
	while (selection != 0) {
		Clear();
		Menu::movieRoot(db.getMovies()[index]);
		Menu::inputMovieRoot();
		Menu::processMovieRoot(db.getMovies()[index], db);
	}
}
//search for a movie by string
string Menu::collectMovieSearchParameters() {
	cout << "Enter part of the movie you're looking for (case-sensitive): ";
	return GetString();
}
void Menu::searchMoviesResults(Database& db, bool found) {
	while (!found) {
		cout << "-----NO RESULTS FOUND, TRY AGAIN-----" << endl;
		found = db.searchMoviesResults(Menu::collectMovieSearchParameters());
	}
	cout << "-----Here's a list of movies that match your request-----" << endl;
	for (int loop_count = 0; loop_count < db.getResultsSize(); loop_count++) {
		cout << loop_count + 1 << ". " << db.getResults()[loop_count].getTitle() << endl;
	}
	cout << "0. Go back to the main menu" << endl;
}

//choose what to do with the movie
void Menu::movieRoot(Movie &movie) {
	cout << "What would you like to do?" << endl;
	cout << PLAY << ". Play " << movie.getTitle() << endl;
	cout << INFO << ". See detailed info about " << movie.getTitle() << endl;
	cout << METADATA << ". Edit metadata" << endl;
	cout << SIMILAR_TAGS << ". View movies similar to " << movie.getTitle() << endl;
	cout << BACK_FROM_MOVIE_ROOT << ". Go back to the main menu" << endl;
}
void Menu::inputMovieRoot() {
	selection = validatedInput(BACK_FROM_MOVIE_ROOT, MOVIE_ROOT_MAX);
}
void Menu::processMovieRoot(Movie &movie, Database &db) {
	MovieRoot choice = static_cast<MovieRoot>(selection);
	switch (choice) {
		case PLAY:
			movie.playMovie();
			break;
		case INFO:
			cout << movie;
			Pause();
			break;
		case METADATA:
			while (selection != 0) {
				Clear();
				cout << movie;
				Menu::editMetadata();
				Menu::inputEditMetadata();
				Menu::processEditMetadata(movie);
			}
			selection = -1; //prevents from quitting completely
			break;
		case SIMILAR_TAGS:
			UnderConstruction();
			/*
			if (!db.searchMetaResults(movie.getTags(), movie.getTagSize())) {
				cout << "-----There aren't any movies similar to " << movie.getTitle() << "-----" << endl;
			}
			else {
				cout << "-----Here's a list of movies similar to " << movie.getTitle() << "-----" << endl;
				for (int loop_count = 0; loop_count < db.getResultsSize(); loop_count++) {
					cout << loop_count + 1 << ". " << db.getResults()[loop_count].getTitle() << endl;
				}
			}
			Pause();
			*/
			break;
		case BACK_FROM_MOVIE_ROOT:
			break;
		default:
			cout << "Something horrible has happened!" << endl;
	}
}

//edit metadata menu
void Menu::editMetadata() {
	cout << "What would you like to edit?" << endl;
	cout << YEAR << ". Year" << endl;
	cout << RUNTIME << ". Runtime" << endl;
	cout << DISTRIBUTEDBY << ". Distributed By" << endl;
	cout << TAGS << ". Tags" << endl;
	cout << BACK_FROM_EDIT_METADATA << ". Cancel Edit" << endl;
}
void Menu::inputEditMetadata() {
	selection = validatedInput(BACK_FROM_EDIT_METADATA, EDIT_METADATA_MAX);
}
void Menu::processEditMetadata(Movie& movie) {
	EditMetadata choice = static_cast<EditMetadata>(selection);
	switch (choice) {
		case YEAR:
			cout << "Enter a year: ";
			movie.setYear();
			break;
		case RUNTIME:
			cout << "Enter the runtime: ";
			movie.setRuntime();
			break;
		case DISTRIBUTEDBY:
			movie.setDistributedBy();
			break;
		case TAGS:
			movie.setTags();
			break;
		case BACK_FROM_EDIT_METADATA:
			break;
		default:
			cout << "Something horrible has happened!" << endl;
	}
}

int Menu::lastSelection() const {
	return selection;
}

//helper functions
int validatedInput(int min, int max) {
	int number = GetInt();
	while (number < min || number > max) {
		cout << "Incorrect entry!" << endl;
		number = GetInt();
	}
	return number;
}