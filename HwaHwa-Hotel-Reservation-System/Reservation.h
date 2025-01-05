#pragma once

#include <string>
#include <iostream>
#include <cstdlib>
#include <iomanip>
#include <fstream>
#include <conio.h>
#include <windows.h>
#include <sstream>
#include <fstream>
#include <chrono> 

using namespace std;

#define RETURN 13
#define BACKSPACE 8

enum RoomType
{
    SINGLE_ROOM = 1,
    DOUBLE_ROOM = 2,
    DELUXE_ROOM = 3,
    FAMILY_ROOM = 4,
    PRESIDENTIAL_ROOM = 5,
};

enum MealType
{
    BREAKFAST = 1,
    FULL_BOARD = 2,
    NONE = 0
};

class Reservation
{
public:
    Reservation();
    Reservation(string bookingId, string username, int number_of_people, int number_of_nights,
        int meal_type, bool car_parking_required, int room_type, string date, double total_price);

    static void customerReservationScreen(Reservation[], int);
    static void addCustomerReservation(Reservation[], int);

    static void confirmReservation(Reservation[], int);

    static int getReservationNights();
    static int getReservationNOP();
    static int getReservationMealType();
    static bool getReservationCarParkRequired();
    static int getReservationRoomType(int);
    static string getReservationDate();

    string getMealTypeValue();
    string getRoomTypeValue();

    // Getter methods
    string getBookingId();
    string getUsername();
    int getNumberOfPeople();
    int getNumberOfNights();
    int getMealType();
    bool isCarParkingRequired();
    int getRoomType();
    string getDate();
    double getTotalPrice();

    // Setter methods
    void setBookingId(const string id);
    void setUsername(const string user);
    void setNumberOfPeople(int people);
    void setNumberOfNights(int nights);
    void setMealType(int meal_type);
    void setCarParkingRequired(bool parking);
    void setRoomType(int type);
    void setDate(string reservationDate);
    void setTotalPrice(double price);


private:
    string bookingId;
    string username;
    int number_of_people;
    int number_of_nights;
    int meal_type;
    bool car_parking_required;
    int room_type;
    string date;
    double total_price;
};

