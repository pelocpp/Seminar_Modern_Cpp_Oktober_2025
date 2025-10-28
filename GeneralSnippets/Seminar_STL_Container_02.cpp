#include <list>
#include <algorithm>
#include <deque>
#include <print>   // C++ 23
#include <vector>

void main_seminar_stl_fill()
{
    std::vector<int> numbers (1000, 1);

    // std::fill

    std::fill(
        numbers.begin(),
        numbers.end(),
        123
    );

    // bitte keine for-Schleife verwenden ....
}

void main_seminar_stl_generate()
{
    std::vector<int> numbers(10);

    // berechnete Werte
    // Beispiel: 1, 2, 3, 4

    int start = 0;

    std::generate(
        numbers.begin(),
        numbers.end(),
        
        // generator function  // berechnet für jeden Slot im Container einen Vorbelegungswert
        [=]() mutable {
            std::println("im Lambda");
            ++start;
            return start;
        }
    );

    std::println("Danach: {}", start);
}


void main_seminar_stl_generate_02()
{
    std::vector<int> numbers(10);

    // berechnete Werte
    // Beispiel: 1, 2, 3, 4

    std::generate(
        numbers.begin(),
        numbers.end(),
        [start = 0]() mutable {               // alles, was der Lambda benötigt
            std::println("im Lambda (2)");        // ist hier gepapselt ....
            ++start;
            return start;
        }
    );
}

// Suchen ...
void main_seminar_stl_find_03()
{
    std::vector<int> numbers(10);

    std::generate(
        numbers.begin(),
        numbers.end(),
        [start = 0]() mutable {              
            std::println("im Lambda (3)"); 
            ++start;
            return start;
        }
    );

    // den Wert 7
    auto pos = std::find(
        numbers.begin(),
        numbers.end(),
        77
    );

    if (pos != numbers.end()) {
        std::println("Found 7");
    }
    else {
        std::println("NOT Found!");
    }

    // Oder: specific criteria: Gibt es einen Wert im Container: ist gerade 

    pos = std::find_if(
        numbers.begin(),
        numbers.end(),
        [] (int elem) {     
        
            bool result = ((elem % 2) == 0);
            return result;
        }
    );

    if (pos != numbers.end()) {
        std::println("Found Even Element: {}", *pos);
    }
    else {
        std::println("NOT Found!");
    }
}


void main_seminar_stl_02()
{
    main_seminar_stl_find_03();
}
