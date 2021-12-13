#pragma once
#include <iostream>
#include <conio.h>
#include <windows.h>
#include <cstdlib>
#include <string>

using namespace std;
HANDLE console = GetStdHandle(STD_OUTPUT_HANDLE); // used for goto
COORD CursorPosition; // used for goto

class UI {

public:
	static void welcome();
	static void gotoXY(int x, int y);
	static void clear(int x, int y);
	//static void print();
	static int Selector(std::string name_selector, int count_options, std::string* options, int x, int y);
	static int InputNumber(string answer);
	static int* MultiInputNumber(string* answers, int count, int* ns);
	static string* MultiInputString(string* answers, int count, string* ns);
	static string InputString(string answer);
};



void UI::welcome() {
	cout << R"(
						 _          _    ____
						| |    __ _| |__|___ \
						| |   / _` | '_ \ __) |
						| |__| (_| | |_) / __/
						|_____\__,_|_.__/_____|
	)";
}
void UI::gotoXY(int x, int y) {
	CursorPosition.X = x;
	CursorPosition.Y = y;
	SetConsoleCursorPosition(console, CursorPosition);
}
void UI::clear(int x, int y) {
	COORD topLeft = { x, y };
	CONSOLE_SCREEN_BUFFER_INFO screen;
	DWORD written;

	GetConsoleScreenBufferInfo(console, &screen);
	FillConsoleOutputCharacterA(
		console, ' ', screen.dwSize.X * screen.dwSize.Y, topLeft, &written
	);
	FillConsoleOutputAttribute(
		console, FOREGROUND_GREEN | FOREGROUND_RED | FOREGROUND_BLUE,
		screen.dwSize.X * screen.dwSize.Y, topLeft, &written
	);
	SetConsoleCursorPosition(console, topLeft);
}
int UI::Selector(std::string name_selector, int count_options, std::string* options, int x, int y) {
	int menu_item = 0, run, option = y + 2;
	bool running = true;

	// x0 = 18; y0 = 5
	gotoXY(x, y); cout << name_selector;
	SetConsoleTextAttribute(console, 12);
	gotoXY(x, option); cout << "->";
	SetConsoleTextAttribute(console, 15);

	while (running)
	{
		for (size_t i = 0; i < count_options; i++)
		{
			gotoXY(x + 2, y + 2 + i);  cout << i + 1 << ". "<< options[i];

		}

		system("pause>nul"); // the >nul bit causes it the print no message


		if (GetAsyncKeyState(VK_DOWN) && option != y + count_options + 1) //down button pressed
		{
			gotoXY(x, option); cout << "  ";
			option++;
			SetConsoleTextAttribute(console, 12);
			gotoXY(x, option); cout << "->";
			SetConsoleTextAttribute(console, 15);
			menu_item++;
			continue;

		}

		if (GetAsyncKeyState(VK_UP) && option != y + 2) //up button pressed
		{
			gotoXY(x, option); cout << "  ";
			option--;
			SetConsoleTextAttribute(console, 12);
			gotoXY(x, option); cout << "->";
			SetConsoleTextAttribute(console, 15);
			menu_item--;
			continue;
		}

		if (GetAsyncKeyState(VK_RETURN)) { // Enter key pressed
			return menu_item;
			/*switch (menu_item) {

			case 0: {

				gotoXY(x + 2, y + 11);
				cout << "You chose Input...     ";
				return 0;
				break;
			}


			case 1: {
				gotoXY(x + 2, y + 11);
				cout << "You chose Output...     ";
				return 1;
				break;
			}

			case 2: {
				gotoXY(x + 2, y + 11);
				cout << "You chose Option 3...     ";
				return 2;
				break;
			}

			case 3: {
				gotoXY(x + 2, y + 11);
				cout << "You chose Option 4...     ";
				return 3;
				break;
			}

			case 4: {
				gotoXY(x + 2, y + 11);
				cout << "The program has now terminated!!";
				return 4;
				running = false;
			}

			}*/
		}

	}
	gotoXY(x + 2, y + 16);
}
int UI::InputNumber(string answer) {
	int n;
	cout << "\n-------------- " << answer << " -------------\n";
	cout << "> ";
	cin >> n;
	cout << "\n---------------------------------------------\n";
	return n;
}
int* UI::MultiInputNumber(string* answers, int count, int* ns) {
	cout << "\n---------------------------------------------\n";
	for (size_t i = 0; i < count; i++){
		cout << answers[i] << "\n";
		cout << "> ";
		cin >> ns[i];
		cout << "\n";
	}
	cout << "\n---------------------------------------------\n";
	return ns;
}
string* UI::MultiInputString(string* answers, int count, string* ns) {
	cout << "\n---------------------------------------------\n";
	for (size_t i = 0; i < count; i++){
		cout << answers[i] << "\n";
		cout << "> ";
		cin >> ns[i];
		cout << "\n";
	}
	cout << "\n---------------------------------------------\n";
	return ns;
}
string UI::InputString(string answer) {
	string n;
	cout << "\n-------------- "<< answer << " --------------\n";
	cout << "> ";
	cin >> n;
	cout << "\n---------------------------------------------\n";
	return n;
}