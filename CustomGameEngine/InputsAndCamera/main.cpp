#include <iostream>

#include "AppWindow.h"
int main()
{
	AppWindow::initialize();
	AppWindow* runningApp = (AppWindow*)AppWindow::getInstance();

	//std::cout << "Made app window" << std::endl;

	runningApp->initializeEngine();
	//std::cout << "Engine is initialized" << std::endl;

	while (runningApp->isRunning()) {
		//std::cout << "app is running" << std::endl;
		runningApp->broadcast();
	}
}