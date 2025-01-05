#include "Reservation.h"
#include "Customer.h"
#include "ReservationHistory.h"

Reservation::Reservation()
{
}

Reservation::Reservation(string bookingId, string username, int number_of_people, int number_of_nights,
    int meal_type, bool car_parking_required, int room_type, string date, double total_price)
{
    this->bookingId = bookingId;
    this->username = username;
    this->number_of_people = number_of_people;
    this->number_of_nights = number_of_nights;
    this->meal_type = meal_type;
    this->car_parking_required = car_parking_required;
    this->room_type = room_type;
    this->date = date;
    this->total_price = total_price;
}

void Reservation::customerReservationScreen(Reservation reservations[], int size)
{
    cout << fixed;
    system("cls");
    unsigned char opt = 0;
    int current = 1;

    cout << "\n\t\t\t\t\t\t\t 1. Add Reservation\t\t2. Confirm Reservation\t\t3. Back" << endl;

    if (size != 0)
    {
        cout << "\n\t\t" << setfill('-') << setw(149) << "\n";
        cout << "\t\t|" << setfill(' ') << setw(5) << "Bil" << " |";
        cout << setfill(' ') << setw(15) << "Booking ID" << " |";
        cout << setfill(' ') << setw(20) << "Username" << " |";
        cout << setfill(' ') << setw(8) << "People" << " |";
        cout << setfill(' ') << setw(10) << "Nights" << " |";
        cout << setfill(' ') << setw(15) << "Meal Type" << " |";
        cout << setfill(' ') << setw(10) << "Parking" << " |";
        cout << setfill(' ') << setw(20) << "Room Type" << " |";
        cout << setfill(' ') << setw(12) << "Date" << " |";
        cout << setfill(' ') << setw(12) << "Total Price" << " |";
        cout << "\n\t\t" << setfill('-') << setw(149) << "\n";

        double sum = 0;

        for (int i = 0; i < size; i++)
        {
            cout << "\t\t|" << setfill(' ') << setw(5) << i + 1 << " |";
            cout << setfill(' ') << setw(15) << reservations[i].getBookingId() << " |";
            cout << setfill(' ') << setw(20) << reservations[i].getUsername() << " |";
            cout << setfill(' ') << setw(8) << reservations[i].getNumberOfPeople() << " |";
            cout << setfill(' ') << setw(10) << reservations[i].getNumberOfNights() << " |";
            cout << setfill(' ') << setw(15) << reservations[i].getMealTypeValue() << " |";
            cout << setfill(' ') << setw(10) << (reservations[i].isCarParkingRequired() ? "Yes" : "No") << " |";
            cout << setfill(' ') << setw(20) << reservations[i].getRoomTypeValue() << " |";
            cout << setfill(' ') << setw(12) << reservations[i].getDate() << " |";
            cout << setfill(' ') << setw(12) << setprecision(2) << reservations[i].getTotalPrice() << " |";
            cout << "\n\t\t" << setfill('-') << setw(149) << "\n";

            sum += reservations[i].getTotalPrice();
        }

        int c = 0;
        int scaledSum = sum;

        while (scaledSum >= 100) {
            scaledSum /= 10;
            c++;
        }

        cout << "\t\t|" << setfill(' ') << setw(73 - c) << "Total Price: RM " << sum << setw(70) << "|\n";
        cout << "\t\t" << setfill('-') << setw(149) << "\n";
    }

    cout << endl << setfill(' ') << setw(90) << "> " << current;
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


    if (current == 1) {
        Reservation::addCustomerReservation(reservations, size);
    }
    else if (current == 2)
    {
        Reservation::confirmReservation(reservations, size);
    }
    else if (current == 3) {
        // back
        Customer::cusMenu();
    }
}

void Reservation::addCustomerReservation(Reservation reservations[], int size)
{
    system("cls");

    cout << "\n\n\n" << setw(80) << "Hwa Hwa Hotel Reservation System" << endl;

    string bookingId, username, date;
    int number_of_people, number_of_nights, meal_type, room_type;
    bool car_parking_required;
    double total_price;

    Reservation* reservations_history = new Reservation[MAX_RESERVATIONS];

    int rowSize = 0;

    ReservationHistory::getReservationHistoryFromFile(reservations_history, rowSize);

    // Generate Booking ID (e.g., HWA + a unique number based on current size)
    bookingId = "HWA" + to_string(rowSize + size + 1);

    // Collect Username
    cout << "\n\n" << setw(69) << "Enter Your Name         : ";

    if (cin.peek() == '\n')
        cin.ignore();

    getline(cin, username);

    // Collect Number of People
    cout << "\n" << setw(69) << "Number of People        : ";
    number_of_people = Reservation::getReservationNOP();

    // Collect Number of Nights
    cout << "\n\n" << setw(69) << "Number of Nights        : ";
    number_of_nights = Reservation::getReservationNights();

    // Select Meal Plan
    cout << "\n\n" << setw(69) << "Select Meal Plan        : ";
    meal_type = Reservation::getReservationMealType();

    // Check for Car Parking
    cout << "\n\n" << setw(69) << "Do You Require Parking? : ";
    car_parking_required = Reservation::getReservationCarParkRequired();

    // Select Room Type
    cout << "\n\n" << setw(69) << "Select Room Type        : ";
    room_type = Reservation::getReservationRoomType(number_of_people);

    // Collect Reservation Date
    cout << "\n\n" << setw(69) << "Enter Check-in Date     : ";
    date = Reservation::getReservationDate();

    double base_price = 0;

    switch (room_type)
    {
        case 1: base_price = 50; break;  // Single Room
        case 2: base_price = 100; break; // Double Room
        case 3: base_price = 150; break; // Deluxe Room
        case 4: base_price = 200; break; // Family Room
        case 5: base_price = 250; break; // Presidential Room
        default: base_price = 0; break;
    }

    switch (room_type)
    {
        case 1: base_price += 30; break;  // Single Room
        case 2: base_price += 50; break; // Double Room
        default:; break;
    }

    total_price = base_price * number_of_nights;

    // Add reservation to the list
    reservations[size] = Reservation(bookingId, username, number_of_people, number_of_nights, meal_type, car_parking_required, room_type, date, total_price);

    cout << "\n\n" << setw(75) << "Reservation Successfully Added !!!" << endl;
    cout << "\n\n\t\t\t\t\t     ";
    system("pause");

    Reservation::customerReservationScreen(reservations, size + 1);
}

void Reservation::confirmReservation(Reservation reservations[], int size)
{
    if (size > 0) {
        ofstream file("receipt.csv", ofstream::out);

        // Writing headers for the CSV file
        file << "Bil" << ',' << "Booking ID" << ',' << "Username" << ','
            << "Number of People" << ',' << "Number of Nights" << ','
            << "Meal Type" << ',' << "Car Parking" << ',' << "Room Type" << ','
            << "Date" << ',' << "Total Price" << endl;

        double totalRevenue = 0.0;

        for (int i = 0; i < size; i++) {
            file << i + 1 << ','
                << reservations[i].getBookingId() << ','
                << reservations[i].getUsername() << ','
                << reservations[i].getNumberOfPeople() << ','
                << reservations[i].getNumberOfNights() << ','
                << reservations[i].getMealTypeValue() << ','
                << (reservations[i].isCarParkingRequired() ? "Yes" : "No") << ','
                << reservations[i].getRoomTypeValue() << ','
                << reservations[i].getDate() << ','
                << reservations[i].getTotalPrice() << endl;

            totalRevenue += reservations[i].getTotalPrice();
        }

        file << ",,,,,,,,Total Revenue (RM)," << totalRevenue << endl;

        file.close();

        // Confirmation message
        system("cls");
        cout << "\n\n\n\n\n\n\n\n\n\n";
        cout << endl << setw(71) << "Receipt Generated !!!";
        cout << "\n\n\n\n\t\t\t\t\t     ";
        system("pause");
        system("cls");
    }
    else {
        // No reservations case
        system("cls");
        cout << "\n\n\n\n\n\n\n\n\n\n";
        cout << endl << setw(73) << "Oops, No Reservation Made !!!";
        cout << "\n\n\n\n\t\t\t\t\t     ";
        system("pause");
        system("cls");
    }

    Reservation* new_reservations = new Reservation[100];
    Reservation::customerReservationScreen(new_reservations, 0);
}

int Reservation::getReservationNights()
{
    unsigned char ch = 0;
    int i = 1;
    cout << 1;

    while ((ch = _getch()) != RETURN)
    {
        if (ch == 80) // move down
        {
            if (i < 14 && i <= 9)
            {
                cout << "\b \b";
                i++;
                cout << i;
            }
            else if (i < 14 && i >= 9)
            {
                cout << "\b \b";
                cout << "\b \b";
                i++;
                cout << i;
            }
        }
        else if (ch == 72) // move up
        {
            if (i > 1 && i <= 9)
            {
                cout << "\b \b";
                i--;
                cout << i;
            }
            else if (i > 1 && i >= 9)
            {
                cout << "\b \b";
                cout << "\b \b";
                i--;
                cout << i;
            }
        }
        fflush(stdin);
    }

    return i;
}

int Reservation::getReservationNOP()
{
    unsigned char ch = 0;
    int i = 1;
    cout << 1;

    while ((ch = _getch()) != RETURN)
    {
        if (ch == 80) // move down
        {
            if (i < 6)
            {
                cout << "\b \b";
                i++;
                cout << i;
            }
        }
        else if (ch == 72) // move up
        {
            if (i > 1)
            {
                cout << "\b \b";
                i--;
                cout << i;
            }
        }
        fflush(stdin);
    }

    return i;
}

int Reservation::getReservationMealType()
{
    const char* mealTypes[] = { "Breakfast", "Full Board", "None" };
    const int mealCount = sizeof(mealTypes) / sizeof(mealTypes[0]);

    unsigned char ch = 0;
    int i = 0;
    cout << mealTypes[i];

    while ((ch = _getch()) != RETURN) {
        if (ch == 80) { // Move down
            if (i < mealCount - 1) {
                for (int j = 0; j < strlen(mealTypes[i]); j++) {
                    cout << "\b \b";
                }

                i++;

                cout << mealTypes[i];
            }
        }
        else if (ch == 72) { // Move up
            if (i > 0) {
                for (int j = 0; j < strlen(mealTypes[i]); j++) {
                    cout << "\b \b";
                }

                i--;

                cout << mealTypes[i];
            }
        }

        fflush(stdin);
    }

    return i;
}

bool Reservation::getReservationCarParkRequired()
{
    const char* boolExpress[] = { "Yes", "No" };
    const int boolCount = sizeof(boolExpress) / sizeof(boolExpress[0]);

    unsigned char ch = 0;
    int i = 0;
    cout << boolExpress[i];

    while ((ch = _getch()) != RETURN) {
        if (ch == 80) { // Move down
            if (i < boolCount - 1) {
                for (int j = 0; j < strlen(boolExpress[i]); j++) {
                    cout << "\b \b";
                }

                i++;

                cout << boolExpress[i];
            }
        }
        else if (ch == 72) { // Move up
            if (i > 0) {
                for (int j = 0; j < strlen(boolExpress[i]); j++) {
                    cout << "\b \b";
                }

                i--;

                cout << boolExpress[i];
            }
        }

        fflush(stdin);
    }

    return i;
}

int Reservation::getReservationRoomType(int nop)
{
    const int MAX_ROOM_TYPES = 5;
    const char* roomTypes[MAX_ROOM_TYPES];
    int roomCount = 0;

    if (nop == 1)
    {
        roomTypes[roomCount++] = "Single Room";
        roomTypes[roomCount++] = "Double Room";
        roomTypes[roomCount++] = "Deluxe Room";
        roomTypes[roomCount++] = "Family Room";
        roomTypes[roomCount++] = "Presidential Room";
    }
    else if (nop == 2 || nop == 3)
    {
        roomTypes[roomCount++] = "Double Room";
        roomTypes[roomCount++] = "Deluxe Room";
        roomTypes[roomCount++] = "Family Room";
        roomTypes[roomCount++] = "Presidential Room";
    }
    else if (nop == 4 || nop == 5)
    {
        roomTypes[roomCount++] = "Family Room";
        roomTypes[roomCount++] = "Presidential Room";
    }
    else if (nop >= 6)
    {
        roomTypes[roomCount++] = "Presidential Room";
    }

    unsigned char ch = 0;
    int i = 0;
    cout << roomTypes[i];

    while ((ch = _getch()) != RETURN)
    {
        if (ch == 80) // move down
        {
            if (i < roomCount - 1)
            {
                for (int j = 0; j < strlen(roomTypes[i]); j++)
                {
                    cout << "\b \b";
                }

                i++;

                cout << roomTypes[i];
            }
        }
        else if (ch == 72) // move up
        {
            if (i > 0)
            {
                for (int j = 0; j < strlen(roomTypes[i]); j++)
                {
                    cout << "\b \b";
                }

                i--;

                cout << roomTypes[i];
            }
        }

        fflush(stdin);
    }

    return i + 1;
}

string Reservation::getReservationDate()
{
    unsigned char ch = 0;
    int y = 2025;

    cout << y;

    while ((ch = _getch()) != RETURN)
    {
        if (ch == 80) // move down
        {
            if (y < 2027)
            {
                cout << "\b\b\b\b";
                y++;
                cout << y;
            }
        }
        else if (ch == 72) // move up
        {
            if (y > 2025)
            {
                cout << "\b\b\b\b";
                y--;
                cout << y;
            }
        }
    }

    cout << '/';

    int m = 1;

    cout << m;

    while ((ch = _getch()) != RETURN)
    {
        if (ch == 80) // move down
        {
            if (m < 12)
            {
                cout << "\b \b";

                if (m >= 10)
                {
                    cout << "\b \b";
                }

                m++;
                cout << m;
            }
        }
        else if (ch == 72) // move up
        {
            if (m > 1)
            {
                cout << "\b \b";
                if (m >= 10)
                {
                    cout << "\b \b";
                }
                m--;
                cout << m;
            }
        }
    }

    cout << '/';

    int d = 1;

    cout << d;

    int limit = 31;

    if (m == 2)
    {
        limit = 28;
    }
    else if (m == 4 || m == 6 || m == 9 || m == 11)
    {
        limit = 30;
    }

    while ((ch = _getch()) != RETURN)
    {
        if (ch == 80) // move down
        {
            if (d < limit)
            {
                cout << "\b \b";

                if (d >= 10)
                {
                    cout << "\b \b";
                }

                d++;
                cout << d;
            }
        }
        else if (ch == 72) // move up
        {
            if (d > 1)
            {
                cout << "\b \b";
                if (d >= 10)
                {
                    cout << "\b \b";
                }
                d--;
                cout << d;
            }
        }
    }

    ostringstream dateStream;

    dateStream << d << "/" << m << "/" << y;

    return dateStream.str();
}

string Reservation::getMealTypeValue()
{
    if (this->meal_type == 1)
    {
        return "Breakfast";
    }
    else if (this->meal_type == 2)
    {
        return "Full Board";
    }

    return "None";
}

string Reservation::getRoomTypeValue()
{
    if (this->room_type == 1)
    {
        return "Single Room";
    }
    else if (this->room_type == 2)
    {
        return "Double Room";
    }
    else if (this->room_type == 3)
    {
        return "Deluxe Room";
    }
    else if (this->room_type == 4)
    {
        return "Family Room";
    }

    return "Presidential Room";
}

// Getter methods
string Reservation::getBookingId() {
    return bookingId;
}

string Reservation::getUsername() {
    return username;
}

int Reservation::getNumberOfPeople() {
    return number_of_people;
}

int Reservation::getNumberOfNights() {
    return number_of_nights;
}

int Reservation::getMealType() {
    return meal_type;
}

bool Reservation::isCarParkingRequired() {
    return car_parking_required;
}

int Reservation::getRoomType() {
    return room_type;
}

string Reservation::getDate() {
    return date;
}

double Reservation::getTotalPrice() {
    return total_price;
}

// Setter methods
void Reservation::setBookingId(const string id) {
    bookingId = id;
}

void Reservation::setUsername(const string user) {
    username = user;
}

void Reservation::setNumberOfPeople(int people) {
    number_of_people = people;
}

void Reservation::setMealType(int meal) {
    meal_type = meal;
}

void Reservation::setNumberOfNights(int nights) {
    number_of_nights = nights;
}

void Reservation::setCarParkingRequired(bool parking) {
    car_parking_required = parking;
}

void Reservation::setRoomType(int type) {
    room_type = type;
}

void Reservation::setDate(string reservationDate) {
    date = reservationDate;
}

void Reservation::setTotalPrice(double price) {
    total_price = price;
}