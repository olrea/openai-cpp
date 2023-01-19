#include "openai.hpp"

#include <fstream>

int main() {
    // Load the OpenAI API key from a file. You can also specify directly the token in your code as a string.
    std::string mytoken;
    std::ifstream infile("token.txt");
    std::getline(infile, mytoken);

    {
        openai::configure(mytoken); // Configure and launch the OpenAI instance
    }

    {
        // Calling API method is easy with some chosen free function 
        auto models = openai::model().list();
        std::cout << models["data"][0] << std::endl;

        // Or if you prefer you can take back the instance reference and use member function
        auto& openai = openai::instance();
        auto models_other_approach = openai.model.list();
        std::cout << models_other_approach["data"][1] << std::endl;
        // Helper member and free functions have the same signature

        auto model = openai::model().retrieve("text-davinci-003");
        std::cout << model << std::endl;
    }
}
