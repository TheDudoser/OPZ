#include "gtest/gtest.h"
#include "OPZ_lib.h"
#include <vector>

TEST(methodWriteInVector, expectedWriteInVector) {
    std::vector<char> message;
    std::vector<char> new_message = {'1','+','(','2','-','3','*','4',')','/','5'};
    bool check = false;
    char message1[] = "1+(2-3*4)/5";
    message = write_in_vector(message1);

    for (int i = 0; i < message.size(); ++i) {
        if (message[i] != new_message[i]) {
            check = true;
            break;
        }
    }
    if (check)
        FAIL();
    else SUCCEED();

    char message2[] = "1+     2-3*4";
    ASSERT_ANY_THROW(write_in_vector(message2));

    char message3[] = "1+2-3*4/5    ";
    ASSERT_ANY_THROW(write_in_vector(message3));

    char message4[] = "1+2-3dsfs*4/5";
    ASSERT_ANY_THROW(write_in_vector(message4));
}

TEST (methodStackAndOut, expectedStackAndOut) {
    std::vector<char> stack;
    char message[] = "(8+2*5)/(1+1*2)";
    std::vector<char> result = {'8','2','5','*','+','1','1','2','*','+','/'};

    stack = StackAndOut(write_in_vector(message));

    if (result != StackAndOut(write_in_vector(message)))
        FAIL();
    else SUCCEED();

    std::vector<char> stack1;
    char message1[] = "(6+9-4)/(1+1*2)+1";
    std::vector<char> result1 = {'6','9','+','4','-','1','1','2','*','+','/', '1','+'};

    if (result1 != StackAndOut(write_in_vector(message1)))
        FAIL();
    else SUCCEED();

    std::vector<char> stack2;
    char message2[] = "(1+5)*(2-3*4)/5-(5-7)";
    std::vector<char> result2 = {'1','5','+','2','3','4','*','-','*','5','/','5','7','-','-'};

    if (result2 != StackAndOut(write_in_vector(message2)))
        FAIL();
    else SUCCEED();

}

TEST (methodCalculate, expectedCalculate) {
    char message[] = "(6+9-4)/(1+1*2)+1";
    ASSERT_NEAR(4.66667, calculate(StackAndOut(write_in_vector(message))), 0.00003);
    //ASSERT_FLOAT_EQ(4.66667, calculate(StackAndOut(write_in_vector(message))));

    char message1[] = "(8+2*5)/(1+1*2)";
    ASSERT_FLOAT_EQ(6, calculate(StackAndOut(write_in_vector(message1))));

    char message2[] = "1+(2-3*4)/5";
    ASSERT_FLOAT_EQ(-1, calculate(StackAndOut(write_in_vector(message2))));

    char message3[] = "(1+5)*(2-3*4)/5-(5-7)";
    ASSERT_FLOAT_EQ(-10, calculate(StackAndOut(write_in_vector(message3))));
}

int main(int argc, char **argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}