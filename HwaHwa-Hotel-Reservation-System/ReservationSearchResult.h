#pragma once
#include "Reservation.h"

class ReservationSearchResult
{
	public:
	ReservationSearchResult();
	ReservationSearchResult(string, bool, Reservation);
	~ReservationSearchResult();
	
	string getBookingId();
	bool getIsReservationFound();
	Reservation getReservation();

	void setBookingId(string);
	void setIsReservationFound(bool);
	void setReservation(Reservation);

private:
	string bookingId;
	bool IsReservationFound;
	Reservation reservation;
};

