#include <stdio.h>
#include <iostream>
#include <string>
using namespace std;

class Car {
    public:
    string color;
    int reg_no;
    Car(int number,string color)
    {
        this->color = color;
        this->reg_no = number;
    }
};

class Slot {
    int s_no;
    bool is_available;
    public:
    Car* c;
    Slot(int x)
    {
        this->s_no = x;
        this->is_available = true;
        this->c = nullptr;
    }
    bool Is_Available() { return this->is_available; }
    void park(Car* c)
    {
        this->c = c;
        this->is_available = false;
    }
    void unpark()
    {
        this->c = nullptr;
        this->is_available = true;
    }
};

class Floor {
    public:
    int f_no;
    vector<Slot> lst_slot;
    Floor(int fno, int nos)
    {
        this->f_no = fno;
        for(int i = 1; i <= nos; i++)
        {
            lst_slot.push_back(Slot(i));
        }
    }
};

class Parking_Lot {
    vector<Floor> lst_floor;
    public:
    Parking_Lot(int nof,int nos)
    {
        for(int i = 1; i <= nof; i++)
        {
            lst_floor.push_back(Floor(i,nos));
        }
    }
    Slot& get_emptySpace()
    {
        for(Floor& f:lst_floor)
        {
            for(Slot& s:f.lst_slot)
            {
                if(s.Is_Available()) return s;
            }
        }
        throw "Parking Lot is full";
    }
};

class Parking_lotManager {
    unordered_map<int,Slot*> parked_cars;
    public:
    Parking_Lot* P;
    Parking_lotManager(int nof, int nos)
    {
        this->P = new Parking_Lot(nof,nos);
    }
    bool Park_Car(Car& c)
    {
        try{
            Slot& empty_s = P->get_emptySpace();
            empty_s.park(&c);
            this->parked_cars.insert(make_pair(c.reg_no,&empty_s));
            cout<<"car is parked"<<endl;
            return true;
        }
        catch (const char* exp) {
            cout << "Exception caught \n ";
            cout << exp << endl;
            return false;
        }
        
    }
    bool unpark_car(int number)
    {
        auto iter = this->parked_cars.find(number);
        if(iter != this->parked_cars.end())
        {
            cout << "car has been unparked from parking lot" << endl;
            iter->second->unpark();
            this->parked_cars.erase(iter);
            return true;
        }
        return false;
    }
    bool search_regno(int number)
    {
        if(this->parked_cars.find(number) != this->parked_cars.end())
        {
            cout<<"Car with specified reg no is found in parking lot"<<endl;
             return true;
        }
        cout<<"Car is not found in parking lot"<<endl;
        return false;
    }
    void return_colorbasaed(string color)
    {
        cout<<"The list of cars in parking lot in color "<<color<<":"<<endl;
        for(auto i:this->parked_cars)
        {
            if((i.second -> c -> color).compare(color)==0)
            {
                cout << i.second -> c -> reg_no <<endl;
            }
        }
    }
};

int main()
{
    Car c1(1234,"white");
    Car c2(4879,"blue");
    Car c3(2334,"red");
    Car c4(5443,"orange");
    Car c5(675,"white");
    Parking_lotManager pm(1,4);
    pm.Park_Car(c1);
    pm.Park_Car(c2);
    pm.Park_Car(c3);
    pm.Park_Car(c4);
    pm.unpark_car(1234);
    pm.Park_Car(c5);
    pm.search_regno(1234);
    pm.search_regno(675);
    pm.return_colorbasaed("white");
    return 0;
    
}