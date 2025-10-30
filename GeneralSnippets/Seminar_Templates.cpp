#include <vector>
#include <list>
#include <print>
#include <algorithm>

template <typename T>
struct Point
{
    T m_x;
    T m_y;
};

using IntPoint = Point<int>;

class Rectangle
{
    Point<double> m_leftUpper;
    Point<double> m_rightLower;
};

void main_seminar_templates_erste_anwendung()
{
    IntPoint p3{};

    Point<int> p{ 1, 2 };

    // Class Template Argument Deduction
    Point p2{ 1.5, 2.5 };
}

// test anwendung // unit test // zweite , semigrafische Oberfläche
void main_seminar_templates_zweite_anwendung()
{
    Point<double> p{ 1.0, 2.5 };
}

//void PrintContainer(const std::vector<int>& data)
//{
//    for (auto elem : data) {
//        std::println("Wert: {}", elem);
//    }
//}

template <typename T>
void PrintContainer(const T& data)
{
    for (auto elem : data) {
        std::println("Wert: {}", elem);
    }
}

template <typename T>
void PrintContainer2(const T& data)
{
    // wie komme ich an den Typ der Elemente des Containers T

    // 1. Variante
    using ElemType = T::value_type;
    ElemType n{};

    // 2. Variante
    using ElemType2 = decltype (*data.begin());
    ElemType n2{};

    std::for_each(
        data.begin(),
        data.end(),
        [](auto elem) {
            std::println("Wert: {}", elem);
        }
    );
}

void main_seminar_templates()
{
    std::list<int> myData{ 1, 2, 3, 4, 5 };
    PrintContainer(myData);

    std::vector<int> myData2{ 11, 12, 13, 14, 15 };
    PrintContainer2(myData2);
}

