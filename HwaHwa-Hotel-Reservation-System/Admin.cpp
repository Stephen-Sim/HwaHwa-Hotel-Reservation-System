#include "Admin.h"
#include "Menu.h"
#include "Reservation.h"
#include "ReservationHistory.h"

using namespace std;

Admin::Admin()
{
}

Admin::~Admin()
{
    //dtor
}

string Admin::getPass(bool show_asterisk = true)
{
    string password;
    unsigned char ch = 0;

    while ((ch = _getch()) != RETURN)
    {
        if (ch == BACKSPACE)
        {
            if (password.length() != 0)
            {
                if (show_asterisk)
                    cout << "\b \b";
                password.resize(password.length() - 1);
            }
        }
        else if (ch == 0 || ch == 224) // handle escape sequences
        {
            _getch(); // ignore non printable chars
            continue;
        }
        else
        {
            password += ch;
            if (show_asterisk)
                cout << '*';
        }
    }

    cout << endl;
    return password;
}

void Admin::adminMenu() {
    system("cls");

    cout << "\n\n\n\n\n\n\n\n";

    cout << setw(45);
    for (int i = 0; i < 33; i++)
    {
        Sleep(5);
        cout << "*";
    }

    cout << endl << setw(68) << "Admin Action\n\n";
    cout << setw(80) << "1. Display Reservation Detail\n\n";
    cout << setw(74) << "2. Search Customer Info\n\n";
    cout << setw(58) << "3. Back\n\n";

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

    adminAction(current);
}

void Admin::adminAction(int opt) {

    if (opt == 1)
    {
        ReservationHistory::displayReservationHistory();
    }
    else if (opt == 2)
    {
        vector<Reservation> reservations = ReservationHistory::getReservationHistoryFromFile();
        ReservationHistory::adminSearchMenu(reservations);
    }
    else if (opt == 3)
    {
        Menu::userAction(Menu::selectUser());
    }
}

void Admin::adminLogin() {
    system("cls");
    bool loginTrue = false;
    string username, pwd;
    cout << "\n\n\n\n\n\n";

    cout << endl << setw(82) << "Admin Sign In to Login In the System\n\n";
    cout << setw(45);

    for (int i = 0; i < 36; i++)
    {
        Sleep(5);
        cout << "=";
    }

    cout << "\n\n" << setw(66) << "Admin Login : ";
    getline(cin, username);

    cout << "\n" << setw(66) << "Password : ";
    pwd = Admin::getPass();

    cout << "\n\n" << setw(45);
    for (int i = 0; i < 36; i++)
    {
        Sleep(5);
        cout << "=";
    }

    if (username == ADMIN_USERNAME && pwd == ADMIN_PWD)
    {
        cout << "\n\n\n" << setw(74) << "Login Successfully !!!" << endl;
        loginTrue = true;
    }
    else {
        cout << "\n\n\n" << setw(71) << "Login Failed !!!" << endl;
    }

    fflush(stdin);
    cout << "\n\n\n\n\t\t\t\t\t     ";
    system("pause");
    system("cls");

    if (loginTrue)
    {
        Admin::adminMenu();
    }
    else
    {
        Menu::userAction(Menu::selectUser());
    }
}
