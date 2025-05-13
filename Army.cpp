#include <iostream>
#include <string>
#include <cstdlib>
#include <thread>
#include <chrono>
#include "Army.h"
#include<fstream>
#include<iomanip>

using namespace std;

Army::Army(int Soldiers, int G, int Food, int Level) {
    if (Soldiers < 0 || G < 0 || Food < 0 || Level < 0)
        throw invalid_argument("Invalid Army Requirements");

    TotalSoldiers = Soldiers;
    Gold = G;
    FoodSupply = Food;
    BlacksmithLevel = Level;
    Morale = 70;
    TrainedSoldiers = Soldiers / 2;
}

// Copy Constructor
Army::Army(const Army& other) {
    TotalSoldiers = other.TotalSoldiers;
    TrainedSoldiers = other.TrainedSoldiers;
    Gold = other.Gold;
    FoodSupply = other.FoodSupply;
    Morale = other.Morale;
    BlacksmithLevel = other.BlacksmithLevel;
}

// Copy Assignment
Army& Army::operator=(const Army& other) {
    if (this != &other) {
        TotalSoldiers = other.TotalSoldiers;
        TrainedSoldiers = other.TrainedSoldiers;
        Gold = other.Gold;
        FoodSupply = other.FoodSupply;
        Morale = other.Morale;
        BlacksmithLevel = other.BlacksmithLevel;
    }
    return *this;
}

// Destructor
Army::~Army() {
}

// Train
void Army::TrainSoldiers(Kingdom&kingdom) {
    cout << "Training soldiers (5 seconds)...\n";
    this_thread::sleep_for(chrono::seconds(10));

    int untrained = TotalSoldiers - TrainedSoldiers;
    int trainNow = min(30, untrained);

    TrainedSoldiers += trainNow;
    Morale += 2;

    cout << trainNow << " soldiers trained. Morale increased.\n";
    GetFromKingdom(kingdom);  // Function call  
}

// Pay Salary
void Army::PaySoldiers() {
    int amount = TotalSoldiers * 1;
    if (Gold >= amount) {
        Gold -= amount;
        Morale += 5;
        cout << "Salary paid. Army morale increased.\n";
    }
    else {
        Morale -= 10;
        cout << "Not enough gold! Morale decreased.\n";
    }
}

// Rest Soldiers
void Army::RestSoldiers() {
    cout << "Soldiers resting (5 seconds)...\n";
    this_thread::sleep_for(chrono::seconds(5));
    Morale += 3;
    cout << "Soldiers rested. Morale increased.\n";
}

// Fight Battle
void Army::FightSoldiers() {
    srand(time(0));
    int loss = rand() % 50;

    if (TrainedSoldiers < 20) {
        cout << "You lost the battle. Army too weak.\n";
        Morale -= 5;
    }
    else {
        cout << "Army fought bravely but lost " << loss << " soldiers.\n";
        TotalSoldiers -= loss;
        TrainedSoldiers -= min(loss, TrainedSoldiers);
        Morale -= 5;
    }
}

// Upgrade Weapons
void Army::LevelUpgrade() {
    if (Gold >= 200) {
        Gold -= 200;
        BlacksmithLevel++;
        cout << "Blacksmith level upgraded to " << BlacksmithLevel << ".\n";
    }
    else {
        cout << "Not enough gold to upgrade blacksmith.\n";
    }
}

// NEW FUNCTION: Eat Food
void Army::EatFood() {
    int dailyFood = TotalSoldiers * 1;
    if (FoodSupply >= dailyFood) {
        FoodSupply -= dailyFood;
        cout << "Soldiers consumed food. Supply now: " << FoodSupply << endl;
    }
    else {
        Morale -= 5;
        cout << "Not enough food! Morale decreased.\n";
        cout << " Army started Revolt against Kingdom\n";
    }
}

// Display Army Status
void Army::displayArmy() const {
    cout << "\n===== ARMY STATUS =====\n";
    cout << "Total Soldiers: " << TotalSoldiers << endl;
    cout << "Trained Soldiers: " << TrainedSoldiers << endl;
    cout << "Food Supply: " << FoodSupply << endl;
    cout << "Morale: " << Morale << endl;
    cout << "Gold: " << Gold << endl;
    cout << "Blacksmith Level: " << BlacksmithLevel << endl;
    cout << "========================\n";
}

//    File Handling start 
void Army::SaveFile(string Filename) {
    ofstream file(Filename);
    if (file.is_open()) {
        file << setw(35) << " TOTAL SOLDIERS   : " << TotalSoldiers << endl;
        file << setw(35) << " TRAINED SOLDIERS     : " << TrainedSoldiers << endl;
        file << setw(35) << " FOOD SUPPLY FROM KINGDOM     : " << FoodSupply<< endl;
        file << setw(35) << " MORALE       : " << Morale<< endl;
        file << setw(35) << " ARMY GOLD        : " << Gold<< endl;
        file << setw(35) << " BLACKS MITH LEVEL    : " << BlacksmithLevel << endl;
        file.close();
    }
}

void Army::LoadFile(string Filename) {
    ifstream file1(Filename);
    if (file1.is_open()) {
        string skip;
        getline(file1, skip, ':'); file1 >> TotalSoldiers; file1.ignore();
        getline(file1, skip, ':'); file1 >> TrainedSoldiers; file1.ignore();
        getline(file1, skip, ':'); file1 >> FoodSupply; file1.ignore();
        getline(file1, skip, ':'); file1 >> Morale; file1.ignore();
        getline(file1, skip, ':'); file1 >> Gold; file1.ignore();
        getline(file1, skip, ':'); file1 >> BlacksmithLevel; file1.ignore();
        file1.close();
    }
}
////////////////////////////////////////////////////

// Get From Kingdom
void Army::GetFromKingdom(Kingdom&kingdom) {
    int F, P, G;
    kingdom.HelpArmy( F,  P,  G);
    cout <<F<< " Food is Approched from Kingdom : \n";
    FoodSupply += F;
    cout << P << " New Army Members Approached  From Kingdom \n";
    TotalSoldiers += P;
    cout << G << "  Gold Got from Kingdom for Army Salary ||||  Army is Loyal to Kingdom \n";
    Gold += G;
    Morale += 10;
}

// Getters
int Army::GetSoldiers() const { return TotalSoldiers; }
int Army::GetTrainSoldiers() const { return TrainedSoldiers; }
int Army::GetMorale() const { return Morale; }
int Army::GetFoodSupply() const { return FoodSupply; }
int Army::GetGold() const { return Gold; }
