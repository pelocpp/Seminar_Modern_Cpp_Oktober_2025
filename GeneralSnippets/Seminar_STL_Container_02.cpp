#include <list>
#include <algorithm>
#include <deque>
#include <print>   // C++ 23
#include <vector>
#include <forward_list>
#include <unordered_map>
#include <map>

static auto main_seminar_stl_fill_mit_for_each()
{
    std::println("std::vector: using std::for_each");

    std::vector<double> values(10, 1.0);

    std::for_each(
        values.begin(),
        values.end(),
        [](double& elem) {   // modifying elements of container
            elem = elem + 123.0;    // Note: Using &
        }
    );

    std::generate(
        values.begin(),
        values.end(),
        [] () { return 456.0; }
    );

    // std::for_each kann auch die Elemente eines Containers ändern !!!
    // durch Verwendung einer Referenz

    std::for_each(
        values.begin(),
        values.end(),
        [](double elem) {
            std::println("Wert: {}", elem);
        }
    );
}


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


void main_seminar_stl_find_04()
{
    // Von std::vector zu std::list // #include
    // std::list<int> numbers(10);   // 10   0-
    std::forward_list<int> numbers(10);   // 10   0-Werte

    // Vorbelegung mit 1, 2, 3, 4, 5 .....
    std::generate(
        numbers.begin(),
        numbers.end(),
        [start = 0]() mutable {
            std::println("im Lambda bzgl. list");
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
    // 
    pos = std::find_if(
        numbers.begin(),
        numbers.end(),
        [](int elem) {

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

void main_seminar_stl_find_05()
{
    // Telefonbuch: Schlüssel: std::string // Wert: long
    std::unordered_map<std::string, long> phonebook;

    // Schlüssel/Wert-Paare in das Telefonbuch einfügen
    // Mehrere Möglichkeiten

    std::pair<std::string, long> entry1{ "Meier", 234234 };

    // ----------------------------------------------------------------
    // Objekt erzeugen / Aufbauen
    
    std::pair < std::unordered_map<std::string, long>::iterator, bool> result1 
        = phonebook.insert(entry1);

    bool success = result1.second;
    if (success) {
        std::println("Hat geklappt");
    }

    std::pair<std::string, long> entry2{ "Mueller", 56756756 };
    phonebook.insert(entry2);

    std::pair<std::string, long> entry3{ "Meier", 8667868 };
    auto result3 = phonebook.insert(entry3);

    // hat nicht geklappt
    success = result3.second;
    if (! success) {
        std::println("Hat NICHT geklappt");
    }

    // ----------------------------------------------------------------
    // Element suchen 
    // 
    // std::unordered_map<std::string, long>::iterator pos = phonebook.find("Mueller");
    auto pos = phonebook.find("Mueller");

    // find bedeutet "suchen"  // aber hier ist das jetzt effizient !!!

    if (pos != phonebook.end()) {

        // auto entry = *pos;  // VORSICHT: Kopie,die ich nicht brauche
        const auto& entry = *pos;   // Referenz, die in den Container zeigt

        // Wenn ihr ohne auto arbeiten wolltet // Verständnis
        // const std::pair<std::string, long>& entry = *pos;

        // std::string name = entry.first;     // Zur Kontrolle // Ginge // Vorsicht: Kopie
        const std::string& name = entry.first; // Zur Kontrolle // Besser // keine Kopie
        long number = entry.second;            // Die gesuchte Tel.Nummer

        std::println("Kollege {} hat Tel.Nr. {}", name, number);
    }

    // ----------------------------------------------------------------
    // Container Traversieren ... // Durchlaufen

    // std::pair<std::string, long> 

    std::for_each(
        phonebook.begin(),
        phonebook.end(),
        [] (const std::pair<std::string, long>& entry) {
        
            const std::string& name = entry.first;
            long number = entry.second;
            std::println("Kollege {} hat Tel.Nr. {}", name, number);
        }

        //[](const auto& entry) {

        //    const std::string& name = entry.first;
        //    long number = entry.second;
        //    std::println("Kollege {} hat Tel.Nr. {}", name, number);
        //}
    );

}


template <typename KeyType>
using InsertResultEx
  = std::pair <typename std::unordered_map<KeyType, std::string>::iterator, bool>;


void main_seminar_stl_find_06()
{
    // Wörterbuch: "Deutsch" => "Italienisch"
    std::unordered_map<std::string, std::string> dictionary;

    std::pair<std::string, std::string> entry1{ "Haus", "casa"};
    std::pair<std::string, std::string> entry2{ "Tuere", "porta" };
    std::pair<std::string, std::string> entry3{ "Mann", "uomo" };
    std::pair<std::string, std::string> entry4{ "Frau", "donna" };
    std::pair<std::string, std::string> entry5{ "Kind", "bambino" };
    std::pair<std::string, std::string> entry6{ "Frau", "signora" };

    std::vector<std::pair<std::string, std::string>> entries
    {
        entry1,
        entry2,
        entry3,
        entry4,
        entry5,
        entry6
    };

    // ----------------------------------------------------------------
    // Wörterbuch mit Übersetzungen füllen

    std::for_each(
        entries.begin(),
        entries.end(),
        [&] (const auto& entry) {

            using InsertResult
                = std::pair <std::unordered_map<std::string, std::string>::iterator, bool>;
        
            InsertResult result = dictionary.insert(entry);

            InsertResultEx<std::string> result2 = dictionary.insert(entry);



            //std::pair <std::unordered_map<std::string, std::string>::iterator, bool> result
            //    = dictionary.insert(entry);

            // oder
            auto result3 = dictionary.insert(entry);

            bool success = result.second;

            if (success) {
                std::println("Inserting {} succeeded", entry.first);
            }
            else {
                std::println("Inserting {} FAILED!", entry.first);
            }
        }
    );

    std::println();

    // ----------------------------------------------------------------
    // Übersetzung in einem Wörterbuch suchen 
    // 
    std::unordered_map<std::string, std::string>::iterator pos1 
        = dictionary.find("Tuere");
    // oder
    auto pos = dictionary.find("Tuere");

    if (pos != dictionary.end()) {

        const auto& entry = *pos;  
        // oder
        const std::pair<std::string, std::string>& entry2 = *pos;

        const std::string& word = entry.first;
        const std::string& translation = entry.second; 

        std::println("{:10} => {:10}", word, translation);
    }

    std::println();

    // ----------------------------------------------------------------
    // Inhalt des Wörterbuchs in der Konsole ausgeben

    std::println("Contents of Dictionary:");

    std::for_each(

        dictionary.begin(),
        dictionary.end(),

        [](const std::pair<std::string, std::string>& entry) {

            const std::string& word = entry.first;
            const std::string& translation = entry.second;

            std::println("{:10} => {:10}", word, translation);
        }
    );
}

void main_seminar_stl_02()
{
    main_seminar_stl_fill_mit_for_each();
}
