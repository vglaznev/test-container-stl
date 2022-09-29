#include "menu.h"

std::deque<double> original_container;
std::ifstream file;
std::deque<double> transformed_container;


bool was_original_container_readed = false;
bool was_file_prepared = false;
bool was_container_transformed = false;

void print_menu() {
	std::cout << "1. Заполнить текстовый файл N случайными числами из диапазона [-M; M]q." << std::endl;
	std::cout << "2. Заполнить текстовый файл N случайными числами из диапазона [-M; M] с помощью функции generate." << std::endl;
	std::cout << "3. Считать числа из файла в контейнер." << std::endl;
	std::cout << "4. Выполнить преобразование контейнера. Функция modify, принимающая контейнер." << std::endl;
	std::cout << "5. Выполнить преобразование контейнера. Перегруженная функция modify, принимающая итераторы на начало и конец обрабатываемой части контейнера." << std::endl;
	std::cout << "6. Выполнить преобразование контейнера с помощью алгоритма transform." << std::endl;
	std::cout << "7. Выполнить преобразование контейнера с помощью алгоритма for_each." << std::endl;
	std::cout << "8. Сумма чисел в контейнере." << std::endl;
	std::cout << "9. Cреднее арифметическое чисел в контейнере." << std::endl;
	std::cout << "0. Вывести оригинальный контейнер в консоль." << std::endl;
	std::cout << "c. Вывести измененный контейнер в консоль." << std::endl;
	std::cout << "f. Вывести измененный контейнер в файл." << std::endl;
	std::cout << "Нажмите esc для выхода." << std::endl;
}

void blueprint_for_options_1_2(std::ifstream (*function)(std::string, int, int)) {
	std::string file_name;
	int N, M;
	std::cout << "Введите имя файла: " << std::endl;
	std::cin >> file_name;
	std::cout << "Введите количество чисел N: " << std::endl;
	std::cin >> N;
	std::cout << "Введите границу M: " << std::endl;
	std::cin >> M;
	
	try {
		file = function(file_name, N, M);
	}
	catch (const std::exception& e) {
		std::cerr << "Ошибка: " << e.what() << std::endl;
		return;
	}
	was_file_prepared = true;
}

void option_3() {
	if (!was_file_prepared) {
		std::cout << "Необходимо сначала сгенерировать файл. Выполните опцию 1 или 2." << std::endl;
		return;
	}
	try {
		original_container = read_from_file(file);
	}
	catch (const std::exception& e) {
		std::cerr << "Ошибка: " << e.what() << std::endl;
		return;
	}
	std::cout << "Файл был прочитан успешно!" << std::endl;
	was_original_container_readed = true;
}

void blueprint_for_options_4_6_7(std::deque<double> (*function)(std::deque<double>, int)) {
	if (!was_original_container_readed) {
		std::cout << "Необходимо сначала считать контейнер из файла. Выполните опцию 3." << std::endl;
		return;
	}

	int k;
	std::cout << "Введите номер элемента K: " << std::endl;
	std::cin >> k;

	try {
		transformed_container = function(original_container, k);
	}
	catch (const std::exception& e) {
		std::cerr << "Ошибка: " << e.what() << std::endl;
		return;
	}

	was_container_transformed = true;
}

void option_5() {
	if (!was_original_container_readed) {
		std::cout << "Необходимо сначала считать контейнер из файла. Выполните опцию 3." << std::endl;
		return;
	}

	int begin, end, k;
	std::cout << "Укажите индекс начала обрабатываемой части контейнера:" << std::endl;
	std::cin >> begin;
	std::cout << "Укажите индекс конца обрабатываемой части контейнера (конец не включается в обрабатываемую часть):" << std::endl;
	std::cin >> end;
	if (end <= begin) {
		std::cout << "Индекс конца должна быть больше индекса начала хотя бы на 1! Попробуйте снова." << std::endl;
		return;
	}
	if (end > original_container.size()) {
		std::cout << "Указанные индексы находятся за пределами контейнера. Попробуйте снова." << std::endl;
		return;
	}
	std::cout << "Введите номер элемента K: " << std::endl;
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
		std::cout << "Необходимо сначала считать контейнер из файла. Выполните опцию 3." << std::endl;
		return;
	}
	std::cout << "Сумма чисел в исходном контейнере: " << sum_of_elements(original_container) << std::endl;
}

void option_9() {
	if (!was_original_container_readed) {
		std::cout << "Необходимо сначала считать контейнер из файла. Выполните опцию 3." << std::endl;
		return;
	}
	std::cout << "Среднее арифметическое чисел в исходном контейнере: " << arithmetic_mean_of_elements(original_container) << std::endl;
}

void output_original_container_to_console() {
	if (!was_original_container_readed) {
		std::cout << "Необходимо сначала считать контейнер из файла. Выполните опцию 3." << std::endl;
		return;
	}
	std::cout << "Оригинальный контейнер: " << std::endl;
	output_container_to_stream(original_container, std::cout);
	std::cout << std::endl;
}

void output_transformed_container_to_console() {
	if (!was_container_transformed) {
		std::cout << "Необходимо сначала изменить контейнер. Выполните любую из опций 4-7." << std::endl;
		return;
	}
	std::cout << "Измененный контейнер: " << std::endl;
	output_container_to_stream(transformed_container, std::cout);
	std::cout << std::endl;
}

void output_transformed_container_to_file() {
	if (!was_container_transformed) {
		std::cout << "Необходимо сначала изменить контейнер. Выполните любую из опций 4-7." << std::endl;
		return;
	}
	std::string file_name;
	std::cout << "Введите имя файла: " << std::endl;
	std::cin >> file_name;
	std::ofstream out(file_name);
	if (!out.is_open()) {
		std::cout << "Не удается открыть файл на запись!";
		return;
	}
	output_container_to_stream(transformed_container, out);
	out.close();
	std::cout << "Запись прошла успешно!";
}

void incorrect_button() {
	std::cout << "Такой опции нет! Проверьте раскладку клавиатуры." << std::endl;
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
