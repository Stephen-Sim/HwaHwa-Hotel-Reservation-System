#pragma once

#include <iostream>
#include <string>
#include <cstdlib>
#include <iomanip>
#include <string>
#include <fstream>
#include <conio.h>
#include <windows.h>

using namespace std;

#define RETURN 13
#define BACKSPACE 8

#define ADMIN_USERNAME "admin"
#define ADMIN_PWD "abc123"


class Admin
{
public:
    Admin();
    virtual ~Admin();
    static string getPass(bool);
    static void adminAction(int);
    static void adminMenu();
    static void adminLogin();
protected:

private:
};

