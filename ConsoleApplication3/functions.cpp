#include "functions.h"

//Пункт 1. С использованием циклаq
std::ifstream create_file_with_random_numbers(std::string file_name, int N, int M) {
	std::ofstream out(file_name);
	if (!out.is_open()) {
		throw std::exception("Не удается открыть файл на запись!");
	}
	//Для генератора псевдослучайных чисел необходимо задать стартовое значение, используем текущее время в секундах
	std::srand(std::time(nullptr));
	for (int i = 0; i < N; i++) {
		//Записываем целое псевдослучайное число из диапазона [-M; M]
		out << std::rand() % (2 * M + 1) - M << " ";
	}
	//Закрываем поток
	out.close();
	std::ifstream in(file_name);
	if (!in.is_open()) {
		throw std::exception("Не удается открыть файл на чтение!");
	}
	return in;
}

//Пункт 1. С использование функции generate
std::ifstream create_file_with_random_numbers_with_generate(std::string file_name, int N, int M) {
	std::ofstream out(file_name);
	if (!out.is_open()) {
		throw std::exception("Не удается открыть файл на запись!");
	}
	//Для генератора псевдослучайных чисел необходимо задать стартовое значение, используем текущее время в секундах
	std::srand(std::time(nullptr));
	
	std::vector<int> generated_numbers(N);
	//Генерируем вектор N чисел из диапазона [-M; M] 
	std::generate(generated_numbers.begin(), generated_numbers.end(), [M]() {return std::rand() % (2 * M + 1) - M; });
	//Записываем в файл
	std::copy(generated_numbers.begin(), generated_numbers.end(), std::ostream_iterator<int>(out, " "));

	//Закрываем поток
	out.close();
	std::ifstream in(file_name);
	if (!in.is_open()) {
		throw std::exception("Не удается открыть файл на чтение!");
	}
	return in;
}

//Пункт 2
std::deque<double> read_from_file(std::ifstream& file) {
	std::deque<double> result;
	int current_number;
	while (file >> current_number) {
		result.push_back(current_number);
	}

	return result;
}

//Пункт 3
std::deque<double> modify(std::deque<double> container, int k) {
	double halfsum = halfsum_of_first_negative_and_k_element(container.cbegin(), container.cend(), k);
	for (int i = 0; i < container.size(); i++) {
		container.at(i) /= halfsum;
	}
	return container;
}

//Пункт 4
std::deque<double> modify(std::deque<double>::iterator begin, std::deque<double>::iterator end, int k) {
	double halfsum = halfsum_of_first_negative_and_k_element(begin, end, k);
	for (auto it = begin; it != end; it++) {
		*it /= halfsum;
	}
	//Примечание:
	//Если возвращать контейнер - необязательное условие для этой функции, то можно передавать итераторы по ссылке.
	//Соответсвтенно, изменяться будет исходный контейнер, на элементы которого указывают итераторы.
	//Такой вариант функции закомментирован ниже.
	std::deque<double> result_container(end - begin);
	std::copy(begin, end, result_container.begin());
	return result_container;
}

////Альтернативный вариант функции, принимающей итераторы
////Пункт 4
//void modify(std::deque<double>::iterator& begin, std::deque<double>::iterator& end, int k) {
//	double halfsum = halfsum_of_first_negative_and_k_element(begin, end, k);
//	for (auto it = begin; it != end; it++) {
//		*it /= halfsum;
//	}
//}

//Пункт 5. Применение преобразования с помощью transform.
std::deque<double> modify_with_transform(std::deque<double> container, int k) {
	double halfsum = halfsum_of_first_negative_and_k_element(container.cbegin(), container.cend(), k);
	//Результирующую последовательность сохраняем в том же контейнере, что и исходную (поэтому третьим аргументом идет container.begin())
	std::transform(container.begin(), container.end(), container.begin(), [halfsum](double element) {return element / halfsum; });
	return container;
}

//Пункт 6. Применение преобразования с помощью for_each.
std::deque<double> modify_with_foreach(std::deque<double> container, int k) {
	double halfsum = halfsum_of_first_negative_and_k_element(container.cbegin(), container.cend(), k);
	std::for_each(container.begin(), container.end(), [halfsum](double& element) {element /= halfsum; });
	return container;
}

//Пункт 7. Нахождени суммы элементов в контейнере.
double sum_of_elements(const std::deque<double>& container) {
	double sum = 0;
	for (auto it = container.begin(); it != container.end(); it++) {
		sum += *it;
	}
	return sum;
}

//Пункт 7. Нахождение среднего арифметического элементов в контейнере.
double arithmetic_mean_of_elements(const std::deque<double>& container) {
	return sum_of_elements(container) / container.size();
}

//Пункт 8. Вывод измененного контейнера в консоль/файл (зависит от потока, переданного в качестве out)
void output_container_to_stream(const std::deque<double>& container, std::ostream& out) {
	std::copy(container.begin(), container.end(), std::ostream_iterator<double>(out, " "));
}


//Вспомогательная функция для нахождения полусуммы первого отрицательного числа и K-го числа в контейнере
double halfsum_of_first_negative_and_k_element(std::deque<double>::const_iterator begin, std::deque<double>::const_iterator end, int k) {
	std::deque<double>::const_iterator it;
	//идем по контейнеру пока не найдем первый отрицательный элемент
	for (it = begin; it != end && *it >= 0; it++);
	//если мы дошли до конца контейнера и последний элемент в нем положительный, то выкидываем исключение
	if (*it >= 0) {
		throw std::exception("В контейнере отсутствуют отрицательные числа! Попробуйте перегенировать файл и считать числа заново!");
	}
	
	if ((end - begin) <= k) {
		throw std::exception("k больше, чем количество элементов в контейнере!");
	}
	
	double halfsum = (*it + *(begin + k)) / 2.0;

	if (halfsum == 0) {
		throw std::exception("Полусумма равна нулю. Дальнейшее деление на полусумму невозможно");
	}
	return halfsum;
}
