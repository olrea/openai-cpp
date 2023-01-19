#include "openai.hpp"

#include <fstream>

int main() {
    // Load the OpenAI API key from a file. You can also specify directly the token in your code as a string.
    std::string mytoken;
    std::ifstream infile("token.txt");
    std::getline(infile, mytoken);

    openai::configure(mytoken); // Configure and launch the OpenAI instance
    
    // Upload
    {
        auto upload = openai::fineTune().create({
            {"training_file", "file-gD2KgQKsxcn6zguK0ETuodXO"},
        });
        std::cout << upload.dump(2) << '\n';
    }

    // List fine tunes
    {
        auto files = openai::fineTune().list();
        std::cout << files.dump(2) << '\n'; 
    }

    // Retrieve
    {
        auto retrieve = openai::fineTune().retrieve("ft-N9Zf32f3uzpoXxJLr14CnFy1");
        std::cout << retrieve.dump(2) << '\n';
    }

    // Cancel
    {
        auto cancel = openai::fineTune().cancel("ft-N9Zf32f3uzpoXxJLr14CnFy1");
        std::cout << cancel.dump(2) << '\n';
    }

    // List Events
    {
        auto events = openai::fineTune().events("ft-N9Zf32f3uzpoXxJLr14CnFy1");
        std::cout << events.dump(2) << '\n';
    }

    // Delete
    {
        auto res = openai::fineTune().del("any-model");
        std::cout << res.dump(2) << '\n';
    }

}
