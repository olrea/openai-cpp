# OpenAI C++ library

[![Language](https://img.shields.io/badge/language-C++-blue.svg)](https://isocpp.org/)  [![Standard](https://img.shields.io/badge/c%2B%2B-11-blue.svg)](https://en.wikipedia.org/wiki/C%2B%2B#Standardization) [![License](https://img.shields.io/github/license/mashape/apistatus.svg)](https://opensource.org/licenses/MIT) [![Build Status](https://travis-ci.org/coin-au-carre/openaicpp.svg?branch=main)](https://travis-ci.org/coin-au-carre/openaicpp) [![Build status](https://ci.appveyor.com/api/projects/status/9v928kd5cwd82pt9?svg=true)](https://ci.appveyor.com/project/coin-au-carre/openaicpp) [![GitHub version](https://badge.fury.io/gh/coin-au-carre%2Fopenaicpp.svg)](https://github.com/coin-au-carre/openaicpp/releases) [![Openai Channel](https://img.shields.io/badge/openai-@demo-pink.svg)](https://join.openai.com/t/olrea/shared_invite/zt-nj68r01f-bMq_QCrDRXBxvTVapmFXvg)

## A lightweight modern C++ library

The OpenAI C++ library provides convenient access to the [OpenAI API](https://beta.openai.com/docs/introduction) from applications written in the C++ language. 

## Requirements

No special requirement. You should already have these :

+ C++11 compatible compiler. Tested with Clang (3.5, 3.6, 3.7), GCC (4.9, 5), MSCV (VS 14 2015, VS 15 2017)
+ [libcurl](https://curl.se/libcurl/)

## Installation

Just copy the `include/openaicpp` folder in your project and you can `#include "openai.hpp"` to your code. That is all.  

Note: *OpenAI-CPP* uses [Nlohmann Json](https://github.com/nlohmann/json) (v3.11.2) which is available in `include/json.hpp`. Feel free to use your own copy for faster compile time build. 

## Usage

### Simple showcase

The below code is available at [examples/00-showcase.cpp](examples/00-showcase.cpp)

```c++
auto& openai = openai::configure("xxx-xxx-xxx-xxx"); // "xxx-xxx-xxx-xxx" is your secret OpenAI API key

auto completion = openai::completion().create(R"(
{
    "model": "text-davinci-003",
    "prompt": "Say this is a test",
    "max_tokens": 7,
    "temperature": 0
}
)"_json); // Using user-defined (raw) string literals
std::cout << "Response is:\n" << completion.dump(2) << '\n'; 

auto image = openai::image().create({
    { "prompt", "A cute koala playing the violin"},
    { "n", 1 },
    { "size", "512x512" }
}); // Using initializer lists
std::cout << "Response is:\n" << image.dump(2) << '\n'; 
```

The output received is in the form:
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
>> request: https://api.openai.com/v1/images/generations  {"n":1,"prompt":"A cute koala playing the violin","size":"1024x1024"}
Response is:
{
  "created": 1674121847,
  "data": [
    {
      "url": "https://oaidalleapiprodscus.blob.core.windows.net/private/org-WaIMDdGHNwJiXAmjegDHE6AM/user-bCrYDjR21ly46316ZbdgqvKf/img-fEnvTHYVuXPTeK3XaCvyeURJ.png?st=2023-01-19T08%3A52%3A08Z&se=2023-01-19T10%3A52%3A08Z&sp=r&sv=2021-08-06&sr=b&rscd=inline&rsct=image/png&skoid=6aaadede-4fb3-4698-a8f6-684d7786b067&sktid=a48cca56-e6da-484e-a814-9c849652bcb3&skt=2023-01-19T07%3A05%3A13Z&ske=2023-01-20T07%3A05%3A13Z&sks=b&skv=2021-08-06&sig=Dtdh5taessfocAw/LI0ngnF127E1dXVWlS3HTE1FoEw%3D"
    }
  ]
}
```

![OpenAI-CPP attachments](doc/koala_violin.png?raw=true "OpenAI-CPP attachments")

Since Openai::Json is a typedef to a [nlohmann::json](https://github.com/nlohmann/json), you have all the features of the latter one (conversions, STL like access, ...). For instance, `response["ok"]` will give `true`.

## A word about error handling

By default, OpenAI-CPP will throw a runtime error exception if the curl request does not succeed. You are free to handle these exceptions the way you like.
You can prevent throw exceptions by setting `set_throw_exception(false)` (see example in [examples/09-instances.cpp](examples/09-instances.cpp)). If you do that, a warning will be displayed instead. 

## More control

You can use the `openai::post` or `openai::get` methods to fully control what you are sending.


## Manage OpenAI-CPP instance

Here are two approaches to keep alive the *OpenAI-CPP* session in your program so you can use it anytime, anywhere.

### Use instance()

*OpenAI-CPP* provides free convenient functions : `openai::configure(const std::string& token)` and `openai::instance()`.
Initialize and configure the OpenAI-CPP instance with:

```c++
auto& openai = openai::configure("xxx-xxx-xxx-xxx");
```

When you are in another scope and you have lost the `openai` reference, you can grab it again with :  

```c++
auto& openai = openai::instance();
```

It might not be the recommended way but since we generally want to handle only one Openai instance (one token), it is highly convenient. You can refer to the example usage and  [examples/01-basic.cpp](examples/01-basic.cpp).

### Pass by reference

An other approach is to pass the *OpenAI* instance by reference, store it, and call the appropriate methods when needed.

```c++
void bar(openai::OpenAI& openai) {
    openai.completion.create({
            {"model", "text-davinci-003"},
            {"prompt", "Say bar() function called"}
    });
}

int main() {
    openai::OpenAI openai_instance{"xxx-xxx-xxx-xxx"};
    bar(openai_instance);
}
```

You can use a [std::reference_wrapper](http://en.cppreference.com/w/cpp/utility/functional/reference_wrapper) as shown in [examples/09-instances.cpp](examples/09-instances.cpp). This strategy is useful if you have to manage several OpenAI-CPP instances.

## Build the examples

```bash
mkdir build && cd build
cmake .. && make
examples/[whatever]
```

In your project, if you want a verbose output like when running the examples, add the following compilation flag:  
`-DOPENAICPP_VERBOSE_OUTPUT=1`.

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

## Next steps

- [ ] Add more examples
- [ ] Provide convenient helpers
- [ ] Add delete routes

## Acknowledgment

This work has been inspired mainly inspired by [slacking](https://github.com/coin-au-carre/slacking) and the curl wrapper code from [cpr](https://github.com/libcpr/cpr).

