#include"Flavor.h"

//flavor functions
void Pause() {
	cout << "Press ENTER to continue...";
	char c[5];
	cin.getline(c, 5);
}
void Clear() {
	HANDLE						hStdOut;
	CONSOLE_SCREEN_BUFFER_INFO	csbi;
	DWORD						count;
	DWORD						cellCount;
	COORD						homeCoords = {0, 0};

	hStdOut = GetStdHandle(STD_OUTPUT_HANDLE);
	if (hStdOut == INVALID_HANDLE_VALUE) {return;}

	//Get the number of cells in the current buffer
	if (!GetConsoleScreenBufferInfo(hStdOut, &csbi)) {return;}
	cellCount = csbi.dwSize.X * csbi.dwSize.Y;

	//Fill the entire buffer with spaces
	if (!FillConsoleOutputCharacter(hStdOut, (TCHAR) ' ', cellCount, homeCoords, &count)) {return;}

	//Fill the entire buffer with the current colors and attributes
	if (!FillConsoleOutputAttribute(hStdOut, csbi.wAttributes, cellCount, homeCoords, &count)) {return;}

	//Move the cursor home
	SetConsoleCursorPosition(hStdOut, homeCoords);
}
int GetInt() {
	int num = 0;
	string input;
	while (true) {
		getline(cin, input);
		//convert from string to number safely.
		stringstream ss(input);
		if (ss >> num)
			return num;
		else
			cout << "Invalid entry, please try again: ";
	}
}
char GetChar() {
	string input;
	while (true) {
		getline(cin, input);
		//verifies there's just a single char
		if (input.length() == 1)
			return input[0];
		else
			cout << "Invalid entry, please try again: ";
	}
}
string GetString() {
	string input;
	getline(cin, input);
	return input;
}
void UnderConstruction() {
	cout << "Sorry, this feature is currently under construction and doesn't work properly yet." << endl;
	Pause();
}
bool IsInt(string input) {
	char *p;
	strtol(input.c_str(), &p, 10);
	return *p == 0;
}