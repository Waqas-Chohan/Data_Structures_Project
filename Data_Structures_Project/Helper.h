#pragma once
#include <string>
class Helper
{
public:
	void load();
	void FullScreen();
	void DisplayInBox(const std::string& message, int spacing = 2, char border = '-');
	int read_input(int start, int end);
	void zoomConsoleScreen(int percent);
	void printMiniInstagram();
};


