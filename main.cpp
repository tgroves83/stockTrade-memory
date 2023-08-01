#include "Portfolio.h"
#include "StockTrade.h"
#include "UserInterface.h" // Include the UserInterface header

int main() {
    Portfolio portfolio; // Create an object of portfolio
    UserInterface userInterface; // Create an object of the UserInterface

    // Record some sample trades
    StockTrade trade1(1, "AAPL", "buy", 10, 150.0);
    portfolio.recordTrade(trade1);

    StockTrade trade2(2, "GOOGL", "buy", 5, 2500.0);
    portfolio.recordTrade(trade2);

    StockTrade trade3(3, "AAPL", "sell", 5, 160.0);
    portfolio.recordTrade(trade3);

    StockTrade trade4(4, "MSFT", "buy", 8, 300.0);
    portfolio.recordTrade(trade4);

    // Calculate and display the portfolio value
    portfolio.calculatePortfolioValue();

    // Use the UserInterface to interact with the user
    userInterface.processOption(portfolio);

    return 0;
}