# OpenAI C++ library 

[![Language](https://img.shields.io/badge/language-C++-blue.svg)](https://isocpp.org/)  [![Standard](https://img.shields.io/badge/c%2B%2B-11-blue.svg)](https://en.wikipedia.org/wiki/C%2B%2B#Standardization) [![License](https://img.shields.io/github/license/mashape/apistatus.svg)](https://opensource.org/licenses/MIT) ![Github worflow](https://github.com/olrea/openai-cpp/actions/workflows/cmake.yml/badge.svg)
 [![GitHub version](https://badge.fury.io/gh/olrea%2Fopenai-cpp.svg)](https://github.com/olrea/openai-cpp/releases) 

## A lightweight header only modern C++ library

OpenAI-C++ library is a **community-maintained** library which provides convenient access to the [OpenAI API](https://openai.com/api/) from applications written in the C++ language.  
The library is small with two header files (only one if you already use Nlohmann Json).

## Requirements

No special requirement. You should already have these :

+ C++11/C++14/C++17/C++20 compatible compiler
+ [libcurl](https://curl.se/libcurl/) (check [Install curl](https://everything.curl.dev/get) to make sure you have the development package)

## OpenAI C++ current implementation

The library should implement all requests on [OpenAI references](https://platform.openai.com/docs/api-reference). If any are missing (due to an update), feel free to open an issue.

| API reference | Method | Example file |
| --- | --- | --- |
| API models | [List models](https://platform.openai.com/docs/api-reference/models/list) ✅ | [1-model.cpp](examples/01-model.cpp) |
| API models | [Retrieve model](https://platform.openai.com/docs/api-reference/models/retrieve) ✅ | [1-model.cpp](examples/01-model.cpp) |
| API completions | [Create completion](https://platform.openai.com/docs/api-reference/completions/create) ✅ | [2-completion.cpp](examples/02-completion.cpp) |
| API edits | [Create completion](https://platform.openai.com/docs/api-reference/completions/create) | [3-edit.cpp](examples/03-edit.cpp) |
| API images | [Create image](https://platform.openai.com/docs/api-reference/images) ✅ | [4-image.cpp](examples/04-image.cpp) |
| API images | [Create image edit](https://platform.openai.com/docs/api-reference/images/create-edit) ✅ | [4-image.cpp](examples/04-image.cpp) |
| API images | [Create image variation](https://platform.openai.com/docs/api-reference/images/create-variation) ✅ | [4-image.cpp](examples/04-image.cpp) |
| API embeddings | [Create embeddings](https://platform.openai.com/docs/api-reference/embeddings/create) ✅ | [5-embedding.cpp](examples/05-embedding.cpp) |
| API files | [List file](https://platform.openai.com/docs/api-reference/files/list) ✅ | [6-file.cpp](examples/06-file.cpp) |
| API files | [Upload file](https://platform.openai.com/docs/api-reference/files/upload) ✅ | [6-file.cpp](examples/06-file.cpp) |
| API files | [Delete file](https://platform.openai.com/docs/api-reference/files/delete) ✅ | [6-file.cpp](examples/06-file.cpp) |
| API files | [Retrieve file](https://platform.openai.com/docs/api-reference/files/retrieve) ✅ | [6-file.cpp](examples/06-file.cpp) |
| API files | [Retrieve file content](https://platform.openai.com/docs/api-reference/files/retrieve-content) ✅ | [6-file.cpp](examples/06-file.cpp) |
| API fine-tunes | [Create fine-tune](https://platform.openai.com/docs/api-reference/fine-tunes/create) ✅ | [7-fine-tune.cpp](examples/07-fine-tune.cpp) |
| API fine-tunes | [List fine-tune](https://platform.openai.com/docs/api-reference/fine-tunes/list) ✅ | [7-fine-tune.cpp](examples/07-fine-tune.cpp) |
| API fine-tunes | [Retrieve fine-tune](https://platform.openai.com/docs/api-reference/fine-tunes/retrieve) ✅ | [7-fine-tune.cpp](examples/07-fine-tune.cpp) |
| API fine-tunes | [Cancel fine-tune](https://platform.openai.com/docs/api-reference/fine-tunes/cancel) ✅ | [7-fine-tune.cpp](examples/07-fine-tune.cpp) |
| API fine-tunes | [List fine-tune events](https://platform.openai.com/docs/api-reference/fine-tunes/events) ✅ | [7-fine-tune.cpp](examples/07-fine-tune.cpp) |
| API fine-tunes | [Delete fine-tune model](https://platform.openai.com/docs/api-reference/fine-tunes/delete-model) ✅ | [7-fine-tune.cpp](examples/07-fine-tune.cpp) |
| API chat | [Create chat completion](https://platform.openai.com/docs/api-reference/chat/create) ✅ | [10-chat.cpp](examples/10-chat.cpp) |
| API audio | [Create transcription](https://platform.openai.com/docs/api-reference/audio/create) ✅ | [11-audio.cpp](examples/11-audio.cpp) |
| API audio | [Create translation](https://platform.openai.com/docs/api-reference/audio/create) ✅ | [11-audio.cpp](examples/11-audio.cpp) |
| API moderation | [Create moderation](https://platform.openai.com/docs/api-reference/moderations/create) ✅ | [12-moderation.cpp](examples/11-moderation.cpp) |

## Installation

The library consists of two files: [include/openai/openai.hpp](https://github.com/olrea/openai-cpp/blob/main/include/openai/openai.hpp) and [include/openai/nlohmann/json.hpp](https://github.com/olrea/openai-cpp/blob/main/include/openai/nlohmann/json.hpp).  
Just copy the [include/openaicpp](https://github.com/olrea/openai-cpp/tree/main/include/openai) folder in your project and you can use `#include "openai.hpp"` in your code. That is all.  

> Note: **OpenAI-CPP** uses [Nlohmann Json](https://github.com/nlohmann/json) which is available in `include/json.hpp`. Feel free to use your own copy for faster compile time build. 

## Usage

### Simple showcase

The library needs to be configured with your account's secret key which is available on the [website](https://platform.openai.com/account/api-keys). It is recommended to set your `OPENAI_API_KEY` environment variable before using the library (or you can also set the API key directly in the code):

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


### Build the examples

```bash
mkdir build && cd build
cmake .. && make
examples/[whatever]
```

In your project, if you want to get verbose output like when running the examples, you can define `#define OPENAI_VERBOSE_OUTPUT`.

### Advanced usage

#### A word about error handling

By default, **OpenAI-CPP** will throw a runtime error exception if the curl request does not succeed. You are free to handle these exceptions the way you like.
You can prevent throw exceptions by setting `setThrowException(false)` (see example in [examples/09-instances.cpp](examples/09-instances.cpp)). If you do that, a warning will be displayed instead. 

### More control

You can use the `openai::post()` or `openai::get()` methods to fully control what you are sending (e.g. can be useful when a new method from OpenAI API is available and not provided by `OpenAI-CPP` yet).


#### Manage OpenAI-CPP instance

Here are two approaches to keep alive the **OpenAI-CPP** session in your program so you can use it anytime, anywhere.

##### Use the default instance()

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

##### Pass by reference if you want to manage multiple secret keys

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

You can use a [std::reference_wrapper](http://en.cppreference.com/w/cpp/utility/functional/reference_wrapper) as shown in [examples/09-instances.cpp](examples/09-instances.cpp). 

This strategy is useful if you have to manage several OpenAI-CPP instances with different secret keys.

## Troubleshooting

### Libcurl with Windows

> Note: If you are using [WSL](https://learn.microsoft.com/windows/wsl/) then you are not concerned by the following. 

According to [Install Curl on Windows](https://everything.curl.dev/get/windows),
> Windows 10 comes with the curl tool bundled with the operating system since version 1804

However, you still might have difficulties handling libcurl where CMake throws `Could NOT find CURL (missing: CURL_LIBRARY CURL_INCLUDE_DIR)`.  
You can try to follow one the 2 ways proposed by the the Curl [Install Curl on Windows](https://everything.curl.dev/get/windows).

Another way to solve this is to grab the curl version for Windows [here](https://curl.se/windows/), copy the content of `include`
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


## License

[MIT](LICENSE.md)


## Acknowledgment

This work has been mainly inspired by [slacking](https://github.com/coin-au-carre/slacking) and the curl wrapper code from [cpr](https://github.com/libcpr/cpr).

## Sponsor

[OLREA](https://www.olrea.fr/)
