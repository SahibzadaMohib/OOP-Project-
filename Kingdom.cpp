#include<iostream>
#include<cstdlib> //    For Random
#include<ctime>  //       For time 
#include"Kingdom.h"
#include<iomanip>  //   for setw
#include<fstream>

using namespace std;

Kingdom::Kingdom(int Pop , int F , int G , int S, int Count,int Turns,int Jobs,int Health,int PT,int NT ) {
	if (Pop < 0 || F < 0 || G < 0 || S>100)
		throw invalid_argument{ "Invalid Intial Kingdom values" };
	Population = new int(Pop);
	Food = new int(F);
	Gold = new int(G);
	Stability = new int(S);
	PlagueCount = new int(Count);
	TurnsWithoutFood = new int(Turns);

	//        Social Classes
	Peasonts = new int(*Population * 0.6);   //    60% Population 
	Merchants = new int(*Population * 0.2);   //   20% Merchants 
	Nobility = new int(*Population * 0.1);    //   10% Noboles 
	Miltary = new int(*Population * 0.1);     //   10% Army 
	JobsAvailable = new int(Jobs);
	HealthLevel = new int(Health);
	PeasontTax = new int(PT);
	NobleTax = new int(NT);

}
//              Destructor
Kingdom::~Kingdom() {
	delete Population;
	delete Food;
	delete Gold;
	delete Stability;
	delete Peasonts;
	delete Merchants;
	delete Nobility;
	delete Miltary;
	delete PlagueCount;
	delete TurnsWithoutFood;
	delete JobsAvailable;
	delete HealthLevel;
	delete PeasontTax;
	delete NobleTax;
}

//                Basic Functions 
void Kingdom :: collectTax() {

	int Tax = (*Population * (*PeasontTax + *NobleTax)) / 10;
	*Gold += Tax;
	*Stability -= 5;   //  Tax reduces case 
	cout << " Collected  " << Tax << "   Gold in Taxes \n";
	CheckClassConflict();
	CheckRiot();
}

void Kingdom::feedPopulation() {
	int FoodRequired = *Population * 1;
	if (FoodRequired < *Food) {
		*Food -= FoodRequired;
		cout << " Food is Enough for Population \n";
		*Stability += 5;
	}
	else {
		*Stability -= 5;
		cout << " Food is not Enough Starvation Decrease Population and Kingdom Stability Decreases\n";
		(*TurnsWithoutFood)++;
		CheckFamine();
	}
}

void Kingdom::growPopulation() {
	int bonus = 0;
	if (*Food > *Population) bonus += 5;
	if (*JobsAvailable > *Population * 0.6) bonus += 5;
	if (*HealthLevel > 50) bonus += 5;
	int growth = rand() % 200;
	*Population += growth;
	*Peasonts += growth * 0.6;
	*Merchants += growth * 0.2;
	*Nobility += growth * 0.1;
	*Miltary += growth * 0.1;
	cout << " Population is increased by  " << growth << " Peoples\n";
	JobsAvailabilty();
}

// Help Army
void Kingdom::HelpArmy(int &F, int &P, int &G) {
	F = (*Food * 10) / 100;
	*Food -= F;  //  Food Given to Army 

	P = (*Population * 10) / 100;
	*Population -= P;   // 10 Percent Population is recruitment to army 

	G = (*Gold * 15) / 100;
	*Gold -= G;    //  Population Tax 15 % Is given for Army Salary 
}

// Jobs Checking
void Kingdom::JobsAvailabilty() {
	int Job = rand() % 70;  //   Jobs Created 1 to 70 
	*JobsAvailable += Job;
}

void Kingdom::handlePlague() {
	int death = rand() % 100 + 50; //    1 to 150
	*Population -= death;
	/**Peasonts -= (death * 0.6);
	*Merchants -= (death* 0.2);
	*Nobility -= (death * 0.1);
	*Miltary -= (death * 0.1);*/
	*Stability -= 5;
	(*PlagueCount)++;
	cout << " Plague Killed  " << death << " Peoples\n";
}

//    Famine Check 
void Kingdom::CheckFamine() {
	if (*TurnsWithoutFood >= 2) {
		int death = *Population / 10;
		*Population -= death;
		cout << " Famine is Occured in Kingdom ,  Population died " << death << "  due to Starvation \n";
		*Stability -= 5;
	}
}

// Class Unfair system 
void Kingdom::CheckClassConflict() {
	if (abs(*PeasontTax - *NobleTax) >= 10) {
		cout << " Class Conflict One Class feel unfairly Treatment \n";
		*Stability -= 5;
	}
}

// Riots Check 
void Kingdom::CheckRiot() {
	if (*Stability < 40) {
		cout << " Riots Occured in the Kingdom /////////" <<
			"\n   Product and Growth are major Issue \n";
		*Stability -= 5;
	}
}

void Kingdom::displayStatus() const {
	cout << "\t\t\t\t   KINGDOM STATUS \n\n\n";
	cout << " Total Population of the Kingdom is : " << *Population <<
		"\n Total amount of Gold : " << *Gold <<
		"\n Total Food in Kingdom : " << *Food <<
		"\n Stability of Kingdom is : " << *Stability <<
		"\n Peasonts in Kingdom : " << *Peasonts <<
		"\n Merchants in Kingdom : " << *Merchants <<
		" \n Nobles in Kingdom : " << *Nobility <<
		"\n Miltary In Kingdom is : " << *Miltary <<
		"\n Jobs Available in Kingdom : " << *JobsAvailable <<
		" \n Health Level in Kingdom is : " << *HealthLevel <<
		"\n Peasont Tax Generate in Kingdom : " << *PeasontTax <<
		"\n Noble Tax Generate in Kingdom : " << *NobleTax << endl;
}

//    File Handling start 
void Kingdom::SaveFile( string Filename) {
	ofstream file(Filename);
	if (file.is_open()) {
		file << setw(35) << " TOTAL POPULATION : " << *Population << endl;
		file << setw(35) << " Amount Gold      : " << *Gold << endl;
		file << setw(35) << " TOTAL FOOD       : " << *Food << endl;
		file << setw(35) << " STABILITY        : " << *Stability << endl;
		file << setw(35) << " PEASONTS         : " << *Peasonts << endl;
		file << setw(35) << " MERCHANTS        : " << *Merchants<< endl;
		file << setw(35) << " NOBLE PEOPLE     : " << *Nobility<< endl;
		file << setw(35) << " MILTARY          : " << *Miltary << endl;
		file << setw(35) << " JOBS AVAILABLE   : " << *JobsAvailable<< endl;
		file << setw(35) << " HEALTH LEVEL     : " << *HealthLevel << endl;
		file << setw(35) << " PEASONT TAX      : " << *PeasontTax << endl;
		file << setw(35) << " NOBLE TAX        : " << *NobleTax << endl;
		file.close();
	}
}

void Kingdom::LoadFile( string Filename) {
	ifstream file1(Filename);
	if (file1.is_open()) {
		string skip;
		getline(file1, skip, ':'); file1 >> *Population; file1.ignore();
		getline(file1, skip, ':'); file1 >> *Gold; file1.ignore();
		getline(file1, skip, ':'); file1 >> *Food; file1.ignore();
		getline(file1, skip, ':'); file1 >> *Stability; file1.ignore();
		getline(file1, skip, ':'); file1 >> *Peasonts; file1.ignore();
		getline(file1, skip, ':'); file1 >> *Merchants; file1.ignore();
		getline(file1, skip, ':'); file1 >> *Nobility; file1.ignore();
		getline(file1, skip, ':'); file1 >> *Miltary; file1.ignore();
		getline(file1, skip, ':'); file1 >> *JobsAvailable; file1.ignore();
		getline(file1, skip, ':'); file1 >> *HealthLevel; file1.ignore();
		getline(file1, skip, ':'); file1 >> *PeasontTax; file1.ignore();
		getline(file1, skip, ':'); file1 >> *NobleTax; file1.ignore();
		file1.close();
	}
}
////////////////////////////////////////////////////

//   Food Production 
void Kingdom::Production() {
	int Product = rand() % 2000;   //  Food production from 1 to 2000 
	*Food += Product;
	if (Product > 900) {
		cout << " This Year food Production is good Enough for Kingdom \n";
		cout << " Production is : " << Product << endl;
		*Stability += 5;
	}
	else {
		cout << " This Year Food is not Enough that brings Famine in Kingdom\n";
		cout << " Production is : " << Product << endl;
		*Stability -= 2;
	}
}

//         Gertter and Setter 
int Kingdom::getPopulation() const {
	return *Population;
}
void Kingdom::setPopulation(int Pop) {
	*Population = Pop;
}

int Kingdom::getFood() const {
	return *Food;
}
void Kingdom::setFood(int F) {
	*Food = F;
}

int Kingdom::getGold() const {
	return*Gold;
}
void Kingdom::setGold(int G) {
	*Gold = G;
}

int Kingdom::getStability() const {
	return*Stability;
}
void Kingdom::setStability(int S) {
	*Stability = S;
}

