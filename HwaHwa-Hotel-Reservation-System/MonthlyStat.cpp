#include "MonthlyStat.h"

MonthlyStat::MonthlyStat()
{
}

MonthlyStat::MonthlyStat(int count, double totalPrice, double avgPrice)
{
	this->count = count;
	this->totalPrice = totalPrice;
	this->avgPrice = avgPrice;
}

int MonthlyStat::getCount()
{
	return this->count;
}

double MonthlyStat::getTotalPrice()
{
	return this->totalPrice;
}

double MonthlyStat::getAvgPrice()
{
	return this->avgPrice;
}

void MonthlyStat::setCount(int count)
{
	this->count = count;
}

void MonthlyStat::setTotalPrice(double totalPrice)
{
	this->totalPrice = totalPrice;
}

void MonthlyStat::setAvgPrice(double avgPrice)
{
	this->avgPrice = avgPrice;
}

void MonthlyStat::calculateAvgPrice()
{
	this->avgPrice = this->totalPrice / this->count;
}