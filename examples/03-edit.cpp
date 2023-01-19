#include "openai.hpp"

#include <fstream>

int main() {
    // Load the OpenAI API key from a file. You can also specify directly the token in your code as a string.
    std::string mytoken;
    std::ifstream infile("token.txt");
    std::getline(infile, mytoken);

    openai::configure(mytoken); // Configure and launch the OpenAI instance

    auto edit = openai::edit().create(R"(
    {
        "model": "text-davinci-edit-001",
        "input": "What day of the wek is it?",
        "instruction": "Fix the spelling mistakes"
    }
    )"_json); 
    std::cout << "Response is:\n" << edit.dump(2) << '\n'; 
}
