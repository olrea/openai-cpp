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

    auto image_edit = openai::image().edit(R"({
        "image": "otter.png",
        "prompt": "A cute baby sea otter wearing a beret",
        "n": 1,
        "size": "256x256"
    })"_json);
    std::cout << image_edit.dump(2) << '\n'; 

    auto image_variation = openai::image().variation(R"({
        "image": "otter.png",
        "n": 2,
        "size": "256x256"
    })"_json);
    std::cout << image_variation.dump(2) << '\n'; 
}
