#include <iostream>
#include "Prog1.h"

using namespace Prog1;


// основная функция
int main() {
    Matrix matrix; // исходная матрица
    try {
        matrix = input(); // ввод матрицы
        output("Sourced matrix:", matrix); // вывод матрицы
        //output_real("Sourced nnls:", matrix);
        matrix = process(matrix);
        output("\nEdited matrix:", matrix);
        output2("\nEdited matrix:", matrix);
        //output_real("Edited nnls:", matrix);
        erase(matrix); // освобождение памяти
        return 0;
    }
    catch(const std::bad_alloc &ba) { // в случае ошибок выделения памяти
        std::cerr << "Not enough memory" << std::endl;
        erase(matrix);
        return 1;
    }
    catch(const std::exception &e) { // в случае прочих исключений
        std::cerr << e.what() << std::endl;
        erase(matrix);
        return 1;
    }
    return 0;
}