/* ConsoleApplication4.cpp : Database programm.
Commands:
		 Add year-month(1-12)-day(1-31) event(string) - Adds event to the database.
		 Del year-month(1-12)-day(1-31) event(string) - Delets event on the target date.
		 Del year-month(1-12)-day(1-31) - Delets all events on this date.
		 Print - Prints all date-event pairs.
		 Find year-month(1-12)-day(1-31) - Prints all events of the target date.


											Made by Andrei Mudrov.
*/

#include "stdafx.h"
#include <iostream>
#include <exception>
#include "Database.h"

int main()
{
	Database database;
	//database.OpenDataBase();
		try
		{
			while (true)
			{
				database.Do();
			}
		}
		catch (exception&)
		{
			cout<<" \n" << "ERROR: Please restart the programm." << endl;
			//database.SaveDataBase();
		}
		system("pause");
    return 0;
}