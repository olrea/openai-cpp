#include "openai.hpp"

#include <iostream>

int main() {
    openai::start();

    auto completion = openai::completion().create(R"(
    {
        "model": "text-davinci-003",
        "prompt": "Say this is a test",
        "max_tokens": 7,
        "temperature": 0
    }
    )"_json);
    std::cout << "Response is:\n" << completion.dump(2) << '\n'; 
}
