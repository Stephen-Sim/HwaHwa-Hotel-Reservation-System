#include "ReservationHistory.h"
#include "Customer.h"
#include "Admin.h"

vector<Reservation> ReservationHistory::getReservationHistoryFromFile()
{
    ifstream inputFile("data.csv", ios::in);
    vector<Reservation> reservationList;
    vector<string> row;
    string temp, word;

    if (inputFile.is_open())
    {
        bool isFirstLine = true;

        while (getline(inputFile, temp))
        {
            if (isFirstLine)
            {
                isFirstLine = false;
                continue;
            }

            row.clear();
            stringstream s(temp);

            while (getline(s, word, ','))
            {
                row.push_back(word);
            }

            if (row.size() == 9) // Ensure the row has the correct number of fields
            {
                Reservation reservation;
                reservation.setBookingId(row[0]);
                reservation.setUsername(row[1]);
                reservation.setNumberOfPeople(stoi(row[2]));
                reservation.setNumberOfNights(stoi(row[3]));

                if (row[4] == "1")
                    reservation.setMealType(BREAKFAST);
                else if (row[4] == "2")
                    reservation.setMealType(FULL_BOARD);
                else if (row[4] == "0")
                    reservation.setMealType(NONE);

                reservation.setCarParkingRequired(row[5] == "1");

                // Map room type string to enum
                if (row[6] == "Single Room")
                    reservation.setRoomType(SINGLE_ROOM);
                else if (row[6] == "Double Room")
                    reservation.setRoomType(DOUBLE_ROOM);
                else if (row[6] == "Deluxe Room")
                    reservation.setRoomType(DELUXE_ROOM);
                else if (row[6] == "Family Room")
                    reservation.setRoomType(FAMILY_ROOM);
                else if (row[6] == "Presidential Room")
                    reservation.setRoomType(PRESIDENTIAL_ROOM);

                reservation.setDate(row[7]);
                reservation.setTotalPrice(stod(row[8]));

                reservationList.push_back(reservation);
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

    return reservationList;
}

void ReservationHistory::custSearchMenu(vector<Reservation> reservations)
{
    system("cls");
    bool isTrue = false;
    string customer;
    cout << "\n\n\n\tEnter Customer Name: ";
    getline(cin, customer);

    // Start measuring time
    auto start = chrono::high_resolution_clock::now();

    vector<Reservation> result = ReservationHistory::linearSearchByCustomerName(reservations, customer);

    // End measuring time
    auto end = chrono::high_resolution_clock::now();
    chrono::duration<double> duration = end - start; // Duration in seconds
    double milliseconds = duration.count() * 1000; // Convert to milliseconds

    // Display the time taken in milliseconds

    if (result.size() != 0)
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

        for (int i = 0; i < result.size(); i++)
        {
            cout << "\t|" << setfill(' ') << setw(5) << i + 1 << " |";
            cout << setfill(' ') << setw(15) << result[i].getBookingId() << " |";
            cout << setfill(' ') << setw(20) << result[i].getUsername() << " |";
            cout << setfill(' ') << setw(8) << result[i].getNumberOfPeople() << " |";
            cout << setfill(' ') << setw(10) << result[i].getNumberOfNights() << " |";
            cout << setfill(' ') << setw(15) << result[i].getMealTypeValue() << " |";
            cout << setfill(' ') << setw(10) << (result[i].isCarParkingRequired() ? "Yes" : "No") << " |";
            cout << setfill(' ') << setw(20) << result[i].getRoomTypeValue() << " |";
            cout << setfill(' ') << setw(12) << result[i].getDate() << " |";
            cout << setfill(' ') << setw(12) << result[i].getTotalPrice() << " |";
            cout << "\n\t" << setfill('-') << setw(149) << "\n";

            sum += result[i].getTotalPrice();
        }

        int c = 0;
        int scaledSum = sum;

        while (scaledSum >= 100) {
            scaledSum /= 10;
            c++;
        }

        cout << "\t|" << setfill(' ') << setw(83 - c) << "Total Price: RM " << sum << setw(60) << "|\n";
        cout << "\t" << setfill('-') << setw(149) << "\n";

        double avg = sum * 1.0 / result.size();

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



bool ReservationHistory::compareByUsername(Reservation& r1, Reservation& r2)
{
    return r1.getUsername() < r2.getUsername();
}

void ReservationHistory::adminSearchMenu(vector<Reservation> reservations)
{
    system("cls");
    cout << fixed;
    bool isTrue = false;
    string customer;
    cout << "\n\n\n\tEnter Customer Name: ";
    getline(cin, customer);

    // Start measuring time

    sort(reservations.begin(), reservations.end(), compareByUsername);

    auto start = chrono::high_resolution_clock::now();
    vector<Reservation> result = ReservationHistory::binarySearchByCustomerName(reservations, customer);
    // End measuring time
    auto end = chrono::high_resolution_clock::now();
    chrono::duration<double> duration = end - start;
    double milliseconds = duration.count() * 1000;

    // Display the time taken in milliseconds

    if (result.size() != 0)
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

        for (int i = 0; i < result.size(); i++)
        {
            cout << "\t|" << setfill(' ') << setw(5) << i + 1 << " |";
            cout << setfill(' ') << setw(15) << result[i].getBookingId() << " |";
            cout << setfill(' ') << setw(20) << result[i].getUsername() << " |";
            cout << setfill(' ') << setw(8) << result[i].getNumberOfPeople() << " |";
            cout << setfill(' ') << setw(10) << result[i].getNumberOfNights() << " |";
            cout << setfill(' ') << setw(15) << result[i].getMealTypeValue() << " |";
            cout << setfill(' ') << setw(10) << (result[i].isCarParkingRequired() ? "Yes" : "No") << " |";
            cout << setfill(' ') << setw(20) << result[i].getRoomTypeValue() << " |";
            cout << setfill(' ') << setw(12) << result[i].getDate() << " |";
            cout << setfill(' ') << setw(12) <<  setprecision(2) << result[i].getTotalPrice() << " |";
            cout << "\n\t" << setfill('-') << setw(149) << "\n";

            sum += result[i].getTotalPrice();
        }

        int c = 0;
        int scaledSum = sum;

        while (scaledSum >= 100) {
            scaledSum /= 10;
            c++;
        }

        cout << "\t|" << setfill(' ') << setw(83 - c) << "Total Price: RM " << sum << setw(60) << "|\n";
        cout << "\t" << setfill('-') << setw(149) << "\n";

        double avg = sum * 1.0 / result.size();

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

vector<Reservation> ReservationHistory::linearSearchByCustomerName(vector<Reservation> reservations, string customer)
{
    vector<Reservation> result;

    for (Reservation reservation : reservations)
    {
        if (reservation.getUsername() == customer)
        {
            result.push_back(reservation);
        }
    }

    return result;
}

vector<Reservation> ReservationHistory::binarySearchByCustomerName(vector<Reservation>& reservations, string customer) {
    vector<Reservation> result;

    // Perform binary search
    int left = 0, right = reservations.size() - 1;

    while (left <= right) {
        int mid = left + (right - left) / 2;
        string midUsername = reservations[mid].getUsername();

        // Compare the mid value with the customer name
        if (midUsername == customer) {
            // If a match is found, add the reservation to the result
            result.push_back(reservations[mid]);

            // Now search for more reservations with the same customer name
            // Check to the left side
            int i = mid - 1;
            while (i >= left && reservations[i].getUsername() == customer) {
                result.push_back(reservations[i]);
                i--;
            }

            // Check to the right side
            int j = mid + 1;
            while (j <= right && reservations[j].getUsername() == customer) {
                result.push_back(reservations[j]);
                j++;
            }

            break; // Exit after finding all the matching entries
        }

        // Binary search conditions
        if (midUsername < customer) {
            left = mid + 1;
        }
        else {
            right = mid - 1;
        }
    }

    return result;
}

vector<Reservation> ReservationHistory::getFirst100Reservations(vector<Reservation> reservations) {
    return vector<Reservation>(reservations.begin(), reservations.begin() + min(100, static_cast<int>(reservations.size())));
}

void ReservationHistory::displayReservationHistory()
{
    system("cls");
    unsigned char opt = 0;
    int current = 1;
    int i = 1;

    vector<Reservation> reservations = ReservationHistory::getReservationHistoryFromFile();

    vector<Reservation> first100reservations = getFirst100Reservations(reservations);

    ReservationHistory::getReservationHistoryDataTable(first100reservations, i);

    while ((opt = _getch()) != RETURN) {

        if (opt == 77 && i != 10) // move right
        {
            ++i;
            if (i * 10 > ceil(first100reservations.size()) + 10) {
                i--;
            }

            ReservationHistory::getReservationHistoryDataTable(first100reservations, i);
            continue;
        }
        else if (opt == 75) // move left
        {
            --i;
            if (i <= 0)
                i = 1;

            ReservationHistory::getReservationHistoryDataTable(first100reservations, i);
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

void ReservationHistory::getReservationHistoryDataTable(vector <Reservation> reservations, int counter)
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

    for (int i = iValue; dataTableSize; i++)
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

void ReservationHistory::displaySort(vector <Reservation>& reservations, int current, double time = 0.0, string sorting_method = "")
{
    unsigned char opt = 0; int i = 1;

    ReservationHistory::sortReservationHistoryDataTable(reservations, i, current, time, sorting_method);

    while ((opt = _getch()) != RETURN) {

        if (opt == 77 && i != 10) // move right
        {
            ++i;
            if (i * 10 > ceil(reservations.size()) + 10) {
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
        auto history_reservation = ReservationHistory::getReservationHistoryFromFile();

        // Start measuring time
        auto start = chrono::high_resolution_clock::now();
        auto temp = ReservationHistory::mergeSortByCustomerName(history_reservation);
        // End measuring time
        auto end = chrono::high_resolution_clock::now();
        chrono::duration<double> duration = end - start; // Duration in seconds
        double milliseconds = duration.count() * 1000; // Convert to milliseconds

        vector<Reservation> first100reservations = getFirst100Reservations(temp);
        ReservationHistory::displaySort(first100reservations, current, milliseconds, "Merge Sort");
    }
    else if (current == 2)
    {
        auto history_reservation = ReservationHistory::getReservationHistoryFromFile();

        // Start measuring time
        auto start = chrono::high_resolution_clock::now();
        auto temp = ReservationHistory::bubbleSortByPrice(history_reservation);
        // End measuring time
        auto end = chrono::high_resolution_clock::now();
        chrono::duration<double> duration = end - start; // Duration in seconds
        double milliseconds = duration.count() * 1000; // Convert to milliseconds
        vector<Reservation> first100reservations = getFirst100Reservations(temp);
        ReservationHistory::displaySort(first100reservations, current, milliseconds, "Bubble Sort");;
    }
    else if (current == 3) {
        ReservationHistory::displayReservationHistory();
    }
}

void ReservationHistory::sortReservationHistoryDataTable(vector <Reservation> reservations, int counter, int current, double time = 0.0, string sorting_method = "")
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

    for (int i = iValue; dataTableSize; i++)
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

vector<Reservation> ReservationHistory::mergeSortByCustomerName(vector<Reservation> reservations)
{
    if (reservations.size() <= 1) {
        return reservations; // Base case: already sorted
    }

    // Split the vector into two halves
    int mid = reservations.size() / 2;
    vector<Reservation> left(reservations.begin(), reservations.begin() + mid);
    vector<Reservation> right(reservations.begin() + mid, reservations.end());

    // Recursively sort both halves
    left = mergeSortByCustomerName(left);
    right = mergeSortByCustomerName(right);

    // Merge the sorted halves
    vector<Reservation> merged;
    size_t i = 0, j = 0;
    while (i < left.size() && j < right.size()) {
        if (left[i].getUsername() <= right[j].getUsername()) {
            merged.push_back(left[i++]);
        }
        else {
            merged.push_back(right[j++]);
        }
    }

    // Append any remaining elements
    while (i < left.size()) {
        merged.push_back(left[i++]);
    }
    while (j < right.size()) {
        merged.push_back(right[j++]);
    }

    return merged;
}

vector<Reservation> ReservationHistory::bubbleSortByPrice(vector<Reservation> reservations) {
    int n = reservations.size();

    for (int i = 0; i < n - 1; i++) {
        bool swapped = false;

        for (int j = 0; j < n - 1 - i; j++) {
            // Compare adjacent elements
            if (reservations[j].getTotalPrice() < reservations[j + 1].getTotalPrice()) {
                // Swap using the temporary variable
                Reservation temp = reservations[j];
                reservations[j] = reservations[j + 1];
                reservations[j + 1] = temp;

                swapped = true;
            }
        }

        if (!swapped) {
            break;
        }
    }

    return reservations;
}
