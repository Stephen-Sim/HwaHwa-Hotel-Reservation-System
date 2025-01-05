#pragma once

#include "Reservation.h"
#include "ReservationSearchResult.h"

#define MAX_RESERVATIONS 11000

class ReservationHistory
{
public:
    static void getReservationHistoryFromFile(Reservation[], int&);

    static void adminSearchMenu();
    static void custSearchMenu();

    static void monthlyAnalysisDataTable(int);

    static void linearSearch100Data(bool);
    static void binarySearch100Data();
    
    static void displayReservationHistory();
    static void getReservationHistoryDataTable(Reservation[], int);

    static void displaySort(Reservation [], int, long long, long long, double, string, bool, int);
    static void sortReservationHistoryDataTable(Reservation[], int, int, long long, long long, double, string, bool, int);

    static void linearSearch100DataDataTable(ReservationSearchResult[], int, int, int, long long, long long, double, int, bool);
    static void binarySearch100DataDataTable(ReservationSearchResult [], int , int , int , long long , long long , double, int);

    // searching
    static int linearSearchByCustomerName(Reservation[], string, Reservation[]);
    static int binarySearchByCustomerName(Reservation[], string, Reservation[]);

    // sorting
    static void mergeSortByCustomerName(Reservation reservations[], int left, int right, Reservation temp[]);
    static int bubbleSortByPrice(Reservation reservations[], int size, bool);
};

