#include <iostream>
#include "vagon/vagon.h"
#include "help.h"
#include "vagon/train.h"

int main2() {
    Prog2::wagon v(1,50,30);
    int n = -1;
    int num, newtype, newcapacity, newbusy , passengers ;
    std::cout << "Enter number of wagons in train: " << std::endl;
    int trainlen = getNum<int>(0);
    Prog2::ctrain train(trainlen, 1);
    try{
        while(n != 0) {
            try {
                std::cout << "1 - Show train" << std::endl;
                std::cout << "2 - Add wagon (+=)" << std::endl;
                std::cout << "3 - Delete wagon" << std::endl;
                std::cout << "4 - Show wagon ([])" << std::endl;
                std::cout << "5 - Work with wagon" << std::endl;
                std::cout << "6 - Add with type" << std::endl;
                std::cout << "7 - Show train len" << std::endl;
                std::cout << "8 - Optimize train" << std::endl;
                std::cout << "9 - Place restaurant" << std::endl;
                std::cout << "10 - Equalize (same %)" << std::endl;
                std::cout << "0 - Exit" << std::endl;
                n = getNum(0, 12);
                switch (n) {
                    case 1:
                        train.printTrain();
                        break;
                    case 2:
                        std::cout << "New type: Sedentary = 1, Economy = 2, Luxury = 3, Restaurant = 4" << std::endl;
                        newtype = getNum<int>(1, 4);
                        std::cout << "New capacity: " << std::endl;
                        newcapacity = getNum<int>(0);
                        std::cout << "New busy: " << std::endl;
                        newbusy = getNum<int>(0, newcapacity);
                        v.Editwagon(newcapacity, newbusy, newtype);
                        train+=v;
                        break;
                    case 3:
                        std::cout << "Need to delete: " << std::endl;
                        num = getNum<int>(1, trainlen);
                        train.deleteWagon(num);
                        break;
                    case 4:
                        std::cout << "Need to show: " << std::endl;
                        num = getNum<int>(1, trainlen);
                        v = train[num];
                        std::cout << "Wagon: " << std::endl;
                        v.Printwagon();
                        break;
                    case 5:
                        std::cout << "Need to work with: " << std::endl;
                        num = getNum<int>(1, train.GetLen());
                        v = train[num - 1];
                        v = v.WagonMenu(v);
                        v.Printwagon();
                        train[num - 1].Editwagon(v.GetCapacity(), v.GetBusy(), v.GetType());
                        break;
                    case 6:
                        std::cout << "Type : " << std::endl;
                        num = getNum<int>(1, 3);
                        std::cout << "Passengers : " << std::endl;
                        passengers = getNum<int>(0);
                        train.addWithType(passengers, num);
                        break;
                    case 7:
                        std::cout << "Length : " << train.GetLen() << std::endl;
                        break;
                    case 8:
                        train.optimize();
                        break;
                    case 9:
                        train.placeRestoraunt();
                        break;
                    case 10:
                        train.equalize();
                        break;
                }
            }catch(const std::exception &e) { // в случае прочих исключений
                std::cerr << e.what() << std::endl;
            }
        }
    }catch(const std::bad_alloc &ba) { // в случае ошибок выделения памяти
            std::cerr << "Not enough memory" << std::endl;
            train.~ctrain();
            return 1;
    }catch(const std::exception &e) { // в случае прочих исключений
            std::cerr << e.what() << std::endl;
    }
    train.~ctrain();
    return 0;
}


