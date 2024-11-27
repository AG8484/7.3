#include "weapon.h"
#include "weapon.cpp"
#include "vector.h" 
#include <iostream>

using namespace weapon_system;

using namespace std;

void weaponsbypower(mine::Vector<weapon*>& weapons) 
{
    size_t n = weapons.size();
    for (size_t i = 0; i < n - 1; ++i) 
    {
        for (size_t j = 0; j < n - i - 1; ++j) 
        {
            if (weapons[j]->getpower() < weapons[j + 1]->getpower()) 
            {
                auto temp = weapons[j];
                weapons[j] = weapons[j + 1];
                weapons[j + 1] = temp;
            }
        }
    }
}

int main() 
{
    mine::Vector<weapon*> weapons;

    weapons.pushback(new blade(120, 1.5, true, false));
    weapons.pushback(new bow(90, 2.0));
    weapons.pushback(new mace(100, 3));

    cout << "weapon details:\n";
    for (size_t i = 0; i < weapons.size(); ++i) 
    {
        weapons[i]->printdetails();
    }

    double totalpower = 0;
    for (size_t i = 0; i < weapons.size(); ++i) 
    {
        totalpower += weapons[i]->getpower();
    }
    cout << "\ntotal power : " << totalpower << "\n";

    weaponsbypower(weapons);

    cout << "\nweapons sort by power:\n";
    for (size_t i = 0; i < weapons.size(); ++i) 
    {
        weapons[i]->printdetails();
    }

    for (size_t i = 0; i < weapons.size(); ++i) 
    {
        delete weapons[i];
    }

    return 0;
}
