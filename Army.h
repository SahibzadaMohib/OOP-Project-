#ifndef ARMY_H
#define ARMY_H
#include"Kingdom.h"
#include <string>
using namespace std;

class Army {
private:
    int TotalSoldiers;
    int TrainedSoldiers;
    int Gold;    // Used for Army salary
    int Morale;
    int FoodSupply;
    int BlacksmithLevel;

public:
    // Constructor
    Army(int Soldiers = 100, int G = 500, int Food = 100, int Level = 1);

    // Copy Constructor & Assignment Operator
    Army(const Army& other);
    Army& operator=(const Army& other);

    ~Army();

    // Army Functions
    void TrainSoldiers(Kingdom&kingdom);
    void PaySoldiers();
    void RestSoldiers();
    void FightSoldiers();
    void LevelUpgrade();
    void EatFood(); 
    void GetFromKingdom(Kingdom&Kingdom); // Source from Kingdom
    void displayArmy() const;

    // Getters
    int GetSoldiers() const;
    int GetTrainSoldiers() const;
    int GetMorale() const;
    int GetFoodSupply() const;
    int GetGold() const;

    //   File Handling structure 
    void SaveFile(string Filename);
    void LoadFile(string Filename);
};

#endif
