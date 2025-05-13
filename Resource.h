#ifndef RESOURCE_H
#define RESOURCE_H
#include <string>
using namespace std;
class Resource {
private:
    int totalpopulation;
    string resourceNames[6];
    int resourceQuantities[6];
    int resourcedebt[6];
public:
    Resource();
    void foodsupply();
    void routtype();
    void checkdebt(int debt, int amount);
    void addResource(int index, int amount);
    void consumeResource(int index, int amount);
    int getQuantity(int index) const;
    void showResources() const;

    //   File Handling structure 
    void SaveFile(string Filename);
    void LoadFile(string Filename);

};
#endif
