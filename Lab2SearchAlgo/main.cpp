#include <iostream>
#include <fstream>
#include <cstdlib>
#include "HashMap.hpp"
#include "IDictionary.hpp"
#include "HashMapIterator.hpp"
#include "CachedSequence.hpp"
//#include "../../Lab3_Tests/Person.hpp"

#define FIRST_NAMES_COUNT 5162
#define LAST_NAMES_COUNT 8879

#define TEST_SAMPLE_SIZE 30000
#define TEST_CACHE_SIZE 50

#define TEST_FREQUENT_COUNT 5
#define TEST_FREQUENT_PERCENT 80

#define TEST_QUERIES_COUNT 5000
typedef unsigned long long ID_t;

class Person {
private:
	ID_t id;
	string firstName;
	string midName;
	string lastName;
	int age;
public:
	Person();
	Person(string firstname, string lastname, int age_, ID_t id_ = time(nullptr));
	Person(string firstname, string midname, string lastname, int age_, ID_t id_ = time(nullptr));
public:
	ID_t GetID();
	string GetFirstName();
	string GetMiddleName();
	string GetLastName();
	void SetFirstName(string firstname);
	void SetMiddleName(string midname);
	void SetLastName(string lastname);
	void SetID(ID_t id_);
	int GetAge();
	void SetAge(int age);

};
Person::Person() :
	id(time(nullptr)),
	firstName(""),
	midName(""),
	lastName(""),
	age(0)
{}
Person::Person(string firstname, string lastname, int age_, ID_t id_) :
	id(id_),
	firstName(firstname),
	midName(""),
	lastName(lastname),
	age(age_)
{}
Person::Person(string firstname, string midname, string lastname, int age_, ID_t id_) :
	Person(firstname, lastname, age_, id_)
{
	midName = midname;
}
ID_t Person::GetID()
{
	return id;
}
string Person::GetFirstName()
{
	return firstName;
}
string Person::GetMiddleName()
{
	return midName;
}
string Person::GetLastName()
{
	return lastName;
}
void Person::SetFirstName(string firstname)
{
	firstName = firstname;
}
void Person::SetMiddleName(string midname)
{
	midName = midname;
}
void Person::SetLastName(string lastname)
{
	lastName = lastname;
}
void Person::SetID(ID_t id_)
{
	id = id_;
}
int Person::GetAge()
{
	return age;
}
void Person::SetAge(int age_)
{
	if (age_ < 0)
		throw std::invalid_argument("Age cannot be negative!");
	else
		age = age_;
}


int main()
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
	for (int i = 0; i < TEST_SAMPLE_SIZE; i++)
	{
		inFirst >> firstname;
		inLast >> lastname;
		std::cout << firstname;
		std::cout << lastname;
		seq->Add(i, new Person(firstname, lastname, rand() % 100, i));
	}

	inFirst.close();
	inLast.close();

	Person* gotten;

	ArraySequence<int>* FAQ = new ArraySequence<int>();

	for (int i = 0; i < TEST_FREQUENT_COUNT; i++)
	{
		FAQ->Append(rand() % TEST_SAMPLE_SIZE);
	}

	for (int i = 0; i < TEST_QUERIES_COUNT; i++)
	{
		if (rand() % 100 < TEST_FREQUENT_PERCENT)
		{
			//From FAQ
			gotten = seq->Get(FAQ->Get(rand() % TEST_FREQUENT_COUNT));
		}
		else
		{
			//Random
			gotten = seq->Get(rand() % TEST_SAMPLE_SIZE);
		}
		std::cout << gotten->GetLastName() << ' ';
	}


}
