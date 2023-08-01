#pragma once

// Authors: Pusit Treeraganont, Syed Mystafa, Gian Flores, Tiffany Groves
// Purpose: Group Assignment - Stock Trading

#ifndef _STOCK_TRADE_
#define _STOCK_TRADE_

#include <iostream>
#include <vector>

class StockTrade {
private:
	int id; // the unique identifier for each stock trade.
	std::string symbol; //the stock symbol for the trade
	std::string type; // the trade type, either "buy" or "sell".
	double quantity; //the number of shares or quantity traded
	double price; // mean price per 1 quantity
	double averagePurchasePrice; // the average purchase price per quantity of the stock
public:
	StockTrade(); //default constructor
	StockTrade(int id, std::string ss, std::string tt, double qty, double pr); //constructor which initializes StockTrade object with specific values for each data member
	StockTrade(const StockTrade& t); //copy constructor
	StockTrade& operator=(const StockTrade& t); //assignment operator which allows assigning one StockTrade object to another
	int getId() const; //getter method for trade ID
	std::string getSymbol() const; //getter method for trade symbol
	std::string getType() const; //getter method for trade type
	double getQuantity() const; //getter method for trade quantity
	double getPrice() const; //getter method for trade price

	double getAveragePurchasePrice() const; //getter method for the average purchase price per stock item
	void setAveragePurchasePrice(double newPrice); //setter method for the average purchase price per stock item
	void addQuantity(double q); //method to add more quantity to the trade item

	
	// Methods to calculate current value and profit/loss
	double getCurrentValue(double currentPrice) const;
	double getProfitLoss(double currentPrice) const;

	//Equality operator to check if two StockTrade objects are equal
	bool operator==(const StockTrade& t) const;
};

#endif
