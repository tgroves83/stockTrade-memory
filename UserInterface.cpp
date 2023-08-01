#include "Portfolio.h"
#include "UserInterface.h"
#include <iostream>
#include <limits>

void UserInterface::displayMenu() const { //display of menu options to user
    std::cout << "===== Stock Trading System =====\n";
    std::cout << "1. Record Trade\n";
    std::cout << "2. View Portfolio Positions\n";
    std::cout << "3. Calculate Portfolio Value\n";
    std::cout << "4. Calculate Profit/Loss\n";
    std::cout << "5. Display Trade History\n";
    std::cout << "0. Exit\n";
}

//method to provide switch cases to correspond with user choice
void UserInterface::processOption(Portfolio& pf) {
    portfolio = pf;

    int option; //variable to store user choice
    do {
        displayMenu();
        std::cout << "Enter an option: ";
        std::cin >> option; //storing user choice
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

        switch (option) {
        case 1:
            recordTrade();
            break;
        case 2:
            portfolio.calculatePositions();
            break;
        case 3:
            portfolio.calculatePortfolioValue();
            break;
        case 4:
            portfolio.calculateAndDisplayProfitLoss();
            break;
        case 5:
            portfolio.displayTradeHistory();
            break;
        case 0:
            std::cout << "Exiting...\n";
            break;
        default:
            std::cout << "Invalid option. Please try again.\n";
        }
    } while (option != 0);
}

void UserInterface::recordTrade() {
    

    int tradeId, userQuantity;
    std::string stockSymbol, tradeType;
    double price;

    std::cout << "Enter Trade ID: ";
    std::cin >> tradeId;
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

    /*Validating Trade Type: if the input is invalid, display an error message asking the user to enter a valid
     trade type.*/
    std::cout << "Enter Trade Type (buy/sell): "; //display message to user
    std::getline(std::cin, tradeType);
    if (tradeType != "buy" && tradeType != "sell")
    {
        std::cout << "Please enter a valid trade type" << std::endl;
        return;
    }

    /* Validating Stock Symbols: In the user interface, when users enter the stock symbol for a trade,
    system checks if the symbol exists in your database of available stocks.
    If the symbol is not found, system displays an error message prompting the user to enter a valid stock symbol.*/
    std::cout << "Enter Stock Symbol: "; //display message to user
    std::getline(std::cin, stockSymbol);

    if (tradeType == "sell") {
        int stockSymbolCheck = portfolio.validateSymbol(stockSymbol);
        if (stockSymbolCheck == 0) {
            std::cout << "Stock item doesn't exist. Please enter a valid trade symbol" << std::endl;
            return;
        }
        
    }
    
    double stockQuantity = portfolio.currentQuantity(stockSymbol);


    /*Validating Trade Quantities: if the input is invalid, display an error message asking the user to enter a valid
     quantity.*/
    std::cout << "Enter Quantity: "; //display message to user
    std::cin >> userQuantity;
       
    if ( tradeType == "sell" && stockQuantity < userQuantity)
    {
        std::cout << "There is not enough quantity for this trade. Quantity remaining = " << stockQuantity << std::endl;
        return;
    }
    
    std::cout << "Enter Price: "; //displays message to user
    std::cin >> price; //stores user input to variable
    if (price <= 0) { //validating price entered
        std::cout << "Enter a positive amount"; //if not true, displays error message
        return;
    }
    
    StockTrade trade(tradeId, stockSymbol, tradeType, userQuantity, price); //creates trade object with user input 
    portfolio.recordTrade(trade); //calls recordTrade method from portfolio.h and uses trade object as parameter
    
}




