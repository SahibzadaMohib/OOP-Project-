#include "Resource.h"
#include <iostream>
#include<fstream>
#include<string>
#include<iomanip>
using namespace std;
Resource::Resource() {
    resourceNames[0] = "Wood";    resourceQuantities[0] = 100;
    resourceNames[1] = "Stone";   resourceQuantities[1] = 100;
    resourceNames[2] = "Iron";    resourceQuantities[2] = 50;
    resourceNames[3] = "Gold";    resourceQuantities[3] = 500;
    resourceNames[4] = "Food";    resourceQuantities[4] = 300;
    resourceNames[5] = "Weapons"; resourceQuantities[5] = 30;
    resourcedebt[0] = 0; resourcedebt[3] = 0;
    resourcedebt[1] = 0; resourcedebt[4] = 0;
    resourcedebt[2] = 0; resourcedebt[5] = 0;
    totalpopulation = 200;
}
void Resource::addResource(int index, int amount) {
    if (index >= 0 && index < 6)
        resourceQuantities[index] += amount;
}
void Resource::routtype() {
    int n = rand() % 2;
    if (n == 1) {
        cout << "Your trade products are on safe rout going: " << endl;
    }
    else {
        cout << "Your products are not on safe rout -- Enemy Attacked" << endl;
        int resourceIndex = rand() % 6;
        int damage = 20 + (rand() % 81);
        const string resourceNames[] = { "Wood", "Stone", "Iron", "Gold", "Food", "Weapons" };
        cout << resourceNames[resourceIndex] << " is reduced by " << damage << "." << endl;
        consumeResource(resourceIndex, damage);
    }
}
void Resource::foodsupply() {
    cout << "Total population: " << totalpopulation << endl;
    cout << "Total Food: " << resourceQuantities[4] << endl;
    if (resourceQuantities[4] >= totalpopulation) {
        cout << "Food is enough " << endl;
        resourceQuantities[4] -= totalpopulation;
    }
    else {
        float tfp = (resourceQuantities[4] / totalpopulation) * 100;
        cout << "Food is not enough" << endl;
        resourceQuantities[4] = 0;
        if (tfp >= 75) {
            cout << "Revolt has occured: " << endl;
        }
        else if (tfp >= 50 && tfp < 75) {
            cout << "Starvation has occured,  Revolt has occured" << endl;
        }
        else if (tfp >= 25 && tfp < 50) {
            cout << "Disease has occured, Revolt has occured" << endl;
        }
        else {
            cout << "Starvation has occured,   disease has occured" << endl;
        }

    }
}

void Resource::checkdebt(int index, int amount) {
    if (resourcedebt[index] > 0) {
        int temp = amount;
        amount = amount - resourcedebt[index];
        resourcedebt[index] = resourcedebt[index] - temp;
        if (resourcedebt[index] <= 0) {
            resourcedebt[index] = 0;
            cout << "You have paid your all debt of units of " << resourceNames[index] << endl;
            addResource(index, amount);
        }
        else {
            cout << "You have paid some  debt amount " << temp << " of units of " << resourceNames[index] << endl;
            amount = 0;
        }
    }
    else {
        addResource(index, amount);
        cout << endl;
    }
}
void Resource::consumeResource(int index, int amount) {
    if (index >= 0 && index < 6) {
        if (resourceQuantities[index] >= amount) {
            resourceQuantities[index] -= amount;
        }
        else {
            cout << "Not enough " << resourceNames[index] << " available!" << endl;
            resourcedebt[index] = amount;
            cout << "You are indebted by " << resourcedebt[index] << " " << resourceNames[index] << "." << endl;
        }
    }
}
int Resource::getQuantity(int index) const {
    if (index >= 0 && index < 6)
        return resourceQuantities[index];
    return 0;
}
void Resource::showResources() const {
    cout << "Current Resources:\n";
    for (int i = 0; i < 6; ++i) {
        cout << resourceNames[i] << ": " << resourceQuantities[i] << endl;
    }
}

//   File Handling Start 

void Resource::SaveFile(string filename) {
    ofstream file(filename);
    if (file.is_open()) {
        for (int i = 0; i < 6; ++i) {
            file << setw(35) << "Resource_" + resourceNames[i] + ": " << resourceQuantities[i] << endl;
            file << setw(35) << "Debt_" + resourceNames[i] + ": " << resourcedebt[i] << endl;
        }
        file << setw(35) << "Total_Population: " << totalpopulation << endl;
        file.close();
    }
}

void Resource::LoadFile(string filename) {
    ifstream file(filename);
    if (file.is_open()) {
        string skip;
        for (int i = 0; i < 6; ++i) {
            getline(file, skip, ':'); file >> resourceQuantities[i]; file.ignore();
            getline(file, skip, ':'); file >> resourcedebt[i];       file.ignore();
        }
        getline(file, skip, ':'); file >> totalpopulation;
        file.close();
    }
}