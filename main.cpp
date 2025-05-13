#include<iostream>
#include<fstream>
#include<cstdlib>
#include<cmath>
#include<ctime>
#include<string>
#include"Kingdom.h"
#include"Army.h"
#include"Election.h"
#include"Economy.h"
#include"Resource.h"
#include"Trade.h"
#include"Banking.h"
using namespace std;

void SimulateBribary(Election& election) {
    int choice = rand() % 2;
    election.Bribery(choice);
}

//   Respurce Function 
const int TOTAL_RESOURCES = 6;
string resourceNames[TOTAL_RESOURCES] = { "Wood", "Stone", "Iron", "Gold", "Food", "Weapons" };
void badWeather(Resource& r) {
    srand(time(0));
    int event = rand() % 4;
    int resourceIndex = rand() % 6;
    int damage = 20 + (rand() % 81);
    string eventType;
    switch (event) {
    case 0: eventType = "Drought"; break;
    case 1: eventType = "Storm"; break;
    case 2: eventType = "War"; break;
    case 3: eventType = "Famine"; break;
    }
    const string resourceNames[] = { "Wood", "Stone", "Iron", "Gold", "Food", "Weapons" };
    cout << "   " << eventType << " has occurred!" << endl;
    cout << resourceNames[resourceIndex] << " is reduced by " << damage << "." << endl;
    r.consumeResource(resourceIndex, damage);
}
void showResourceList() {
    cout << endl << "Select a resource:" << endl;
    for (int i = 0; i < TOTAL_RESOURCES; ++i) {
        cout << i << ". " << resourceNames[i] << endl;
    }
}
/////////////////////////////////////////////////////////////////////////////////////////////////////
// Trade Section 
void simulateMarket(Product products[], int size) {
    cout << "\n Market Simulation:\n";
    for (int i = 0; i < size; i++) {
        int event = rand() % 4;
        switch (event) {
        case 0: cout << "High demand for " << products[i].getName() << "! "; break;
        case 1: cout << "Market crash for " << products[i].getName() << "! "; break;
        case 2: cout << "Political issues affecting " << products[i].getName() << "! "; break;
        case 3: cout << "Trade disruption for " << products[i].getName() << "! "; break;
        }
        products[i].fluctuatePrice();
        products[i].display();
    }
}

void displayResources(Product products[], int size) {
    cout << "\n Available Resources:\n";
    for (int i = 0; i < size; i++) {
        products[i].display();
    }
}
//////////////////////////////////////////////////////////////////////


//  Resource Function End 
int main() {
	cout << "\t\t\t\t=======   ====================================================   =======\n";
	cout << "\t\t\t\t\t           WELCOME TO STRONG HOLD GAME  MULTIPLAYER GAME        \n";
	cout << "\t\t\t\t=======   ====================================================   =======\n\n\n";



        srand(time(0)); 

        try {
            Kingdom myKingdom; // Create the kingdom
            Army myArmy;   //    Create the Army 
            Election myElection;  //  Election Create 
            King *myking;        //  King select under Election 
            Economy myEconomy(1000); // Economy Create and call paramaterized Function 
            Resource playerResources; //  Resource Create
            Bank bank(1000); // Bank create and start with 1000 treasury 
            Player obj;    //   Trade obj create 

            ///    Load Data Structure  ///////////////////////////////////////////////////////////////////////////
            myKingdom.LoadFile("kingdom.txt");
            myArmy.LoadFile("army.txt");
            myElection.LoadFile("election.txt");
            myEconomy.LoadFile("economy.txt");
            playerResources.LoadFile("resources.txt");
            bank.LoadFile("bank.txt");

            int number;

            cout << " \t\t WOULD YOU WANTED LOAD DATA IN THIS GAME AND SHOW ON CONSOLE \n\n";
            cout << "   \t\t Then write ( 1 ) for yes otherwise write any number to ignore it \n";
            cin >> number;
            if (number == 1) {
                myKingdom.displayStatus();
                cout << "\n\n";
                myArmy.displayArmy();
                cout << "\n\n";
                myElection.DisplayElectionStatus();
                cout << "\n\n";
                myEconomy.Display();
                cout << "\n\n";
                playerResources.showResources();
                cout << "\n\n";
                bank.showTreasury();
                cout << "\n";
            }

            cout << "\n\n";

            //////////////////////////////////////////////////////////////////////////////////////////////////////
            //  Values for Election 
            int v1, v2, inf1, inf2, rand1;
            string n1, n2, s1, s2;
            ///////////////////////

            // Value for Economy 
            int P, N;
            int PT, NT, amount;
            ///////////////////

            //  Value for Resource 
            int resourceIndex, amount1;
            ///////////////////////

            //   Trade Values 
            int resIndex, quantity;
            ///////////
            
            // Bank values 
            int choice = 1, num = 0;
            int loan;
            int repay;
            /////////////////////
            int choice1;
            int choice2;
            int choice3;
            int choice4;
            int choice5;
            int choice6;
            int choice7;

            ///////////////////////////////////////////////////////////////////////////////////////////
            // Trade Section 
                // Products

            //Product products[4] = {
            //     Product("Iron", 12.0),
            //     Product("Wheat", 8.0),
            //     Product("Wood", 10.0),
            //     Product("Stone", 9.0)
            //};
            //string name;
            //cout << "Enter name of player:" << endl;
            //cin >> name;

            //// Players
            //Player player(name, 100.0);
            //Player rival("Mohib", 100.0);//default name for rival
            //SaveTradeData(products, 3, players, 2, "trade.txt");
            Product products[4] = {
                 Product("Iron", 12.0),
                 Product("Wheat", 8.0),
                 Product("Wood", 10.0),
                 Product("Stone", 9.0)
            };

            string name;
            cout << "Enter name of player: ";
            cin >> name;

            Player player(name, 100.0);
            Player rival("Mohib", 100.0);

            // Combine into array
            Player players[2] = { player, rival };

            // Now pass properly
            obj.SaveTradeData(products, 4, players, 2, "trade.txt");


            do {
                cout << " In Which Section you Wanted to go \n" <<
                    " 1.    Kingdom Section\n" <<
                    " 2.    Army Section \n" <<
                    " 3.    Election Section \n" <<
                    " 4.    Economy Section \n" <<
                    " 5.    Resource Section\n" <<
                    " 6.    Trade Section \n" <<
                    " 7.    Bank Section \n" <<
                    " 0.    Exit Game \n";
                cin >> choice1;
                switch (choice1) {
                case 1:

                    do {
                        cout << "\n\t\t========= Kingdom Management Menu =========\n\n";
                        cout << "1. Display Kingdom Status\n";
                        cout << "2. Collect Taxes\n";
                        cout << "3. Feed Population\n";
                        cout << "4. Grow Population\n";
                        cout << "5. Plague Event\n";
                        cout << "6. Production rate in Kingdom\n";
                        cout << "0. Exit Kingdom Section\n";
                        cout << "Enter your choice: ";
                        cin >> choice2;

                        switch (choice2) {
                        case 1:
                            myKingdom.displayStatus();
                            break;
                        case 2:
                            myKingdom.collectTax();
                            break;
                        case 3:
                            myKingdom.feedPopulation();
                            break;
                        case 4:
                            myKingdom.growPopulation();
                            break;
                        case 5:
                            myKingdom.handlePlague();
                            break;
                        case 6:
                            myKingdom.Production();
                            break;
                        case 0:
                            cout << "Exiting Section. Goodbye!\n";
                            break;
                        default:
                            cout << "Invalid choice. Try again.\n";
                            break;
                        }

                    } while (choice2 != 0);
                    break;
                           //   Army Section 
                case 2:
                    do {
                        cout << " \n\t\t\t WELCOME TO KINGDOM ARMY \n\n" <<
                            " 1.   Display Army Status \n" <<
                            " 2.   Display the Number of Train Soldiers\n" <<
                            " 3.   Display the given Salary of Soldiers\n" <<
                            " 4.   Display Resting Soldiers \n" <<
                            " 5.   Display Fight Soldiers\n" <<
                            " 6.   Display the Level of Black Smith\n" <<
                            " 0.   Army Section Exit \n";
                        cin >> choice2;
                        switch (choice2) {
                        case 1:
                            myArmy.displayArmy();
                            break;
                        case 2:
                            myArmy.TrainSoldiers(myKingdom);
                            break;
                        case 3:
                            myArmy.PaySoldiers();
                            break;
                        case 4:
                            myArmy.RestSoldiers();
                            break;
                        case 5:
                            myArmy.FightSoldiers();
                            break;
                        case 6:
                            myArmy.LevelUpgrade();
                            break;
                        case 0:
                            cout << " Army Section Existed ! Good Bye\n";
                            break;
                        default:
                            cout << " Invalid Choice ! Try Again\n";
                            break;
                        }

                    } while (choice2 != 0);
                    break;
                case 3:
                    do {
                        cout << " \t\t\t WELCOME TO KINGDOM ELECTION \n\n";
                        cout << " Conduct Election in Kingdom for King to Avoid any Casualities \n" <<
                            " Enter any number to yes except 0\n";
                        cin >> choice3;
                        if (choice3 != 0) {
                            cout << " \t\tEnter Information for First Candidate \n";
                            cout << " Name : ";
                            cin >> n1;
                            cout << " Style : ";
                            cin >> s1;
                            cout << " Influence : ";
                            cin >> inf1;
                            cout << " \t\tEnter Information for Second candidate \n";
                            cout << " Name : ";
                            cin >> n2;
                            cout << " Style : ";
                            cin >> s2;
                            cout << " Influence : ";
                            cin >> inf2;
                            myElection.SetCandidate(n1, s1, inf1, n2, s2, inf2);
                            v1 = rand() % 150;    // Randomly vote for Candidate 1
                            v2 = rand() % 150;    // Randomly vote for Candidate 2 
                            myElection.ConductElection(v1, v2);
                            myElection.DisplayElectionStatus(); // Display Election Status 
                            SimulateBribary(myElection); // Bribary Occurence 
                            rand1 = rand() % 10;
                            if (rand1 == 8){
                                myElection.KingDiedInBattle();  // Battle Occurence
                            }
                            myking = myElection.GetCurrentKing();
                            if (myking) {
                                cout << "\nAfter all events, the King is still: " << myking->getName() << "\n";
                            }
                            else {
                                cout << "\nNo King currently rules. Political instability continues.\n";
                            }
                        }

                    } while (choice3 != 0);
                    break;
                case 4:
                    do {
                        cout << " \t\t========== WELCOME TO KINGDOM ECONOMY MANAGMENT SYSTEM ===============\n\n";
                        cout << "1.    Collect Tax System \n" <<
                            " 4.     Allocate Budget for Public Services \n" <<
                            " 2.     Adjust Tax Rates \n" <<
                            " 3.     Printed Money \n" <<
                            " 5.     Market Crash \n" <<
                            " 6.     Random Events Occurence \n" <<
                            " 7.     Display Economy Status \n" <<
                            " 0.     Exit Economy Section \n";
                        cin >> choice4;
                        switch (choice4) {
                        case 1:
                            cout << " Enter Number of Peasonts : ";
                            cin >> P;
                            cout << " Enter Number of Nobles : ";
                            cin >> N;
                            myEconomy.CollectTax(P, N);
                            break;
                        case 2:
                            cout << " Enter New amount for Peasont Tax in Percentage (1 to 16)\n";
                            do {
                                cin >> PT;
                                if (PT < 1 || PT > 16) {
                                    cout << " Tax Percenatge should less than 16 or 16\n";
                                }
                            } while ( PT < 1|| PT > 16);
                            cout << " Enter New amount for Noble Tax in Percentage (1 to 31)\n";
                            do {
                                cin >> NT;
                                if (NT < 1 || NT > 31) {
                                    cout << " Tax Percentage should less than 32 \n";
                                }
                            } while (NT < 1 || NT > 31);
                            myEconomy.ManageTaxRate(PT, NT);
                            break;
                        case 3:
                            cout << " Enter Amount of gold to print money : ";
                            cin >> amount;
                            myEconomy.PrintMoney(amount);
                            break;
                        case 4:
                            cout << " Enter the amount for Public Services : ";
                            cin >> amount;
                            myEconomy.AllocateBudget(amount);
                            break;
                        case 5:
                            myEconomy.MarketCrassh();
                            break;
                        case 6:
                            myEconomy.Randomevent();
                            break;
                        case 7:
                            myEconomy.Display();
                            break;
                        case 0:
                            cout << " Economy Section exist \n";
                            break;
                        default:
                            cout << " Invalid Choice \n";
                            break;
                        }

                    } while (choice4 != 0);
                    break;
                case 5:
                    do {
                        cout << " \t\t WELCOME TO RESOURCE MANAGMENT SYSTEM \n\n";
                        cout << "1. Add Resource " << endl;
                        cout << "2. Trigger Random  Event " << endl;
                        cout << "3. Show All Resources" << endl;
                        cout << "4. Food Section" << endl;
                        cout << "5. Trading Route" << endl;
                        cout << "0. Exit Game Early" << endl;
                        cin >> choice5;
                        switch (choice5) {
                        case 1:
                            showResourceList();
                            cout << "Enter resource number (0 to 5): ";
                            cin >> resourceIndex;

                            if (resourceIndex >= 0 && resourceIndex < TOTAL_RESOURCES) {
                                amount1 = rand() % 200;
                                cout << "Amount of " << amount1 << " " << resourceNames[resourceIndex] << "  recieved" << endl;
                                playerResources.checkdebt(resourceIndex, amount1);
                            }
                            else {
                                cout << " Invalid resource number.";
                            }
                            break;
                        case 2:
                            badWeather(playerResources);
                            break;
                        case 3:
                            playerResources.showResources();
                            break;
                        case 4:
                            playerResources.foodsupply();
                            break;
                        case 5:
                            playerResources.routtype();
                            break;
                        case 0:
                            cout << " Resource Exited !! Good Bye \n";
                            break;
                        default:
                            cout << " Invalid choice! Please select from the menu.";
                            break;
                        }

                    } while (choice5 != 0);
                    break;
                case 6:
                    do {
                        cout << "\n=========== Medieval Market Menu ===========\n";
                        cout << "1. View All Resources & Prices\n";
                        cout << "2. Trade Resource\n";
                        cout << "3. Smuggle Resource\n";
                        cout << "4. Simulate Market Fluctuation\n";
                        cout << "5. Form Alliance with Rival\n";
                        cout << "6. Break Alliance with Rival\n";
                        cout << "7. Impose Trade Sanctions\n";
                        cout << "8. Deal with Merchant Guild\n";
                        cout << "9. Show Player Gold\n";
                        cout << "0. Exit\n";
                        cout << "Enter your choice: ";
                        cin >> choice6;

                        switch (choice6) {
                        case 1:
                            displayResources(products, 4);
                            break;

                        case 2:
                            displayResources(products, 4);
                            cout << "Enter product number (0-3): ";
                            cin >> resIndex;
                            cout << "Enter quantity: ";
                            cin >> quantity;
                            if (resIndex >= 0 && resIndex < 4) {
                                player.trade(products[resIndex], quantity);
                            }
                            else {
                                cout << "Invalid product selection.\n";
                            }
                            break;

                        case 3:
                            displayResources(products, 4);
                            cout << "Enter product number to smuggle (0-3): ";
                            cin >> resIndex;
                            if (resIndex >= 0 && resIndex < 4) {
                                player.smuggle(products[resIndex]);
                            }
                            else {
                                cout << "Invalid product selection.\n";
                            }
                            break;

                        case 4:
                            simulateMarket(products, 4);
                            break;

                        case 5:
                            player.formAlliance(rival);
                            break;

                        case 6:
                            player.breakAlliance(rival);
                            break;

                        case 7:
                            player.imposeSanction();
                            break;

                        case 8:
                            displayResources(products, 4);
                            cout << "Enter product number for guild interaction (0-3): ";
                            cin >> resIndex;
                            if (resIndex >= 0 && resIndex < 4) {
                                player.dealWithGuild(products[resIndex]);
                            }
                            else {
                                cout << "Invalid product selection.\n";
                            }
                            break;

                        case 9:
                            player.showGold();
                            break;

                        case 0:
                            cout << "Exiting game. Goodbye!\n";
                            break;

                        default:
                            cout << "Invalid option. Try again.\n";
                        }

                    } while (choice6 != 0);
                    break;
                case 7:
                    while (true) {
                        switch (choice) {

                        case 1:

                            cout << "1: Take Loan. " << endl;
                            cout << "2: Simulate Corruption. " << endl;
                            cout << "3: Hire audit." << endl;
                            cout << "4: Repay Loan." << endl;
                            cout << "5: Show treasure." << endl;
                            cout << "6: Exit." << endl;
                            cin >> choice7;
                            switch (choice7) {

                            case 1:
                                cout << "Plz! Enter the amount of loan you want to take:"; cin >> loan;
                                bank.takeLoan(loan);
                                break;
                            case 2:
                                bank.simulateCorruption();
                                break;
                            case 3:
                                bank.audit();
                                break;
                            case 4:
                                if (bank.loanAmount > 0) {

                                    cout << "The amount required to repay the loan = " << bank.loanAmount << endl;

                                    cin >> repay;
                                    bank.repayLoan(repay);
                                }
                                else {
                                    bank.repayLoan(10);
                                }
                                break;
                            case 5:
                                bank.showTreasury();

                                break;
                            case 6:
                                num = 1;
                                break;
                            default:
                                cout << "Wrong input!";
                                break;
                            }
                            break;

                        default:
                            cout << "Wrong input!";
                            break;

                        }
                        if (num > 0) {
                            break;
                        }
                    }
                    break;
                }
            } while (choice1 != 0);


            //   SAVE FILE 
            myKingdom.SaveFile("kingdom.txt");
            myArmy.SaveFile("army.txt");
            myElection.SaveFile("election.txt");
            myEconomy.SaveFile("economy.txt");
            playerResources.SaveFile("resources.txt");
            obj.SaveTradeData(products, 4, players, 2, "trade.txt");
            bank.SaveFile("bank.txt");
            cout << " \n\t\t\t\t ALL DATA SAVED CAREFULLY AND SUCCESSFULLY\n";
        }
        catch (const exception& ex) {
            cerr << "Error: " << ex.what() << endl;
        }

	return 0;
}