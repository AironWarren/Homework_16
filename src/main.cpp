#include <string>
#include <iostream>
#include <vector>
#include <iterator>
#include <ctime>
#include <numeric>
#include <limits>
#include <algorithm>
//
// #include "game.h"

namespace Data
{
    struct GameData
    {
        double maxValue = 0.0;
        std::vector<double> valueCords;
    };
}// namespace Data

namespace utils {

    enum class Elems : int16_t
    {
        First = 1,
        Second = 2
    };

    constexpr double COMPARE_VALUE = 20.0;

    void calculateV1(std::vector<double>& data)
    {
        for (auto& elem : data)
        {
            elem = std::pow(elem, 2);
        }
    }
    void powElem(double& elemData)
    {
        elemData = std::pow(elemData, 2);
    }
    void calculateV2(std::vector<double>& data)
    {
        std::for_each(data.begin(), data.end(), powElem);
    }

    double powElemDouble(double elemData)
    {
        return std::pow(elemData, 2);
    }

    void calculateV3(std::vector<double>& data)
    {
        std::transform(data.begin(), data.end(), data.begin(), powElemDouble);
    }


    void show(const std::vector<double>& data)
    {
        for (const auto& elem : data)
        {
            std::cout << elem << " ";
        }
        std::cout << std::endl;
    }

    bool isLess(double elem1) {
        return  std::less<double>{}(elem1, COMPARE_VALUE);
    }


    bool isMore(double elem1, double elem2)
    {
        return  std::greater<double>{}(elem1, elem2);
    }
    // bool existsInContainer(const std::vector<double>& container)
    // {
    //     bool result = std::none_of(std::cbegin(container), std::cend(container),isMore);
    //     return result;
    // }

    bool existsInContainer(const std::vector<double>& container, double elem)
    {
        const auto& labdaMore = [elem](double value1) -> bool
            {
                return  std::greater<double>{}(value1, elem);
            };
        bool result = std::any_of(std::cbegin(container), std::cend(container), labdaMore);
        return result;
    }

}


int main()
{
    setlocale(LC_ALL, "ru");

    std::vector<double> coords1 = { 2.12, 3.0, 4.0, 5.0, 6.0, 7.0, 8.0, 9.0 };
    std::vector<double> coords2 = { 20.2, 30.0, 40.0, 50.0, 60.0, 70.0, 80.0, 90.0 };
    std::vector<double> coords3 = { 200.2, 300.0, 400.0, 500.0, 600.0, 700.0, 800.0, 900.0 };

    std::vector<Data::GameData> surfaces;
    surfaces.reserve(static_cast<size_t>(3));

    const auto maxValueFromVec = [](const std::vector<double>& vec)-> double {
        const auto pIter = std::max_element(std::cbegin(vec), std::cend(vec));

        if (std::end(vec) == pIter)
        {
            std::numeric_limits<double>::quiet_NaN();
        }

        return *pIter;
        };

    surfaces.push_back(Data::GameData{ maxValueFromVec(coords1), coords1 });
    surfaces.push_back(Data::GameData{ maxValueFromVec(coords2), coords2 });
    surfaces.push_back(Data::GameData{ maxValueFromVec(coords3), coords3 });

    // Доделал задача про данные отсортированные в обратном порядке

    for (Data::GameData data : surfaces) {
        std::sort(std::begin(data.valueCords), std::end(data.valueCords), [](double a, double b) {
            return a > b;
            });

        utils::show(data.valueCords);
        std::cout << std::endl;
    }

    //16.1
    int val1 = 0, val2 = 0;
    
    auto read =
        [](int& val1, int& val2) {
        std::cout << "Введите значение первого числа: ";
        std::cin >> val1;
        std::cout << std::endl;
        std::cout << "Введите значение второго числа: ";
        std::cin >> val2;
        std::cout << std::endl;
        };

    auto pr =
        [](int val1, int val2) {
        return val1 + val2;
        };

    read(val1, val2);

    std::cout << pr(val1, val2);
    std::cout << "\n";
    
    //16.2
    auto pr1 =
        [val1, val2]() {
        return val1 * val2;
        };
    std::cout << pr1();
    std::cout << "\n";
    
    //16.3
    int choise;

    auto sum =
        [](auto a, auto b) {
        return a + b;
        };

    std::cout << "С какими типами вы хотите работать?"
        << "\n1 - INT"
        << "\n2 - DOUBLE"
        << "\n3 - CHAR"
        << "\n4 - BOOL\n";

    std::cin >> choise;
    switch (choise) {
    case 1:
        std::cout << "Сумма двух целых чисел: " << sum(1, 5);
        break;
    case 2:
        std::cout << "Сумма двух целых чисел: " << sum(1.3, 5.56);
        break;
    case 3:
        std::cout << "Сумма двух целых чисел: " << static_cast<char>(sum('9', '5'));
        break;
    case 4:
        std::cout << "Сумма двух целых чисел: " << sum(false, true);
        break;
    default:
        std::cout << "Wrong number\n";
        break;
    }



    return 0;
}