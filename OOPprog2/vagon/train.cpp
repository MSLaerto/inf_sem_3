#include "vagon.h"
#include "train.h"
#include "help.h"
namespace Prog2 {
    ctrain::ctrain(){
        this->train = new Prog2::wagon[1];
        this->len = 0;
    }
    ctrain::ctrain(int new_len , int type) {
        try {
            if (type == 1) {
                Prog2::wagon v(1);
                this->train = new Prog2::wagon[new_len];
                this->len = new_len;
                int newtype = 1, newcapacity = 0, newbusy = 0;
                for (int i = 0; i < new_len; i++) {
                    std::cout << "New type: Sedentary = 1, Economy = 2, Luxury = 3, Restaurant = 4" << std::endl;
                    newtype = getNum<int>(1, 4);
                    std::cout << "New capacity: " << std::endl;
                    newcapacity = getNum<int>(0);
                    std::cout << "New busy: " << std::endl;
                    newbusy = getNum<int>(0, newcapacity);
                    v.Editwagon(newcapacity, newbusy, newtype);
                    this->train[i] = v;
                }
            }else{
                Prog2::wagon v(1);
                this->train = new Prog2::wagon[new_len];
                this->len = new_len;
                for (int i = 0; i < new_len; i++) {
                    v.Editwagon(50, 30, 1);
                    this->train[i] = v;
                }
            }
        } catch (const std::exception &e) {
            std::cerr << e.what() << std::endl;
        }
    }

    void ctrain::printTrain() {
        std::cout << "Train length: " << this->len << std::endl;
        for (int i = 0; i < len; i++) {
            this->train[i].Printwagon();
        }
    }
    ctrain ctrain::operator+=(wagon &v) {
        if (this->train == nullptr){
            throw std::underflow_error("Train is empty");
        }
        ctrain temp(this->len + 1 , 0);
        for (int i = 0; i < this->len; i++) {
            temp.train[i] = this->train[i];
        }
        temp.train[this->len] = v;
        delete[] this->train;
        this->len++;
        this->train = new wagon[this->len];
        for (int i = 0; i < this->len; i++) {
            this->train[i] = temp.train[i];
        }
        delete[] temp.train;
    }
    wagon& ctrain::operator[](int num) {
        return this->train[num];
    }
    void ctrain::deleteWagon(int num) {
        ctrain temp(this->len-1,0);
        for (int i = 0; i < num ; i++ ){
            temp.train[i]=this->train[i];
        }
        for (int i = num ; i < len-1 ; i++ ){
            temp.train[i]=this->train[i+1];
        }
        delete[] this->train;
        this->train = new wagon[this->len-1];
        this->len=this->len-1;
        for (int i = 0; i < this->len; i++) {
            this->train[i] = temp.train[i];
        }
    }
    void ctrain::addWithType(int num, int type){
        int min_pass = this->train[0].GetBusy();
        int min_ind = 0 ;
        int ok = 0;
        Prog2::wagon::typeData wType = Prog2::wagon::tType(type);
        for(int i = 0 ; i < this->len ; i++ ) {
            if (this->train[i].GetType() == wType) {
                ok = 1;
            }
        }
        if (!ok){
            throw std::underflow_error("No such wagon");
        }
        for(int i = 0 ;i < this->len ; i++ ){
            if(this->train[i].GetType()==wType){
                if(this->train[i].GetBusy()<=min_pass){
                    min_pass=this->train[i].GetBusy();
                    min_ind = i;
                }
            }
        }
        this->train[min_ind].add(num);
    }
    void ctrain::optimize(){
        try {
            if (this->train == nullptr) {
                throw std::underflow_error("Train is empty");
            }
            int S_pass = 0, E_pass = 0, L_pass = 0;
            for (int i = 0; i < this->len; i++) {
                if (this->train[i].GetType() == Prog2::wagon::typeData::Sedentary) {
                    S_pass += this->train[i].GetBusy();
                }
                if (this->train[i].GetType() == Prog2::wagon::typeData::Economy) {
                    E_pass += this->train[i].GetBusy();
                }
                if (this->train[i].GetType() == Prog2::wagon::typeData::Luxury) {
                    L_pass += this->train[i].GetBusy();
                }
            }
            for (int i = 0; i < this->len; i++) {
                this->train[i].SetBusy(0);
            }
            for (int i = 0; i < this->len; i++) {
                if (this->train[i].GetType() == Prog2::wagon::typeData::Sedentary) {
                    if (this->train[i].GetCapacity() - this->train[i].GetBusy() > 0) {
                        if (S_pass > 0) {
                            if (S_pass < this->train[i].GetCapacity() - this->train[i].GetBusy()) {
                                this->train[i].add(S_pass);
                                S_pass = 0;
                            } else {
                                this->train[i].add(this->train[i].GetCapacity() - this->train[i].GetBusy());
                                S_pass -= this->train[i].GetCapacity();
                            }
                        }
                    }
                }
                if (this->train[i].GetType() == Prog2::wagon::typeData::Economy) {
                    if (this->train[i].GetCapacity() - this->train[i].GetBusy() > 0) {
                        if (E_pass > 0) {
                            if (E_pass < this->train[i].GetCapacity() - this->train[i].GetBusy()) {
                                this->train[i].add(E_pass);
                                E_pass = 0;
                            } else {
                                this->train[i].add(this->train[i].GetCapacity() - this->train[i].GetBusy());
                                E_pass -= this->train[i].GetCapacity();
                            }
                        }
                    }
                }
                if (this->train[i].GetType() == Prog2::wagon::typeData::Luxury) {
                    if (this->train[i].GetCapacity() - this->train[i].GetBusy() > 0) {
                        if (L_pass > 0) {
                            if (L_pass < this->train[i].GetCapacity() - this->train[i].GetBusy()) {
                                this->train[i].add(L_pass);
                                L_pass = 0;
                            } else {
                                this->train[i].add(this->train[i].GetCapacity() - this->train[i].GetBusy());
                                L_pass -= this->train[i].GetCapacity();
                            }
                        }
                    }
                }
            }
            for (int i = 0; i < this->len; i++) {
                if (this->train[i].GetBusy() == 0) {
                    this->deleteWagon(i);
                    i--;
                    this->len--;
                }
            }
        }catch (const std::exception &e) {
                std::cerr << e.what() << std::endl;
            }
        }
    void ctrain::placeRestoraunt(){
        if (this->train == nullptr){
            throw std::underflow_error("Train is empty");
        }
        int pass_count = 0 , cur_pass = 0 ;
        for(int i = 0 ; i < this->len ; i++) {
            if (this->train[i].GetType() != Prog2::wagon::typeData::Luxury) {
                pass_count += this->train[i].GetBusy();
            }
        }
        if (pass_count == 0 ){
            throw std::underflow_error("There is no customers for restoraunt wagon");
        }
        for(int i = 0 ; i < this->len ; i++){
            if (double(cur_pass)/double(pass_count)<0.5 && i != this->len-1){
                cur_pass += this->train[i].GetBusy();
            }else{
                auto* trainnew = new Prog2::wagon[this->len+1];
                for(int j = 0; j<this->len; j++){
                    if(j<i){
                        trainnew[j] = this->train[j];
                    }else{
                        trainnew[j+1] = this->train[j];
                    }
                }
                trainnew[i] = wagon(4 , 0 , 0);
                delete[] this->train;
                this->train = trainnew;
                this->len++;
                break;
            }
        }
    }
    void ctrain::equalize(){
        if (this->train == nullptr){
            throw std::underflow_error("Train is empty");
        }
        int S_pass = 0 , E_pass = 0 , L_pass = 0;
        int S_pass_cap = 0 , E_pass_cap = 0 , L_pass_cap = 0;
        for(int i = 0 ; i < this->len ; i++){
            if(this->train[i].GetType()==Prog2::wagon::typeData::Sedentary) {
                S_pass += this->train[i].GetBusy();
                S_pass_cap += this->train[i].GetCapacity();
            }
            if(this->train[i].GetType()==Prog2::wagon::typeData::Economy){
                E_pass += this->train[i].GetBusy();
                E_pass_cap += this->train[i].GetCapacity();
            }
            if(this->train[i].GetType()==Prog2::wagon::typeData::Luxury){
                L_pass += this->train[i].GetBusy();
                L_pass_cap += this->train[i].GetCapacity();
            }
        }
        double S_fullness = double(S_pass)/double(S_pass_cap);
        double E_fullness = double(E_pass)/double(E_pass_cap);
        double L_fullness = double(L_pass)/double(L_pass_cap);
        for(int i = 0 ; i < this->len ; i++){
            this->train[i].SetBusy(0);
        }
        for(int i = 0 ; i < this->len ; i++){
            if(this->train[i].GetType()==Prog2::wagon::typeData::Sedentary) {
                int pass_num = int(double(this->train[i].GetCapacity())*S_fullness);
                this->train[i].add(pass_num);
                S_pass -= pass_num;
            }
            if(this->train[i].GetType()==Prog2::wagon::typeData::Economy){
                int pass_num = int(double(this->train[i].GetCapacity())*E_fullness);
                this->train[i].add(pass_num);
                E_pass -= pass_num;
            }
            if(this->train[i].GetType()==Prog2::wagon::typeData::Luxury){
                int pass_num = int(double(this->train[i].GetCapacity())*L_fullness);
                this->train[i].add(pass_num);
                L_pass -= pass_num;
            }
        }
        for(int i = 0 ; i < this->len ; i++){
            if(this->train[i].GetType()==Prog2::wagon::typeData::Sedentary) {
                if(S_pass != 0) {
                    this->train[i].add(1);
                    S_pass -= 1;
                }
            }
            if(this->train[i].GetType()==Prog2::wagon::typeData::Economy){
                if(E_pass != 0) {
                    this->train[i].add(1);
                    E_pass -= 1;
                }
            }
            if(this->train[i].GetType()==Prog2::wagon::typeData::Luxury){
                if(L_pass != 0) {
                    this->train[i].add(1);
                    L_pass -= 1;
                }
            }
        }
    }
    ctrain::~ctrain(){
        delete[] this->train;
    }
    void ctrain::tcopy(wagon *train , int len){
        this->train=train;
        this->len=len;
        train = nullptr;
        len = 0;
    }
    //ctrain& ctrain::operator=(ctrain&& other) noexcept {
    //    if (this != &other) {
    //        delete[] train;
    //        train = other.train;
    //        len = other.len;
    //        other.train = nullptr;
    //        other.len = 0;
    //    }
    //    return *this;
    //}
}
