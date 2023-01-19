#include "openai.hpp"

#include <iostream>

int main() {
    // your_API_key should come from an environment variable or an env file
    openai::configure("your_API_key", "optional_organization");

    auto completion = openai::completion().create(R"(
    {
        "model": "text-davinci-003",
        "prompt": "Say this is a test",
        "max_tokens": 7,
        "temperature": 0
    }
    )"_json); // Using user-defined (raw) string literals
    std::cout << "Response is:\n" << completion.dump(2) << '\n'; 

    auto image = openai::image().create({
        { "prompt", "A cute koala playing the violin"},
        { "n", 1 },
        { "size", "512x512" }
    }); // Using initializer lists
    std::cout << "Response is:\n" << image.dump(2) << '\n'; 
}
