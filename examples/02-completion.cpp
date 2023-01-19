#include "openai.hpp"

#include <fstream>

int main() {
    // Load the OpenAI API key from a file. You can also specify directly the token in your code as a string.
    std::string mytoken;
    std::ifstream infile("token.txt");
    std::getline(infile, mytoken);

    openai::configure(mytoken); // Configure and launch the OpenAI instance

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
