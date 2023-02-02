# OpenAI C++ library 

[![Language](https://img.shields.io/badge/language-C++-blue.svg)](https://isocpp.org/)  [![Standard](https://img.shields.io/badge/c%2B%2B-11-blue.svg)](https://en.wikipedia.org/wiki/C%2B%2B#Standardization) [![License](https://img.shields.io/github/license/mashape/apistatus.svg)](https://opensource.org/licenses/MIT) ![Github worflow](https://github.com/olrea/openai-cpp/actions/workflows/cmake.yml/badge.svg)
 [![GitHub version](https://badge.fury.io/gh/olrea%2Fopenai-cpp.svg)](https://github.com/olrea/openai-cpp/releases) 

## A lightweight header only modern C++ library

OpenAI-C++ library is a **community-maintained** library which provides convenient access to the [OpenAI API](https://openai.com/api/) from applications written in the C++ language. 

## Requirements

No special requirement. You should already have these :

+ C++11 compatible compiler.
+ [libcurl](https://curl.se/libcurl/)


## Installation

The library consists of two files: `include/openaicpp/openai.hpp` and `include/openaicpp/json.hpp`.  
Just copy the `include/openaicpp` folder in your project and you can `#include "openai.hpp"` to your code. That is all.  

Note: **OpenAI-CPP** uses [Nlohmann Json](https://github.com/nlohmann/json) (v3.11.2) which is available in `include/json.hpp`. Feel free to use your own copy for faster compile time build. 

## Usage

### Simple showcase

The library needs to be configured with your account's secret key which is available on the [website](https://beta.openai.com/account/api-keys). It is recommended to set your `OPENAI_API_KEY` environment variable before using the library (or you can also set the API key directly in the code):

```bash
export OPENAI_API_KEY='sk-...'
```

The following code is available at [examples/00-showcase.cpp](examples/00-showcase.cpp).

```cpp
#include "openai.hpp"
#include <iostream>

int main() {
    openai::start(); // Will use the api key provided by `OPENAI_API_KEY` environment variable
    // openai::start("your_API_key", "optional_organization"); // Or you can handle it yourself

    auto completion = openai::completion().create(R"({
        "model": "text-davinci-003",
        "prompt": "Say this is a test",
        "max_tokens": 7,
        "temperature": 0
    })"_json); // Using user-defined (raw) string literals
    std::cout << "Response is:\n" << completion.dump(2) << '\n'; 

    auto image = openai::image().create({
        { "prompt", "A cute koala playing the violin"},
        { "n", 1 },
        { "size", "512x512" }
    }); // Using initializer lists
    std::cout << "Image URL is: " << image["data"][0]["url"] << '\n'; 
}
```

The output received looks like:

```bash
>> request: https://api.openai.com/v1/completions  {"max_tokens":7,"model":"text-davinci-003","prompt":"Say this is a test","temperature":0}
Response is:
{
  "choices": [
    {
      "finish_reason": "length",
      "index": 0,
      "logprobs": null,
      "text": "\n\nThis is indeed a test"
    }
  ],
  "created": 1674121840,
  "id": "cmpl-6aLr6jPhtxpLyu9rNsJFKDHU3SHpe",
  "model": "text-davinci-003",
  "object": "text_completion",
  "usage": {
    "completion_tokens": 7,
    "prompt_tokens": 5,
    "total_tokens": 12
  }
}
>> request: https://api.openai.com/v1/images/generations  {"n":1,"prompt":"A cute koala playing the violin","size":"512x512"}
Image URL is: "https://oaidalleapiprodscus.blob.core.windows.net/private/org-WaIMDdGHNwJiXAmjegDHE6AM/user-bCrYDjR21ly46316ZbdgqvKf/img-sysAePXF2c8yu28AIoZLLmEG.png?st=2023-01-19T20%3A35%3A19Z&se=2023-01-19T22%3A35%3A19Z&sp=r&sv=2021-08-06&sr=b&rscd=inline&rsct=image/png&skoid=6aaadede-4fb3-4698-a8f6-684d7786b067&sktid=a48cca56-e6da-484e-a814-9c849652bcb3&skt=2023-01-19T18%3A10%3A41Z&ske=2023-01-20T18%3A10%3A41Z&sks=b&skv=2021-08-06&sig=nWkcGTTCsWigHHocYP%2BsyiV5FJL6izpAe3OVvX1GLuI%3D"
```

![OpenAI-CPP attachments](doc/koala_violin.png?raw=true "OpenAI-CPP attachments")

Since `Openai::Json` is a typedef to a [nlohmann::json](https://github.com/nlohmann/json), you get all the features provided by the latter one (conversions, STL like access, ...). 


### All examples reference

- [00-showcase.cpp](examples/00-showcase.cpp)
- [01-model.cpp](examples/01-model.cpp) · [API models](https://beta.openai.com/docs/api-reference/models)
- [02-completion.cpp](examples/02-completion.cpp) · [API completions](https://beta.openai.com/docs/api-reference/completions)
- [03-edit.cpp](examples/03-edit.cpp) · [API edits](https://beta.openai.com/docs/api-reference/edits)
- [04-image.cpp](examples/04-image.cpp) · [API images](https://beta.openai.com/docs/api-reference/images)
- [05-embedding.cpp](examples/05-embedding.cpp) · [API embeddings](https://beta.openai.com/docs/api-reference/embeddings)
- [06-file.cpp](examples/06-file.cpp) · [API files](https://beta.openai.com/docs/api-reference/files)
- [07-fine-tune.cpp](examples/07-fine-tune.cpp) · [API fine-tunes](https://beta.openai.com/docs/api-reference/fine-tunes)
- [09-instances.cpp](examples/09-instances.cpp)


## Build the examples

```bash
mkdir build && cd build
cmake .. && make
examples/[whatever]
```

In your project, if you want a verbose output like when running the examples, add the following compilation flag:  
`-DOPENAICPP_VERBOSE_OUTPUT=1`.

For conveniency, you can put your api secret key in `build/token.txt`, to make the examples work. 

### Note for Windows users

If you are using WSL then you are not concerned by the following. 

You might have difficulties handling libcurl where CMake throws `Could NOT find CURL (missing: CURL_LIBRARY CURL_INCLUDE_DIR)`.

One way to solve this is to grab the curl version for Windows [here](https://curl.se/windows/), copy the content of `include`
in appropriate folders available visible in your PATH (e.g. if in your Git installation `[...]/Git/mingw64/include/`).
You also need to grab the `curl.lib` and the `libcurl.dll` files from [here](https://dl.dropboxusercontent.com/s/jxwohqax4e2avyt/libcurl-7.48.0-WinSSL-zlib-x86-x64.zip?dl=0) and copy them in appropriate folders (e.g. if in your Git installation `[...]/Git/mingw64/lib/`).

```bash
mkdir build && cd build
cmake .. -DCMAKE_GENERATOR_PLATFORM=x64
cmake --build .
cmake --build . --target 00-showcase # For a specific target
```

Or if you prefer using GNU GCC on Windows

```bash
cmake -G "MSYS Makefiles" -D CMAKE_CXX_COMPILER=g++ ..
make
```

## Advanced usage

### A word about error handling

By default, **OpenAI-CPP** will throw a runtime error exception if the curl request does not succeed. You are free to handle these exceptions the way you like.
You can prevent throw exceptions by setting `setThrowException(false)` (see example in [examples/09-instances.cpp](examples/09-instances.cpp)). If you do that, a warning will be displayed instead. 

### More control

You can use the `openai::post()` or `openai::get()` methods to fully control what you are sending (e.g. can be useful when a new method from OpenAI API is available and not provided by `OpenAI-CPP` yet).


### Manage OpenAI-CPP instance

Here are two approaches to keep alive the **OpenAI-CPP** session in your program so you can use it anytime, anywhere.

#### Use instance()

This is the default behavior. **OpenAI-CPP** provides free convenient functions : `openai::start(const std::string& token)` and `openai::instance()`.
Initialize and configure the **OpenAI-CPP** instance with:

```cpp
auto& openai = openai::start();
```

When you are in another scope and you have lost the `openai` reference, you can grab it again with :  

```cpp
auto& openai = openai::instance();
```

It might not be the recommended way but since we generally want to handle only one OpenAI instance (one token), this approach is highly convenient. 

#### Pass by reference

An other approach is to pass the *OpenAI* instance by reference, store it, and call the appropriate methods when needed.

```cpp
void bar(openai::OpenAI& openai) {
    openai.completion.create({
        {"model", "text-davinci-003"},
        {"prompt", "Say bar() function called"}
    });
}

int main() {
    openai::OpenAI openai_instance{"your_api_key"};
    bar(openai_instance);
}
```

You can use a [std::reference_wrapper](http://en.cppreference.com/w/cpp/utility/functional/reference_wrapper) as shown in [examples/09-instances.cpp](examples/09-instances.cpp). This strategy is useful if you have to manage several OpenAI-CPP instances.


## Acknowledgment

This work has been mainly inspired by [slacking](https://github.com/coin-au-carre/slacking) and the curl wrapper code from [cpr](https://github.com/libcpr/cpr).

### Sponsor

[OLREA](https://www.olrea.fr/)
