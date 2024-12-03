#include "Menu.h"
#include "Admin.h"
#include "Customer.h"

using namespace std;

Menu::Menu()
{
    cout << "\n\n\n\n\n";
    cout << setw(30);
    for (int i = 0; i < 60; i++)
    {
        Sleep(3);
        cout << "*";
    }

    cout << "\n\n" << setw(83) << "Welcome to Hwa Hwa Hotel Reservation System\n\n";
    cout << setw(65) << "Presented By\n\n";

    cout << setw(78) << "1. CHAI YI JING (S1G1) - B032310827\n\n";
    cout << setw(78) << "2. LIM ZHI YING (S1G2) - B032310439\n\n";
    cout << setw(77) << "3. HO XIN YONG (S1G1) - B032310518\n\n";
    cout << setw(88) << "4. STEPHEN SIM SHAN SIONG (S1G1) - B032220027\n\n";


    cout << setw(30) << endl;
    for (int i = 0; i < 60; i++)
    {
        Sleep(3);
        cout << "*";
    }

    cout << "\n\n\n\n\t\t\t\t\t     ";

    system("pause");

    this->userAction(this->selectUser());
}

Menu::~Menu()
{
    //dtor
}

int Menu::selectUser()
{
    system("cls");
    cout << "\n\n\n\n\n\n\n\n";

    cout << setw(45);
    for (int i = 0; i < 33; i++)
    {
        Sleep(5);
        cout << "*";
    }

    cout << endl << setw(69) << "The User Menu\n\n";
    cout << setw(68) << "1. Admin Login\n\n";
    cout << setw(77) << "2. Customer Reservation\n\n";
    cout << setw(61) << "3. Exit\n\n";

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

    return current;
}

void Menu::exitPage() {
    system("cls");
    cout << "\n\n\n\n\n\n\n\n\n\n";
    cout << endl << setw(80) << "Thank You for Using Our System ! ! !";
    cout << "\n\n\n\n\t\t\t\t\t     ";
    system("pause");
    system("cls");
}

void Menu::userAction(int opt) {
    system("cls");

    if (opt == 1)
    {
        Admin::adminLogin();
    }
    else if (opt == 2)
    {
        Customer::cusMenu();
    }
    else if (opt == 3)
    {
        Menu::exitPage();
    }
}
