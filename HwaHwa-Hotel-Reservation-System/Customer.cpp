#include "Customer.h"
#include "Menu.h"
#include "ReservationHistory.h"

Customer::Customer()
{
    //ctor
    this->cusMenu();
}

Customer::~Customer()
{
    //dtor
}

void Customer::cusMenu() {
    system("cls");

    cout << "\n\n\n\n\n\n\n\n";

    cout << setw(45);
    for (int i = 0; i < 33; i++)
    {
        Sleep(5);
        cout << "*";
    }

    cout << endl << setw(68) << "Customer Action\n\n";
    cout << setw(69) << "1. Make Reservation\n\n";
    cout << setw(79) << "2. Search Reservation History\n\n";
    cout << setw(57) << "3. Back\n\n";

    cout << setw(45);
    for (int i = 0; i < 33; i++)
    {
        Sleep(5);
        cout << "*";
    }

    unsigned char opt = 0;
    int current = 1;

    cout << endl << setw(60) << "> 1";


    while ((opt = _getch()) != RETURN) {

        if (opt == 72) // move up
        {
            if (current > 1) {
                cout << "\b \b";
                cout << --current;
            }
        }
        else if (opt == 80) // move up
        {
            if (current < 3) {
                cout << "\b \b";
                cout << ++current;
            }
        }

        fflush(stdin);
    }

    cusAction(current);
}

void Customer::cusAction(int opt) {

    if (opt == 1)
    {
        Reservation* reservations = new Reservation[100];
        Reservation::customerReservationScreen(reservations, 0);
    }
    else if (opt == 2)
    {
        ReservationHistory::custSearchMenu();
    }
    else if (opt == 3)
    {
        Menu::userAction(Menu::selectUser());
    }
}