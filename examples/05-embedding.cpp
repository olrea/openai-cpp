#include "openai.hpp"

#include <iostream>

int main() {
    openai::start();

    auto res = openai::embedding().create({
        { "model", "text-embedding-ada-002" },
        { "input", "The food was delicious and the waiter..." }
    }); 
    std::cout << "Response is:\n" << res.dump(2) << '\n'; 
}
