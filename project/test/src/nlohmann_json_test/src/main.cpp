#include <stdio.h>
#include <type_traits>
#include "json.hpp"

using namespace nlohmann;

int JsonAddTest()
{
    json js_obj                   = json::object();
    js_obj["name"]                = "John";
    js_obj["age"]                 = 30;
    js_obj["company"]["location"] = "Cupertino";

    printf("%s\n", js_obj.dump().c_str());
    return 0;
}

int JsonTrueTest()
{
    json js_bool = true;
    printf("%d\n", (std::uint8_t)js_bool.type());

    json js_int = 1;
    printf("%d\n", (std::uint8_t)js_int.type());

    json js_double = 3.14;
    printf("%d\n", (std::uint8_t)js_double.type());

    json js_string = "hello world";
    printf("%d\n", (std::uint8_t)js_string.type());

    json js_null = nullptr;
    printf("%d\n", (std::uint8_t)js_null.type());

    json js_array = {1, 2, 3, 4, 5};
    printf("%d\n", (std::uint8_t)js_array.type());

    json js_object = {
        {  "one", 1},
        {  "two", 2},
        {"three", 3}
    };
    printf("%d\n", (std::uint8_t)js_object.type());

    json js_empty_array = {};
    printf("%d\n", (std::uint8_t)js_empty_array.type());

    json js_empty_object = json::object();
    printf("%d\n", (std::uint8_t)js_empty_object.type());

    return 0;
}

int CreateObjectTest()
{
    json ex1;

    ex1["name"]    = "John";
    ex1["age"]     = 30;
    ex1["city"]    = "New York";
    ex1["hobbies"] = {"reading", "swimming", "hiking"};

    std::string output = ex1.dump();

    printf("hobbies size: %lu\n", ex1["hobbies"].size());
    printf("%d\n", (std::uint8_t)ex1.type());
    printf("%d\n", (std::uint8_t)ex1["name"].type());
    printf("%d\n", (std::uint8_t)ex1["age"].type());
    printf("%d\n", (std::uint8_t)ex1["hobbies"].type());

    for (auto &hobby : ex1["hobbies"])
    {
        printf("%s\n", hobby.get<std::string>().c_str());
    }

    json ex2{true};

    for (int i = 0; i < ex1["hobbies"].size(); i++)
    {
        printf("%s\n", ex1["hobbies"][i].get<std::string>().c_str());
    }

    printf("%s\n", output.c_str());

    return 0;
}


int main()
{
    // CreateObjectTest();
    // JsonTrueTest();
    JsonAddTest();

    return 0;
}

