#include "Election.h"
#include <iostream>
#include <cstdlib>
#include <ctime>

#include<fstream>
#include<iomanip>

using namespace std;

// King Class Implementation
King::King(){}
King::King(string name, string style, int influence) {
    this->name = name;
    this->LeaderStyle = style;
    this->Influence = influence;
    this->Alive = true;
}

string King::getName() const {
    return name;
}

string King::getStyle() const {
    return LeaderStyle;
}

int King::Influencee() const {
    return Influence;
}

bool King::isAlive() const {
    return Alive;
}

void King::Die() {
    Alive = false;
}

void King::SetKing(string name, string style, int influence) {
    this->name = name;
    this->LeaderStyle = style;
    this->Influence = influence;
    this->Alive = true;
}

void King::display() const {
    cout << "\nCurrent King: " << name
        << "\nLeadership Style: " << LeaderStyle
        << "\nInfluence: " << Influence
        << "\nStatus: " << (Alive ? "Alive" : "Dead") << endl;
}

// Election Class Implementation
Election::Election() {
    CurrentKing = nullptr;
}

void Election::SetCandidate(string name1, string style1, int inf1, string name2, string style2, int inf2) {
    Candidate1.SetKing(name1, style1, inf1);
    Candidate2.SetKing(name2, style2, inf2);
}

void Election::ConductElection(int votesFor1, int votesFor2) {
    if (votesFor1 > votesFor2) {
        CurrentKing = &Candidate1;
    }
    else {
        CurrentKing = &Candidate2;
    }
    cout << "\nElection Result: King " << CurrentKing->getName() << " is elected." << endl;
    int Coup = rand() % 50; 
    if (Coup == 35) {
        coup();
    }
    else
        cout << " No Coup has Occured | King has Strong Influence\n";
}

void Election::coup() {
    cout << "\nA coup has occurred! The current king " << CurrentKing->getName() << " has been overthrown." << endl;
    CurrentKing = nullptr;
}

void Election::Bribery(int candidate) {
    if (candidate == 1) 
        Candidate1.SetKing(Candidate1.getName(), Candidate1.getStyle(), Candidate1.Influencee() + 10);
    else 
        Candidate2.SetKing(Candidate2.getName(), Candidate2.getStyle(), Candidate2.Influencee() + 10);
    cout << "\nBribery used. Candidate " << candidate << " gains influence." << endl;
}

void Election::Assasination(int candidate) {
    if (candidate == 1) 
        Candidate1.Die();
    else 
        Candidate2.Die();
    cout << "\nCandidate " << candidate << " has been assassinated!" << endl;
}

void Election::Blackmail(int candidate) {
    if (candidate == 1) 
        Candidate1.SetKing(Candidate1.getName(), Candidate1.getStyle(), Candidate1.Influencee() - 10);
    else 
        Candidate2.SetKing(Candidate2.getName(), Candidate2.getStyle(), Candidate2.Influencee() - 10);
    cout << "\nBlackmail used. Candidate " << candidate << " loses influence." << endl;
}

King* Election::GetCurrentKing() {
    return CurrentKing;
}

void Election::KingDiedInBattle() {
    if (CurrentKing != nullptr) {
        cout << "\nKing " << CurrentKing->getName() << " died in battle! Political instability begins." << endl;
        CurrentKing->Die();
        CurrentKing = nullptr;
    }
}

void Election::DisplayElectionStatus()  {
    cout << "\n===== Election Candidates =====" << endl;
    cout << "\nCandidate 1:" << endl;
    Candidate1.display();
    cout << "\nCandidate 2:" << endl;
    Candidate2.display();
    if (CurrentKing != nullptr) {
        cout << "\n===== Current Ruler =====" << endl;
        CurrentKing->display();
    }
    else {
        cout << "\nNo king is currently ruling. Political chaos is ongoing." << endl;
    }
}

//  File Handling start 

void Election::SaveFile(string filename) {
    ofstream file(filename);
    if (file.is_open()) {
        file << setw(35) << "Candidate1 Name : " << Candidate1.getName() << endl;
        file << setw(35) << "Candidate1 Style : " << Candidate1.getStyle() << endl;
        file << setw(35) << "Candidate1 Influence : " << Candidate1.Influencee() << endl;
        file << setw(35) << "Candidate1 Alive : " << Candidate1.isAlive() << endl;

        file << setw(35) << "Candidate2 Name : " << Candidate2.getName() << endl;
        file << setw(35) << "Candidate2 Style : " << Candidate2.getStyle() << endl;
        file << setw(35) << "Candidate2 Influence : " << Candidate2.Influencee() << endl;
        file << setw(35) << "Candidate2 Alive : " << Candidate2.isAlive() << endl;

        string Currentname = "";
        if (CurrentKing == &Candidate1)
            Currentname = Candidate1.getName();
        else if (CurrentKing == &Candidate2)
            Currentname = Candidate2.getName();

        file << setw(35) << " Current King : " << Currentname << endl;
    

        file.close();
    }
    else {
        cout << "Failed to open file for saving election data.\n";
    }
}


void Election::LoadFile( string filename) {
    ifstream file(filename);
    if (file.is_open()) {
        string skip, name1, style1, name2, style2, kingname;
        int inf1, inf2, alive1, alive2 ;

        getline(file, skip, ':'); file >> ws; 
        getline(file, name1);
        getline(file, skip, ':'); file >> ws;
        getline(file, style1);
        getline(file, skip, ':'); file >> inf1;
        getline(file, skip, ':'); file >> alive1; 
        file.ignore();

        getline(file, skip, ':'); file >> ws; 
        getline(file, name2);
        getline(file, skip, ':'); file >> ws; 
        getline(file, style2);
        getline(file, skip, ':'); file >> inf2;
        getline(file, skip, ':'); file >> alive2;
        file.ignore();

        getline(file, skip, ':'); file >> kingname;

        Candidate1.SetKing(name1, style1, inf1);
        Candidate2.SetKing(name2, style2, inf2);
        /*if (!alive1) Candidate1.Die();
        if (!alive2) Candidate2.Die();*/

        if (kingname == Candidate1.getName()) CurrentKing = &Candidate1;
        else if (kingname == Candidate2.getName()) CurrentKing = &Candidate2;
        else CurrentKing = nullptr;

        file.close();
    }
}

//////////////////////////////

Election :: ~Election() {
    //delete CurrentKing;
}
