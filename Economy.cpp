#include<iostream>
#include<string>
#include"Economy.h"
#include<fstream>
#include<iomanip>

using namespace std;

Economy::Economy(int gold) {
	Gold = new int(gold);
	PeasontTax = new int(5);  // Tax 5% from Peasont
	NobleTax = new int(10);   // Tax 10% from Noble
	Inflation = new int(0);   // No Inflation Occur
	PublicService = new int(0); // No Public services 
	CorruptionLevel = new int(10);  // Starting 10%
	MarketCrash = new bool(false);   // No Market Crash
	LoanToken = new bool(false); // No Loan Taken
}

Economy :: ~Economy() {
	delete Gold;
	delete PeasontTax;
	delete NobleTax;
	delete Inflation;
	delete PublicService;
	delete CorruptionLevel;
	delete MarketCrash;
	delete LoanToken;
}

void Economy::CollectTax(int Peasont, int Noble) {
	int Ptax = (Peasont * (*PeasontTax)) - (*CorruptionLevel);
	int Ntax = (Noble * (*NobleTax)) - (*CorruptionLevel);
	int TTax = max(0, Ptax + Ntax);

	*Gold += TTax;

	if (*PeasontTax > 10 || *NobleTax > 15) {
		(*Inflation)+=12;
		cout << " Over Taxation can occur Inflation \n";
	}
	if (*NobleTax > 30) {
		(*Inflation)+=22;
		cout << " Revolt!!! Nobles are unhappy due to high unfair taxes\n";
	}
	cout << " Collected Amount of Gold is / Tax \n";
	cout << TTax;
	cout << "\n Total Amount for Gold is : " << *Gold << endl;
}

void Economy::ManageTaxRate(int PTax, int Ntax) {
	*PeasontTax = PTax;
	*NobleTax = Ntax;
	cout << " Taxes are updated :  Peasonts Tax " << *PeasontTax << "%   || Nobles Tax  " << *NobleTax << "%" << endl;
}

//   Allocate Budget 
void Economy::AllocateBudget(int amount) {
	if (amount > *Gold) {
		cout << " Insufficient Gold to allocate this much for Services \n";
		return;
	}
	*Gold -= amount;
	cout << " Allocated " << amount << " Gold for Hospitals and Food\n";
}

// Market Crash 
void Economy::MarketCrassh() {
	*MarketCrash = true;
	*Gold /= 2;
	cout << " Kingdom has lost its Half money due to Market crash \n";
	cout << " Amount Left in Kingdom : " << *Gold << " Gold \n";
}

// Print money 
void Economy::PrintMoney(int amount) {
	*Gold += amount;
	(*Inflation)++;
	cout << " Printed " << amount << " Gold , Inflation has increased \n";
}

// Random event 
void Economy::Randomevent() {
	int event = rand() % 4;
	switch (event) {
	case 0:
		cout << " Trade Boosted the Economy\n";
		*Gold += 300;
		break;
	case 1:
		cout << " War Occured : Economy has Affected \n";
		*Gold -= 150;
		break;
	case 2:
		cout << " Corruption Scanadal\n";
		*CorruptionLevel += 5;
	case 3:
		cout << " Noble donations Strengthen Treasury \n";
		*Gold += 150;
	}
}

// Display Economy Status
void Economy::Display() {
	cout << "\t\t ========= ECONOMY STATUS ===========\n";
	cout << " Gold From Economy : " << *Gold <<
		"\n Tax Rate (Peasonts ) : " << *PeasontTax << "%" <<
		"\n Tax Rate (Nobles ) : " << *NobleTax << "%" <<
		"\n Inflation in Kingdom : " << *Inflation << "%" <<
		"\n Amount for Public Services : " << *PublicService << "%" <<
		"\n Corruption Level in Economy : " << *CorruptionLevel << "%" <<
		"\n Market Crash In Economy : " << (*MarketCrash ? " Yes " : " No ") <<
		"\n Loan Taken In Economy : " << (*LoanToken ? " Yes " : " No ") << endl;
}

//    File Handling start 
void Economy::SaveFile(string Filename) {
	ofstream file(Filename);
	if (file.is_open()) {
		file << setw(35) << " Amount Gold      : " << *Gold << endl;
		file << setw(35) << " INFLATION      : " << *Inflation << endl;
		file << setw(35) << " PUBLIC SERVICE        : " << *PublicService << endl;
		file << setw(35) << " CORRUPTION IN MARKET       : " << *CorruptionLevel << endl;
		file << setw(35) << " MARKET CRASH       : " << *MarketCrash << endl;
		file << setw(35) << " LOAN SYSTEM    : " << *LoanToken << endl;
		file << setw(35) << " PEASONT TAX      : " << *PeasontTax << endl;
		file << setw(35) << " NOBLE TAX        : " << *NobleTax << endl;
		file.close();
	}
}

void Economy::LoadFile(string Filename) {
	ifstream file1(Filename);
	if (file1.is_open()) {
		string skip;
		getline(file1, skip, ':'); file1 >> *Gold; file1.ignore();
		getline(file1, skip, ':'); file1 >> *Inflation; file1.ignore();
		getline(file1, skip, ':'); file1 >> *PublicService; file1.ignore();
		getline(file1, skip, ':'); file1 >> *CorruptionLevel; file1.ignore();
		getline(file1, skip, ':'); file1 >> *MarketCrash; file1.ignore();
		getline(file1, skip, ':'); file1 >> *LoanToken; file1.ignore();
		getline(file1, skip, ':'); file1 >> *PeasontTax; file1.ignore();
		getline(file1, skip, ':'); file1 >> *NobleTax; file1.ignore();
		file1.close();
	}
}
////////////////////////////////////////////////////


// Getter Functions 
int Economy::GetGold() const {
	return*Gold;
}
int Economy::GetInflation() const {
	return*Inflation;
}
bool Economy::IsMarketCrash() const {
	return*MarketCrash;
}
bool Economy::IsLoanTaken() const {
	return*LoanToken;
}