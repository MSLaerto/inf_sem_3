#include "vagon.h"
#include <string>
#include <iostream>
#include <string>
#include <limits>
#include <cstring>

#ifndef OOPPROG2_HELP_H
#define OOPPROG2_HELP_H
template<class T>
T getNum(T min = std::numeric_limits<T>::min(), T max = std::numeric_limits<T>::max()) {
    T a;
    while (true) {
        std::cin >> a;
        if (std::cin.eof()) // обнаружен конец файла
            throw std::runtime_error("Failed to read number: EOF");
        else if (std::cin.bad()) // обнаружена невосстановимая ошибка входного потока
            throw std::runtime_error(std::string("Failed to read number: ") + strerror(errno));
        else if (std::cin.fail()) { // прочие ошибки (неправильный формат ввода)
            std::cin.clear(); // очищаем флаги состояния потока
            // игнорируем все символы до конца строки
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            std::cout << "You are wrong; repeat please!" << std::endl;
        } else if (a >= min && a <= max) // если число входит в заданный диапазон
            return a;
    }
}
#endif //OOPPROG2_HELP_H
