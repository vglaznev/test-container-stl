#pragma once

#include <string>
#include <fstream>
#include <deque>
#include <algorithm>
#include <ctime>
#include <vector>

//Пункт 1. С использованием цикла.
std::ifstream create_file_with_random_numbers(std::string, int, int);

//Пункт 1. С использование функции generate.
std::ifstream create_file_with_random_numbers_with_generate(std::string, int, int);

//Пункт 2. Чтение чисел из файла в контейнер.
std::deque<double> read_from_file(std::ifstream&);

//Пункт 3. Выполнение преобразования.
std::deque<double> modify(std::deque<double>, int);

//Пункт 4. Выполнения преобразования. Перегруженная функция modify, принимающая итераторы.
std::deque<double> modify(std::deque<double>::iterator, std::deque<double>::iterator, int);

//Пункт 5. Применение преобразования с помощью transform.
std::deque<double> modify_with_transform(std::deque<double>, int);

//Пункт 6. Применение преобразования с помощью for_each.
std::deque<double> modify_with_foreach(std::deque<double>, int);

//Пункт 7. Нахождени суммы элементов в контейнере.
double sum_of_elements(const std::deque<double>&);

//Пункт 7. Нахождение среднего арифметического элементов в контейнере.
double arithmetic_mean_of_elements(const std::deque<double>&);

//Пункт 8. Вывод контейнера в консоль/файл (зависит от потока, переданного в качестве out)
void output_container_to_stream(const std::deque<double>&, std::ostream&);

double halfsum_of_first_negative_and_k_element(std::deque<double>::const_iterator, std::deque<double>::const_iterator, int k);