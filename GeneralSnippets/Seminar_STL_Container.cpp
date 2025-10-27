#include <iostream>
#include <vector>
#include <list>
#include <algorithm>
#include <deque>
#include <print>   // C++ 23

static void main_seminar_stl_01()
{
    // Vector: flexibel langes Array

    // std::vector<int> numbers;
    std::vector<int> numbers;
    numbers.reserve(80);

    for (int i = 0; i != 100; ++i) {

        numbers.push_back(2 * i);

        std::println("{}: {} - Size: {} - Capacity: {}", 
            i, numbers[i], numbers.size(), numbers.capacity());
    }

    numbers.shrink_to_fit();

    std::println("Size: {} - Capacity: {}",
        numbers.size(), numbers.capacity());
}

static void main_seminar_stl_02()
{
    std::vector<int> numbers;

    // füllen
    for (int i = 0; i != 10; ++i) {
        numbers.push_back(2 * i);
    }

    // ausgeben
    for (int i = 0; i != numbers.size(); ++i) {

        std::println("{}: {}", i, numbers[i]);  // Schwachpunkt
    }
}


static void main_seminar_stl_03()
{
    std::vector<int> numbers;

    // füllen
    for (int i = 0; i != 3; ++i) {
        numbers.push_back(2 * i);
    }

    // Konzept von Iteratoren
    std::vector<int>::iterator  pos = numbers.begin();

    // pos ist nun die Position des ersten Elements
    int elem = *pos;

    // gehe zur nächsten Position
    ++pos;

    elem = *pos;

    // gehe zur nächsten Position
    ++pos;

    elem = *pos;

    // gibt es noch eine weitere Position ???
    ++pos;

    elem = *pos;
}

static void main_seminar_stl_04()
{
    std::vector<int> numbers;

    // füllen
    for (int i = 0; i != 3; ++i) {
        numbers.push_back(2 * i);
    }

    // Konzept von Iteratoren
    std::vector<int>::iterator  pos = numbers.begin();

    while ( pos != numbers.end() ) {

        int elem = *pos;
        std::println("{}", elem);

        ++pos;
    }
}

static void main_seminar_stl_05()
{
   // std::vector<int> numbers;
    // std::list<int> numbers;
    std::deque<int> numbers;

    // füllen
    for (int i = 0; i != 3; ++i) {
        numbers.push_back(2 * i);
    }

    // Konzept von Iteratoren
   // std::vector<int>::iterator  pos = numbers.begin();
   // std::list<int>::iterator  pos = numbers.begin();
    std::deque<int>::iterator  pos = numbers.begin();

    while (pos != numbers.end()) {

        int elem = *pos;
        std::println("{}", elem);

        ++pos;

        // break
    }
}

static void output(int elem)
{
    int m = elem;

    std::println("{}", elem);
}

static void main_seminar_stl_06()
{
    std::vector<int> numbers;

    // füllen
    for (int i = 0; i != 3; ++i) {
        numbers.push_back(2 * i);
    }

    // Konzept von Algorithmen:
    // Beispiel: Durchlaufen (Traversieren) eines Containers
    std::for_each (
        numbers.begin(),
        numbers.end(),
        output
    );
}


void main_seminar_stl()
{
    main_seminar_stl_06();
}
