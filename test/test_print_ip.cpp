#define BOOST_TEST_MODULE MyTests

#include <boost/test/included/unit_test.hpp>


#include <tuple>
#include <vector>
#include <list>
#include <string>
#include <iostream>
#include <cstdint> // Для int8_t, uint8_t и т.д.
#include "../include/template.h" 




// --- Вспомогательная функция для захвата вывода ---
// Эта функция временно перенаправляет std::cout в std::stringstream
// и выполняет переданную лямбда-функцию, затем возвращает захваченный вывод.
std::string capture_stdout(std::function<void()> func) {
    std::stringstream ss;
    std::streambuf* old_cout = std::cout.rdbuf(ss.rdbuf()); // Сохраняем старый буфер cout и устанавливаем новый

    func(); // Выполняем функцию, которая выводит в std::cout

    std::cout.rdbuf(old_cout); // Восстанавливаем старый буфер cout
    return ss.str(); // Возвращаем захваченный вывод
}


// --- ТЕСТЫ ---



// Тесты для PrintInt
BOOST_AUTO_TEST_SUITE(PrintInt_Tests)

BOOST_AUTO_TEST_CASE(PrintInt_uint8_t)
{
    BOOST_CHECK_EQUAL(capture_stdout([]() { PrintInt<uint8_t>(0xFF); }), "255\n");
    BOOST_CHECK_EQUAL(capture_stdout([]() { PrintInt<uint8_t>(0x0A); }), "10\n");
    BOOST_CHECK_EQUAL(capture_stdout([]() { PrintInt<uint8_t>(0x00); }), "0\n");
    BOOST_CHECK_EQUAL(capture_stdout([]() { PrintInt<uint8_t>(1); }), "1\n");
}

BOOST_AUTO_TEST_CASE(PrintInt_uint16_t)
{
    // 192.168.1.1 -> 0xC0A80101
    BOOST_CHECK_EQUAL(capture_stdout([]() { PrintInt<uint16_t>(0xC0A8); }), "192.168\n"); // 49320

    // 10.0.0.1 -> 0x0A000001
    BOOST_CHECK_EQUAL(capture_stdout([]() { PrintInt<uint16_t>(0x0A00); }), "10.0\n"); // 2560

    BOOST_CHECK_EQUAL(capture_stdout([]() { PrintInt<uint16_t>(0x0001); }), "0.1\n"); // 1
}

BOOST_AUTO_TEST_CASE(PrintInt_uint32_t)
{
    // 192.168.1.1 -> 0xC0A80101
    BOOST_CHECK_EQUAL(capture_stdout([]() { PrintInt<uint32_t>(0xC0A80101); }), "192.168.1.1\n");

    // 10.0.0.1 -> 0x0A000001
    BOOST_CHECK_EQUAL(capture_stdout([]() { PrintInt<uint32_t>(0x0A000001); }), "10.0.0.1\n");

    // 255.255.255.255 -> 0xFFFFFFFF
    BOOST_CHECK_EQUAL(capture_stdout([]() { PrintInt<uint32_t>(0xFFFFFFFF); }), "255.255.255.255\n");

    BOOST_CHECK_EQUAL(capture_stdout([]() { PrintInt<uint32_t>(0); }), "0.0.0.0\n");
}

BOOST_AUTO_TEST_CASE(PrintInt_uint64_t)
{
    // Пример IPv6 или просто большое число, разбитое на байты
    // 1.2.3.4.5.6.7.8 -> 0x0102030405060708
    BOOST_CHECK_EQUAL(capture_stdout([]() { PrintInt<uint64_t>(0x0102030405060708ULL); }), "1.2.3.4.5.6.7.8\n");

    BOOST_CHECK_EQUAL(capture_stdout([]() { PrintInt<uint64_t>(0); }), "0.0.0.0.0.0.0.0\n");
}

BOOST_AUTO_TEST_SUITE_END() // PrintInt_Tests




// Тесты для print_ip
BOOST_AUTO_TEST_SUITE(PrintIP_Tests)


// Тесты для print_ip(T container) - нецелочисленные типы
BOOST_AUTO_TEST_SUITE(PrintIP_Container_Tests)

BOOST_AUTO_TEST_CASE(print_ip_vector)
{
    BOOST_CHECK_EQUAL(capture_stdout([]() {
        std::vector<int> vec = { 192, 168, 1, 1 };
        print_ip(vec);
        }), "192.168.1.1\n");

    BOOST_CHECK_EQUAL(capture_stdout([]() {
        std::vector<std::string> vec_str = { "hello", "world" };
        print_ip(vec_str);
        }), "hello.world\n");

    BOOST_CHECK_EQUAL(capture_stdout([]() {
        std::vector<int> empty_vec;
        print_ip(empty_vec);
        }), "\n"); // Ожидаем пустую строку и перенос

}

BOOST_AUTO_TEST_CASE(print_ip_list)
{
    BOOST_CHECK_EQUAL(capture_stdout([]() {
        std::list<int> lst = { 10, 0, 0, 1 };
        print_ip(lst);
        }), "10.0.0.1\n");

    BOOST_CHECK_EQUAL(capture_stdout([]() {
        std::list<std::string> lst_str = { "test" };
        print_ip(lst_str);
        }), "test\n");

    BOOST_CHECK_EQUAL(capture_stdout([]() {
        std::list<int> empty_lst;
        print_ip(empty_lst);
        }), "\n"); // Ожидаем пустую строку и перенос
}

BOOST_AUTO_TEST_CASE(print_ip_string)
{
    BOOST_CHECK_EQUAL(capture_stdout([]() { std::string str = "example.string"; print_ip(str); }), "example.string\n");
    BOOST_CHECK_EQUAL(capture_stdout([]() { std::string empty_str = ""; print_ip(empty_str); }), "\n");
}



BOOST_AUTO_TEST_SUITE_END() // PrintIP_Container_Tests

BOOST_AUTO_TEST_SUITE_END() // IP_Printer_Tests
