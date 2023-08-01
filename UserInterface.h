#pragma once

#ifndef USERINTERFACE_H
#define USERINTERFACE_H

#include "StockTrade.h"
#include "Portfolio.h"

class UserInterface {
private:
    Portfolio portfolio; //Instance of Portfolio class to interact with trades and portfolios

public:
    void displayMenu() const; //Method to create and display menu options to user
    void processOption(Portfolio& portfolio); //Method to process user's choice and execute corresponding action
    
    void recordTrade(); //Method to record new trade
};

#endif
