#ifndef ECONOMY_H
#define ECONOMY_H
#include<string>

using namespace std;

class Economy {
	int* Gold;  // Kingdom Treasury from Economy 
	int* PeasontTax; // Tax rate for Peasonts 
	int* NobleTax; //   Tax rate for Nobles 
	int* Inflation;// over Taxes or Printing too much money 
	int* PublicService; // Budget for Hospitals,food Dustribution 
	int* CorruptionLevel; // Corruption effects the stability level 
	bool* MarketCrash; // Market crash due to war,bankcorrupt,LoanDepends
	bool* LoanToken; // Taking Loan to weak kingdom

public:
	Economy(int gold);
	~Economy();

	void CollectTax(int Peasont, int Noble);
	void ManageTaxRate(int PeasontTax, int NobleTax);


	void AllocateBudget(int amount);
	void MarketCrassh();
	void PrintMoney(int amount);
	void Randomevent();

	void Display();

	int GetGold() const;
	int GetInflation() const;
	bool IsMarketCrash() const;
	bool IsLoanTaken() const;

	//   File Handling structure 
	void SaveFile(string Filename);
	void LoadFile(string Filename);
};

#endif