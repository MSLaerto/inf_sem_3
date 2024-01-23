#ifndef OOPPROG2_VAGON_H
#define OOPPROG2_VAGON_H
#include <iostream>
#include <string>
#include <limits>
#include <cstring>
namespace Prog2{
    class wagon {
    private:
        int capacity;
        int busy;
    public:
        enum typeData { Sedentary = 1, Economy = 2, Luxury = 3, Restaurant = 4};
        typeData typeName ;
        wagon();
        explicit wagon(int vag_type);
        wagon(int wag_type, int cap, int engaged);
        double GetBusyPercentage() const{ return double(busy)/double(capacity);};
        void add(int col);
        void del(int col);
        int GetCapacity() const{return capacity;};
        int GetBusy() const{return busy;};
        int GetType() const{return typeName;};
        void Printwagon() const;
        void Editwagon(int newcapacity , int newbusy , int newtype);
        wagon& operator>>(wagon &v);
        void SetType(int newtype);
        void SetCapacity(int newcapacity);
        void SetBusy(int newbusy);
        wagon WagonMenu(wagon &v);
        static typeData tType(int ind) ;
    };

}

#endif //OOPPROG2_VAGON_H
