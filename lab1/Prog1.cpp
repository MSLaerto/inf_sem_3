#include <iostream>
#include <algorithm>
#include <iterator>
#include "Prog1.h"
/*
struct NotNullElements{
    int rows = 0;
    int cols = 0;
    int nnls = 0;
};
struct Matrix {
    int m = 0; // строки
    int n = 0; // столбцы
    int nnl = 0;// кол-во ненулевых эл.
    NotNullElements *nne = nullptr;
};
 */
namespace Prog1 {
    Matrix input() {
        Matrix matrix;
        try {
            std::cout << "Enter number of lines: --> ";
            matrix.m = getNum<int>(0);
            std::cout << "Enter number of columns: --> ";
            matrix.n = getNum<int>(0);
            matrix.nne = new NotNullElements[sizeof(NotNullElements)*matrix.m*matrix.n];
            for (int i = 0; i < matrix.m; i++) {
                std::cout << "Enter items for matrix line #" << (i + 1) << ":" << std::endl;
                for (int j = 0; j < matrix.n; j++) {
                    int tmp = getNum<int>();
                    if (tmp) {
                        matrix.nne[matrix.nnl].rows = i;
                        matrix.nne[matrix.nnl].cols = j;
                        matrix.nne[matrix.nnl].nnls = tmp;
                        matrix.nnl += 1;
                    }
                }
            }
        }
        catch (...) { // в случае любого исключения
            erase(matrix); // очищаем уже выделенную память
            throw; // перекидываем то же исключение дальше
        }
        return matrix;
    }


    // функция вывода
    void output(const char *msg, const Matrix &matrix) {
        int k = 0;
        std::cout << msg << ":\n";
        for (int i = 0; i < matrix.m; i++) {
            for (int j = 0; j < matrix.n; j++) {
                if (matrix.nne[k].rows == i && matrix.nne[k].cols == j) {
                    std::cout << matrix.nne[k].nnls << " ";
                    k++;
                }else{
                    std::cout << "0 ";
                }
            }
            std::cout << std::endl;
        }
    }
    void output2(const char *msg, const Matrix &matrix) {
        int k = 0;
        std::cout << msg << ":\n";
        for (int i = 0; i < matrix.m; i++) {
            for (int j = 0; j < matrix.n; j++) {
                if (matrix.nne[k].rows == i && matrix.nne[k].cols == j) {
                    std::cout << matrix.nne[k].nnls << " ";
                    k++;
                }else{
                    if (k < matrix.nnl){
                        if(matrix.nne[k].rows==matrix.nne[k+1].rows){
                            std::cout << "0 ";
                        }else{
                            std::cout << "  ";
                        }
                    }else{
                        std::cout << " ";
                    }
                }
            }
            std::cout << std::endl;
        }
    }
    // вывод того , что на самом деле хранится :
    void output_real(const char *msg, const Matrix &matrix){
        std::cout << msg << ":\n";
        for (int i = 0; i < matrix.nnl; i++){
            std::cout << matrix.nne[i].rows;
        }
        std::cout << "\n";
        for (int i = 0; i < matrix.nnl; i++){
            std::cout << matrix.nne[i].cols;
        }
        std::cout << "\n";
        for (int i = 0; i < matrix.nnl; i++){
            std::cout << matrix.nne[i].nnls;
        }
    }
    // функция освобождения занятой памяти
    void erase(Matrix matrix) {
            delete[] matrix.nne;
        matrix.m = 0;
        matrix.n = 0;
        matrix.nnl = 0;
    }
int* el_del(int ind , int* arr , int len){
    int* tmp = new int[len-1];
    for(int i = 0 ; i < ind; i++){
        tmp[i] = arr[i];
    }
    for(int i = ind ; i < len-1; i++){
        tmp[i] = arr[i+1];
    }
    delete[] arr ;
    return tmp;
}

Matrix process(Matrix &matrix){ //3 3 1 1 1 1 1 1 1 1 1
    int max, max_pos;
    for(int i = 0 ; i < matrix.nnl-1  ; i++){
        if (matrix.nne[i].rows==matrix.nne[i+1].rows) {
            max = matrix.nne[i].nnls;
            max_pos = i;
            for (int j = 0; j < matrix.nnl; j++) {
                if (matrix.nne[i].rows == matrix.nne[j].rows) {
                    if (max <= matrix.nne[j].nnls) {
                        max = matrix.nne[j].nnls;
                        max_pos = j;
                    }
                }
            }
            for (int j = 0; j < matrix.nnl; j++) {
                if (matrix.nne[i].rows == matrix.nne[j].rows) {
                    if (j > max_pos) {
                        matrix.nne = del(matrix.nne , j , matrix.nnl);
                        matrix.nnl -= 1;
                        j -=1;
                        if (i >=1){
                            i-=1;
                        }
                    }
                }
            }
        }
    }
    return matrix;
}
    NotNullElements *del(NotNullElements *nne ,int ind , int len){
        for (int i = ind ; i < len ; i++){
            nne[i]=nne[i+1];
        }
        return nne;
    }
// вставка в конец массива
    int *append(int append_el, int *arr, int len) {
        arr[len] = append_el;
        return arr;
    }
}
