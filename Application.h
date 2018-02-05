#ifndef __APPLICATION_H__
#define __APPLICATION_H__
#include <windows.h>
#include <iostream>
#include "Database.h"
#include "Menu.h"
#include "Flavor.h"

class Application {
private:
	string path;
	Database db;
	Menu menu;
public:
	Application();
	void prompt_loop();
	bool is_running();
	void welcomeMessage();
	void updateFolderList();
	void loadDatabase();
};

#endif