#include "openai.hpp"

#include <fstream>

int main() {
    // Load the token from a file. You can also specify directly the token in your code as a string.
    std::string mytoken;
    std::ifstream infile("token.txt");
    std::getline(infile, mytoken);
    {
        // Create a OpenAI-CPP instance membered as long as the instance lives
        openai::configure(mytoken);
    }
    {
        auto files = openai::file().list();
        std::cout << files.dump(2) << '\n'; // 
    }
}
