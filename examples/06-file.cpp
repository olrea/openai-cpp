#include "openai.hpp"

#include <iostream>

int main() {
    openai::start();
    
    // Upload file
    auto upload = openai::file().upload({
        {"file", "finetune1.jsonl"},
        {"purpose", "fine-tune"}
    });
    std::cout << upload.dump(2) << "\n\n";
    std::string uploaded_file_id = upload["id"].get<std::string>(); // retrieve file id of uploaded file file-....


    // List files
    auto files = openai::file().list();
    std::cout << files.dump(2) << "\n\n"; 

    // Retrieve file
    auto retrieve = openai::file().retrieve(uploaded_file_id); // file-....
    std::cout << retrieve.dump(2) << "\n\n"; 


    // Retrieve file content
    try {
        auto content = openai::file().content(uploaded_file_id); // file-....
        std::cout << content.dump(2) << "\n\n"; 
    } catch(std::exception const& e) {
        std::cerr << "You might have this exception because you have a free account " << e.what() << "\n\n";
    }

    // Delete file
    auto deletion = openai::file().del(uploaded_file_id);
    std::cout << deletion.dump(2) << "\n\n"; 
}
