#include "openai.hpp"

#include <fstream>

int main() {
    // Load the OpenAI API key from a file. You can also specify directly the token in your code as a string.
    std::string mytoken;
    std::ifstream infile("token.txt");
    std::getline(infile, mytoken);

    openai::configure(mytoken); // Configure and launch the OpenAI instance
    
    // Upload file
    {
        auto upload = openai::file().upload({
            {"file", "finetune1.jsonl"},
            {"purpose", "fine-tune"}
        });
        std::cout << upload.dump(2) << '\n';
    }

    // List files
    {
        auto files = openai::file().list();
        std::cout << files.dump(2) << '\n'; 
    }

    // Retrieve file
    {
        auto retrieve = openai::file().retrieve("file-PXSN5R3NV2BjlTPdeudRD8Dv");
        std::cout << retrieve.dump(2) << '\n'; 
    }

    // Retrieve file content
    {
        auto content = openai::file().content("file-PXSN5R3NV2BjlTPdeudRD8Dv");
        std::cout << content.dump(2) << '\n'; 
    }

    // Delete file
    {
        auto content = openai::file().del("file-PXSN5R3NV2BjlTPdeudRD8Dv");
        std::cout << content.dump(2) << '\n'; 
    }
}
