#ifndef OOPPROG1_PROG1_H
#define OOPPROG1_PROG1_H
#include <iostream>
#include <string>
#include <limits>
#include <cstring>
namespace Prog1 {
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

    template<class T>
    T getNum(T min = std::numeric_limits<T>::min(), T max = std::numeric_limits<T>::max()) {
        T a;
        while(true) {
            std::cin >> a;
            if(std::cin.eof()) // обнаружен конец файла
                throw std::runtime_error("Failed to read number: EOF");
            else if(std::cin.bad()) // обнаружена невосстановимая ошибка входного потока
                throw std::runtime_error(std::string("Failed to read number: ") + strerror(errno));
            else if(std::cin.fail()) { // прочие ошибки (неправильный формат ввода)
                std::cin.clear(); // очищаем флаги состояния потока
                // игнорируем все символы до конца строки
                std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
                std::cout << "You are wrong; repeat please!" << std::endl;
            }
            else if(a >= min && a <= max) // если число входит в заданный диапазон
                return a;
        }

    }
    // прототипы функций
    Matrix input(); // ввод матрицы
    void output(const char *msg, const Matrix &matrix); // вывод матрицы
    void output2(const char *msg, const Matrix &matrix);
    void output_real(const char *msg, const Matrix &matrix);
    void erase(Matrix matrix); // освобождение занятой памяти
    Matrix process(Matrix &matrix);
    int* append(int append_el , int* arr , int len);
    NotNullElements *del(NotNullElements *nne ,int ind , int len);
}

#endif //OOPPROG1_PROG1_H
