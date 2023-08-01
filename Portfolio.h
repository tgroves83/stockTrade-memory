#pragma once
#ifndef _PORTFOLIO_
#define _PORTFOLIO_

#include <string>
#include <vector>
#include <map>
#include <algorithm>
#include "StockTrade.h"


/**
 * this class holds list of trades, you bought or sell
 *
 * this class contains abilities to get current percentage of stock you hold
 **/
class Portfolio {
public:
	void recordTrade(const StockTrade& trade); //Method to record a new trade and update the portfolio, quantity and average purchase price
	void calculatePortfolioValue(); //Method to calculate and display the total value of the portfolio
	const std::vector<StockTrade>& getTrades() const { //method to get trades from trades vector
		return trades;
	}
	const std::map<std::string, double> getQuantity() { //method to get quantities from stockQuantity map 
		return stockQuantity;
	}
	void displayTradeHistory() const; //method to display trade history
	void calculatePositions(); //method to calculate new positions of stock items
    void calculateAndDisplayProfitLoss(); //method to calculate and display profit/loss
	int validateSymbol(std::string) const;
	double currentQuantity(std::string) const;

private:
	std::vector<StockTrade> trades; //A vector to store the list of StockTrade objects
	std::map<std::string, StockTrade> portfolio; //A map of stock symbols as keys and StockTrade objects as values
	std::map<std::string, double> stockQuantity; //A map of stock symbols as keys and total quantity of stock as values
	
public:
	double getCurrentStockPrice(const std::string& symbol) const; //getter method for current stock price
};



#endif
