#ifndef __MENU_H__
#define __MENU_H__
#include "Flavor.h"
#include "Database.h"

class Menu {
private:
	int selection;
public:
	Menu();
	
	//root menu
	void showRoot();
	void inputPromptRoot();
	void processRoot(Database&);
	
	//used for both metadata and title searches
	void inputSearchResults(int);
	void processSearchResults(Database&, int);
	
	//search for a movie by metadata string
	string collectMetaSearchParamaters();
	void searchMetaResults(Database&, bool);
	
	//select a movie section
	void movieSelection();
	void inputPromptMovieSelection();
	void processMovieSelection(Database&);
	void inputChooseMovieFromList(int);
	void processMovieChoiceFromList(Database&, int);
	//search for a movie by string
	string collectMovieSearchParameters();
	void searchMoviesResults(Database&, bool);
	
	//choose what to do with the movie
	void movieRoot(Movie&);
	void inputMovieRoot();
	void processMovieRoot(Movie&, Database&);
	
	//edit metadata menu
	void editMetadata();
	void inputEditMetadata();
	void processEditMetadata(Movie&);
	
	int lastSelection() const;
};

//helper functions
int validatedInput(int, int);

#endif