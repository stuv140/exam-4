/*! \file */
/// @brief Интерпретирует 32-битное целочисленное значение как IP-адрес и выводит его на экран.
/// @tparam U Целочисленный тип (ожидается, что он будет иметь размер не менее 2 байт).
/// @param number Целочисленное значение, представляющее IP-адрес.
/// @warning для корректного представления IP-адреса функция ожидает, что входной тип T будет иметь размер не менее 4 байт.
template<typename U>
void PrintInt(const U number) {
    /*  int i = sizeof(number);

          for (int j = (i - 1); j > 0; --j) {
          // std::cout << (temp >> 24 & 0xFF) << "." << (temp >> 16 & 0xFF) << "." << (temp >> 8 & 0xFF) << "." << (temp >> 0 & 0xFF) << std::endl;
          std::cout << (number >> (j * 8) & 0xFF) << ".";
          }
      std::cout << (number >> 0 & 0xFF) << "\n"; */
}
template <bool condition, typename Type>
/**
* @brief структура для проверки типа объекта переданного в шаблон
*/
struct EnableIf;

template <typename Type>
struct EnableIf<true, Type>
{
    using type = Type;
};
/**
* @brief функция шаблон проверяет, что у объектов в шаблоне одинаковый тип данных
* @tparam T2 первый объект в контейнере
* @param values последующие объекты в контейнере
* @return контейнер std::make_tuple
*/
template<typename T1, typename... T2>
auto if_make_types(T2... values) {

    static_assert((std::is_same_v<T2, T1> && ...),
        "All elements must be convertible to the specified target type.");

    return std::make_tuple(std::forward<T2>(values)...);
}
/**
* @brief функция шаблон проверяет соответствует ли объект типу std::string
* @param str шабон некоторого объекта
* если проверяемое условие истинно, то объект выводится на экран
*/
template <typename T> typename EnableIf<!std::is_integral<T>::value&& std::is_same<T, std::string>::value, void>::type print_ip(T str) {
    std::cout << str << std::endl;
}

/**
* @brief функция шаблон проверяет соответствует ли объект типу: std::vector или  std::list
* @param container шабон некоторого объекта
* если проверяемое условие истинно, то  выводится условный ip адрес хранящийся в объекте
*/
template <typename T> typename EnableIf<!std::is_integral<T>::value && (std::is_same<T, std::vector<typename T::value_type>>::value || std::is_same<T, std::list<typename T::value_type>>::value), void>::type print_ip(T container) {
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
/**
* @brief функция шаблон проверяет соответствует ли объект целым числам
* @param number шаблон некоторого объекта
* если проверяемое условие истинно, то  выводится условный ip адрес хранящийся в объекте
*/
template <typename T> typename EnableIf<std::is_integral<T>::value, void>::type print_ip(T number)
{
    const auto n = sizeof(number);
    switch (n)
    {
        case sizeof(int8_t) :
        {
            uint8_t temp = number; // uint8_t при передачи -1 = 255, т.к. реализуется выход за диапазон значений для этого типа
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

            PrintInt(temp);

            break;
        }
        case sizeof(int64_t) :
        {
            uint64_t temp = number;

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
/**
* @brief функция шаблон проверяет соответствует ли объект типу std::tuple
* @param ip шаблон некоторого объекта
* если проверяемое условие истинно, то выводится условный ip адрес хранящийся в объекте
*/
template <typename... Ts>
void print_ip(const std::tuple<Ts...>& ip) {

    bool first = true;
    std::apply([&](const auto&... args) {

        (([&]() { // Внутренняя лямбда для обработки каждого элемента
            if (!first) {
                std::cout << ".";
            }
            else {
                first = false;
            }
            std::cout << args; // Печатаем текущий аргумент
            }()), ...); // Fold expression для применения внутренней лямбды к каждому arg
        }, ip);
    std::cout << "\n";
}