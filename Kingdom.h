#pragma once
#ifndef EXAMPLE_K
#define EXAMPLE_K
#include<string>
using namespace std;

class Kingdom {
	//         Resources 
private:
	int* Population;
	int* Food;
	int* Gold;
	int* Stability;
    int* PlagueCount;
    int* TurnsWithoutFood;
	//         Social Classes 
	int* Peasonts;
	int* Merchants;
	int* Nobility;
	int* Miltary;
    int* JobsAvailable;
    int* HealthLevel;
    int* PeasontTax;
    int* NobleTax;

public:
    Kingdom(int Pop = 1000, int F = 600, int G = 1000, int S = 80, int Count = 0, int Turns = 0, int Jobs = 700, int Health = 60, int PT = 10, int NT = 5);
	~Kingdom();

    // Basic Functions
    void collectTax();
    void feedPopulation();
    void growPopulation();
    void handlePlague();
    void Production();  //    Food for Population 
    void CheckFamine();
    void CheckRiot();
    void CheckClassConflict();
    void JobsAvailabilty();
    void HelpArmy(int &F,int &P,int &G);
    void displayStatus() const;

    // Getters and Setters
    int getPopulation() const ;
    void setPopulation(int pop);

    int getFood() const;
    void setFood(int f);

    int getGold() const;
    void setGold(int g);

    int getStability() const;
    void setStability(int s);

    //   File Handling structure 
    void SaveFile( string Filename);
    void LoadFile( string Filename);

};


#endif
