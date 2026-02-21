#include <iostream>
#include <string>
#include<vector>
#include<list>
#include<tuple>
#include<stdint.h>
#include"Template.h"

//<summary>
/// Применяем полученные знания о шаблонах, реализуя перегруженные шаблонные функции с помощью механизма SFINAE. Подключаем к своей сборочной ферме утилиту doxygen.
/// </summary>

int main()
{
    int number = 2130706433;
    int8_t u8 =  -1;
    int16_t u16= 0;
    int32_t u32 = 2130706433;
    int64_t u64 = 8875824491850138409;
    std::string str("Hello world!");
    std::vector<int> vInt = {100,200,300,400};
    std::list<short> lInt= {400,300,200,100};
    
   
    auto make_tuple = if_make_types<int>(123, 456, 789, 0);
    std::tuple<int, int, int, int> t1 = { 123, 456, 789, 0 };
  // тут ошибка компиляции
 //auto make_tuple2 = if_make_types<double>(123.3, 45645, 789.666, 0.2);
  //print_ip(int8_t) вывод в виде произвольного целочисленного типа
 print_ip(u8);
 //print_ip(int16_t) вывод в виде двух целочисленных типов разделенных точкой
 print_ip(u16);
// print_ip(int32_t) вывод ip адресса
 print_ip(u32);
 // print_ip(int64_t) вывод целых чисел разделенных точкой
 print_ip(u64);
 // print_ip(std::string) вывод String
 print_ip(str);
 // print_ip(std::vector<int>) вывод через точку чисел вектора
 print_ip(vInt);
 print_ip(lInt);
 print_ip(make_tuple);
// print_ip(number);  //надоже это тоже работает 
 
  
    return 0; 

}
