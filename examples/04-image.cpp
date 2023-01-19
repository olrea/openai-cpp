#include "openai.hpp"

#include <fstream>

int main() {
    openai::start();

    auto image = openai::image().create(R"({
        "prompt": "A cute baby sea otter",
        "n": 2,
        "size": "1024x1024"
    })"_json);
    std::cout << image.dump(2) << '\n'; 
    
}
