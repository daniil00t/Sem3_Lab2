#pragma once
#include <string>
#include <ctime>

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

Person::Person() :
	id(time(nullptr)),
	firstName(""),
	lastName(""),
	age(0)
{}

Person::Person(string firstname, string lastname, int age_, ID_t id_) :
	id(id_),
	firstName(firstname),
	lastName(lastname),
	age(age_)
{}

ID_t Person::GetID()
{
	return id;
}
string Person::GetFirstName()
{
	return firstName;
}

string Person::GetLastName()
{
	return lastName;
}
void Person::SetFirstName(string firstname)
{
	firstName = firstname;
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

