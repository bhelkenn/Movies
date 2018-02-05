#include "Flavor.h"
#include "Application.h"
using namespace std;

int main() {
	Application application;
	application.welcomeMessage();
	
	application.updateFolderList();
	
	application.loadDatabase();
	Pause();
	
	while (application.is_running()) {
		application.prompt_loop();
	}
	
  return 0;
}