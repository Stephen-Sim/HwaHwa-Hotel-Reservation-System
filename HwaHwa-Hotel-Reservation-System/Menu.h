#pragma once
#include <iostream>
#include <iomanip>
#include <windows.h>
#include <conio.h>

using namespace std;

#define RETURN 13

class Menu
{
public:
	Menu();
	virtual ~Menu();
	static int selectUser();
	static void exitPage();
	static void userAction(int);
};

