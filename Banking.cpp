#include<iostream>
#include "Banking.h"
#include<cstring>
#include<string>
#include<fstream>
#include<iomanip>
using namespace std;

Bank::Bank(double initialFunds) {
    treasury = initialFunds;
    loanAmount = 0;
    interestRate = 0.2;
    isLoanActive = false;
    corruptOfficial = false;
    logIndex = 0;


}

void Bank::takeLoan(double amount) {
    if (isLoanActive) {


        cout << "Attempted loan while one is active." << endl;
        cout << "Error: Loan already active!\n";
        return;
    }
    loanAmount = amount + (amount * interestRate);
    treasury += amount;
    isLoanActive = true;
    cout << "Loan taken: " + to_string(amount) + " | To repay: " + to_string(loanAmount) << endl;

}

void Bank::repayLoan(double amount) {
    if (!isLoanActive) {

        cout << "Error: No active loan to repay!\n";
        return;
    }

    if (amount < loanAmount) {

        cout << "Error: Incomplete repayment! Land seized.\n";
        treasury -= 50;  // penalty
    }
    if (amount > loanAmount) {

        cout << "Extra payment detected.The extra amount has been refunded to your treasury" << endl;
        treasury -= amount;
        amount -= loanAmount;
        treasury += amount;

    }
    else {
        treasury -= amount;
        cout << "Loan repaid: " + to_string(amount) << endl;

    }

    isLoanActive = false;
    loanAmount = 0;
}

void Bank::simulateCorruption() {
    srand(time(0));
    int chance = rand() % 2;
    corruptOfficial = (chance == 1);
    if (corruptOfficial) {
        double stolen = treasury * 0.1;
        treasury -= stolen;
        cout << "Corruption occurred! Stolen: " + to_string(stolen) << endl;

    }
    else {
        cout << "No corruption this round." << endl;

    }
}

void Bank::audit() {
    treasury -= 10;
    cout << "Audit performed. Cost: 10" << endl;


    if (corruptOfficial) {
        corruptOfficial = false;
        cout << "Corruption found and stopped." << endl;

    }
    else {
        cout << "Audit found no corruption." << endl;

    }
}

void Bank::showTreasury() {
    cout << "Current Treasury: " << treasury << "\n";
}

//  File Handling start 
void Bank::SaveFile(string filename) {
    std::ofstream file(filename);
    if (file.is_open()) {
        file << std::setw(30) << "Treasury: " << treasury << "\n";
        file << std::setw(30) << "LoanAmount: " << loanAmount << "\n";
        file << std::setw(30) << "InterestRate: " << interestRate << "\n";
        file << std::setw(30) << "IsLoanActive: " << isLoanActive << "\n";
        file << std::setw(30) << "CorruptOfficial: " << corruptOfficial << "\n";
        file.close();
    }
}

void Bank::LoadFile(string filename) {
    std::ifstream file(filename);
    if (file.is_open()) {
        std::string skip;
        file >> skip >> treasury;
        file >> skip >> loanAmount;
        file >> skip >> interestRate;
        file >> skip >> isLoanActive;
        file >> skip >> corruptOfficial;
        file.close();
    }
}