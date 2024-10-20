#include "cJSON.h"
#include "gtest/gtest.h"

TEST(EvenTest, cJSONTypeTest)
{
    EXPECT_EQ(0, []() -> int32_t {
        cJSON *json    = cJSON_CreateTrue();
        int32_t result = cJSON_IsBool(json) && cJSON_IsTrue(json);
        cJSON_Delete(json);
        if (result)
        {
            return 0;
        }
        else
        {
            return -1;
        }
    }());
}

TEST(JSONParsingTest, ParseSimpleObject)
{
    const char *json_string = R"(
    {
        "name": "John Doe",
        "age": 30,
        "city": "New York"
    })";

    cJSON *json = cJSON_Parse(json_string);
    ASSERT_NE(json, nullptr);

    cJSON *name = cJSON_GetObjectItemCaseSensitive(json, "name");
    ASSERT_NE(name, nullptr);
    EXPECT_STREQ(name->valuestring, "John Doe");

    cJSON *age = cJSON_GetObjectItemCaseSensitive(json, "age");
    ASSERT_NE(age, nullptr);
    EXPECT_EQ(age->valueint, 30);

    cJSON *city = cJSON_GetObjectItemCaseSensitive(json, "city");
    ASSERT_NE(city, nullptr);
    EXPECT_STREQ(city->valuestring, "New York");

    cJSON_Delete(json);
}


int main()
{
    printf("cjson_test start\n");
    testing::InitGoogleTest();
    return RUN_ALL_TESTS();
}
