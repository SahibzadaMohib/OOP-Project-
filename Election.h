
#ifndef ELECTION_H
#define ELECTION_H
#include<string>

using namespace std;

class King {
	string name;
	string LeaderStyle;
	int Influence;
	bool Alive;
public:
	King();
	King(string name, string LeaderStyle, int Influence);
	string getName() const;
	string getStyle() const;
	int Influencee() const;
	bool isAlive() const;

	void Die();
	void SetKing(string na,string st,int Inf);
	void display() const;

};

class Election {
	King Candidate1;
	King Candidate2;
	King* CurrentKing;
public:
	Election();
	void SetCandidate(string name1, string style1, int inf1, string name2, string style2, int inf2);
	void ConductElection(int votes1, int votes2);
	void coup();
	void Bribery(int candidate);
	void Assasination(int candidate);
	void Blackmail(int candidate);

	King* GetCurrentKing();
	void KingDiedInBattle();
	void DisplayElectionStatus() ;


	//   File Handling structure 
	void SaveFile(string Filename);
	void LoadFile(string Filename);

	~Election();
};


#endif