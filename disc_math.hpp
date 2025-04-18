#ifndef MY_LIBRARY_HPP
#define MY_LIBRARY_HPP

#include <iostream>
#include <vector>
#include <sstream>
#include <string>
#include <algorithm>
#include <unordered_set>
#include <unordered_map>
#include <cctype>
#include <cmath>
#include <windows.h>

namespace disc_math
{
    auto trim = [](std::string s)
    {
        s.erase(0, s.find_first_not_of(" \t\n\r\f\v"));
        s.erase(s.find_last_not_of(" \t\n\r\f\v") + 1);
        return s;
    };

    template <typename T>
    std::pair<std::vector<T>, std::vector<T>> read_input_values()
    {
        std::vector<T> vec1, vec2;
        std::string line;

        auto parse_vector = [](const std::string &input)
        {
            std::vector<T> result;
            std::stringstream ss(input);
            std::string token;

            while (getline(ss, token, ','))
            {
                token.erase(0, token.find_first_not_of(" \t\n\r\f\v"));
                token.erase(token.find_last_not_of(" \t\n\r\f\v") + 1);

                if (!token.empty())
                {
                    std::stringstream converter(token);
                    T value;
                    if (converter >> value)
                    {
                        result.push_back(value);
                    }
                }
            }
            return result;
        };

        std::cout << "Enter first vector (values separated by ','): ";
        getline(std::cin, line);
        vec1 = parse_vector(line);

        std::cout << "Enter second vector (values separated by ','): ";
        getline(std::cin, line);
        vec2 = parse_vector(line);

        return std::make_pair(vec1, vec2);
    }

    template <typename T>
    std::vector<T> read_input_value()
    {
        std::vector<T> vec;
        std::string line;

        auto parse_vector = [](const std::string &input)
        {
            std::vector<T> result;
            std::stringstream ss(input);
            std::string token;

            while (getline(ss, token, ','))
            {
                token.erase(0, token.find_first_not_of(" \t\n\r\f\v"));
                token.erase(token.find_last_not_of(" \t\n\r\f\v") + 1);

                if (!token.empty())
                {
                    std::stringstream converter(token);
                    T value;
                    if (converter >> value)
                    {
                        result.push_back(value);
                    }
                }
            }
            return result;
        };

        std::cout << "Enter vector (values separated by ','): ";
        getline(std::cin, line);
        vec = parse_vector(line);
        return vec;
    }

    std::pair<std::vector<int>, std::vector<int>> check(int X)
    {
        std::string input;
        std::cout << "\nВведите числа через запятую или условие \n(Например '>=num' || '>num' || '<=num' || '<num'): ";
        std::getline(std::cin, input);

        std::vector<int> valid_numbers;
        std::vector<int> out_of_range_numbers;
        if (!input.empty() && (input[0] == '>' || input[0] == '<' || input[0] == '='))
        {
            input.erase(std::remove_if(input.begin(), input.end(), ::isspace), input.end());
            char op = input[0];
            bool has_equal = (input.size() > 1 && input[1] == '=');
            int value;

            try
            {
                size_t pos = has_equal ? 2 : 1;
                value = std::stoi(input.substr(pos));
            }
            catch (...)
            {
                std::cerr << "Неверный формат условия. Используйте '>5', '>=5', '<3', '<=3' или '=7'\n";
                return {valid_numbers, out_of_range_numbers};
            }
            for (int i = 1; i <= X; ++i)
            {
                bool match = false;
                if (op == '>')
                {
                    match = has_equal ? (i >= value) : (i > value);
                }
                else if (op == '<')
                {
                    match = has_equal ? (i <= value) : (i < value);
                }
                else if (op == '=')
                {
                    match = (i == value);
                }

                if (match)
                {
                    valid_numbers.push_back(i);
                }
            }
        }
        else
        {
            std::stringstream ss(input);
            std::string token;
            while (std::getline(ss, token, ','))
            {
                token.erase(0, token.find_first_not_of(" \t\n\r\f\v"));
                token.erase(token.find_last_not_of(" \t\n\r\f\v") + 1);

                if (!token.empty())
                {
                    try
                    {
                        int num = std::stoi(token);
                        if (num >= 1 && num <= X)
                        {
                            valid_numbers.push_back(num);
                        }
                        else
                        {
                            out_of_range_numbers.push_back(num);
                        }
                    }
                    catch (...)
                    {
                        std::cerr << "Неверный формат числа: '" << token << "'\n";
                    }
                }
            }
            std::sort(valid_numbers.begin(), valid_numbers.end());
            valid_numbers.erase(std::unique(valid_numbers.begin(), valid_numbers.end()), valid_numbers.end());

            std::sort(out_of_range_numbers.begin(), out_of_range_numbers.end());
            out_of_range_numbers.erase(std::unique(out_of_range_numbers.begin(), out_of_range_numbers.end()), out_of_range_numbers.end());
        }

        return {valid_numbers, out_of_range_numbers};
    }
    void check_convertible(const std::vector<std::string> &vec1,
                           const std::vector<std::string> &vec2)
    {
        auto is_convertible = [](const std::vector<std::string> &vec)
        {
            for (const auto &elem : vec)
            {
                std::stringstream ss(elem);
                double value;
                if (!(ss >> value) || !ss.eof())
                {
                    return false;
                }
            }
            return true;
        };

        if (!is_convertible(vec1) || !is_convertible(vec2))
        {
            std::cerr << "Warning: Some elements could not be converted to numbers\n";
        }
    }

    std::vector<std::string> find_unique(
        const std::vector<std::string> &vec1,
        const std::vector<std::string> &vec2)
    {

        std::unordered_map<std::string, int> element_counts;
        for (const auto &elem : vec1)
        {
            std::string trimmed = trim(elem);
            element_counts[trimmed]++;
        }
        for (const auto &elem : vec2)
        {
            std::string trimmed = trim(elem);
            element_counts[trimmed]++;
        }

        std::vector<std::string> result;
        for (const auto &[elem, count] : element_counts)
        {
            if (count == 1)
            {
                bool in_vec1 = std::find_if(vec1.begin(), vec1.end(),
                                            [&](const std::string &e)
                                            { return trim(e) == elem; }) != vec1.end();

                if ((in_vec1 && !vec2.empty()) || (!in_vec1 && !vec1.empty()))
                {
                    result.push_back(elem);
                }
            }
        }

        return result;
    }

    std::vector<std::string> find_unification(const std::vector<std::string> &vec1,
                                              const std::vector<std::string> &vec2)
    {

        std::unordered_set<std::string> unique_elements;
        std::vector<std::string> result;

        for (const auto &elem : vec1)
        {
            std::string trimmed = trim(elem);
            if (!unique_elements.count(trimmed))
            {
                result.push_back(trimmed);
                unique_elements.insert(trimmed);
            }
        }
        for (const auto &elem : vec2)
        {
            std::string trimmed = trim(elem);
            if (!unique_elements.count(trimmed))
            {
                result.push_back(trimmed);
                unique_elements.insert(trimmed);
            }
        }

        return result;
    }

    std::vector<std::string> find_intersection(
        const std::vector<std::string> &vec1,
        const std::vector<std::string> &vec2)
    {

        std::unordered_set<std::string> set2;
        for (const auto &elem : vec2)
        {
            set2.insert(trim(elem));
        }

        std::vector<std::string> result;
        std::unordered_set<std::string> added_elements;

        for (const auto &elem : vec1)
        {
            std::string trimmed = trim(elem);
            if (set2.count(trimmed) && !added_elements.count(trimmed))
            {
                result.push_back(trimmed);
                added_elements.insert(trimmed);
            }
        }

        return result;
    }

    std::string vector_to_string(const std::vector<std::string> &vec,
                                 const std::string &name = "")
    {
        std::ostringstream oss;
        if (vec.empty())
        {
            oss << "set is NULL";
            return oss.str();
        }
        if (!name.empty())
        {
            oss << name;
        }
        oss << "[";
        for (size_t i = 0; i < vec.size(); ++i)
        {
            if (i != 0)
                oss << ", ";
            oss << vec[i];
        }
        oss << "]";
        return oss.str();
    }

    int first_exercise()
    {
        auto [vec1, vec2] = read_input_values<std::string>();
        check_convertible(vec1, vec2);

        std::cout << "\nVector A IS --->";
        for (const auto &elem : vec1)
            std::cout << "[" << elem << "]";
        std::cout << "\nVector B IS --->";
        for (const auto &elem : vec2)
            std::cout << "[" << elem << "]";
        std::cout << "\n";

        std::cout << "*****************************************************************************************************" << std::endl
                  << "Find A ∩ B ..." << std::endl
                  << "По формуле: " << " {x ∣ x ∈ A && (и) x ∈ B}" << std::endl
                  << "Расшифровка на человеческий ---> X принадлежит множеству А И ТАК ЖЕ X принадлежит множеству В " << std::endl
                  << "ПОЯСНЕНИЕ: Только те значения из каждого множества, которые находятся в обоих множествах" << std::endl
                  << std::endl;
        std::cout << "*****************************************************************************************************" << std::endl
                  << "Результат A ∩ B ..." << std::endl;
        auto intersection = find_intersection(vec1, vec2);
        std::cout << "\nResult:\n"
                  << vector_to_string(intersection, "A ∩ B: ")
                  << std::endl;

        std::cout << "*****************************************************************************************************" << std::endl
                  << "Find A ∪ B ..." << std::endl
                  << "По формуле: " << " {x ∣ x ∈ A || (или) x ∈ B}" << std::endl
                  << "Расшифровка на человеческий ---> X принадлежит множеству А ИЛИ X принадлежит множеству В " << std::endl
                  << "ПОЯСНЕНИЕ: Все значения, которые содержатся в обоих множествах" << std::endl
                  << std::endl;

        std::cout << "*****************************************************************************************************" << std::endl
                  << "Результат A ∪ B ..." << std::endl;

        auto unification = find_unification(vec1, vec2);
        std::cout << "\nResult:\n"
                  << vector_to_string(unification, "A ∪ B: ")
                  << std::endl
                  << std::endl;

        std::cout << "*****************************************************************************************************" << std::endl
                  << "Find A / B ..." << std::endl
                  << "По формуле: " << " {x ∣ x ∈ A и x ∉ B}" << std::endl
                  << "Расшифровка на человеческий ---> X принадлежит множеству А И ПРИ ЭТОМ X НЕ принадлежит множеству В " << std::endl
                  << "ПОЯСНЕНИЕ: Все значения, которые содержатся только в одном из множеств" << std::endl
                  << std::endl;

        std::cout << "*****************************************************************************************************" << std::endl
                  << "Результат A / B ..." << std::endl;

        auto unique = find_unique(vec1, vec2);
        std::cout << "\nResult:\n"
                  << vector_to_string(unique, "A / B: ")
                  << std::endl
                  << std::endl;
        std::cout << "*****************************************************************************************************" << std::endl;
        std::cout << "FINAL RESULT IS:" << std::endl
                  << "Inserted data is:" << std::endl;
        std::cout << "\nVector A IS --->";
        for (const auto &elem : vec1)
            std::cout << "[" << elem << "]";
        std::cout << "\nVector B IS --->";
        for (const auto &elem : vec2)
            std::cout << "[" << elem << "]";
        std::cout << "\nРезультат A ∩ B ---> " << vector_to_string(intersection, "") << std::endl;
        std::cout << "Результат A ∪ B ---> " << vector_to_string(unification, "") << std::endl;
        std::cout << "Результат A / B ---> " << vector_to_string(unique, "") << std::endl;
        return 0;
    }

    int second_exercise()
    {
        std::vector<int> universal;
        auto const universal_diapasone = read_input_value<int>();
        if (universal_diapasone.size() > 2)
        {
            std::cout << "Введено слишком много чисел";
            return 0;
        }
        std::cout << "\nVector universal diapasone IS --->";
        for (const auto &elem : universal_diapasone)
            std::cout << "[" << elem << "]";
        int i = universal_diapasone[0];
        while (universal_diapasone[1] >= i)
        {
            universal.push_back(i);
            i++;
        }
        std::cout << "\nVector universal numbers IS --->";
        for (const auto &elem : universal)
            std::cout << "[" << elem << "]";

        auto [valid_nums, invalid_nums] = check(universal_diapasone[1]);

        if (!valid_nums.empty())
        {
            std::cout << "Валидные числа: ";
            for (int num : valid_nums)
            {
                std::cout << num << " ";
            }
            std::cout << "\n";
        }
        else
        {
            std::cout << "Нет валидных чисел\n";
            return 0;
        }

        if (!invalid_nums.empty())
        {
            std::cout << "Числа вне диапазона: ";
            for (int num : invalid_nums)
            {
                std::cout << num << " ";
            }
            std::cout << "\n";
        }
        return 0;
    }

    long long combinations(int n, int k)
    {
        if (k < 0 || k > n)
            return 0;
        if (k == 0 || k == n)
            return 1;

        k = std::min(k, n - k); // Оптимизация: используем свойство симметрии C(n,k) = C(n,n-k)
        long long res = 1;

        for (int i = 1; i <= k; ++i)
        {
            res *= (n - k + i);
            res /= i;
        }

        return res;
    }

    long long calculate_expulsion_options(int group1, int group2, int k)
    {
        long long total = 0;

        // Перебираем все возможные распределения (i из group1, k-i из group2)
        for (int i = 0; i <= k; ++i)
        {
            if (i <= group1 && (k - i) <= group2)
            {
                total += combinations(group1, i) * combinations(group2, k - i);
            }
        }

        return total;
    }

    int first_combinator_exercise()
    {
        int group1 = 0;
        int group2 = 0;
        int k = 0;

        std::cout << "Введите количество студентов в 1 группе: ";
        std::cin >> group1;
        std::cout << "\nВведите количество студентов во 2 группе: ";
        std::cin >> group2;
        std::cout << "\nВведите количество студентов для отчисления: ";
        std::cin >> k;

        long long options = calculate_expulsion_options(group1, group2, k);

        std::cout << "Количество комбинация для отчисления " << k
                  << " студентов: " << options << std::endl;
        if (0 > k || 0 > group1 || 0 > group2)
        {
            std::cout << "Ошибка: количество студентов не может быть отрицательным!\n";
            return 1;
        }
        return 0;
    }

    int second_combinator_exercise()
    {
        int num_of_passengers = 0;
        int num_of_floors = 0;
        std::cout << "\nЗадача:" << std::endl;
        std::cout << "В лифт A-этажного дома вошли N пассажиров. Сколькими способами могут выйти пассажиры на каждом этаже, начиная со второго ? \n";
        std::cout << "Введите количество этажей (A)" << std::endl;
        std::cin >> num_of_floors;
        std::cout << "\nВведите количество пассажиров в лифте (N) " << std::endl;
        std::cin >> num_of_passengers;
        long long total_ways = std::pow((num_of_floors - 1), num_of_passengers);
        std::cout << "\nЭлементарно решается, возведя количество этажей (" << num_of_floors << "-1, т.к первый этаж мы не учитываем), в степень '" << num_of_passengers << "', равную общему количеству пассажиров" << std::endl;
        std::cout << "\nИтого, количество способов для выхода " << num_of_passengers << " пассажира(ов) с " << num_of_floors << " этажа(ей) ---> " << total_ways << std::endl;
        return 0;
    }

    long long factorial(int n)
    {
        long long result = 1;
        for (int i = 2; i <= n; ++i)
        {
            result *= i;
        }
        return result;
    }

    long long combs(int n, int k)
    {
        return factorial(n) / (factorial(k) * factorial(n - k));
    }

    int third_combinator_exercise()
    {
        int num_of_candidates = 0;
        int num_of_positions = 0;
        std::cout << "\nЗадача:" << std::endl;
        std::cout << "Сколькими способами можно назначить A человек на A различные должности, если всего есть N кандидатов на эти должности?\n";
        std::cout << "Введите количество должностей (A)" << std::endl;
        std::cin >> num_of_positions;
        std::cout << "\nВведите количество кандидатов (N) " << std::endl;
        std::cin >> num_of_candidates;
        std::cout << "Задачка решается через сочетание С(" << num_of_candidates << "," << num_of_positions << ") и перестановку выбранных кандидатов" << std::endl;
        long long ways = combs(num_of_candidates, num_of_positions) * factorial(num_of_positions);

        std::cout << "Количество способов назначить " << num_of_positions
                  << " человек на " << num_of_positions << " должностей из "
                  << num_of_candidates << " кандидатов: " << ways << std::endl;
        return 0;
    }
}

#endif // MY_LIBRARY_HPP