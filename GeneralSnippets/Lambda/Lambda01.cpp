// =====================================================================================
// Lambda01.cpp // Lambda Methods
// =====================================================================================

module modern_cpp:lambda;

namespace Lambdas {

    // freie Funktion
    static bool compare (int n1, int n2) { 

        std::cout << "vgl. " << n1 << " mit " << n2 << std::endl;

        return n1 < n2;
    }

    class Comparer
    {
    private:
        bool m_flag;   // um aufsteigend oder absteigend sortieren zu können

    public:
        Comparer() : m_flag{ true } {}
        Comparer(bool flag) : m_flag{ flag } {}

        bool operator() (int n1, int n2) const {

            std::cout << "operator(): vgl. " << n1 << " mit " << n2 << std::endl;

            return (m_flag) ? n1 < n2 : n1 > n2;
        }
    };

    // =====================================================================================

    static void test_00()
    {
        Comparer obj{ false };

        bool result{ obj(1, 2) };

        std::cout << std::boolalpha << result << std::endl;
    }

    // =====================================================================================

    static void test_01()
    {
        std::vector<int> vec{ 5, 6, 4, 1, 3, 2, 7, 8 };

        for (int n : vec) {
            std::cout << n << ' ';
        }
        std::cout << std::endl;

        std::sort(
            vec.begin(),  // Position Anfang
            vec.end(),    // Position Ende
            compare     // freie Funktion
        );

        for (int n : vec) {
            std::cout << n << ' ';
        }
    }

    // =====================================================================================

    static void test_02()
    {
        std::vector<int> vec{ 5, 6, 4, 1, 3, 2, 7, 8 };

        for (int n : vec) {
            std::cout << n << ' ';
        }
        std::cout << std::endl;

        Comparer myComparer;

        std::sort(
            vec.begin(),
            vec.end(),
            myComparer 
        );

        for (int n : vec) {
            std::cout << n << ' ';
        }
    }

    // =====================================================================================

    static void test_03()
    {
        // local class within function possible
        class LocalComparer
        {
        private:
            bool m_flag;

        public:
            LocalComparer() : m_flag{ true } {}
            LocalComparer(bool flag) : m_flag{ flag } {}

            bool operator() (int n1, int n2) const {

                std::cout << "LocalComparer: operator(): vgl. " << n1 << " mit " << n2 << std::endl;

                return (m_flag) ? n1 < n2 : n1 > n2;
            }
        };

        std::vector<int> vec{ 5, 6, 4, 1, 3, 2, 7, 8 };

        for (int n : vec) {
            std::cout << n << ' ';
        }
        std::cout << std::endl;

        LocalComparer localCmp (false);

        //std::sort(
        //    vec.begin(),
        //    vec.end(),
        //    localCmp             // ist ein Lambda :)
        //);

        bool flag = true;   // Lokale Variable

        // man kann einem anonymen Lambda-Funktion/Lambda-Objekt
        // einen Namen geben

        auto myLambda = [&](int n1, int n2) -> bool {

            std::cout << "Lambda: vgl. " << n1 << " mit " << n2 << std::endl;
            return (flag) ? n1 < n2 : n1 > n2;
            //return n1 < n2;
        };

        // Ziel eines Lambdas: Kompaktere Schreibweise
        // In Lamdbas kann auf lokale Variablen "der Umgebung" zugegriffen werden !!!
        // In JavaScript nennt man dies den "Closure" einer lokalen Funktion
        
        std::sort(
            vec.begin(),
            vec.end(),
            // Mit Lambdas ist inlining möglich 
            [&] (int n1, int n2) {
        
                // 10 oder Mehrzeiler mutieren ......
                // ist das ein kleiner Lambda
                // Lesbarkeit !!!
                std::cout << "Lambda: vgl. " << n1 << " mit " << n2 << std::endl;
                return (flag) ? n1 < n2 : n1 > n2;
                //return n1 < n2;
            }        
        );

        for (int n : vec) {
            std::cout << n << ' ';
        }
    }

    // =====================================================================================

    static void test_04() {

        std::vector<int> vec{ 50, 90, 10, 30, 70, 80 };

        for (int n : vec) {
            std::cout << n << ' ';
        }
        std::cout << std::endl;

        std::sort(
            vec.begin(),
            vec.end(),
            [] (int n1, int n2) { return n1 < n2; }
        );

        for (int n : vec) {
            std::cout << n << ' ';
        }
    }

    // =====================================================================================

    static void test_05() {

        // shortest lambda on earth: no parameters, capturing and doing nothing
        auto nothing{ [] {} };
        nothing();

        // c'tor notation
        auto itsOne{ [] { return 1; } };
        auto itsTwo{ [] { return 2; } };
        std::cout << itsOne() << ", " << itsTwo() << std::endl;
    }

    static void test_06() {

        // defining a lambda without 'auto'
        std::function<int(int, int, int)> lambdaWithThreeParams {
            [] (int x, int y, int z) {
                return x + y + z;
            }
        };

        std::cout << lambdaWithThreeParams(5, 6, 7) << std::endl;
    }

    static void test_07() {

        //  auto variable = 0;

        // lambda with instance variable definition
        auto lambda = [variable = 0] ()  mutable -> int {
        
           // int variable = 0;

            variable++;
            
            return variable; 
        };

        //  variable = 123;

        std::cout << lambda() << std::endl;
        std::cout << lambda() << std::endl;
        std::cout << lambda() << std::endl;
    }

    static void test_08() {

        int n = 1;  // Closure
        int m = 2;  // lokale Variablen

        auto l1 = [=] {
            std::cout << "Copy:      " << n << " " << m << std::endl;
        };

        auto l2 = [&] {
            std::cout << "Reference: " << n << " " << m << std::endl;
        };

        auto l3 = [&, m] {
            std::cout << "Both:      " << n << " " << m << std::endl;
        };

        auto l4 = [=, &m] {
            std::cout << "More both: " << n << " " << m << std::endl;
        };

        n = 3;
        m = 4;

        l1();  // operator()
        l2();
        l3();
        l4();
    }

    static auto test_09_helper_a() {

        int n = 1;
        int m = 2;

        auto lambda = [=] {
            std::cout << "Copy:      " << n << " " << m << std::endl;
        };

        return lambda;
    }

    static auto test_09_helper_b() {

        int n = 1;    // Closure ==> Heap:  Verkettete Liste von Blöcken von Variablen
        int m = 2;

        auto lambda = [&] {
            std::cout << "Reference: " << n << " " << m << std::endl;
        };

        return lambda;                                                                             // I would't do this never ever :-)
    }

    static void test_09() {

        auto outerLambda1 = test_09_helper_a();

        auto outerLambda2 = test_09_helper_b();

        outerLambda1();

        outerLambda2();
    }

    static void test_10() {

        // demonstrating 'noexcept'
        auto itsOne([] () noexcept { return 1; });
        auto itsTwo = [] () noexcept { return 2; };
        std::cout << itsOne() << ", " << itsTwo() << std::endl;
    }

    static void test_11() {

        // IIFE - Immediately Invoked Functional Expression:
        // Inline-definition and direct invocation of lambda funtion:
        
        std::cout << [](int l, int r) { return l + r; } (11, 12) << std::endl;

        // Use case for IIFE:
        // This kind of expression might be useful when you have
        // a complex initialization of a const  object:

        auto constexpr ConstValue = [] () {
            /* several lines of code ... - "very complex" computation */
            return 123;
        } ();

        std::cout << "Const Value: " << ConstValue << std::endl;
    }

    // Another IIFE Examples:
    // Lambda are defined 'constexpr' - some concrete values are computed
    auto constexpr times = [] (int n, int m) {

        auto result = m;
        for (size_t i{ 1 }; i != n; ++i) {
            result *= m;
        }
        return result;
    };

    template <typename T>
    auto constexpr power = [](T base, T exp) {

        auto result = base;
        for (size_t i{ 1 }; i != exp; ++i) {
            result *= base;
        }
        return result;
    };

    static void test_12() {

        // IIFE - Immediately Invoked Functional Expression:
        // some real-world examples

        constexpr auto twoTimesTen = times(2, 10);
        constexpr auto fiveTimesTen = times(5, 10);

        constexpr auto twoToThePowerOfTen = power<int>(2, 10);
        constexpr auto threeToThePowerOfThree = power<double>(3.0, 3.0);
    }

    static void test_13() {

        // Feature: Generalized Lambda Capture

        class SampleClass
        {
        public:
            void doSomething() { std::println("Doing Something"); };
        };

        std::unique_ptr<SampleClass> ptr { 
            std::make_unique<SampleClass>() 
        };

        // Does not compile: by-value capture with move-only type (!)
        // auto lambda = [=] () { ptr->doSomething(); };

        // Compiles: by-reference capture with move-only type (!)
        auto lambda = [&] () { ptr->doSomething(); };

        // How about by-move capture?
        // Instead of adding it, C++14 introduced the "Generalized Lambda Capture",
        // also known as "Init Capture":

        auto lambda2 = [ptrSampleClass = std::move(ptr)] () {
            ptrSampleClass->doSomething();
        };

        lambda2();

        // Note:
        // We are allowed to keep the name of the variable 'ptr' the same inside the lambda:

        ptr = std::make_unique<SampleClass>();

        auto lambda3 = [ptr = std::move(ptr)]() {
            ptr->doSomething();
        };

        lambda3();
    }
}

void main_lambdas()
{
    using namespace Lambdas;
    //test_00();
    //test_01();
    //test_02();
    //test_03();
    //test_04();
    //test_05();
    //test_06();
    test_07();
    //test_08();
    //test_09();
    //test_10();
    //test_11();
    //test_12();
    //test_13();
}

// =====================================================================================
// End-of-File
// =====================================================================================
