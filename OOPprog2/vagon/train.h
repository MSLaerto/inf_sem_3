//
// Created by 1 on 25.10.2023.
//

#ifndef OOPPROG2_TRAIN_H
#define OOPPROG2_TRAIN_H

namespace Prog2 {
    class ctrain {
    private:
        Prog2::wagon *train;
        int len = 0;
    public:
        ctrain();
        explicit ctrain(int len , int type);
        void printTrain();
        ctrain operator+=(wagon &v);
        wagon& operator[](int num);
        void deleteWagon(int num);
        int GetLen() const{return len;};
        void addWithType(int num , int type);
        void optimize();
        void placeRestoraunt();
        void equalize();
        ~ctrain();
        ctrain(wagon *train , int len);
        void tcopy(wagon *train , int len);
        ctrain& operator=(ctrain&& other) noexcept ;
    };
}


#endif //OOPPROG2_TRAIN_H
