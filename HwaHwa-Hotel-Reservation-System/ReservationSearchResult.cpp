#include "ReservationSearchResult.h"

ReservationSearchResult::ReservationSearchResult()
{
}

ReservationSearchResult::ReservationSearchResult(string bookingId, bool isReservationFound, Reservation reservation)
{
	this->bookingId = bookingId;
	this->IsReservationFound = isReservationFound;
	this->reservation = reservation;
}

ReservationSearchResult::~ReservationSearchResult()
{
}


string ReservationSearchResult::getBookingId()
{
	return this->bookingId;
}

bool ReservationSearchResult::getIsReservationFound()
{
	return this->IsReservationFound;
}

Reservation ReservationSearchResult::getReservation()
{
	return this->reservation;
}

void ReservationSearchResult::setBookingId(string bookingId)
{
	this->bookingId = bookingId;
}

void ReservationSearchResult::setIsReservationFound(bool isReservationFound)
{
	this->IsReservationFound = isReservationFound;
}

void ReservationSearchResult::setReservation(Reservation reservation)
{
	this->reservation = reservation;
}