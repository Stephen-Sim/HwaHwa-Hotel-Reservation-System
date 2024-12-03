#pragma once
#include "Reservation.h"
#include <vector>
#include <algorithm>

#define iValue ((counter - 1) * 10)
#define dataTableSize i < reservations.size() && i < counter * 10

class ReservationHistory
{
public:
	static vector<Reservation> getReservationHistoryFromFile();

	static void custSearchMenu(vector <Reservation>);
	static void adminSearchMenu(vector <Reservation>);
	
	static bool compareByUsername(Reservation&, Reservation&);
	static void displayReservationHistory();
	static void getReservationHistoryDataTable(vector <Reservation>, int);
	static vector<Reservation> getFirst100Reservations(vector<Reservation> reservations);
	static void displaySort(vector<Reservation>& reservations, int current, double, string);
	static void sortReservationHistoryDataTable(vector<Reservation>, int, int, double, string);
	
	// searching
	static vector<Reservation> linearSearchByCustomerName(vector <Reservation>, string);
	static vector<Reservation> binarySearchByCustomerName(vector<Reservation>&, string);


	// sorting
	static vector<Reservation> mergeSortByCustomerName(vector<Reservation>);
	static vector<Reservation> bubbleSortByPrice(vector<Reservation>);
};

