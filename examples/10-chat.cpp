#include "openai.hpp"

#include <iostream>

int main() {
    openai::start();

    auto chat = openai::chat().create(R"(
    {
        "model": "gpt-3.5-turbo",
        "messages":[{"role":"user", "content":"blah"}],
        "max_tokens": 7,
        "temperature": 0
    }
    )"_json);
    std::cout << "Response is:\n" << chat.dump(2) << '\n'; 
}