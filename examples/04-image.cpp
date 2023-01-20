#include "openai.hpp"

#include <iostream>

int main() {
    openai::start();

    auto image = openai::image().create(R"({
        "prompt": "A cute baby sea otter",
        "n": 2,
        "size": "512x512"
    })"_json);
    std::cout << image.dump(2) << '\n'; 
}
