#include "openai.hpp"

#include <iostream>

// A class which handles a openai instance by reference
class Foo {
    std::reference_wrapper<openai::OpenAI> openai_;
    // Or
    // OpenAI& openai_;

public:
    Foo(openai::OpenAI& openai) : openai_{openai} {
        auto res = openai_.get().completion.create({
            {"model", "text-davinci-003"},
            {"prompt", "Say Foo class ctor called"}
        }); // parameters channel, username, iconemoji reused from bar()
        std::cout << res << "\n\n";
    }
}; 

// Pass by ref in parameter function
void bar(openai::OpenAI& openai) {
    // You can try catch API method if an error occur
    try {
        auto res = openai.completion.create({
            {"model", "text-davinci-003"},
            {"prompt", "Say bar() function called"}
        });
        std::cout << res << "\n\n";
    }
    catch(std::exception const& e) {
        std::cerr << "Exception:" <<  e.what() << "\n\n";
    }
}


int main() {
    // Create openai instance
    openai::OpenAI openai_instance{};
    bar(openai_instance);
    Foo foo{openai_instance};

    // You can create other openai instances with different tokens and parameters
    {
        openai::OpenAI another_openai_instance{"wrong apy key"};
        // another_openai_instance.setThrowException(false); // You can set throw exception to false if you want
        
        try {
            another_openai_instance.completion.create({
                {"model", "text-davinci-003"},
                {"prompt", "Say this should throw since token is invalid here"}
            }); 
        }
        catch(std::exception const& e) {
            std::cerr << "02-basic failed purposely because of " << e.what() << "\n\n";
        }
    }
}
