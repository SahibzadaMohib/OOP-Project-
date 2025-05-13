#include<iostream>                                                                                                                   #include "Trade.h"
#include<cstdlib>
#include"Trade.h"
#include<fstream>
#include<iomanip>
using namespace std;

Player :: Player () {} 

Product::Product(string n, float p) : name(n), price(p) {}

void Product::fluctuatePrice() {
    int change = rand() % 21 - 10; // -10% to +10%
    price += price * (change / 100.0);
    if (price < 1) price = 1;
}

void Product::display() const {
    cout << "Product: " << name << " | Current Price: $" << price << endl;
}

float Product::getPrice() const {
    return price;
}

string Product::getName() const {
    return name;
}

Player::Player(string n, float g) : name(n), gold(g), inAlliance(false) {}

void Player::trade(Product& p, int quantity) {
    float totalCost = p.getPrice() * quantity;
    if (gold >= totalCost) {
        gold -= totalCost;
        cout << name << " bought " << quantity << " " << p.getName()
            << "(s) for $" << totalCost << ". Gold left: $" << gold << endl;
    }
    else {
        cout << name << " doesn't have enough gold to buy " << quantity << " " << p.getName() << "(s)." << endl;
    }
}

void Player::formAlliance(Player& p) {
    inAlliance = true;
    cout << name << " has formed an alliance with " << p.getName() << ".\n";
}

void Player::breakAlliance(Player& p) {
    inAlliance = false;
    cout << name << " has broken the alliance with " << p.getName() << "!\n";
}

void Player::smuggle(Product& product) {
    int quantity;
    cout << "\nEnter quantity of " << product.getName() << " you want to smuggle: ";
    cin >> quantity;

    if (quantity <= 0) {
        cout << "Invalid quantity!\n";
        return;
    }

    double smugglePrice = product.getPrice() * 0.5; // 50% cheaper
    double totalCost = quantity * smugglePrice;

    cout << "Attempting to smuggle " << quantity << " units of " << product.getName()
        << " at illegal price $" << smugglePrice << " per unit.\n";
    cout << "Total smuggling cost: $" << totalCost << endl;

    if (gold >= totalCost) {
        int chance = rand() % 100;
        if (chance < 30) { // 30% chance of getting caught
            double fine = totalCost * 2;
            gold -= fine;
            cout << "?? You got caught smuggling! You are fined $" << fine << ".\n";
        }
        else {
            gold -= totalCost;
            cout << "? Smuggling successful. " << quantity << " units acquired at lower cost.\n";
        }
    }
    else {
        cout << "? Not enough gold to attempt smuggling.\n";
    }
}


void Player::imposeSanction() {
    cout << name << "'s kingdom has imposed a trade sanction. Market prices spike!\n";
}

void Player::dealWithGuild(Product& p) {
    cout << "Merchant Guild demands a fair price for " << p.getName() << ".\n";
    if (p.getPrice() > 15) {
        cout << "Refused guild demand. Boycott initiated!\n";
    }
    else {
        cout << "Guild satisfied. Trade continues smoothly.\n";
    }
}

void Player::showGold() const {
    cout << name << "'s Gold: $" << gold << endl;
}

string Player::getName() const {
    return name;
}

float Player::getGold() const {
    return gold;
}

//   File Handling start 

void Player :: SaveTradeData(const Product products[], int pSize, const Player players[], int plSize, string filename) {
    ofstream file(filename);
    if (file.is_open()) {
        for (int i = 0; i < pSize; ++i) {
            file << setw(20) << "Product_" + products[i].getName() + ": " << products[i].getPrice() << endl;
        }
        for (int i = 0; i < plSize; ++i) {
            file << setw(20) << "Player_" + players[i].getName() + ": " << players[i].getGold() << endl;
        }
        file.close();
    }
}

void Player :: LoadTradeData(Product products[], int pSize, Player players[], int plSize, string filename) {
    ifstream file(filename);
    if (file.is_open()) {
        std::string skip;
        float value;

        for (int i = 0; i < pSize; ++i) {
            getline(file, skip, ':');
            file >> value;
            products[i] = Product(products[i].getName(), value);
            file.ignore();
        }

        for (int i = 0; i < plSize; ++i) {
            getline(file, skip, ':');
            file >> value;
            players[i] = Player(players[i].getName(), value);
            file.ignore();
        }

        file.close();
    }
}
