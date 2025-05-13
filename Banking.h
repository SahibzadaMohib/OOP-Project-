#pragma once                                                                                                                 
#ifndef BANKING_H
#define BANKING_H
#include<iostream>
#include<string>
using namespace std;


class Bank {
public:
    double treasury;
    double loanAmount;
    double interestRate;
    bool isLoanActive;
    bool corruptOfficial;

    int logIndex;

    //Funtions
    Bank(double initialFunds);
    void takeLoan(double amount);
    void repayLoan(double amount);
    void simulateCorruption();
    void audit();
    void showTreasury();

    // File Handling 
    void SaveFile(string filename) ;
    void LoadFile(string filename);


};

#endif