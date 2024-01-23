#include "vagon.h"
#include "help.h"
#include <string>
#include <iostream>
namespace Prog2 {
    wagon::wagon(){
        capacity = 0;
        busy = 0;
        typeName = typeData::Sedentary;
    }
    wagon::wagon(int vag_type) {
        if (vag_type == 1) {
            capacity = 100;
            busy = 0;
            typeName = typeData::Sedentary;
        } else if (vag_type == 2) {
            capacity = 60;
            busy = 0;
            typeName = typeData::Economy;
        } else if (vag_type == 3) {
            capacity = 10;
            busy = 0;
            typeName = typeData::Luxury;
        } else if (vag_type == 4) {
            capacity = 0;
            busy = 0;
            typeName = typeData::Restaurant;
        } else {
            throw std::runtime_error("Wrong type");
        }
    }

    wagon::wagon(int vag_type, int cap, int engaged) {
        if (cap < engaged) {
            throw std::overflow_error("Not enougth capacity");
        } else if ((vag_type == 4) && (cap != 0) && (engaged != 0)) {
            throw std::logic_error("Restoraunt have no seats");
        } else if (cap < 0 || engaged < 0 || vag_type < 1 || vag_type > 4) {
            throw std::runtime_error("Wrong type");
        } else {
            capacity = cap;
            busy = engaged;
            if (vag_type == 1) {
                typeName = typeData::Sedentary;
            } else if (vag_type == 2) {
                typeName = typeData::Economy;
            } else if (vag_type == 3) {
                typeName = typeData::Luxury;
            } else {
                typeName = typeData::Restaurant;
            }
        }
    }

    void wagon::add(int col) {
        if (busy + col > capacity) {
            throw std::runtime_error("Not enougth capacity");
        } else {
            busy = busy + col;
        }
    }

    void wagon::del(int col) {
        if (busy - col < 0) {
            throw std::runtime_error("Not enougth busy");
        } else {
            busy = busy - col;
        }
    }

    void wagon::Printwagon() const {
        if (typeName == typeData::Sedentary) {
            std::cout << "type:Sedentary";
        }
        if (typeName == typeData::Economy) {
            std::cout << "type:Economy";
        }
        if (typeName == typeData::Luxury) {
            std::cout << "type:Luxury";
        }
        if (typeName == typeData::Restaurant) {
            std::cout << "type:Restaurant";
        }
        std::cout << " Capacity:" << capacity << " busy:" << busy << std::endl;
    }

    void wagon::Editwagon(int newcapacity, int newbusy, int newtype) {
        if (newtype != 4) {
            if (newtype == 1) {
                typeName = typeData::Sedentary;
            } else if (newtype == 2) {
                typeName = typeData::Economy;
            } else if (newtype == 3) {
                typeName = typeData::Luxury;
            }
            capacity = newcapacity;
            busy = newbusy;
        } else {
            typeName = typeData::Restaurant;
            capacity = 0;
            busy = 0;
        }
    }

    wagon &wagon::operator>>(wagon &v2) {
        int capacity_to = v2.capacity;
        double aver = double(capacity_to) / double(this->GetCapacity());
        int new_busy = int(double(this->GetBusy()) / (double(aver) + 1));
        std::cout << "moved " << this->GetBusy() - new_busy << " people" << std::endl;
        this->busy -= (this->GetBusy() - new_busy);
        return *this;
    }

    void wagon::SetType(int newtype) {
        if (newtype == 1) {
            typeName = typeData::Sedentary;
        } else if (newtype == 2) {
            typeName = typeData::Economy;
        } else if (newtype == 3) {
            typeName = typeData::Luxury;
        } else {
            typeName = typeData::Restaurant;
        }
    }

    void wagon::SetCapacity(int newcapacity) {
        capacity = newcapacity;
    }

    void wagon::SetBusy(int newbusy) {
        busy = newbusy;
    }
    Prog2::wagon::typeData wagon::tType(int ind) {
        switch (ind) {
            case 1:
                return typeData::Sedentary;
            case 2:
                return typeData::Economy;
            case 3:
                return typeData::Luxury;
            case 4:
                return typeData::Restaurant;
            default:
                throw std::runtime_error("Wrong type");
        }
    }
    wagon wagon::WagonMenu(wagon &v) {
        int n = -1;
        int newtype = 0, newcapacity = 0, newbusy = 0, col = 0;
        Prog2::wagon v2(1);
        while (n != 0) {
            try {
                std::cout << "1 - Show wagon" << std::endl;
                std::cout << "2 - Edit wagon" << std::endl;
                std::cout << "3 - Add passenger" << std::endl;
                std::cout << "4 - Delete passenger" << std::endl;
                std::cout << "5 - Move passengers(>>)" << std::endl;
                std::cout << "6 - Show busy percent" << std::endl;
                std::cout << "7 - Show Type" << std::endl;
                std::cout << "8 - Show Busy" << std::endl;
                std::cout << "9 - Show Capacity" << std::endl;
                std::cout << "10 - Set Type" << std::endl;
                std::cout << "11 - Set Busy" << std::endl;
                std::cout << "12 - Set Capacity" << std::endl;
                std::cout << "0 - Exit" << std::endl;
                n = getNum(0, 12);
                switch (n) {
                    case 1:
                        v.Printwagon();
                        break;
                    case 2:
                        std::cout << "New type: Sedentary = 1, Economy = 2, Luxury = 3, Restaurant = 4" << std::endl;
                        newtype = getNum<int>(1, 4);
                        std::cout << "New capacity: " << std::endl;
                        newcapacity = getNum<int>(0);
                        std::cout << "New busy: " << std::endl;
                        newbusy = getNum<int>(0, newcapacity);
                        v.Editwagon(newcapacity, newbusy, newtype);
                        break;
                    case 3:
                        std::cout << "Need to add: " << std::endl;
                        col = getNum<int>(0);
                        v.add(col);
                        break;
                    case 4:
                        std::cout << "Need to delete: " << std::endl;
                        col = getNum<int>(0);
                        v.del(col);
                        break;
                    case 5:
                        std::cout << "Input second wagon: " << std::endl;
                        std::cout << "Type: Sedentary = 1, Economy = 2, Luxury = 3, Restaurant = 4" << std::endl;
                        newtype = getNum<int>(1, 4);
                        std::cout << "Capacity: " << std::endl;
                        newcapacity = getNum<int>(0);
                        std::cout << "Busy: " << std::endl;
                        newbusy = getNum<int>(0, newcapacity);
                        v2.Editwagon(newtype, newcapacity, newbusy);
                        v >> (v2);
                        break;
                    case 6:
                        std::cout << 100 * v.GetBusyPercentage() << "%" << std::endl;
                        break;
                    case 7:
                        std::cout << "Type:" << v.GetType() << std::endl;
                        break;
                    case 8:
                        std::cout << "Busy:" << v.GetBusy() << std::endl;
                        break;
                    case 9:
                        std::cout << "Capacity:" << v.GetCapacity() << std::endl;
                        break;
                    case 10:
                        std::cout << "New Type: Sedentary = 1, Economy = 2, Luxury = 3, Restaurant = 4" << std::endl;
                        col = getNum<int>(1, 4);
                        v.SetType(col);
                        break;
                    case 11:
                        std::cout << "New Capacity:" << std::endl;
                        col = getNum<int>(0);
                        v.SetCapacity(col);
                        break;
                    case 12:
                        std::cout << "New Busy:" << std::endl;
                        col = getNum<int>(0);
                        v.SetBusy(col);
                        break;
                }
            } catch (const std::bad_alloc &ba) { // в случае ошибок выделения памяти
                std::cerr << "Not enough memory" << std::endl;
                //return 1;
            } catch (const std::exception &e) { // в случае прочих исключений
                std::cerr << e.what() << std::endl;
                //return 1;
            }
        }
        return v;
    }
}
