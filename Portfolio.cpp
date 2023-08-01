#include <string>
#include <vector>
#include <map>
#include <algorithm>
#include <numeric>
#include "StockTrade.h"
#include "Portfolio.h"

using namespace std;

void Portfolio::recordTrade(const StockTrade& trade) {
    
    trades.push_back(trade); //adds user input of the trade into the trades vector
    

    string type = trade.getType(); //checks and stores trade type into variable
    string symbol = trade.getSymbol(); //checks and stores trade symbol into variable
    if (type != "buy" && type != "sell") { //validates trade type
        return;
    }
    if (type == "sell"){
        if (portfolio.find(symbol) == portfolio.end()) {
            portfolio[symbol] = trade;
            stockQuantity[symbol] = trade.getQuantity();
            return;
        }
    }

    double totalInvestment = trade.getQuantity() * trade.getPrice();
    double oldAveragePurchasePrice = portfolio[symbol].getAveragePurchasePrice() * stockQuantity[symbol];

    //checks the trade type to update portfolio and stock quantity
    if (type == "buy") { //checks trade type to see if it is a buy type

        double newAveragePurchasePrice =
            (oldAveragePurchasePrice + totalInvestment) /
            (stockQuantity[symbol] + trade.getQuantity()); //calculates new average purchase price and stores it in a variable

        stockQuantity[symbol] += trade.getQuantity();

        portfolio[symbol].addQuantity(trade.getQuantity()); //adds stock sold back into stock quantity
        portfolio[symbol].setAveragePurchasePrice(newAveragePurchasePrice); //sets new average purchase price
    }
    else if (type == "sell") { //checks trade type to see if it is a sell type
        double newAveragePurchasePrice =
        (oldAveragePurchasePrice - totalInvestment) /
        (stockQuantity[symbol] + trade.getQuantity()); //calculates new average purchase price and stores it in a variable

        stockQuantity[symbol] -= trade.getQuantity();
        portfolio[symbol].addQuantity(-trade.getQuantity()); //subtracts stock sold from stock quantity
        portfolio[symbol].setAveragePurchasePrice(newAveragePurchasePrice); //sets new average purchase price

    }

    std::cout << "Trade recorded successfully.\n";
}

void Portfolio::calculatePortfolioValue() {
    double portfolioValue = 0.0; //initializes variable to zero
    for (auto const& [key, val] : portfolio) { //iterates through each stock item in the portfolio map
        double currentPrice = getCurrentStockPrice(key); //gets current stock price for each symbol
        double currentValue = val.getCurrentValue(currentPrice); //gets current value of each stock trade based on current price
        double profitLoss = val.getProfitLoss(currentPrice); //calculates profit loss for each stock trade

        portfolioValue += currentValue; //adds current value of stock item to total portfolio value

        //displays symbol, quantity, current value and profit loss for each stock item
        std::cout << "Symbol: " << key << ", Quantity: " << stockQuantity[key]
            << ", Current Value: " << currentValue << ", Profit/Loss: " << profitLoss << std::endl;
    }

    //displays total portfolio value
    std::cout << "Total Portfolio Value: " << portfolioValue << std::endl;
}

// mock value
double Portfolio::getCurrentStockPrice(const std::string& symbol) const {
    if (symbol == "AAPL") {
        return 150.0;
    }
    else if (symbol == "GOOGL") {
        return 2500.0;
    }
    else if (symbol == "MSFT") {
        return 300.0;
    }
    return 0.0;
}

//method to iterate through the trades vector and display each element by element name
void Portfolio::displayTradeHistory() const { 
    std::cout << "-------------------------\n";
    std::cout << "Printout of Trade History\n";
    std::cout << "-------------------------\n";
        
    for (const auto& trade : trades) { //iterates through trade vector
        std::cout << "Trade ID: " << trade.getId() //displays messages to user
        << ", Stock Symbol: " << trade.getSymbol()
        << ", Trade Type: " << trade.getType()
        << ", Quantity: " << trade.getQuantity()
        << ", Price: " << trade.getPrice() << "\n";
    }
}

int Portfolio::validateSymbol(std::string stockSymbol) const {
    
    std::cout << "Checking for entered stock item...\n";
    int symbolChecker = 0;
    for (const auto& trade : trades) { //iterates through trade vector
       std::string symbol = trade.getSymbol();
        if (symbol == stockSymbol) {
            symbolChecker = 1;
        }
    }
    return symbolChecker;
}

double Portfolio::currentQuantity(std::string stockSymbol) const {
    int quantityGetter = 0;
    for (const auto& trade : trades) { //iterates through trade vector
        std::string symbol = trade.getSymbol();
        std::string type = trade.getType();
        if (symbol == stockSymbol) {
            if (type == "sell") {
                quantityGetter -= trade.getQuantity();
            }
            else {
                quantityGetter += trade.getQuantity();
            }
        }
    }
    std::cout << "Currrent quantity of " << stockSymbol << " is: " << quantityGetter << std::endl;
    return quantityGetter;
}

void Portfolio::calculatePositions()  { 
    std::vector<std::pair<int, std::string>> positionsVector;//A vector to store the positions of stock items
    std::vector<std::pair<std::string, double>> currentValueVector;//A vector to store the current price by stock item


    for (auto const& [key, val] : portfolio) { //iterates through each stock item in the portfolio map
        double currentPrice = getCurrentStockPrice(key); //iterates through each stock item in the portfolio map
        double value = val.getCurrentValue(currentPrice);

        std::pair<std::string, double> currentValue(key, value); //creates pair of stock symbol and stock price  
        currentValueVector.push_back(currentValue);  //inserts pair into a vector
    }
     
    //sorts vector in descending order
    std::sort(currentValueVector.begin(), currentValueVector.end(), []
        (std::pair<std::string, double>& a, std::pair<std::string, double>& b) {
        return a.second > b.second;
        });

    int rank = 1; //variable to keep track of portfolio item rank
    for (const auto& data : currentValueVector) //iterates through currentValueVector
    {
        const std::string& symbol = data.first; //stores the first of the pair to variable
        std::pair<int, std::string> position(rank, symbol); //creates pair of rank and stock symbol
        positionsVector.push_back(position); //pushes pair into positonsVector
        rank++; //increases rank number by 1
    }

    std::cout << "------------------------------\n";
    std::cout << "Display of Portfolio Positions\n";
    std::cout << "------------------------------\n";
    for (const auto& data : positionsVector) //iterates through positionsVector
    {
        int position = data.first; //creates variable to store first of the pair 
        const std::string& symbol = data.second; //creates variable to store second of the pair

        std::cout << "The position of " << symbol << " is: " << position << std::endl; //displays position message to user
    }
}

void Portfolio::calculateAndDisplayProfitLoss() 
{
    std::cout << "------------------------------------------\n";
    std::cout << "Display of Porfit/Loss for each stock item\n";
    std::cout << "------------------------------------------\n";
    double portfolioValue = 0.0; //initializes variable to zero
    for (auto const& [key, val] : portfolio) { //iterates through each stock item in the portfolio map
        double currentPrice = getCurrentStockPrice(key); //gets current stock price for each stock symbol and stores in variable
        double currentValue = val.getCurrentValue(currentPrice); //gets current value of each stock trade based on current price and stores in variable
        double profitLoss = val.getProfitLoss(currentPrice); //calculates profit loss for stock item and stores in variable

        //displays symbol and profit loss for each stock item
        std::cout << "Symbol: " << key <<  ", Profit/Loss: " << profitLoss << std::endl;
    }
}




