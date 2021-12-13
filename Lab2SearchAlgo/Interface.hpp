#pragma once
#include "UI.hpp"
#include "SparseMatrix.hpp"
#include "CachedSequence.hpp"
#include "ATD/ArraySequence.h"
#include <fstream>
#include "IMatrix.hpp"
#include "../ATD/Person.hpp"
#include <string>

#define STOP 3
#define DEFAULT_X 5
#define DEFAULT_Y 7

#define TYPE_INT 0
#define TYPE_STRING 1

#define TEST_SAMPLE_SIZE 30000
#define TEST_CACHE_SIZE 50

#define TEST_FREQUENT_COUNT 5
#define TEST_FREQUENT_PERCENT 80

#define TEST_QUERIES_COUNT 5000


class Interface {
private:
	static int SparseMatrixInterface();
	static int HashMapInterface();
	static int CacheInterface();
	static int loop();
public:
	static int start();
};


int Interface::SparseMatrixInterface() {
	
	std::size_t width, height;
	width = (std::size_t)UI::InputNumber("Input width");
	UI::clear(0, 0);
	height = (std::size_t)UI::InputNumber("Input height");
	UI::clear(0, 0);

	string types_options[] = { "int", "string", "return back" };
	int choice_type = UI::Selector("Select type", 3, types_options, DEFAULT_X, DEFAULT_Y);
	
	UI::clear(0, 0);
	string options[] = { "Add element", "Get Element", "Map", "Print Matrix", "Return back" };


	switch (choice_type) {
	case TYPE_INT:
	{
		int choice = -1;
		SparseMatrix<int> SM(width, height, 0);
		while (choice != 5) {
			
			choice = UI::Selector("Select Action", 5, options, DEFAULT_X, DEFAULT_Y);
			UI::clear(0, 0);

			switch (choice) {
			case 0: {
				int* adders = new int[3];
				string questions[] = { "Element: ", "x position: ", "y position" };
				UI::MultiInputNumber(questions, 3, adders);
				SM.set((int)adders[0], (int)adders[1], (int)adders[2]);
				UI::clear(0, 0);
			}
				break;
			case 1:
			{
				UI::clear(0, 0);
				int x, y;
				x = UI::InputNumber("Input x position:");
				UI::clear(0, 0);
				y = UI::InputNumber("Input y position:");
				UI::clear(0, 0);
				cout << "Element: " << SM.get(x, y);
			}; break;
			case 2:
			{
				SM.map(
					[](int p) -> int {
						return p * 2;
					}
				);
				cout <<  "Complete!";
			}; break;
			case 3:
				UI::clear(0, 0);
				SM.print();
				break;
			case 4:
				return 0;

			default:
				return 0;
			}
		}

	}; break;
	case TYPE_STRING:
	{
		int choice = -1;
		SparseMatrix<string> SM(width, height, "");
		while (choice != 4) {
			choice = UI::Selector("Select Type of Data", 5, options, DEFAULT_X, DEFAULT_Y);
			UI::clear(0, 0);
			

			switch (choice) {
			case 0: {
				string element = UI::InputString("Input element(string)");
				UI::clear(0, 0);
				int x, y;
				x = UI::InputNumber("Input x position:");
				UI::clear(0, 0);
				y = UI::InputNumber("Input y position:");
				UI::clear(0, 0);
				SM.set(element, x, y);
				UI::clear(0, 0);
			}; break;
			case 1:
				UI::clear(0, 0);
				int x, y;
				x = UI::InputNumber("Input x position:");
				UI::clear(0, 0);
				y = UI::InputNumber("Input y position:");
				UI::clear(0, 0);
				cout << "Element: " << SM.get(x, y);
				break;
			case 2:
				SM.map(
					[](string p) -> string {
						return p + " Hello!";
					}
				);
				cout << "Complete!";
				break;
			case 3:
				UI::clear(0, 0);
				SM.print();
				break;
			default:
				return 0;
			}
		}

	}; break;
	default:
		return 0;
	}

	
}

int Interface::HashMapInterface() {
	
	std::size_t size;
	size = (std::size_t)UI::InputNumber("Input size of hash map");
	UI::clear(0, 0);

	string types_options[] = { "int", "string", "return back" };
	int choice_type = UI::Selector("Select type", 3, types_options, DEFAULT_X, DEFAULT_Y);
	
	UI::clear(0, 0);
	string options[] = { "Add element", "Get Element", "Map", "Print HashMap", "Return back" };


	switch (choice_type) {
	case TYPE_INT:
	{
		int choice = -1;
		HashMap<int, int>HM(
			[](int p, int tableSize)->int
			{
				return p % tableSize;
			}, size);

		while (choice != 5) {
			
			choice = UI::Selector("Select Action", 5, options, DEFAULT_X, DEFAULT_Y);
			UI::clear(0, 0);

			switch (choice) {
			case 0: {
				int* adders = new int[2];
				string questions[] = { "Element: ", "index: " };
				UI::MultiInputNumber(questions, 2, adders);
				HM.Add((int)adders[1], (int)adders[0]);
				UI::clear(0, 0);
			}
				break;
			case 1:
			{
				UI::clear(0, 0);
				int index;
				index = UI::InputNumber("Input index element: ");
				UI::clear(0, 0);
				cout << "Element: " << HM.Get(index);
			}; break;
			case 2:
			{
				std::function mult = [](int p) -> int { return p * 2; };
				HashMapIterator it = HM.Iterator();
				for (; it != HM.End(); ++it)
				{
					HM.Add((*it).first, mult((*it).second));
				}
				cout << "Complete!";
			}; break;
			case 3:
				UI::clear(0, 0);
				cout << HM;
				break;
			default:
				return 0;
			}
		}

	}; break;
	case TYPE_STRING:
	{
		int choice = -1;
		HashMap<int, string>HM(
			[](int p, int tableSize)->int
			{
				return p % tableSize;
			}, size);

		while (choice != 5) {

			choice = UI::Selector("Select Action", 5, options, DEFAULT_X, DEFAULT_Y);
			UI::clear(0, 0);

			switch (choice) {
			case 0: {
				string el = UI::InputString("Input element: ");
				UI::clear(0, 0);
				int index = UI::InputNumber("Input index: ");
				UI::clear(0, 0);
				
				HM.Add(index, el);
				UI::clear(0, 0);
			}
				  break;
			case 1:
			{
				UI::clear(0, 0);
				int index;
				index = UI::InputNumber("Input index element: ");
				UI::clear(0, 0);
				cout << "Element: " << HM.Get(index);
			}; break;
			case 2:
			{
				std::function mult = [](string p) -> string { return p + " hello"; };
				HashMapIterator it = HM.Iterator();
				for (; it != HM.End(); ++it)
				{
					HM.Add((*it).first, mult((*it).second));
				}
				cout << "Complete!";
			}; break;
			case 3:
				UI::clear(0, 0);
				cout << HM;
				break;
			default:
				return 0;
			}
		}

	}; break;
	default:
		return 0;
	}

	
}

int Interface::CacheInterface() {
	

	string mod_options[] = { "test", "return back" };
	int mod_type = UI::Selector("Select type", 2, mod_options, DEFAULT_X, DEFAULT_Y);
	
	UI::clear(0, 0);
	switch (mod_type) {
	case 0:
	{
		CachedSequence<int, Person*>* seq = new CachedSequence<int, Person*>(
			[](int id, int tableSize)->int
			{
				return id % tableSize;
			},
			TEST_CACHE_SIZE);

		Person* p;
		std::ifstream inFirst("../Lab3_Tests/data/firstnames.txt", /*std::ios::binary|*/std::ios::in);
		std::ifstream inLast("../Lab3_Tests/data/us.txt", /*std::ios::binary|*/std::ios::in);

		string firstname;
		string lastname;
		for (int i = 0; i < TEST_SAMPLE_SIZE; i++) {
			inFirst >> firstname;
			inLast >> lastname;
			try {
				seq->Add(i, new Person(firstname, lastname, rand() % TEST_SAMPLE_SIZE, i));
			}
			catch (const std::exception&) { }

		}

		inFirst.close();
		inLast.close();

		Person* gotten;
		UI::gotoXY(0, 15);
		ArraySequence<int>* FAQ = new ArraySequence<int>();
		cout << "Output FAQ queries: " << endl;
		for (int i = 0; i < TEST_FREQUENT_COUNT; i++) {
			try {
				FAQ->Append(rand() % TEST_SAMPLE_SIZE);
			}
			catch (const std::exception&) { }
		}

		for (int i = 0; i < TEST_QUERIES_COUNT; i++) {
			if (rand() % 100 < TEST_FREQUENT_PERCENT) {
				//From FAQ

				try {
					gotten = seq->Get(FAQ->Get(rand() % TEST_FREQUENT_COUNT));
				}
				catch (const std::exception&) {  }
			}
			else {
				try {
					//Random - because exception -> key_not_found
					gotten = seq->Get(rand() % TEST_SAMPLE_SIZE);
					std::cout << gotten->GetLastName() << ' ';
				}
				catch (const std::exception&) {  }
			}
		}

	}; break;
	default:
		return 0;
	}

}

int Interface::loop() {
	int main_choice = -1;
	UI::welcome();


	while (main_choice != STOP) {
		string main_options[] = { "HashMap", "Cache", "Sparse Matrix", "Exit" };
		main_choice = UI::Selector("Select Type of Data", 4, main_options, DEFAULT_X, DEFAULT_Y);
		UI::clear(0, 0);
		switch (main_choice) {
		case 0:
			Interface::HashMapInterface();
			break;
		case 1:
			Interface::CacheInterface();
			break;
		case 2:
			Interface::SparseMatrixInterface();
			break;
		default:
			return 0;

		}
	}
}

int Interface::start() {
	return Interface::loop();
}