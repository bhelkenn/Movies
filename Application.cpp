#include "Application.h"

Application::Application() {
	path = "M:\\Movies\\Movies";
}

void Application::prompt_loop() {
	menu.showRoot();
	menu.inputPromptRoot();
	menu.processRoot(db);
}

bool Application::is_running() {
	return menu.lastSelection() != 0;
}

void Application::welcomeMessage() {
	cout << "Welcome to the Movies application, by Brady Helkenn!" << endl;
}
void Application::updateFolderList() {
	WIN32_FIND_DATA findfiledata;
	HANDLE hFind = INVALID_HANDLE_VALUE;
	
	char fullpath[MAX_PATH];
	GetFullPathName(path.c_str(), MAX_PATH, fullpath, 0);
	string fp(fullpath);
	
	//clears out . and ..
	hFind = FindFirstFile((LPCTSTR)(fp + "\\*").c_str(), &findfiledata);
	FindNextFile(hFind, &findfiledata);
	
	string lastResult = "";
	ofstream file;
	string location = path + "\\MOVIELIST";
	file.open(location.c_str(), ios::trunc | ios::out);
	while (FindNextFile(hFind, &findfiledata) != 0) {
		string fileName = findfiledata.cFileName;
		if (fileName.find("MOVIELIST") != string::npos) {
			FindNextFile(hFind, &findfiledata);
		}
		if (lastResult != findfiledata.cFileName) {
			file << findfiledata.cFileName << endl;
			lastResult = findfiledata.cFileName;
		}
	}
	file.close();
}

void Application::loadDatabase() {
	cout << "Loading movie database..." << endl;
	ifstream file;
  file >> db;
	
	for (int loop_count = 0; loop_count < db.getSize(); loop_count++) {
		file >> db.getMovies()[loop_count];
	}
	
	cout << "Movie database loaded!" << endl;
}