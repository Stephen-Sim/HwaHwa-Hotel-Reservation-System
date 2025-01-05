#include "Admin.h"
#include "Customer.h"
#include "ReservationSearchResult.h"
#include "ReservationHistory.h"
#include "MonthlyStat.h"

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

void ReservationHistory::monthlyAnalysisDataTable(int counter = 1)
{
    Reservation* reservations = new Reservation[MAX_RESERVATIONS];
    int rowSize = 0;

    // Load reservations from a file
    ReservationHistory::getReservationHistoryFromFile(reservations, rowSize);

    // Correct 2D array allocation
    MonthlyStat** stats = new MonthlyStat * [2];
    for (int i = 0; i < 2; i++) {
        stats[i] = new MonthlyStat[12];

        // Initialize each MonthlyStat object with zero values
        for (int j = 0; j < 12; j++) {
            stats[i][j].setCount(0);
            stats[i][j].setTotalPrice(0.0);
            stats[i][j].setAvgPrice(0.0);
        }
    }

    // Process each reservation
    for (int i = 0; i < rowSize; i++) {
        string date = reservations[i].getDate();
        // Parse date (format: "mm/dd/yyyy")
        int month = stoi(date.substr(0, date.find('/'))) - 1; // 0-11
        int year = stoi(date.substr(date.rfind('/') + 1));

        if (year < 2023 || year > 2024) continue;

        int yearIndex = year - 2023; // 0 for 2023, 1 for 2024

        // Update statistics
        stats[yearIndex][month].setCount(stats[yearIndex][month].getCount() + 1);
        stats[yearIndex][month].setTotalPrice(stats[yearIndex][month].getTotalPrice() + reservations[i].getTotalPrice());

    }

    const string months[] = { "Jan", "Feb", "Mar", "Apr", "May", "Jun", "Jul", "Aug", "Sep", "Oct", "Nov", "Dec" };

    system("cls");
    cout << fixed;

    cout << "\n\n\t\t\t\t\t\t\t1. Back\n" << endl;

    cout << "\t\t" << setfill('-') << setw(90) << "\n";
    cout << "\t\t|" << setfill(' ') << setw(50) << "Analysis of Year " << (counter == 1 ? "2023" : "2024") << setw(34) << "|";

    cout << "\n\t\t" << setfill('-') << setw(90) << "\n";
    cout << "\t\t|" << setfill(' ') << setw(20) << "Month" << " |";
    cout << setfill(' ') << setw(20) << "Total Reservation" << " |";
    cout << setfill(' ') << setw(20) << "Total Profit" << " |";
    cout << setfill(' ') << setw(20) << "Average Profit" << " |";
    cout << "\n\t\t" << setfill('-') << setw(90) << "\n";

    double sum = 0;
    int count = 0;

    // Display for both years
    for (int month = 0; month < 12; month++) {
        MonthlyStat& s = stats[counter - 1][month];
        // Calculate average if there are reservations
        if (s.getCount() > 0) {
            s.calculateAvgPrice();
        }

        cout << "\t\t|" << setfill(' ') << setw(15) << months[month] << " " << (2023 + counter - 1) << " |";
        cout << setfill(' ') << setw(20) << s.getCount() << " |";
        cout << setfill(' ') << setw(20) << fixed << setprecision(2) << s.getTotalPrice() << " |";
        cout << setfill(' ') << setw(20) << s.getAvgPrice() << " |";
        cout << "\n\t\t" << setfill('-') << setw(90) << "\n";

        count += s.getCount();
        sum += s.getTotalPrice();
    }

    int c = 0;
    int scaledSum = sum;

    while (scaledSum >= 100) {
        scaledSum /= 10;
        c++;
    }

    double avg = sum * 1.0 / 12;

    cout << "\t\t|" << setfill(' ') << setw(47) << "Total Reservation: " << count << setw(38) << "|\n";
    cout << "\t\t" << setfill('-') << setw(90) << "\n";

    cout << "\t\t|" << setfill(' ') << setw(45) << "Total Profit: RM " << sum << setw(31 + c + (counter == 2 ? -2 : 0)) << "|\n";
    cout << "\t\t" << setfill('-') << setw(90) << "\n";

    c = 0;
    int scaledAvg = avg;

    while (scaledAvg >= 100) {
        scaledAvg /= 10;
        c++;
    }

    cout << "\t\t|" << setfill(' ') << setw(55) << "Monthly Average Profit: RM " << avg << setw(23 + c + (counter == 2 ? -2 : 0)) << "|\n";
    cout << "\t\t" << setfill('-') << setw(90) << "\n";

    // Navigation prompt
    cout << endl << setfill(' ') << right << setw(60) << "> 1";

    unsigned char opt = 0;
    int current = 1;
    int i = 1;

    while ((opt = _getch()) != RETURN) {

        if (opt == 77 && i != 10) // move right
        {
            ++i;
            if (i * 10 > ceil(100) + 10) {
                i--;
            }

            ReservationHistory::monthlyAnalysisDataTable(i);
            continue;
        }
        else if (opt == 75) // move left
        {
            --i;
            if (i <= 0)
                i = 1;

            ReservationHistory::monthlyAnalysisDataTable(i);
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
            if (current < 1) {
                cout << "\b \b";
                cout << ++current;
            }
        }

        fflush(stdin);
    }

    if (current == 1)
    {
        Admin::adminMenu();
    }

}

void ReservationHistory::linearSearch100Data(bool IsImproved = false)
{
    string* datas = new string[100];
    ifstream inputFile("100-sample.txt", ios::in);

    if (!inputFile.is_open())
    {
        cout << "Unable to open file" << endl;
        return;
    }

    int index = 0;
    string line;

    while (getline(inputFile, line) && index < 100)
    {
        datas[index++] = line;
    }

    inputFile.close();

    ReservationSearchResult* results = new ReservationSearchResult[100];
    Reservation* reservations = new Reservation[MAX_RESERVATIONS];
    int rowSize = 0;

    ReservationHistory::getReservationHistoryFromFile(reservations, rowSize);

    // Start measuring time
    auto start = chrono::high_resolution_clock::now();

    int found = 0, notFound = 0;

    int resultCount = 0;

    for (int outerIndex = 0; outerIndex < 100; outerIndex++)
    {
        results[resultCount].setBookingId(datas[outerIndex]);
        bool isFound = false;

        for (int innerIndex = 0; innerIndex < rowSize; innerIndex++)
        {
            if (reservations[innerIndex].getBookingId() == datas[outerIndex])
            {
                results[resultCount].setReservation(reservations[innerIndex]);
                results[resultCount].setIsReservationFound(true);
                isFound = true;
                found++;

                if (IsImproved)
                {
                    break;
                }
            }
        }

        if (!isFound)
        {
            results[resultCount].setIsReservationFound(false);
            notFound++;
        }

        resultCount++;
    }

    // End measuring time
    auto end = chrono::high_resolution_clock::now();
    chrono::duration<double> duration = end - start; // Duration in seconds
    double milliseconds = duration.count() * 1000;

    ReservationHistory::linearSearch100DataDataTable(results, 1, found, notFound, start.time_since_epoch().count(), end.time_since_epoch().count(), milliseconds, 1, IsImproved);
}

void ReservationHistory::binarySearch100Data()
{
    system("cls");
    cout << fixed;

    string* datas = new string[100];
    ifstream inputFile("100-sample.txt", ios::in);

    if (!inputFile.is_open())
    {
        cout << "Unable to open file" << endl;
        return;
    }

    int index = 0;
    string line;

    while (getline(inputFile, line) && index < 100)
    {
        datas[index++] = line;
    }

    inputFile.close();

    ReservationSearchResult* results = new ReservationSearchResult[100];
    Reservation* reservations = new Reservation[MAX_RESERVATIONS];
    int rowSize = 0;

    ReservationHistory::getReservationHistoryFromFile(reservations, rowSize);

    // Start measuring time
    auto start = chrono::high_resolution_clock::now();

    int found = 0, notFound = 0;

    int resultCount = 0;

    for (int outerIndex = 0; outerIndex < 100; outerIndex++)
    {
        results[resultCount].setBookingId(datas[outerIndex]);

        // Binary search for the current datas[outerIndex] in reservations array
        int left = 0;
        int right = rowSize - 1;
        bool isFound = false;

        while (left <= right)
        {
            int mid = left + (right - left) / 2;

            if (reservations[mid].getBookingId() == datas[outerIndex]) {
                results[resultCount].setReservation(reservations[mid]);
                results[resultCount].setIsReservationFound(true);
                found++;
                isFound = true;
                break;
            }
            else if (reservations[mid].getBookingId() < datas[outerIndex]) {
                left = mid + 1;
            }
            else {
                right = mid - 1;
            }
        }

        if (!isFound)
        {
            results[resultCount].setIsReservationFound(false);
            notFound++;
        }

        resultCount++;
    }

    // End measuring time
    auto end = chrono::high_resolution_clock::now();
    chrono::duration<double> duration = end - start; // Duration in seconds
    double milliseconds = duration.count() * 1000;
    ReservationHistory::binarySearch100DataDataTable(results, 1, found, notFound, start.time_since_epoch().count(), end.time_since_epoch().count(), milliseconds, 1);
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
        ReservationHistory::displaySort(reservations, 1, 0, 0, 0.0, "", false, 0);
    }
    else if (current == 2)
    {
        Admin::adminMenu();
    }
}

void ReservationHistory::displaySort(Reservation reservations[], int current, long long start = 0, long long end = 0, double time = 0.0, string sorting_method = "", bool isImproved = true, int swap = 0)
{
    unsigned char opt = 0; int i = 1;

    ReservationHistory::sortReservationHistoryDataTable(reservations, i, current, start, end, time, sorting_method, isImproved, swap);

    while ((opt = _getch()) != RETURN) {

        if (opt == 77 && i != 10) // move right
        {
            ++i;
            if (i * 10 > ceil(100) + 10) {
                i--;
            }

            ReservationHistory::sortReservationHistoryDataTable(reservations, i, current, start, end, time, sorting_method, isImproved, swap);
            continue;
        }
        else if (opt == 75) // move left
        {
            --i;
            if (i <= 0)
                i = 1;

            ReservationHistory::sortReservationHistoryDataTable(reservations, i, current, start, end, time, sorting_method, isImproved, swap);
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
        ReservationHistory::displaySort(reservations, current, start.time_since_epoch().count(), end.time_since_epoch().count(), milliseconds, "Merge Sort", isImproved);
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
        int swap = ReservationHistory::bubbleSortByPrice(reservations, rowSize, isImproved);

        // End measuring time
        auto end = chrono::high_resolution_clock::now();
        chrono::duration<double> duration = end - start; // Duration in seconds
        double milliseconds = duration.count() * 1000; // Convert to milliseconds

        ReservationHistory::displaySort(reservations, current, start.time_since_epoch().count(), end.time_since_epoch().count(), milliseconds, "Bubble Sort", !isImproved, swap);
    }
    else if (current == 3) {
        ReservationHistory::displayReservationHistory();
    }
}

void ReservationHistory::sortReservationHistoryDataTable(Reservation reservations[], int counter, int current, long long start, long long end, double time = 0.0, string sorting_method = "", bool isImproved = true, int swap = 0)
{
    system("cls");
    cout << "\n\n\t\t\t\t1. Sort By Customer Name\t2. Sort By Highest Price " << (!isImproved ? "Without Improvement" : "With Improvement") << "\t\t3. Back" << endl;
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
        cout << "\n\t\t\t\t\t\t\tStart Time: " << start << "\tEnd Time: " << end << endl;
        cout << "\n\t\t\t\t\t\t\tTime taken for search: " << time << " milliseconds." << endl;
        cout << "\n\t\t\t\t\t\t\t" << sorting_method << " techniques is used." << endl;

        if (sorting_method == "Bubble Sort")
        {
            cout << "\n\t\t\t\t\t\t\tNumber of Swap: " << swap << endl;
        }
    }

    cout << endl << setfill(' ') << setw(80) << "> " << current;
}

void ReservationHistory::linearSearch100DataDataTable(ReservationSearchResult results[], int counter, int found, int notFound, long long start, long long end, double milliseconds, int current, bool isImproved)
{
    system("cls");
    cout << fixed;

    cout << "\n\n\t\t\t\t\t\t" << (!isImproved ? "1. Searching with Improvement" : "1. Searching without Improvement") << " \t\t2. Back" << endl;

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

    if (counter < 1)
    {
        counter = 1;
    }
    
    if (counter > 10)
    {
        counter = 10;
    }

    for (int i = (counter - 1) * 10; i < counter * 10 && i <= 100; i++)
    {
        if (results[i].getIsReservationFound())
        {
            cout << "\t|" << setfill(' ') << setw(5) << i + 1 << " |";
            cout << setfill(' ') << setw(15) << results[i].getReservation().getBookingId() << " |";
            cout << setfill(' ') << setw(20) << results[i].getReservation().getUsername() << " |";
            cout << setfill(' ') << setw(8) << results[i].getReservation().getNumberOfPeople() << " |";
            cout << setfill(' ') << setw(10) << results[i].getReservation().getNumberOfNights() << " |";
            cout << setfill(' ') << setw(15) << results[i].getReservation().getMealTypeValue() << " |";
            cout << setfill(' ') << setw(10) << (results[i].getReservation().isCarParkingRequired() ? "Yes" : "No") << " |";
            cout << setfill(' ') << setw(20) << results[i].getReservation().getRoomTypeValue() << " |";
            cout << setfill(' ') << setw(12) << results[i].getReservation().getDate() << " |";
            cout << setfill(' ') << setw(12) << setprecision(2) << results[i].getReservation().getTotalPrice() << " |";
            cout << "\n\t" << setfill('-') << setw(149) << "\n";
        }
        else
        {
            cout << "\t|" << setfill(' ') << setw(5) << i + 1 << " |";
            cout << setfill(' ') << setw(70) << results[i].getBookingId() + " is not found." << setfill(' ') << setw(70) << " |";
            cout << "\n\t" << setfill('-') << setw(149) << "\n";
        }
    }

    cout << "\n\t\t\t\t\t\t\tTotal Found: " << found << "\t\tTotal Not Found: " << notFound << endl;
    cout << "\n\t\t\t\t\t\t\tStart Time: " << start << "\tEnd Time: " << end << endl;
    cout << "\n\t\t\t\t\t\t\tTime taken for search: " << milliseconds << " milliseconds." << endl;
    cout << "\n\t\t\t\t\t\t\tLinear Search techniques is used." << endl;

    cout << "\n\n\t\t\t\t\t\t\t\t";

    cout << endl << setfill(' ') << setw(80) << "> " << current;

    unsigned char opt = 0; int i = 1;

    while ((opt = _getch()) != RETURN) {

        if (opt == 77 && i != 10) // move right
        {
            ++i;
            if (i * 10 > ceil(100) + 10) {
                i--;
            }

            ReservationHistory::linearSearch100DataDataTable(results, ++counter, found, notFound, start, end, milliseconds, current, isImproved);
            continue;
        }
        else if (opt == 75) // move left
        {
            --i;
            if (i <= 0)
                i = 1;

            ReservationHistory::linearSearch100DataDataTable(results, --counter, found, notFound, start, end, milliseconds, current, isImproved);
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
        ReservationHistory::linearSearch100Data(!isImproved);
    }
    else if (current == 2) {
        Admin::adminMenu();
    }
}

void ReservationHistory::binarySearch100DataDataTable(ReservationSearchResult results[], int counter, int found, int notFound, long long start, long long end, double milliseconds, int current)
{
    system("cls");
    cout << fixed;

    cout << "\n\n\t\t\t\t\t\t\t\t\t1. Back" << endl;

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

    if (counter < 1)
    {
        counter = 1;
    }

    if (counter > 10)
    {
        counter = 10;
    }

    for (int i = (counter - 1) * 10; i < counter * 10 && i <= 100; i++)
    {
        if (results[i].getIsReservationFound())
        {
            cout << "\t|" << setfill(' ') << setw(5) << i + 1 << " |";
            cout << setfill(' ') << setw(15) << results[i].getReservation().getBookingId() << " |";
            cout << setfill(' ') << setw(20) << results[i].getReservation().getUsername() << " |";
            cout << setfill(' ') << setw(8) << results[i].getReservation().getNumberOfPeople() << " |";
            cout << setfill(' ') << setw(10) << results[i].getReservation().getNumberOfNights() << " |";
            cout << setfill(' ') << setw(15) << results[i].getReservation().getMealTypeValue() << " |";
            cout << setfill(' ') << setw(10) << (results[i].getReservation().isCarParkingRequired() ? "Yes" : "No") << " |";
            cout << setfill(' ') << setw(20) << results[i].getReservation().getRoomTypeValue() << " |";
            cout << setfill(' ') << setw(12) << results[i].getReservation().getDate() << " |";
            cout << setfill(' ') << setw(12) << setprecision(2) << results[i].getReservation().getTotalPrice() << " |";
            cout << "\n\t" << setfill('-') << setw(149) << "\n";
        }
        else
        {
            cout << "\t|" << setfill(' ') << setw(5) << i + 1 << " |";
            cout << setfill(' ') << setw(70) << results[i].getBookingId() + " is not found." << setfill(' ') << setw(70) << " |";
            cout << "\n\t" << setfill('-') << setw(149) << "\n";
        }
    }

    cout << "\n\t\t\t\t\t\t\tTotal Found: " << found << "\t\tTotal Not Found: " << notFound << endl;
    cout << "\n\t\t\t\t\t\t\tStart Time: " << start << "\tEnd Time: " << end << endl;
    cout << "\n\t\t\t\t\t\t\tTime taken for search: " << milliseconds << " milliseconds." << endl;
    cout << "\n\t\t\t\t\t\t\tBinary Search techniques is used." << endl;

    cout << "\n\n\t\t\t\t\t\t\t\t";

    cout << endl << setfill(' ') << setw(80) << "> " << current;

    unsigned char opt = 0; int i = 1;

    while ((opt = _getch()) != RETURN) {

        if (opt == 77 && i != 10) // move right
        {
            ++i;
            if (i * 10 > ceil(100) + 10) {
                i--;
            }

            ReservationHistory::binarySearch100DataDataTable(results, ++counter, found, notFound, start, end, milliseconds, current);
            continue;
        }
        else if (opt == 75) // move left
        {
            --i;
            if (i <= 0)
                i = 1;

            ReservationHistory::binarySearch100DataDataTable(results, --counter, found, notFound, start, end, milliseconds, current);
            continue;
        }
        else if (opt == 72) // move up
        {
            if (current > 1) {
                cout << "\b \b";
                cout << --current;
            }
        }
        else if (opt == 80) // move down
        {
            if (current < 1) {
                cout << "\b \b";
                cout << ++current;
            }
        }

        fflush(stdin);
    }

    if (current == 1) {
        Admin::adminMenu();
    }
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

int ReservationHistory::bubbleSortByPrice(Reservation reservations[], int size, bool isImproved) {
    int count = 0;

    for (int i = 0; i < size - 1; i++) {
        bool swapped = false;

        int expression = isImproved ? size - 1 - i : size - 1;

        for (int j = 0; j < expression; j++) {
            if (reservations[j].getTotalPrice() < reservations[j + 1].getTotalPrice()) {
                // Swap using a temporary variable
                Reservation temp = reservations[j];
                reservations[j] = reservations[j + 1];
                reservations[j + 1] = temp;

                swapped = true;

                count++;
            }
        }

        if (isImproved && !swapped) {
            break; // Early exit if no swaps occurred
        }
    }

    return count;
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