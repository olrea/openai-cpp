#include "openai.hpp"

#include <fstream>

int main() {
    // Load the token from a file. You can also specify directly the token in your code as a string.
    std::string mytoken;
    std::ifstream infile("token.txt");
    std::getline(infile, mytoken);
    {
        // Create a OpenAI-CPP instance. The secret api key should be set as OPEN_API_KEY env and will be remembered as long as the instance lives
        openai::configure(mytoken);
    }
    {
        auto image = openai::image().create(R"({
            "prompt": "A cute baby sea otter",
            "n": 2,
            "size": "1024x1024"
        })"_json);
        std::cout << image.dump(2) << '\n'; 
    }
}
