#pragma once 
#ifndef TRADE_H
#define TRADE_H

#include<iostream>
#include<string>
using namespace std;

class Product {
    string name;
    float price;
public:
    Product(string n, float p);
    void fluctuatePrice();
    void display() const;
    float getPrice() const;
    string getName() const;
};

class Player {
    string name;
    float gold;
    bool inAlliance;
public:
    Player();
    Player(string n, float g);
    void trade(Product& p, int quantity);
    void formAlliance(Player& p);
    void breakAlliance(Player& p);
    void smuggle(Product& p);
    void imposeSanction();
    void dealWithGuild(Product& p);
    void showGold() const;
    string getName() const;
    float getGold() const;

    //   File Handlin
    void SaveTradeData(const Product products[], int pSize, const Player players[], int plSize,string filename);
    void LoadTradeData(Product products[], int pSize, Player players[], int plSize, string filename);

};

#endif
