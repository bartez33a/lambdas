/*
   1. create function schedule(), which takes two parameters:
   -  first - any function "func" which takes no parameter and returns nothing
   -  second - "duration" - time period in secnods (use library std::chrono).
   Function schedule should wait "duration" seconds and then call function
   "func".

   2. Create overload of the function "schedule", which takes two arguments:
      -  any function which takes int and returns nothing, and
      -  int (instead of "duration").
      How to pass int argument to this function?

   3. Create another overload of schedule, which takes functions which take
      std::string and double as their parameters and returns nothing.

   Bonus: implement schedule as a templete function. One version will be enough
   (without any overloads)!

*/

#include <chrono>
#include <functional>
#include <iomanip>
#include <iostream>
#include <string>

/*
   Inputs:
   -  func     - pointer to function which takes no argument and reutrns nothing
   -  duration - duration of time in seconds after which func is called
*/
void schedule(std::function<void(void)> func, const std::chrono::seconds duration) {
    using namespace std::chrono_literals;

    const auto start = std::chrono::steady_clock::now();
    while (true) {
        auto now = std::chrono::steady_clock::now();
        auto elapsed_seconds = std::chrono::duration_cast<std::chrono::seconds>(now - start);
        if (elapsed_seconds >= duration) {
            break;
        }
    }

    // call function
    func();
}

void schedule(std::function<void(int)> func, const std::chrono::seconds duration, int func_arg) {
    using namespace std::chrono_literals;

    const auto start = std::chrono::system_clock::now();
    while (true) {
        auto now = std::chrono::system_clock::now();
        auto elapsed_seconds = std::chrono::duration_cast<std::chrono::seconds>(now - start);
        if (elapsed_seconds >= duration) {
            break;
        }
    }

    // call function
    func(func_arg);
}

// Napisz kolejne przeciążenie, które będzie przyjmować funkcje,
// które przyjmują std::string oraz double jako swoje argumenty i nic nie zwracają.
void schedule(std::function<void(std::string, double)> func, const std::chrono::seconds duration, std::string text, double value) {
    using namespace std::chrono_literals;

    const auto start = std::chrono::system_clock::now();
    while (true) {
        auto now = std::chrono::system_clock::now();
        auto elapsed_seconds = std::chrono::duration_cast<std::chrono::seconds>(now - start);
        if (elapsed_seconds >= duration) {
            break;
        }
    }

    // call function
    func(text, value);
}

int main() {
    using namespace std::chrono_literals;

    auto start = std::chrono::system_clock::now();
    std::cout << "start!\n";
    schedule([] { std::cout << "I'm an empty function\n"; }, 1s);
    schedule([](int a) { std::cout << "Param int a = " << a << '\n'; }, 2s, 42);

    schedule(
        [](std::string s, double d) {
            std::cout << "Params: string s  = " << s << ", double d = " << d << '\n';
        },
        0s, "text", 42.5);

    auto stop = std::chrono::system_clock::now();

    std::chrono::duration<double> diff = stop - start;
    std::cout << "Everything took " << std::fixed << std::setprecision(6) << diff.count()
              << " seconds\n";

    return 0;
}