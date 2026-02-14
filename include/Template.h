#pragma once
#include <string>
#include<list>
#include<tuple>

template<typename U>
void PrintInt(const U number) {
    int i = sizeof(number);
    
        for (int j = (i - 1); j > 0; --j) {
        // std::cout << (temp >> 24 & 0xFF) << "." << (temp >> 16 & 0xFF) << "." << (temp >> 8 & 0xFF) << "." << (temp >> 0 & 0xFF) << std::endl;
        std::cout << (number >> (j * 8) & 0xFF) << ".";
        }
    std::cout << (number >> 0 & 0xFF) << "\n";
}

template <bool condition, typename Type>

struct EnableIf;

template <typename Type>
struct EnableIf<true, Type>
{
    using type = Type;
};

template<typename T>
struct container_category {
    constexpr static bool vector_ip = false;
    constexpr static bool list_ip = false;
    constexpr static bool string_ip = false;
    constexpr static bool tuple_ip = false;
};
template<typename T>
struct container_category <std::vector<T>> {
    constexpr static bool vector_ip = true;
    constexpr static bool list_ip = false;
    constexpr static bool string_ip = false;
    constexpr static bool tuple_ip = false;
};

template<typename T>
struct container_category <std::list<T>> {
    constexpr static bool list_ip = true;
    constexpr static bool vector_ip = false;
    constexpr static bool string_ip = false;
    constexpr static bool tuple_ip = false;
};

template<typename... Args>
struct container_category <std::tuple<Args...>> {
    constexpr static bool tuple_ip = true;
    constexpr static bool vector_ip = false;
    constexpr static bool list_ip = false;
    constexpr static bool string_ip = false;
};
template<>
struct container_category <std::string> {
    constexpr static bool vector_ip = false;
    constexpr static bool list_ip = false;
    constexpr static bool string_ip = true;
    constexpr static bool tuple_ip = false;
};
template<typename T1, typename... T2>
inline constexpr auto if_make_types(T2... values) {
    
    static_assert((std::is_same_v<T2, T1> && ...),
        "All elements must be convertible to the specified target type.");
   
    return std::make_tuple(std::forward<T2>(values)...); 
}


template <typename T> EnableIf<!std::is_integral<T>::value, void>::type print_ip(T container)
{
    if constexpr (container_category<T>::vector_ip || container_category<T>::list_ip) {
        auto num = container.size();
        for (auto elem : container)
        {
            std::cout << elem;
            --num;
            if (num) {
                std::cout << ".";
            }
        }
        std::cout << std::endl;
    }
    else {
        if constexpr (container_category<T>::string_ip) {
            std::cout << container << std::endl;
        }
            else {
                 if constexpr (container_category<T>::tuple_ip) { 
                                
               //  оказывается std::get<index> не будет работать т.к. значения подставляются на этапе компиляции
                 // если в новой версии программы количество элеменов изменится, то нужно будет изменять код. не удобно! 
                 // если передать три значения std::make_tuple(123,456,789);, то в коде нужно будет удалить вызов std::get<3>(container)
                     for (auto index = 0; index < ((std::tuple_size<decltype(container)>::value)); ++index)
                     {
                         switch (index) {
                         case 0:
                         {
                             std::cout << std::get<0>(container) << ".";
                             break;
                         }
                         case 1:
                         {
                             std::cout << std::get<1>(container) << ".";
                             break;
                         }
                         case 2:
                         {
                             std::cout << std::get<2>(container) << ".";
                             break;
                         }
                         case 3:
                         {
                             std::cout << std::get<3>(container) << std::endl;
                             break;
                         }
                             default:
                             {
                             std::cerr << "invalid index" << std::endl;
                             }
                         }
                     }

                 }

        }
    }
}
template <typename T> EnableIf<std::is_integral<T>::value, void>::type print_ip(T number)
{


    const auto n = sizeof(number);
    switch (n)
    {
        case sizeof(int8_t) :
        {
            uint8_t temp = number; //-1 = 255, т.к. реализуется выход за диапазон значений для этого типа
            std::cout << (int)temp << std::endl; //можно раскоментировать PrintInt результат такой же, но так на мой взгляд быстрее
          //  PrintInt(temp);
            break;
        }
        case sizeof(int16_t) :
        {
            uint16_t temp = number; // по анологии с uint8_t  в подобных местах используем беззнаковые числа.
            /* int i = sizeof(int16_t);

             for (int j = sizeof(temp) - 1; j > 0; --j) {
                 std::cout << (temp >> (j & 0xFF)) << ".";
             }
             std::cout << (temp >> (0xFF)) << "\n";*/
             
            PrintInt(temp);
            break;
        }
        case sizeof(int32_t) :
        {
            uint32_t temp = number;
            /*  for (int j = sizeof(temp) - 1; j > 0; --j) {
             // std::cout << (temp >> 24 & 0xFF) << "." << (temp >> 16 & 0xFF) << "." << (temp >> 8 & 0xFF) << "." << (temp >> 0 & 0xFF) << std::endl;
                  std::cout << (temp >> (j * 8) & 0xFF) << ".";
              }
              std::cout << (temp >>0 & 0xFF) << "\n";*/
            PrintInt(temp);

            break;
        }
        case sizeof(int64_t) :
        {
            uint64_t temp = number;
            /*  for (int j = sizeof(temp) - 1; j > 0; --j) {
                  // std::cout << (temp >> 24 & 0xFF) << "." << (temp >> 16 & 0xFF) << "." << (temp >> 8 & 0xFF) << "." << (temp >> 0 & 0xFF) << std::endl;
                  std::cout << (temp >> (j * 8) & 0xFF) << ".";
              }
              std::cout << (temp >> 0 & 0xFF) << "\n";*/

            PrintInt(temp);
            break;
        }

        default:
        {
            std::cerr << "invalid type" << std::endl;
            break;
        }
    }


}

//Можно раскоментировать void print_ip(std::string str) тогда if constexpr (container_category<T>::string_ip)  не будет работать
/*
void print_ip(std::string str)
{
    std::cout << str <<" no works if constexpr (container_category<T>::string_ip)"<< std::endl;
}
*/
