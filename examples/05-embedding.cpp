#include "openai.hpp"

#include <fstream>

int main() {
    // Load the OpenAI API key from a file. You can also specify directly the token in your code as a string.
    std::string mytoken;
    std::ifstream infile("token.txt");
    std::getline(infile, mytoken);

    openai::configure(mytoken); // Configure and launch the OpenAI instance

    auto res = openai::embedding().create({
        { "model", "text-embedding-ada-002" },
        { "input", "The food was delicious and the waiter..." }
    }); 
    std::cout << "Response is:\n" << res.dump(2) << '\n'; 
}
