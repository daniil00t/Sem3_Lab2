#pragma once
#include <string>
#include <ctime>
#include <stdexcept>

#include "../CachedSequence.hpp"
#include "Person.hpp"
#include "../ATD/DoubleLinkedList.h"

#include "../ATD/TestEnvironment.h"
#include "../ATD/TimedTest.h"

using std::string;

typedef unsigned long long ID_t;

class Person {
private:
	ID_t id;
	string firstName;
	string lastName;
	int age;
public:
	Person();
	Person(string firstname, string lastname, int age_, ID_t id_ = time(nullptr));
public:
	ID_t GetID();
	string GetFirstName();
	string GetLastName();
	void SetFirstName(string firstname);
	void SetLastName(string lastname);
	void SetID(ID_t id_);
	int GetAge();
	void SetAge(int age);
};



