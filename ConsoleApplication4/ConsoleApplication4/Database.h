/*                                        Database Header.
Commands:
		 Add year-month(1-12)-day(1-31) event(string) - Adds event to the database.
		 Del year-month(1-12)-day(1-31) event(string) - Delets event on the target date.
		 Del year-month(1-12)-day(1-31) - Delets all events on this date.
		 Print - Prints all date-event pairs.
		 Find year-month(1-12)-day(1-31) - Prints all events of the target date.
											Made by Andrei Mudrov.
											*/

#pragma once
#include "stdafx.h"
#include <string>
#include <map>
#include <vector>
#include <algorithm>
#include <stdio.h>
#include <iostream>
#include <sstream>
#include <iomanip>
#include <iostream>
#include <exception>
#include <set>
#include <fstream>



using namespace std;

struct Date
{
	Date(int _year, int _month, int _day)
	{
		year = _year;
		month = _month;
		day = _day;
	}
	Date()
	{
		year = 0;
		month = 0;
		day = 0;
	}
	int year;
	int month;
	int day;
};
bool operator< (const Date& lhs, const Date rhs) {
	bool result = 0;
	if (lhs.year < rhs.year)
	{
		result = 1;
	}
	else if (lhs.year == rhs.year)
	{
		if (lhs.month < rhs.month)
		{
			result = 1;
		}
		else if (lhs.month == rhs.month)
		{
			if (lhs.day < rhs.day)
			{
				result = 1;
			}

		}
	}
	return result;
}
bool operator> (const Date& lhs, const Date rhs) {
	bool result = 0;
	if (lhs.year > rhs.year)
	{
		result = 1;
	}
	else if (lhs.year == rhs.year)
	{
		if (lhs.month > rhs.month)
		{
			result = 1;
		}
		else if (lhs.month == rhs.month)
		{
			if (lhs.day > rhs.day)
			{
				result = 1;
			}

		}
	}
	return result;
}
bool operator == (const Date& lhs, const Date rhs) {
	bool result = 0;
	if (lhs.year == rhs.year && lhs.month == rhs.month && lhs.day == rhs.day)
	{
		result = 1;
	}
	return result;
}
ostream& operator<< (ostream& stream, const Date& date)
{
	stream << setfill('0');
	stream << setw(4) << date.year << '-' << setw(2) << date.month << '-' << setw(2) << date.day;
	return stream;
}
void EnsureMonth(int value)
{
	if (value > 12 || value < 1)
	{
		cout << "Month value is invalid:" << value << endl;
		throw exception();
	}
}
void EnsureDay(int value)
{
	if (value > 31 || value < 1)
	{
		cout << "Day value is invalid:" << value << endl;
		throw exception();
	}
}
void EnsureNextSymbolAndSkip(istream& stream, char c, const Date& date)
{
	if (stream.peek() != c)
	{
		cout << "Wrong date format :" << date << endl;
		throw exception();
	}
	stream.ignore(1);
}
istream& operator>> (istream& stream, Date& date)
{
	stream >> date.year;
	EnsureNextSymbolAndSkip(stream, '-', date);
	stream >> date.month;
	EnsureMonth(date.month);
	EnsureNextSymbolAndSkip(stream, '-', date);
	stream >> date.day;
	EnsureDay(date.day);
	return stream;
}
class Database
{
public:
	void Do()
	{
		string command;
		Date date;
		string _event;
		GetConsole(command);
		FindCommand(command, date, _event);
	}
	void GetConsole(string& command)
	{
		system("color 02");
		cin >> command;
		system("color 01");
	}
	void FindCommand(string& command, Date& date, string _event)
	{

		if (command == "Add")
		{
			cin >> date >> _event;
			AddDate(date, _event);
		}
		else if (command == "Del")
		{
			cin >> date;
			if (char(cin.peek()) == '\n')
			{
				DeleteDate(date);
			}
			else
			{
				cin >> _event;
				DeleteEvent(date, _event);
			}

		}
		else if (command == "Find")
		{
			cin >> date;
			FindEvent(date);
		}
		else if (command == "Print")
		{
			PrintAll();
		}
		else
		{
			cout << "Unknown command :" << command << endl;
		}

	}
	void AddDate(Date& date, string&_event)
	{
		bool New = true;
		for (const auto& v : database[date])
		{
			if (v == _event)
			{
				New = false;

			}
		}
		if (New)
		{
			database.at(date).insert(_event);
		}
	}
	void DeleteEvent(Date& date, string _event)
	{
		if (database.at(date).find(_event) == database.at(date).end() || database.at(date).empty())
		{
			cout << "Event not found" << endl;
		}
		else
		{
			database.at(date).erase(_event);
			cout << "Deleted successfully" << endl;
		}
	}
	void DeleteDate(Date& date)
	{
		int size = database.at(date).size();
		database.at(date).clear();
		cout << "Deleted " << size << " events" << endl;
	}
	void FindEvent(const Date& date)
	{
		for (const auto& _event : database.at(date))
		{
			cout << _event << " ";
		}
		cout << endl;
	}
	void PrintAll()
	{
		for (const auto& item : database)
		{

			cout << item.first << " ";
			FindEvent(item.first);
		}
	}
	/*void SaveDataBase()
	{
	ofstream  Savefile;
	Savefile.open("Save.txt");
	for (auto item : database)
	{
	Savefile << item.first << "-";
	for (auto item_1 : item.second)
	{
	Savefile << item_1 << "-";
	}
	Savefile << "/";
	}
	Savefile.close();

	}
	void OpenDataBase()
	{

	ifstream Openfile;
	Openfile.open("Save.txt");
	system("pause");
	cout << test << endl;
	if (Openfile)
	{
	system("pause");
	Date date{};
	set <string> s;
	system("pause");
	while (Openfile.eof() == false)
	{
	if (Openfile.peek() != '9' || Openfile.peek() != '8' || Openfile.peek() != '7' || Openfile.peek() != '6' || Openfile.peek() != 5 || Openfile.peek() != 4 || Openfile.peek() != 3 || Openfile.peek() != 2 || Openfile.peek() != 1 || Openfile.peek() != 0 )
	{
	break;
	}
	Openfile >> date;
	Openfile.ignore(1);
	cout << date << endl;
	while (Openfile.peek() != '/')
	{
	string temp;
	Openfile >> temp;
	Openfile.ignore(1);
	s.insert(temp);
	}
	database[date] = s;
	}
	system("pause");
	}

	}*/
private:
	map<Date, set<string>> database;
};