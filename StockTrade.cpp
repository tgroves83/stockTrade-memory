#include "StockTrade.h"

using namespace std;

StockTrade::StockTrade() { //default constructor for StockTrade class
	id = 0;
	symbol = "";
	type = "";
	quantity = 0.0;
	price = 0.0;
	averagePurchasePrice = 0.0;
}

StockTrade::StockTrade(int _id, string _symbol, string _type, double _qty, double _price) : //constructor for StockTrade class
	id(_id), symbol(_symbol), type(_type), quantity(_qty), price(_price)
{
	averagePurchasePrice = price;
}

StockTrade::StockTrade(const StockTrade& t) {
	*this = t;
}

StockTrade& StockTrade::operator=(const StockTrade& t) {
	id = t.id;
	symbol = t.symbol;
	type = t.type;
	quantity = t.quantity;
	price = t.price;
	averagePurchasePrice = t.averagePurchasePrice;
	return *this;
}

int StockTrade::getId() const { //method to get id from StockTrade class
	return id;
}

string StockTrade::getSymbol() const { //method to get symbol from StockTrade class
	return symbol;
}

string StockTrade::getType() const { //method to get trade type from StockTrade class
	return type;
}

double StockTrade::getQuantity() const { //method to get quantity of stock item from StockTrade class
	return quantity;
}

double StockTrade::getPrice() const { //method to get item price from StockTrade class
	return price;
}

double StockTrade::getAveragePurchasePrice() const { //method to get avergae purchase price from StockTrade class
	return averagePurchasePrice;
}

double StockTrade::getCurrentValue(double currentPrice) const { //method to get current value from StockTrade class
	return currentPrice * quantity;
}

double StockTrade::getProfitLoss(double currentPrice) const { //method to calculate profit/loss
	return getCurrentValue(currentPrice) - (quantity * averagePurchasePrice);
}

bool StockTrade::operator==(const StockTrade& t) const {
	return t.id == t.id;
}

void StockTrade::setAveragePurchasePrice(double newPrice) { //method to set average purchase price
	averagePurchasePrice = newPrice;
}

void StockTrade::addQuantity(double q) { //method to add quantity to stock 
	quantity += q;
}