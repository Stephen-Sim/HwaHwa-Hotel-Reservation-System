#include "ReservationHistory.h"
#include "Admin.h"
#include "Customer.h"

void ReservationHistory::getReservationHistoryFromFile(Reservation reservations[], int& reservationCount)
{
    ifstream inputFile("data.csv", ios::in);
    reservationCount = 0;
    string row[9];
    string temp, word;
    int wordCount;

    if (inputFile.is_open())
    {
        bool isFirstLine = true;

        while (getline(inputFile, temp) && reservationCount < MAX_RESERVATIONS)
        {
            if (isFirstLine)
            {
                isFirstLine = false;
                continue;
            }

            wordCount = 0;
            stringstream s(temp);

            while (getline(s, word, ',') && wordCount < 9)
            {
                row[wordCount++] = word;
            }

            if (wordCount == 9) // Ensure the row has the correct number of fields
            {
                reservations[reservationCount].setBookingId(row[0]);
                reservations[reservationCount].setUsername(row[1]);
                reservations[reservationCount].setNumberOfPeople(stoi(row[2]));
                reservations[reservationCount].setNumberOfNights(stoi(row[3]));

                if (row[4] == "1")
                    reservations[reservationCount].setMealType(BREAKFAST);
                else if (row[4] == "2")
                    reservations[reservationCount].setMealType(FULL_BOARD);
                else if (row[4] == "0")
                    reservations[reservationCount].setMealType(NONE);

                reservations[reservationCount].setCarParkingRequired(row[5] == "1");

                // Map room type string to enum
                if (row[6] == "Single Room")
                    reservations[reservationCount].setRoomType(SINGLE_ROOM);
                else if (row[6] == "Double Room")
                    reservations[reservationCount].setRoomType(DOUBLE_ROOM);
                else if (row[6] == "Deluxe Room")
                    reservations[reservationCount].setRoomType(DELUXE_ROOM);
                else if (row[6] == "Family Room")
                    reservations[reservationCount].setRoomType(FAMILY_ROOM);
                else if (row[6] == "Presidential Room")
                    reservations[reservationCount].setRoomType(PRESIDENTIAL_ROOM);

                reservations[reservationCount].setDate(row[7]);
                reservations[reservationCount].setTotalPrice(stod(row[8]));

                reservationCount++;
            }
            else
            {
                cout << "Invalid row format: " << temp << endl;
            }
        }

        inputFile.close();
    }
    else
    {
        cout << "Unable to open file" << endl;
    }
}

void ReservationHistory::adminSearchMenu()
{
    system("cls");
    cout << fixed;
    bool isTrue = false;
    string customer;
    cout << "\n\n\n\tEnter Customer Name: ";
    getline(cin, customer);

    Reservation* reservations = new Reservation[MAX_RESERVATIONS];
    Reservation* temp = new Reservation[MAX_RESERVATIONS];
    Reservation* results = new Reservation[MAX_RESERVATIONS];
    int rowSize = 0;

    // Load reservations from a file
    ReservationHistory::getReservationHistoryFromFile(reservations, rowSize);

    ReservationHistory::mergeSortByCustomerName(reservations, 0, rowSize - 1, temp);

    auto start = chrono::high_resolution_clock::now();
    int resultRow = ReservationHistory::binarySearchByCustomerName(reservations, customer, results);
    // End measuring time
    auto end = chrono::high_resolution_clock::now();
    chrono::duration<double> duration = end - start;
    double milliseconds = duration.count() * 1000;

    // Display the time taken in milliseconds

    if (resultRow != 0)
    {
        cout << "\n\t" << setfill('-') << setw(149) << "\n";
        cout << "\t|" << setfill(' ') << setw(5) << "Bil" << " |";
        cout << setfill(' ') << setw(15) << "Booking ID" << " |";
        cout << setfill(' ') << setw(20) << "Username" << " |";
        cout << setfill(' ') << setw(8) << "People" << " |";
        cout << setfill(' ') << setw(10) << "Nights" << " |";
        cout << setfill(' ') << setw(15) << "Meal Type" << " |";
        cout << setfill(' ') << setw(10) << "Parking" << " |";
        cout << setfill(' ') << setw(20) << "Room Type" << " |";
        cout << setfill(' ') << setw(12) << "Date" << " |";
        cout << setfill(' ') << setw(12) << "Total Price" << " |";
        cout << "\n\t" << setfill('-') << setw(149) << "\n";

        double sum = 0;

        for (int i = 0; i < resultRow; i++)
        {
            cout << "\t|" << setfill(' ') << setw(5) << i + 1 << " |";
            cout << setfill(' ') << setw(15) << results[i].getBookingId() << " |";
            cout << setfill(' ') << setw(20) << results[i].getUsername() << " |";
            cout << setfill(' ') << setw(8) << results[i].getNumberOfPeople() << " |";
            cout << setfill(' ') << setw(10) << results[i].getNumberOfNights() << " |";
            cout << setfill(' ') << setw(15) << results[i].getMealTypeValue() << " |";
            cout << setfill(' ') << setw(10) << (results[i].isCarParkingRequired() ? "Yes" : "No") << " |";
            cout << setfill(' ') << setw(20) << results[i].getRoomTypeValue() << " |";
            cout << setfill(' ') << setw(12) << results[i].getDate() << " |";
            cout << setfill(' ') << setw(12) << setprecision(2) << results[i].getTotalPrice() << " |";
            cout << "\n\t" << setfill('-') << setw(149) << "\n";

            sum += results[i].getTotalPrice();
        }

        int c = 0;
        int scaledSum = sum;

        while (scaledSum >= 100) {
            scaledSum /= 10;
            c++;
        }

        cout << "\t|" << setfill(' ') << setw(83 - c) << "Total Price: RM " << sum << setw(60) << "|\n";
        cout << "\t" << setfill('-') << setw(149) << "\n";

        double avg = sum * 1.0 / resultRow;

        int scaledAvg = avg;
        c = 0;

        cout << "\t|" << setfill(' ') << setw(82 - c) << "Average Spend Amount: RM " << avg << setw(60) << "|\n";
        cout << "\t" << setfill('-') << setw(149) << "\n";

        while (scaledAvg >= 100) {
            scaledAvg /= 10;
            c++;
        }

        if (sum >= 3000)
        {
            cout << "\t|" << setfill(' ') << setw(87) << "Platinum Tier Customer" << setw(60) << "|\n";
        }
        else if (sum >= 2000)
        {
            cout << "\t|" << setfill(' ') << setw(90) << "Gold Tier Customer" << setw(60) << "|\n";
        }
        else if (sum >= 1000)
        {
            cout << "\t|" << setfill(' ') << setw(88) << "Silver Tier Customer" << setw(60) << "|\n";
        }
        else
        {
            cout << "\t|" << setfill(' ') << setw(88) << "Bronze Tier Customer" << setw(60) << "|\n";
        }

        cout << "\t" << setfill('-') << setw(149) << "\n";

        cout << "\n\t\t\t\t\t\t\t\tTime taken for search: " << milliseconds << " milliseconds." << endl;
        cout << "\n\t\t\t\t\t\t\t\t    Binary Search techniques is used." << endl;

        cout << "\n\n\n\n\t\t\t\t\t\t\t\t";

    }
    else
    {
        cout << "\n\n\n\t\t" << setfill('-') << setw(85) << "\n";
        cout << "\t\t|" << setfill(' ') << setw(84) << " |\n";
        cout << "\t\t|" << setfill(' ') << setw(54) << "Record Not Found !!! " << setw(30) << "|\n";
        cout << "\t\t|" << setfill(' ') << setw(84) << " |\n";
        cout << "\t\t" << setfill('-') << setw(85) << "\n";

        cout << "\n\n\n\n\t\t\t\t\t     ";
    }

    system("pause");

    cout << setfill(' ');

    Admin::adminMenu();
}

void ReservationHistory::custSearchMenu()
{
    system("cls");
    bool isTrue = false;
    string customer;
    cout << "\n\n\n\tEnter Customer Name: ";
    getline(cin, customer);

    Reservation* reservations = new Reservation[MAX_RESERVATIONS];
    int rowSize = 0;

    Reservation* results = new Reservation[MAX_RESERVATIONS];

    // Load reservations from a file
    ReservationHistory::getReservationHistoryFromFile(reservations, rowSize);

    // Start measuring time
    auto start = chrono::high_resolution_clock::now();

    int resultRow = ReservationHistory::linearSearchByCustomerName(reservations, customer, results);

    // End measuring time
    auto end = chrono::high_resolution_clock::now();
    chrono::duration<double> duration = end - start; // Duration in seconds
    double milliseconds = duration.count() * 1000; // Convert to milliseconds

    // Display the time taken in milliseconds

    if (resultRow != 0)
    {
        cout << "\n\t" << setfill('-') << setw(149) << "\n";
        cout << "\t|" << setfill(' ') << setw(5) << "Bil" << " |";
        cout << setfill(' ') << setw(15) << "Booking ID" << " |";
        cout << setfill(' ') << setw(20) << "Username" << " |";
        cout << setfill(' ') << setw(8) << "People" << " |";
        cout << setfill(' ') << setw(10) << "Nights" << " |";
        cout << setfill(' ') << setw(15) << "Meal Type" << " |";
        cout << setfill(' ') << setw(10) << "Parking" << " |";
        cout << setfill(' ') << setw(20) << "Room Type" << " |";
        cout << setfill(' ') << setw(12) << "Date" << " |";
        cout << setfill(' ') << setw(12) << "Total Price" << " |";
        cout << "\n\t" << setfill('-') << setw(149) << "\n";

        double sum = 0;

        for (int i = 0; i < resultRow; i++)
        {
            cout << "\t|" << setfill(' ') << setw(5) << i + 1 << " |";
            cout << setfill(' ') << setw(15) << results[i].getBookingId() << " |";
            cout << setfill(' ') << setw(20) << results[i].getUsername() << " |";
            cout << setfill(' ') << setw(8) << results[i].getNumberOfPeople() << " |";
            cout << setfill(' ') << setw(10) << results[i].getNumberOfNights() << " |";
            cout << setfill(' ') << setw(15) << results[i].getMealTypeValue() << " |";
            cout << setfill(' ') << setw(10) << (results[i].isCarParkingRequired() ? "Yes" : "No") << " |";
            cout << setfill(' ') << setw(20) << results[i].getRoomTypeValue() << " |";
            cout << setfill(' ') << setw(12) << results[i].getDate() << " |";
            cout << setfill(' ') << setw(12) << results[i].getTotalPrice() << " |";
            cout << "\n\t" << setfill('-') << setw(149) << "\n";

            sum += results[i].getTotalPrice();
        }

        int c = 0;
        int scaledSum = sum;

        while (scaledSum >= 100) {
            scaledSum /= 10;
            c++;
        }

        cout << "\t|" << setfill(' ') << setw(83 - c) << "Total Price: RM " << sum << setw(60) << "|\n";
        cout << "\t" << setfill('-') << setw(149) << "\n";

        double avg = sum * 1.0 / resultRow;

        int scaledAvg = avg;
        c = 0;

        while (scaledAvg >= 100) {
            scaledAvg /= 10;
            c++;
        }

        cout << "\t|" << setfill(' ') << setw(83 - c) << "Average Spend Amount: RM " << avg << setw(60) << "|\n";
        cout << "\t" << setfill('-') << setw(149) << "\n";

        cout << "\n\t\t\t\t\t\t\tTime taken for search: " << milliseconds << " milliseconds." << endl;
        cout << "\n\t\t\t\t\t\t\t\tLinear Search techniques is used." << endl;

        cout << "\n\n\n\n\t\t\t\t\t\t\t\t";
    }
    else
    {
        cout << "\n\n\n\t\t" << setfill('-') << setw(85) << "\n";
        cout << "\t\t|" << setfill(' ') << setw(84) << " |\n";
        cout << "\t\t|" << setfill(' ') << setw(54) << "Record Not Found !!! " << setw(30) << "|\n";
        cout << "\t\t|" << setfill(' ') << setw(84) << " |\n";
        cout << "\t\t" << setfill('-') << setw(85) << "\n";

        cout << "\n\n\n\n\t\t\t\t\t     ";
    }

    system("pause");

    cout << setfill(' ');

    Customer::cusMenu();
}

void ReservationHistory::displayReservationHistory()
{
    system("cls");
    unsigned char opt = 0;
    int current = 1;
    int i = 1;

    Reservation * reservations = new Reservation[MAX_RESERVATIONS];

    int rowSize = 0;

    ReservationHistory::getReservationHistoryFromFile(reservations, rowSize);

    ReservationHistory::getReservationHistoryDataTable(reservations, i);

    while ((opt = _getch()) != RETURN) {

        if (opt == 77 && i != 10) // move right
        {
            ++i;
            if (i * 10 > ceil(100) + 10) {
                i--;
            }

            ReservationHistory::getReservationHistoryDataTable(reservations, i);
            continue;
        }
        else if (opt == 75) // move left
        {
            --i;
            if (i <= 0)
                i = 1;

            ReservationHistory::getReservationHistoryDataTable(reservations, i);
            continue;
        }

        if (opt == 72) // move down
        {
            if (current > 1) {
                cout << "\b \b";
                cout << --current;
            }

        }
        else if (opt == 80) // move up
        {
            if (current < 2) {
                cout << "\b \b";
                cout << ++current;
            }
        }

        fflush(stdin);
    }

    if (current == 1) {
        ReservationHistory::displaySort(reservations, 1, 0.0, "");
    }
    else if (current == 2)
    {
        Admin::adminMenu();
    }
}

void ReservationHistory::displaySort(Reservation reservations[], int current, double time = 0.0, string sorting_method = "")
{
    unsigned char opt = 0; int i = 1;

    ReservationHistory::sortReservationHistoryDataTable(reservations, i, current, time, sorting_method);

    while ((opt = _getch()) != RETURN) {

        if (opt == 77 && i != 10) // move right
        {
            ++i;
            if (i * 10 > ceil(100) + 10) {
                i--;
            }

            ReservationHistory::sortReservationHistoryDataTable(reservations, i, current, time, sorting_method);
            continue;
        }
        else if (opt == 75) // move left
        {
            --i;
            if (i <= 0)
                i = 1;

            ReservationHistory::sortReservationHistoryDataTable(reservations, i, current, time, sorting_method);
            continue;
        }
        else if (opt == 72) // move up
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

    if (current == 1)
    {
        Reservation* reservations = new Reservation[MAX_RESERVATIONS];
        Reservation* temp = new Reservation[MAX_RESERVATIONS]; // Temporary array for merge sort
        int rowSize = 0;

        // Load reservations from a file
        ReservationHistory::getReservationHistoryFromFile(reservations, rowSize);

        // Start measuring time
        auto start = chrono::high_resolution_clock::now();

        // Perform merge sort
        ReservationHistory::mergeSortByCustomerName(reservations, 0, rowSize - 1, temp);

        // End measuring time
        auto end = chrono::high_resolution_clock::now();
        chrono::duration<double> duration = end - start; // Duration in seconds
        double milliseconds = duration.count() * 1000; // Convert to milliseconds

        // Display sorted results
        ReservationHistory::displaySort(reservations, current, milliseconds, "Merge Sort");
    }
    else if (current == 2)
    {
        Reservation* reservations = new Reservation[MAX_RESERVATIONS];
        int rowSize = 0;

        // Load reservations from file
        getReservationHistoryFromFile(reservations, rowSize);

        // Start measuring time
        auto start = chrono::high_resolution_clock::now();

        // Perform bubble sort
        ReservationHistory::bubbleSortByPrice(reservations, rowSize);

        // End measuring time
        auto end = chrono::high_resolution_clock::now();
        chrono::duration<double> duration = end - start; // Duration in seconds
        double milliseconds = duration.count() * 1000; // Convert to milliseconds

        ReservationHistory::displaySort(reservations, current, milliseconds, "Bubble Sort");
    }
    else if (current == 3) {
        ReservationHistory::displayReservationHistory();
    }
}

void ReservationHistory::sortReservationHistoryDataTable(Reservation reservations[], int counter, int current, double time = 0.0, string sorting_method = "")
{
    system("cls");
    cout << "\n\n\t\t\t\t1. Sort By Customer Name\t\t2. Sort By Highest Price\t\t3. Back" << endl;
    cout << fixed;

    // table header
    cout << "\n\t" << setfill('-') << setw(149) << "\n";
    cout << "\t|" << setfill(' ') << setw(5) << "Bil" << " |";
    cout << setfill(' ') << setw(15) << "Booking ID" << " |";
    cout << setfill(' ') << setw(20) << "Username" << " |";
    cout << setfill(' ') << setw(8) << "People" << " |";
    cout << setfill(' ') << setw(10) << "Nights" << " |";
    cout << setfill(' ') << setw(15) << "Meal Type" << " |";
    cout << setfill(' ') << setw(10) << "Parking" << " |";
    cout << setfill(' ') << setw(20) << "Room Type" << " |";
    cout << setfill(' ') << setw(12) << "Date" << " |";
    cout << setfill(' ') << setw(12) << "Total Price" << " |";
    cout << "\n\t" << setfill('-') << setw(149) << "\n";

    for (int i = (counter - 1) * 10; i < counter * 10 && i <= 100; i++)
    {
        cout << "\t|" << setfill(' ') << setw(5) << i + 1 << " |";
        cout << setfill(' ') << setw(15) << reservations[i].getBookingId() << " |";
        cout << setfill(' ') << setw(20) << reservations[i].getUsername() << " |";
        cout << setfill(' ') << setw(8) << reservations[i].getNumberOfPeople() << " |";
        cout << setfill(' ') << setw(10) << reservations[i].getNumberOfNights() << " |";
        cout << setfill(' ') << setw(15) << reservations[i].getMealTypeValue() << " |";
        cout << setfill(' ') << setw(10) << (reservations[i].isCarParkingRequired() ? "Yes" : "No") << " |";
        cout << setfill(' ') << setw(20) << reservations[i].getRoomTypeValue() << " |";
        cout << setfill(' ') << setw(12) << reservations[i].getDate() << " |";
        cout << setfill(' ') << setw(12) << setw(12) << setprecision(2) << reservations[i].getTotalPrice() << " |";
        cout << "\n\t" << setfill('-') << setw(149) << "\n";
    }


    if (time != 0.0)
    {
        cout << "\n\t\t\t\t\t\t\tTime taken for search: " << time << " milliseconds." << endl;
        cout << "\n\t\t\t\t\t\t\t\t" << sorting_method << " techniques is used." << endl;
    }

    cout << endl << setfill(' ') << setw(80) << "> " << current;
}

int ReservationHistory::linearSearchByCustomerName(Reservation reservations[], string customerName, Reservation result[]) {
    int resultCount = 0;

    for (int i = 0; i < MAX_RESERVATIONS; i++) {
        if (reservations[i].getUsername() == customerName) {
            result[resultCount++] = reservations[i];
        }
    }

    return resultCount; // Return the number of matching rows
}

int ReservationHistory::binarySearchByCustomerName(Reservation reservations[], string customerName, Reservation result[]) {
    int resultCount = 0;

    int left = 0, right = MAX_RESERVATIONS - 1;

    while (left <= right) {
        int mid = left + (right - left) / 2;
        string midUsername = reservations[mid].getUsername();

        if (midUsername == customerName) {
            // Add the matching reservation
            result[resultCount++] = reservations[mid];

            // Check to the left side for more matches
            int i = mid - 1;
            while (i >= left && reservations[i].getUsername() == customerName) {
                result[resultCount++] = reservations[i];
                i--;
            }

            // Check to the right side for more matches
            int j = mid + 1;
            while (j <= right && reservations[j].getUsername() == customerName) {
                result[resultCount++] = reservations[j];
                j++;
            }

            break; // Exit after finding all matching entries
        }

        if (midUsername < customerName) {
            left = mid + 1;
        }
        else {
            right = mid - 1;
        }
    }

    return resultCount; // Return the number of matching rows
}


void ReservationHistory::mergeSortByCustomerName(Reservation reservations[], int left, int right, Reservation temp[]) {
    if (left >= right) {
        return; // Base case: single element
    }

    int mid = (left + right) / 2;

    // Recursively sort both halves
    mergeSortByCustomerName(reservations, left, mid, temp);
    mergeSortByCustomerName(reservations, mid + 1, right, temp);

    // Merge the sorted halves
    int i = left, j = mid + 1, k = left;
    while (i <= mid && j <= right) {
        if (reservations[i].getUsername() <= reservations[j].getUsername()) {
            temp[k++] = reservations[i++];
        }
        else {
            temp[k++] = reservations[j++];
        }
    }

    while (i <= mid) {
        temp[k++] = reservations[i++];
    }
    while (j <= right) {
        temp[k++] = reservations[j++];
    }

    // Copy back to the original array
    for (int idx = left; idx <= right; idx++) {
        reservations[idx] = temp[idx];
    }
}

void ReservationHistory::bubbleSortByPrice(Reservation reservations[], int size) {
    for (int i = 0; i < size - 1; i++) {
        bool swapped = false;

        for (int j = 0; j < size - 1 - i; j++) {
            if (reservations[j].getTotalPrice() < reservations[j + 1].getTotalPrice()) {
                // Swap using a temporary variable
                Reservation temp = reservations[j];
                reservations[j] = reservations[j + 1];
                reservations[j + 1] = temp;

                swapped = true;
            }
        }

        if (!swapped) {
            break; // Early exit if no swaps occurred
        }
    }
}


void ReservationHistory::getReservationHistoryDataTable(Reservation reservations [], int counter)
{
    system("cls");
    cout << "\n\n\t\t\t\t\t\t1. Sort Reservation History \t\t\t\t2. Back" << endl;
    cout << fixed;

    // table header
    cout << "\n\t" << setfill('-') << setw(149) << "\n";
    cout << "\t|" << setfill(' ') << setw(5) << "Bil" << " |";
    cout << setfill(' ') << setw(15) << "Booking ID" << " |";
    cout << setfill(' ') << setw(20) << "Username" << " |";
    cout << setfill(' ') << setw(8) << "People" << " |";
    cout << setfill(' ') << setw(10) << "Nights" << " |";
    cout << setfill(' ') << setw(15) << "Meal Type" << " |";
    cout << setfill(' ') << setw(10) << "Parking" << " |";
    cout << setfill(' ') << setw(20) << "Room Type" << " |";
    cout << setfill(' ') << setw(12) << "Date" << " |";
    cout << setfill(' ') << setw(12) << "Total Price" << " |";
    cout << "\n\t" << setfill('-') << setw(149) << "\n";

    for (int i = (counter - 1) * 10; i < counter * 10 && i <= 100; i++)
    {
        cout << "\t|" << setfill(' ') << setw(5) << i + 1 << " |";
        cout << setfill(' ') << setw(15) << reservations[i].getBookingId() << " |";
        cout << setfill(' ') << setw(20) << reservations[i].getUsername() << " |";
        cout << setfill(' ') << setw(8) << reservations[i].getNumberOfPeople() << " |";
        cout << setfill(' ') << setw(10) << reservations[i].getNumberOfNights() << " |";
        cout << setfill(' ') << setw(15) << reservations[i].getMealTypeValue() << " |";
        cout << setfill(' ') << setw(10) << (reservations[i].isCarParkingRequired() ? "Yes" : "No") << " |";
        cout << setfill(' ') << setw(20) << reservations[i].getRoomTypeValue() << " |";
        cout << setfill(' ') << setw(12) << reservations[i].getDate() << " |";
        cout << setfill(' ') << setw(12) << setw(12) << setprecision(2) << reservations[i].getTotalPrice() << " |";
        cout << "\n\t" << setfill('-') << setw(149) << "\n";
    }

    cout << endl << setfill(' ') << setw(85) << "> 1";
}