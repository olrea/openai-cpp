#include "openai.hpp"

#include <iostream>

int main() {
    openai::start();

    {
        // Change "audio.mp3" to your audio file location
        auto transcription = openai::audio().transcribe(R"(
            {
            "file": "audio.mp3",
            "model": "whisper-1"
            }
        )"_json);
        std::cout << "Response is:\n" << transcription.dump(2) << '\n'; 
    }

    { 
        // Change "german.m4a" to your audio file location
        auto translation = openai::audio().translate(R"(
            {
            "file": "german.m4a",
            "model": "whisper-1"
            }
        )"_json);
        std::cout << "Response is:\n" << translation.dump(2) << '\n'; 
    }
}

