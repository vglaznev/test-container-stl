#include "functions.h"

//����� 1. � �������������� �����
std::ifstream create_file_with_random_numbers(std::string file_name, int N, int M) {
	std::ofstream out(file_name);
	if (!out.is_open()) {
		throw std::exception("�� ������� ������� ���� �� ������!");
	}
	//��� ���������� ��������������� ����� ���������� ������ ��������� ��������, ���������� ������� ����� � ��������
	std::srand(std::time(nullptr));
	for (int i = 0; i < N; i++) {
		//���������� ����� ��������������� ����� �� ��������� [-M; M]
		out << std::rand() % (2 * M + 1) - M << " ";
	}
	//��������� �����
	out.close();
	std::ifstream in(file_name);
	if (!in.is_open()) {
		throw std::exception("�� ������� ������� ���� �� ������!");
	}
	return in;
}

//����� 1. � ������������� ������� generate
std::ifstream create_file_with_random_numbers_with_generate(std::string file_name, int N, int M) {
	std::ofstream out(file_name);
	if (!out.is_open()) {
		throw std::exception("�� ������� ������� ���� �� ������!");
	}
	//��� ���������� ��������������� ����� ���������� ������ ��������� ��������, ���������� ������� ����� � ��������
	std::srand(std::time(nullptr));
	
	std::vector<int> generated_numbers(N);
	//���������� ������ N ����� �� ��������� [-M; M] 
	std::generate(generated_numbers.begin(), generated_numbers.end(), [M]() {return std::rand() % (2 * M + 1) - M; });
	//���������� � ����
	std::copy(generated_numbers.begin(), generated_numbers.end(), std::ostream_iterator<int>(out, " "));

	//��������� �����
	out.close();
	std::ifstream in(file_name);
	if (!in.is_open()) {
		throw std::exception("�� ������� ������� ���� �� ������!");
	}
	return in;
}

//����� 2
std::deque<double> read_from_file(std::ifstream& file) {
	std::deque<double> result;
	int current_number;
	while (file >> current_number) {
		result.push_back(current_number);
	}

	return result;
}

//����� 3
std::deque<double> modify(std::deque<double> container, int k) {
	double halfsum = halfsum_of_first_negative_and_k_element(container.cbegin(), container.cend(), k);
	for (int i = 0; i < container.size(); i++) {
		container.at(i) /= halfsum;
	}
	return container;
}

//����� 4
std::deque<double> modify(std::deque<double>::iterator begin, std::deque<double>::iterator end, int k) {
	double halfsum = halfsum_of_first_negative_and_k_element(begin, end, k);
	for (auto it = begin; it != end; it++) {
		*it /= halfsum;
	}
	//����������:
	//���� ���������� ��������� - �������������� ������� ��� ���� �������, �� ����� ���������� ��������� �� ������.
	//��������������, ���������� ����� �������� ���������, �� �������� �������� ��������� ���������.
	//����� ������� ������� ��������������� ����.
	std::deque<double> result_container(end - begin);
	std::copy(begin, end, result_container.begin());
	return result_container;
}

////�������������� ������� �������, ����������� ���������
////����� 4
//void modify(std::deque<double>::iterator& begin, std::deque<double>::iterator& end, int k) {
//	double halfsum = halfsum_of_first_negative_and_k_element(begin, end, k);
//	for (auto it = begin; it != end; it++) {
//		*it /= halfsum;
//	}
//}

//����� 5. ���������� �������������� � ������� transform.
std::deque<double> modify_with_transform(std::deque<double> container, int k) {
	double halfsum = halfsum_of_first_negative_and_k_element(container.cbegin(), container.cend(), k);
	//�������������� ������������������ ��������� � ��� �� ����������, ��� � �������� (������� ������� ���������� ���� container.begin())
	std::transform(container.begin(), container.end(), container.begin(), [halfsum](double element) {return element / halfsum; });
	return container;
}

//����� 6. ���������� �������������� � ������� for_each.
std::deque<double> modify_with_foreach(std::deque<double> container, int k) {
	double halfsum = halfsum_of_first_negative_and_k_element(container.cbegin(), container.cend(), k);
	std::for_each(container.begin(), container.end(), [halfsum](double& element) {element /= halfsum; });
	return container;
}

//����� 7. ��������� ����� ��������� � ����������.
double sum_of_elements(const std::deque<double>& container) {
	double sum = 0;
	for (auto it = container.begin(); it != container.end(); it++) {
		sum += *it;
	}
	return sum;
}

//����� 7. ���������� �������� ��������������� ��������� � ����������.
double arithmetic_mean_of_elements(const std::deque<double>& container) {
	return sum_of_elements(container) / container.size();
}

//����� 8. ����� ����������� ���������� � �������/���� (������� �� ������, ����������� � �������� out)
void output_container_to_stream(const std::deque<double>& container, std::ostream& out) {
	std::copy(container.begin(), container.end(), std::ostream_iterator<double>(out, " "));
}


//��������������� ������� ��� ���������� ��������� ������� �������������� ����� � K-�� ����� � ����������
double halfsum_of_first_negative_and_k_element(std::deque<double>::const_iterator begin, std::deque<double>::const_iterator end, int k) {
	std::deque<double>::const_iterator it;
	//���� �� ���������� ���� �� ������ ������ ������������� �������
	for (it = begin; it != end && *it >= 0; it++);
	//���� �� ����� �� ����� ���������� � ��������� ������� � ��� �������������, �� ���������� ����������
	if (*it >= 0) {
		throw std::exception("� ���������� ����������� ������������� �����! ���������� �������������� ���� � ������� ����� ������!");
	}
	
	if ((end - begin) <= k) {
		throw std::exception("k ������, ��� ���������� ��������� � ����������!");
	}
	
	double halfsum = (*it + *(begin + k)) / 2.0;

	if (halfsum == 0) {
		throw std::exception("��������� ����� ����. ���������� ������� �� ��������� ����������");
	}
	return halfsum;
}
