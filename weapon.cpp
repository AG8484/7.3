#include "weapon.h"

using namespace std;

namespace weapon_system 
{

    int weapon::nextid = 1;

    weapon::weapon(double power) : id(nextid++), power(power), durability(power / 10.0), level(1) 
    {

    }

    double weapon::getdurability() const 
    {
        return durability;
    }

    blade::blade(double power, double sharpness, bool magical, bool dual) : weapon(power), sharpness(sharpness), magical(magical), dual(dual) 
    {
        calculatelevel();
    }

    void blade::calculatelevel() 
    {
        if (power < 100) level = 1;
        else if (power < 200) level = 2;
        else level = 3;
    }

    int blade::getid() const 
    {
        return 10000 + id;
    }

    double blade::getpower() const 
    {
        double result = power * sharpness;
        if (dual) result *= 2;
        if (magical) result *= 3;
        return result;
    }

    string blade::gettypr() const 
    {
        return "blade";
    }

    void blade::printdetails() const 
    {
        cout << "type: blade       id: " << getid() << "       power: " << getpower() << "       durability: " << getdurability() << "      level: " << level << endl;
    }

    bow::bow(double power, double firstrate) : weapon(power), firstrate(firstrate) 
    {
        calculatelevel();
    }

    void bow::calculatelevel() 
    {
        if (power < 80)
        {
            level = 1;
        }
        else if(power < 150)
        {
            level = 2;
        }
        else
        { 
            level = 3;
        }
    }

    int bow::getid() const 
    {
        return 20000 + id;
    }

    double bow::getpower() const 
    {
        return power * firstrate;
    }

    string bow::gettypr() const 
    {
        return "bow";
    }

    void bow::printdetails() const 
    {
        cout << "type: bow       id: " << getid() << "       power: " << getpower() << "       durability: " << getdurability() << "      level: " << level << endl;
    }

    mace::mace(double power, int bladecount) : weapon(power), bladecount(bladecount) 
    {
        calculatelevel();
    }

    void mace::calculatelevel() 
    {
        if (power < 50) 
        {
            level = 1;
        }
        else if (power < 120) 
        {
            level = 2;
        }
        else
        {
            level = 3;
        }
    }

    int mace::getid() const 
    {
        return 30000 + id;
    }

    double mace::getpower() const 
    {
        return power * bladecount;
    }

    string mace::gettypr() const 
    {
        return "mace";
    }

    void mace::printdetails() const 
    {
        cout << "type: mace       id: " << getid() << "       power: " << getpower() << "       durability: " << getdurability() << "      level: " << level << endl;
    }

}
