#include <iostream>
#include <string>

bool MP(std::string in)
{
    char c;                                     // Бегунок по строчке
    
    int counter_one = 0;                        // Счетчик для n и m символов
    int counter_two = 0;                        // Счетчик для 2n и 2m символов
    
    bool open_zero = false;                     // Проверка на то, что уже были '(' и '0'
    bool close_one = false;                     // Проверка на то, что уже были ')' и '1'
    bool mid_minus = false;                     // Проверка на то, что уже был  '-'
    
    int first_after_pos = 0;                    // Запоминаем позицию элемента после последнего '0'
    char first_after_val = in[0];               // Запоминаем элемент после последнего '0'
    
    // Цикл для прохода по строке
    for(int idx = 0; idx < in.length(); ++idx)
    {
        c = in[idx];                            // Обновление текста
        if(c == '(')                            // Начало считывания конструкции (^n 0^(2n)
        {
            if( open_zero == false && close_one == false && mid_minus == false) // проверка на то, что такой конструкции еще не было
            {
                open_zero = true;               // Показываем, что началась конструкция (^n 0^(2n)
                
                while(c == '(')                 // Считываем все '('
                {
                    ++counter_one;
                    c = in[++idx];
                }
            
                if(c == '0')                    // Проверяем символ после последнего '('
                {
                    while (c == '0')            // Считываем все '0'
                    {
                        ++counter_two;
                        c = in[++idx];
                    }
                } else {
                    std::cout << "Ошибка: в позиции " << idx + 1 << " неожидаемый символ " << c << std::endl;
                    return false;
                }
                
                if((counter_two - (2*counter_one)) != 0)    //проверка на то, что ( в 2 раза меньше 0
                {
                    if((counter_two - (2*counter_one)) >= 0)
                        std::cout << "Ошибка: в позиции " << idx << " неожидаемый символ " << in[idx-1] << std::endl;
                    
                    if((counter_two - (2*counter_one)) < 0)
                        std::cout << "Ошибка: в позиции " << idx+1 << " неожидаемый символ " << in[idx] << std::endl;
                    return false;
                }
                
                first_after_pos = idx + 1;      // Запоминаем позицию последнего символа и сам символ
                first_after_val = c;            // На случай множетва нежданных символов после 0
                counter_one = 0;
                counter_two = 0;
                
            } else {
                std::cout << "Ошибка: в позиции " << idx + 1 << " неожидаемый символ " << c << std::endl;
                return false;
            }
        }
        
        if(c == '-' && mid_minus == false)      // Проверяем на наличие '-'
        {
            mid_minus = true;                   // Показываем, что '-' считался
            
            // Обработка ряда потенциальных ошибок последовательной расстановки конструкции (^n 0^(2n), - и конструкции 1^(2n) )^n
            if(in[idx + 1] == '0' || in[idx + 1] == '(' || in[idx + 1] == '-')
            {
                std::cout << "Ошибка: в позиции " << idx + 2 << " неожидаемый символ " << in[idx + 1] << std::endl;
                return false;
            }
            
            if((in[idx - 1] == ')' || in[idx - 1] == '1' ) && close_one == false)
            {
                std::cout << "Ошибка: в позиции " << first_after_pos << " неожидаемый символ " << first_after_val << std::endl;
                return false;
            }
            
            if((in[idx - 1] == ')' || in[idx - 1] == '1' ) && close_one == true)
            {
                std::cout << "Ошибка: в позиции " << idx + 1 << " неожидаемый символ " << c << std::endl;
                return false;
            }
            c = in[++idx];
        }
        
        if(c == '1' && mid_minus == true)       // Проверка на наличие минуса перед конструкцией 1^(2n) )^n
        {
            close_one = true;                   // Показываем, что такая конструкция начала считываться
            
            while (c == '1')                    // Считываем все единицы
            {
                ++counter_two;
                c = in[++idx];
            }
        
            if (c == ')')                       // Проверка на наличие ')' после '1'
            {
                while(c == ')')                 // Считывание ')'
                {
                    ++counter_one;
                    c = in[++idx];
                }
            } else {
                std::cout << "Ошибка: в позиции " << idx + 1 << " неожидаемый символ " << c << std::endl;
                return false;
            }
            
            if ((counter_two - 2*counter_one) != 0) // Проверка на то, что '1' в два раза больше чем ')'
            {
                if((counter_two - (2*counter_one)) >= 0)
                    std::cout << "Ошибка: в позиции " << idx+1 << " неожидаемый символ \\0" << std::endl;
                
                if((counter_two - (2*counter_one)) < 0)
                    std::cout << "Ошибка: в позиции " << idx << " неожидаемый символ " << in[idx-1] << std::endl;
                return false;
            }
            --idx;
        } else if (mid_minus == false)
        {
            std::cout << "Ошибка: в позиции " << idx + 1 << " неожидаемый символ " << in[idx] << std::endl;
            return false;
        }
        
        // Проверка на сторонние символы
        if(c != ')' && c != '1' && c != '-' && c != '0' && c != '(' && c != '\0')
        {
            std::cout << "Ошибка: в позиции " << idx + 2 << " неожидаемый символ " << in[++idx] << std::endl;
            return 0;
        }
        
        // Дополнительная проверка на то, что символов ')' слишком много
        if(c == ')')
        {
            std::cout << "Ошибка: в позиции " << idx + 1 << " неожидаемый символ " << in[idx] << std::endl;
            return 0;
        }
    }
    std::cout << "Цепочка принадлежит языку" << std::endl;
    return true;
}

int main(int argc, const char * argv[]) {
    
//    std::string input = "((((((((((000000000000000000000-111111)))";
//    bool avtomat = MP(input);

    
//---------------------------------------------------------
    // Тест на верную строку:

    std::string test_01 = "(00-11)";

    std::cout << "=== Test 01: ===" << std::endl;

    MP(test_01);

    std::cout << std::endl;

    // Вывод:

    //      === Test 01: ===

//---------------------------------------------------------
    // Тест на строку из -:
        std::string test_02 = "-";

        std::cout << "=== Test 02: ===" << std::endl;

        MP(test_02);

        std::cout << std::endl;
    
    // Вывод:

    //      === Test 02: ===

    //
    
//---------------------------------------------------------
    // Тест строку c n=0:
        std::string test_03 = "-11)";

        std::cout << "=== Test 03: ===" << std::endl;

        MP(test_03);

        std::cout << std::endl;
    
    // Вывод:

    //      === Test 03: ===

    //
    
//---------------------------------------------------------
    // Тест на длинную строку n = 26, m = 3:
        std::string test_04 = "((((((((((((((((((((((((((0000000000000000000000000000000000000000000000000000-111111)))";

        std::cout << "=== Test 04: ===" << std::endl;

        MP(test_04);

        std::cout << std::endl;
    
    // Вывод:

    //      === Test 04: ===

    //
    
//---------------------------------------------------------
    // Тест с ошибкой в количестве '(' и '0':
        std::string test_05 = "((00000-11)";

        std::cout << "=== Test 05: ===" << std::endl;

        MP(test_05);

        std::cout << std::endl;
    // Вывод:

    //      === Test 05: ===

    // Ошибка: в позиции 7 неожидаемый символ 0
    
//---------------------------------------------------------
    // Тест с ошибкой в количестве '1' и ')':
        std::string test_06 = "((0000-1111)";

        std::cout << "=== Test 06: ===" << std::endl;

        MP(test_06);

        std::cout << std::endl;
    // Вывод:

    //      === Test 06: ===

    // Ошибка: в позиции 13 неожидаемый символ \0
    
//---------------------------------------------------------
    // Тест c ошибкой последовательности №1:

        std::string test_07 = "-11)(00";

        std::cout << "=== Test 07: ===" << std::endl;

        MP(test_07);

        std::cout << std::endl;

    // Вывод:

    //      === Test 07: ===

    // Ошибка: в позиции 5 неожидаемый символ (
    
//---------------------------------------------------------
    // Тест c ошибкой последовательности №2:

        std::string test_08 = "11)-";

        std::cout << "=== Test 08: ===" << std::endl;

        MP(test_08);

        std::cout << std::endl;
    
    // Вывод:

    //      === Test 08: ===

    // Ошибка: в позиции 1 неожидаемый символ 1

//---------------------------------------------------------
    // Тест с ошибкой на наверное расположение '-':

        std::string test_09 = "(0-011)";

        std::cout << "=== Test 09: ===" << std::endl;

        MP(test_09);

        std::cout << std::endl;
    
    // Вывод:

    //      === Test 09: ===

    // Ошибка: в позиции 3 неожидаемый символ -

//---------------------------------------------------------
    // Тест на ошибочную последоватнльность '(' и '0'

    std::string test_10 = "00(-11)";

    std::cout << "=== Test 10: ===" << std::endl;

    MP(test_10);

    std::cout << std::endl;
    
    // Вывод:

    //      === Test 10: ===

    // Ошибка: в позиции 1 неожидаемый символ 0

//---------------------------------------------------------
    // Тест на ошибочную последоватнльность ')' и '1'

    std::string test_11 = "(00-)11";

    std::cout << "=== Test 11: ===" << std::endl;

    MP(test_11);

    std::cout << std::endl;

    // Вывод:

    //      === Test 11: ===

    // Ошибка: в позиции 5 неожидаемый символ )

//---------------------------------------------------------
    // Тест с ошибкой на сторонние символы в начале:

    std::string test_12 = "+(00-11)";

    std::cout << "=== Test 12: ===" << std::endl;

    MP(test_12);

    std::cout << std::endl;
    
    // Вывод:

    //      === Test 12: ===

    // Ошибка: в позиции 1 неожидаемый символ +

//---------------------------------------------------------
    // Тест с ошибкой на сторонние символы в середине:

    std::string test_13 = "(00+-11)";

    std::cout << "=== Test 13: ===" << std::endl;

    MP(test_13);

    std::cout << std::endl;
    
    // Вывод:

    //      === Test 13: ===

    // Ошибка: в позиции 4 неожидаемый символ +

//---------------------------------------------------------
    // Тест с ошибкой на сторонние символы в конце:

    std::string test_14 = "(00-11)+";

    std::cout << "=== Test 14: ===" << std::endl;

    MP(test_14);

    std::cout << std::endl;
    
    // Вывод:

    //      === Test 14: ===

    // Ошибка: в позиции 8 неожидаемый символ +

//---------------------------------------------------------
    // Тест с ошибкой на двойной минус:

    std::string test_15 = "(00--11)";

    std::cout << "=== Test 15: ===" << std::endl;

    MP(test_15);

    std::cout << std::endl;
    
    // Вывод:

    //      === Test 15 ===

    // Ошибка: в позиции 5 неожидаемый символ -

    return 0;
}
