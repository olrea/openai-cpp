#include "openai.hpp"

#include <iostream>

int main() {
    openai::start();

    {
        auto moderation = openai::moderation().create(R"(
            {
            "input": "I want to kill them."
            }
        )"_json);
        std::cout << "Response is:\n" << moderation.dump(2) << '\n'; 
    }
}

