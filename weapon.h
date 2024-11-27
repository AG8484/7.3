#ifndef weapon_H
#define weapon_H

#include <iostream>
#include <string>

using namespace std;

namespace weapon_system 
{

    class weapon 
    {
    protected:
        static int nextid;    
        int id;                 
        double power;            
        double durability;       
        int level; 

        virtual void calculatelevel() = 0;

    public:
        weapon(double power);
        virtual ~weapon() = default;

        virtual int getid() const = 0;
        virtual double getpower() const = 0;
        virtual string gettypr() const = 0;

        double getdurability() const;

        virtual void printdetails() const = 0;
    };

    class blade : public weapon 
    {
    private:
        double sharpness; 
        bool magical;   
        bool dual;      

        void calculatelevel() override;

    public:
        blade(double power, double sharpness, bool magical, bool dual);

        int getid() const override;
        double getpower() const override;
        string gettypr() const override;
        void printdetails() const override;
    };

    class bow : public weapon 
    {
    private:
        double firstrate;

        void calculatelevel() override;

    public:
        bow(double power, double firstrate);

        int getid() const override;
        double getpower() const override;
        string gettypr() const override;
        void printdetails() const override;
    };

    class mace : public weapon 
    {
    private:
        int bladecount;

        void calculatelevel() override;

    public:
        mace(double power, int bladecount);

        int getid() const override;
        double getpower() const override;
        string gettypr() const override;
        void printdetails() const override;
    };

} 

#endif
