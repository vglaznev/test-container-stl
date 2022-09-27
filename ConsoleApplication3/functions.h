#pragma once

#include <string>
#include <fstream>
#include <deque>
#include <algorithm>
#include <ctime>
#include <vector>

//����� 1. � �������������� �����.
std::ifstream create_file_with_random_numbers(std::string, int, int);

//����� 1. � ������������� ������� generate.
std::ifstream create_file_with_random_numbers_with_generate(std::string, int, int);

//����� 2. ������ ����� �� ����� � ���������.
std::deque<double> read_from_file(std::ifstream&);

//����� 3. ���������� ��������������.
std::deque<double> modify(std::deque<double>, int);

//����� 4. ���������� ��������������. ������������� ������� modify, ����������� ���������.
std::deque<double> modify(std::deque<double>::iterator, std::deque<double>::iterator, int);

//����� 5. ���������� �������������� � ������� transform.
std::deque<double> modify_with_transform(std::deque<double>, int);

//����� 6. ���������� �������������� � ������� for_each.
std::deque<double> modify_with_foreach(std::deque<double>, int);

//����� 7. ��������� ����� ��������� � ����������.
double sum_of_elements(const std::deque<double>&);

//����� 7. ���������� �������� ��������������� ��������� � ����������.
double arithmetic_mean_of_elements(const std::deque<double>&);

//����� 8. ����� ���������� � �������/���� (������� �� ������, ����������� � �������� out)
void output_container_to_stream(const std::deque<double>&, std::ostream&);

double halfsum_of_first_negative_and_k_element(std::deque<double>::const_iterator, std::deque<double>::const_iterator, int k);