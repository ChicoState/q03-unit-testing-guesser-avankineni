#include <gtest/gtest.h>
#include "Guesser.h"

class GuesserTest : public ::testing::Test {
protected:
    Guesser *guesser;

    GuesserTest(){} //constructor runs before each test
    virtual ~GuesserTest(){} //destructor cleans up after tests

    virtual void SetUp() { //sets up before each test (after constructor)
        guesser = new Guesser("password");
    }

    virtual void TearDown() { //clean up after each test, (before destructor)
        delete guesser;
    }
};

TEST_F(GuesserTest, CorrectGuess) {
    ASSERT_TRUE(guesser->match("password"));
    ASSERT_EQ(guesser->remaining(), 3);
}

TEST_F(GuesserTest, IncorrectGuess) {
    ASSERT_FALSE(guesser->match("pass"));
    ASSERT_EQ(guesser->remaining(), 2);
}

TEST_F(GuesserTest, DistanceFunction) {
    ASSERT_EQ(guesser->distance("passw"), 1);
    ASSERT_EQ(guesser->distance("passwords"), 1);
}

TEST_F(GuesserTest, ExceededGuessLimit) {
    guesser->match("pass");
    guesser->match("pass");
    guesser->match("pass");
    ASSERT_EQ(guesser->remaining(), 0);
    ASSERT_FALSE(guesser->match("password"));
}

TEST_F(GuesserTest, ResetRemainingOnCorrectGuess) {
    guesser->match("pass");
    guesser->match("pass");
    guesser->match("password");
    ASSERT_EQ(guesser->remaining(), 3);
}
