#pragma once
class MonthlyStat
{
public:
	MonthlyStat();
	MonthlyStat(int, double, double);

	int getCount();
	double getTotalPrice();
	double getAvgPrice();

	void setCount(int);
	void setTotalPrice(double);
	void setAvgPrice(double);

	void calculateAvgPrice();
private:
    int count;
    double totalPrice;
    double avgPrice;
};

