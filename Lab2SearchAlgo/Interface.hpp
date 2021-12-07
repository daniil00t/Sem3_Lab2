#pragma once
#include "UI.hpp"
#include "SparseMatrix.hpp"
#include "IMatrix.hpp"
#include <string>

#define STOP 3
#define DEFAULT_X 5
#define DEFAULT_Y 7


class Interface {
private:
	static int SparseMatrixInterface();
	static int loop();
public:
	static int start();

};


int Interface::SparseMatrixInterface() {
	int choice = -1;


	// default
	
	string types_options[] = { "int", "string" };
	int choice_type = UI::Selector("Select type", 2, types_options, DEFAULT_X, DEFAULT_Y);
	
	UI::clear(0, 0);

	int width, height;
	width = UI::InputNumber("Input width");
	UI::clear(0, 0);
	height = UI::InputNumber("Input height");

	while (choice != 2) {
		Matrix<int> M(width, height);
		SparseMatrix<int> SM(M, 0);


		string options[] = { "Add element", "Print Matrix", "return back" };
		choice = UI::Selector("Select Type of Data", 2, options, 5, 7);
		UI::clear(0, 0);
		int* adders = new int[3];
		string questions[] = { "Element: ", "x position: ", "y position" };

		switch (choice) {
		case 0:
			UI::MultiInputNumber(questions, 3, adders);
			cout << "--------------------------------------" <<adders[0] << adders[1] << adders[2] << "\n";
			SM.set(adders[0], adders[1], adders[2]);
			break;
		case 1:
			cout << SM.getData();
			break;

		default:
			return 0;
		}
	}
}

int Interface::loop() {
	int main_choice = -1;
	UI::welcome();


	while (main_choice != STOP) {
		string main_options[] = { "Dictionary", "Cache", "Sparse Matrix", "Exit" };
		main_choice = UI::Selector("Select Type of Data", 4, main_options, 5, 7);
		UI::clear(1, 7);
		switch (main_choice) {
		case 0:
		case 1:
		case 3:
			Interface::SparseMatrixInterface();
			break;

		}
	}

	return 0;
}

int Interface::start() {
	return Interface::loop();
}