#include "menu.h"

std::deque<double> original_container;
std::ifstream file;
std::deque<double> transformed_container;


bool was_original_container_readed = false;
bool was_file_prepared = false;
bool was_container_transformed = false;

void print_menu() {
	std::cout << "1. ��������� ��������� ���� N ���������� ������� �� ��������� [-M; M]." << std::endl;
	std::cout << "2. ��������� ��������� ���� N ���������� ������� �� ��������� [-M; M] � ������� ������� generate." << std::endl;
	std::cout << "3. ������� ����� �� ����� � ���������." << std::endl;
	std::cout << "4. ��������� �������������� ����������. ������� modify, ����������� ���������." << std::endl;
	std::cout << "5. ��������� �������������� ����������. ������������� ������� modify, ����������� ��������� �� ������ � ����� �������������� ����� ����������." << std::endl;
	std::cout << "6. ��������� �������������� ���������� � ������� ��������� transform." << std::endl;
	std::cout << "7. ��������� �������������� ���������� � ������� ��������� for_each." << std::endl;
	std::cout << "8. ����� ����� � ����������." << std::endl;
	std::cout << "9. C������ �������������� ����� � ����������." << std::endl;
	std::cout << "0. ������� ������������ ��������� � �������." << std::endl;
	std::cout << "c. ������� ���������� ��������� � �������." << std::endl;
	std::cout << "f. ������� ���������� ��������� � ����." << std::endl;
	std::cout << "������� esc ��� ������." << std::endl;
}

void blueprint_for_options_1_2(std::ifstream (*function)(std::string, int, int)) {
	std::string file_name;
	int N, M;
	std::cout << "������� ��� �����: " << std::endl;
	std::cin >> file_name;
	std::cout << "������� ���������� ����� N: " << std::endl;
	std::cin >> N;
	std::cout << "������� ������� M: " << std::endl;
	std::cin >> M;
	
	try {
		file = function(file_name, N, M);
	}
	catch (const std::exception& e) {
		std::cerr << "������: " << e.what() << std::endl;
		return;
	}
	was_file_prepared = true;
}

void option_3() {
	if (!was_file_prepared) {
		std::cout << "���������� ������� ������������� ����. ��������� ����� 1 ��� 2." << std::endl;
		return;
	}
	try {
		original_container = read_from_file(file);
	}
	catch (const std::exception& e) {
		std::cerr << "������: " << e.what() << std::endl;
		return;
	}
	std::cout << "���� ��� �������� �������!" << std::endl;
	was_original_container_readed = true;
}

void blueprint_for_options_4_6_7(std::deque<double> (*function)(std::deque<double>, int)) {
	if (!was_original_container_readed) {
		std::cout << "���������� ������� ������� ��������� �� �����. ��������� ����� 3." << std::endl;
		return;
	}

	int k;
	std::cout << "������� ����� �������� K: " << std::endl;
	std::cin >> k;

	try {
		transformed_container = function(original_container, k);
	}
	catch (const std::exception& e) {
		std::cerr << "������: " << e.what() << std::endl;
		return;
	}

	was_container_transformed = true;
}

void option_5() {
	if (!was_original_container_readed) {
		std::cout << "���������� ������� ������� ��������� �� �����. ��������� ����� 3." << std::endl;
		return;
	}

	int begin, end, k;
	std::cout << "������� ������ ������ �������������� ����� ����������:" << std::endl;
	std::cin >> begin;
	std::cout << "������� ������ ����� �������������� ����� ���������� (����� �� ���������� � �������������� �����):" << std::endl;
	std::cin >> end;
	if (end <= begin) {
		std::cout << "������ ����� ������ ���� ������ ������� ������ ���� �� �� 1! ���������� �����." << std::endl;
		return;
	}
	if (end > original_container.size()) {
		std::cout << "��������� ������� ��������� �� ��������� ����������. ���������� �����." << std::endl;
		return;
	}
	std::cout << "������� ����� �������� K: " << std::endl;
	std::cin >> k;
	try {
		transformed_container = modify(original_container.begin() + begin, original_container.begin() + end, k);
	}
	catch (const std::exception& e) {
		std::cerr << e.what() << std::endl;
		return;
	}

	was_container_transformed = true;
}

void option_8() {
	if (!was_original_container_readed) {
		std::cout << "���������� ������� ������� ��������� �� �����. ��������� ����� 3." << std::endl;
		return;
	}
	std::cout << "����� ����� � �������� ����������: " << sum_of_elements(original_container) << std::endl;
}

void option_9() {
	if (!was_original_container_readed) {
		std::cout << "���������� ������� ������� ��������� �� �����. ��������� ����� 3." << std::endl;
		return;
	}
	std::cout << "������� �������������� ����� � �������� ����������: " << arithmetic_mean_of_elements(original_container) << std::endl;
}

void output_original_container_to_console() {
	if (!was_original_container_readed) {
		std::cout << "���������� ������� ������� ��������� �� �����. ��������� ����� 3." << std::endl;
		return;
	}
	std::cout << "������������ ���������: " << std::endl;
	output_container_to_stream(original_container, std::cout);
	std::cout << std::endl;
}

void output_transformed_container_to_console() {
	if (!was_container_transformed) {
		std::cout << "���������� ������� �������� ���������. ��������� ����� �� ����� 4-7." << std::endl;
		return;
	}
	std::cout << "���������� ���������: " << std::endl;
	output_container_to_stream(transformed_container, std::cout);
	std::cout << std::endl;
}

void output_transformed_container_to_file() {
	if (!was_container_transformed) {
		std::cout << "���������� ������� �������� ���������. ��������� ����� �� ����� 4-7." << std::endl;
		return;
	}
	std::string file_name;
	std::cout << "������� ��� �����: " << std::endl;
	std::cin >> file_name;
	std::ofstream out(file_name);
	if (!out.is_open()) {
		std::cout << "�� ������� ������� ���� �� ������!";
		return;
	}
	output_container_to_stream(transformed_container, out);
	out.close();
	std::cout << "������ ������ �������!";
}

void incorrect_button() {
	std::cout << "����� ����� ���! ��������� ��������� ����������." << std::endl;
}

void menu() {
	char symb = 0;
	while (symb != 27) {
		print_menu();
		symb = _getch();
		system("cls");
		switch (symb) {
			case '1': {
				blueprint_for_options_1_2(&create_file_with_random_numbers);
				break;
			}
			case '2': {
				blueprint_for_options_1_2(&create_file_with_random_numbers_with_generate);
				break;
			}
			case '3': {
				option_3();
				break;
			}
			case '4': {
				blueprint_for_options_4_6_7(&modify);
				break;
			}
			case '5': {
				option_5();
				break;
			}
			case '6': {
				blueprint_for_options_4_6_7(&modify_with_transform);
				break;
			}
			case '7': {
				blueprint_for_options_4_6_7(&modify_with_foreach);
				break;
			}
			case '8': {
				option_8();
				break;
			}
			case '9': {
				option_9();
				break;
			}
			case '0': {
				output_original_container_to_console();
				break;
			}
			case 'c': {
				output_transformed_container_to_console();
				break;
			}
			case 'f': {
				output_transformed_container_to_file();
				break;
			}
			default: {
				incorrect_button();
			}
		}
		system("pause");
		system("cls");
	}
}
