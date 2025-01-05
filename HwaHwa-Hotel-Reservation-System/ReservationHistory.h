#pragma once

#include "Reservation.h"

#define MAX_RESERVATIONS 11000

class ReservationHistory
{
public:
    static void getReservationHistoryFromFile(Reservation[], int&);

    static void adminSearchMenu();
    static void custSearchMenu();
    
    static void displayReservationHistory();
    static void getReservationHistoryDataTable(Reservation[], int);

    static void displaySort(Reservation [], int, double, string);
    static void sortReservationHistoryDataTable(Reservation[], int, int, double, string);

    // searching
    static int linearSearchByCustomerName(Reservation[], string, Reservation[]);
    static int binarySearchByCustomerName(Reservation[], string, Reservation[]);

    // sorting
    static void mergeSortByCustomerName(Reservation reservations[], int left, int right, Reservation temp[]);
    static void bubbleSortByPrice(Reservation reservations[], int size);
};

