#pragma once

#include <iostream>
#include <cstdlib>
#include <iomanip>
#include <string>
#include <fstream>
#include <conio.h>
#include <windows.h>
#include <vector>
#include "Reservation.h"

#define RETURN 13
#define BACKSPACE 8

using namespace std;

class Customer
{
public:
    Customer();
    virtual ~Customer();
    static void cusAction(int);
    static void cusMenu();
protected:

private:
};

