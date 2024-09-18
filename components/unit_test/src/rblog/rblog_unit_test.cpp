#include "gtest/gtest.h"
#include "rblog.h"

#define TAG_RBLOG_UT ("RBLOG_UT")

TEST(RblogTest, LoggingFunctions)
{
    // Initialize rblog
    ASSERT_EQ(rblog_init(), 0);

    // Test different logging levels
    rblog_a(TAG_RBLOG_UT, "This is a fatal message");
    rblog_e(TAG_RBLOG_UT, "This is an error message");
    rblog_w(TAG_RBLOG_UT, "This is a warning message");
    rblog_i(TAG_RBLOG_UT, "This is an info message");
    rblog_d(TAG_RBLOG_UT, "This is a debug message");
    rblog_v(TAG_RBLOG_UT, "This is a verbose message");

    // Test logging with format specifiers
    int testInt            = 42;
    float testFloat        = 3.14f;
    const char *testString = "test string";
    rblog_i(TAG_RBLOG_UT, "Formatted message: int=%d, float=%.2f, string=%s", testInt, testFloat, testString);

    // Test rblog_output function
    rblog_output(TAG_RBLOG_UT, RBLOG_LVL_INFO, "This is a message using rblog_output");

    // Finalize rblog
    rblog_fini();

    // Note: We can't easily assert the output of these logging functions in a unit test.
    // Typically, we would need to redirect the output and parse it, which is beyond the scope of this simple test.
    // For now, we'll just visually inspect the output when running the test.

    SUCCEED();
}


