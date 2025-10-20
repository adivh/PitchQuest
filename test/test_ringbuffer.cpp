#include "gtest/gtest.h"

#include "ringbuffer.hpp"
#include "ringbuffer_testfriend.hpp"

using namespace PitchQuest;

TEST(RingBufferTest, CapacityMatches) {
    RingBuffer<int> buffer {1024};
    EXPECT_EQ(buffer.capacity(), 1024);
    EXPECT_EQ(buffer.capacity(), PitchQuestTest::RingBuffer_TestFriend::vector_capacity(buffer));
}

TEST(RingBufferTest, SizeZeroAtCreation) {
    RingBuffer<char> buffer {32};
    EXPECT_EQ(buffer.size(), 0);
}

TEST(RingBufferTest, EmptyAtCreation) {
    RingBuffer<double> buffer {4};
    EXPECT_TRUE(buffer.empty());
}

TEST(RingBufferTest, Buffer1Full) {
    RingBuffer<long> buffer {1};
    buffer.push_back(0l);
    EXPECT_TRUE(buffer.full());
}

TEST(RingBufferTest, Buffer4Full) {
    RingBuffer<short> buffer {4};
    buffer.push_back(1);
    buffer.push_back(2);
    buffer.push_back(3);
    buffer.push_back(4);
    EXPECT_TRUE(buffer.full());
}

TEST(RingBufferTest, NotFull) {
    RingBuffer<bool> buffer {8};
    EXPECT_FALSE(buffer.full());

    buffer.push_back(true);
    EXPECT_FALSE(buffer.full());

    buffer.push_back(false);
    EXPECT_FALSE(buffer.full());

    buffer.push_back(true);
    buffer.push_back(true);
    buffer.push_back(true);
    buffer.push_back(true);
    buffer.push_back(true);
    EXPECT_FALSE(buffer.full());
}

TEST(RingBufferTest, PushBackIncreasesSize) {
    RingBuffer<float> buffer {64};
    buffer.push_back(1.0f);
    EXPECT_EQ(buffer.size(), 1);

    buffer.push_back(4.0f);
    EXPECT_EQ(buffer.size(), 2);

    buffer.push_back(3.0f);
    buffer.push_back(2.0f);
    EXPECT_EQ(buffer.size(), 4);
}

TEST(RingBufferTest, PushBackIncreasesBack) {
    RingBuffer<char> buffer {8};
    EXPECT_EQ(PitchQuestTest::RingBuffer_TestFriend::back(buffer), 0);

    buffer.push_back('a');
    EXPECT_EQ(PitchQuestTest::RingBuffer_TestFriend::back(buffer), 1);

    buffer.push_back('b');
    EXPECT_EQ(PitchQuestTest::RingBuffer_TestFriend::back(buffer), 2);
}
    
TEST(RingBufferTest, PopFrontDecreasesSize) {
    RingBuffer<bool> buffer {8};
    EXPECT_EQ(buffer.size(), 0);

    buffer.push_back(true);
    buffer.push_back(true);
    buffer.push_back(true);
    buffer.push_back(true);
    EXPECT_EQ(buffer.size(), 4);

    buffer.pop_front();
    EXPECT_EQ(buffer.size(), 3);

    buffer.pop_front();
    EXPECT_EQ(buffer.size(), 2);
 
    buffer.pop_front();
    EXPECT_EQ(buffer.size(), 1);

    buffer.pop_front();
    EXPECT_EQ(buffer.size(), 0);
}

TEST(RingBufferTest, PopFrontIncreasesFront) {
    RingBuffer<int> buffer {8};
    buffer.push_back(0);
    buffer.push_back(1);
    buffer.pop_front();
    EXPECT_EQ(PitchQuestTest::RingBuffer_TestFriend::front(buffer), 1);

    buffer.pop_front();
    EXPECT_EQ(PitchQuestTest::RingBuffer_TestFriend::front(buffer), 2);
}

TEST(RingBufferTest, FrontAndBackWrapAround) {
    RingBuffer<char> buffer {4};
    buffer.push_back('a');
    buffer.push_back('b');
    buffer.push_back('c');
    buffer.push_back('d');
    EXPECT_EQ(PitchQuestTest::RingBuffer_TestFriend::back(buffer), 0);

    buffer.pop_front();
    buffer.pop_front();
    buffer.pop_front();
    EXPECT_EQ(PitchQuestTest::RingBuffer_TestFriend::front(buffer), 3);

    buffer.push_back('e');
    buffer.push_back('f');
    buffer.push_back('g');
    EXPECT_EQ(PitchQuestTest::RingBuffer_TestFriend::back(buffer), 3);

    buffer.pop_front();
    EXPECT_EQ(PitchQuestTest::RingBuffer_TestFriend::front(buffer), 0);

    buffer.pop_front();
    EXPECT_EQ(PitchQuestTest::RingBuffer_TestFriend::front(buffer), 1);

    buffer.pop_front();
    EXPECT_EQ(PitchQuestTest::RingBuffer_TestFriend::front(buffer), 2);
}
    

TEST(RingBufferTest, OpNoOffset) {
    RingBuffer<double> buffer {8};
    buffer.push_back(0.0);
    buffer.push_back(1.0);
    buffer.push_back(2.0);
    buffer.push_back(3.0);

    EXPECT_EQ(buffer[0], PitchQuestTest::RingBuffer_TestFriend::vector_at(buffer, 0));
    EXPECT_EQ(buffer[1], PitchQuestTest::RingBuffer_TestFriend::vector_at(buffer, 1));
    EXPECT_EQ(buffer[2], PitchQuestTest::RingBuffer_TestFriend::vector_at(buffer, 2));
    EXPECT_EQ(buffer[3], PitchQuestTest::RingBuffer_TestFriend::vector_at(buffer, 3));
}

TEST(RingBufferTest, Op2Offset) {
    RingBuffer<double> buffer {8};
    buffer.push_back(0.0);
    buffer.push_back(1.0);
    buffer.push_back(2.0);
    buffer.push_back(3.0);
    buffer.push_back(4.0);
    buffer.push_back(5.0);
    buffer.pop_front();
    buffer.pop_front();

    EXPECT_EQ(buffer[0], PitchQuestTest::RingBuffer_TestFriend::vector_at(buffer, 2));
    EXPECT_EQ(buffer[1], PitchQuestTest::RingBuffer_TestFriend::vector_at(buffer, 3));
    EXPECT_EQ(buffer[2], PitchQuestTest::RingBuffer_TestFriend::vector_at(buffer, 4));
    EXPECT_EQ(buffer[3], PitchQuestTest::RingBuffer_TestFriend::vector_at(buffer, 5));
}

TEST(RingBufferTest, SetElement) {
    RingBuffer<char> buffer {4};
    buffer.push_back('A');
    buffer.push_back('B');
    buffer[0] = 'C';
    EXPECT_EQ(buffer[0], 'C');
    EXPECT_EQ(PitchQuestTest::RingBuffer_TestFriend::vector_at(buffer, 0), 'C');
}

TEST(RingBufferTest, SetElement2Offset) {
    RingBuffer<char> buffer {4};
    buffer.push_back('z');
    buffer.push_back('z');
    buffer.push_back('z');
    buffer.push_back('z');
    buffer.pop_front();
    buffer.pop_front();
    buffer[0] = 'a';
    EXPECT_EQ(buffer[0], 'a');
    EXPECT_EQ(PitchQuestTest::RingBuffer_TestFriend::vector_at(buffer, 2), 'a');
}

TEST(RingBufferTest, PushBackFull) {
    RingBuffer<int> buffer {2};
    buffer.push_back(1);
    buffer.push_back(2);
    EXPECT_THROW(buffer.push_back(3), std::overflow_error);
}

TEST(RingBufferTest, PopFrontEmpty) {
    RingBuffer<short> buffer {2};
    EXPECT_THROW(buffer.pop_front(), std::underflow_error);
}

TEST(RingBufferTest, PopFrontUntilUnderflow) {
    RingBuffer<long> buffer {4};
    buffer.push_back(2);
    buffer.push_back(1);
    buffer.push_back(0);
    buffer.pop_front();
    buffer.pop_front();
    buffer.pop_front();
    EXPECT_THROW(buffer.pop_front(), std::underflow_error);
}

TEST(RingBufferTest, AccessInRange) {
    RingBuffer<int> buffer {4};
    buffer.push_back(0);
    buffer.push_back(0);
    buffer.push_back(0);
    buffer.push_back(0);
    EXPECT_NO_THROW(buffer[0]);
    EXPECT_NO_THROW(buffer[1]);
    EXPECT_NO_THROW(buffer[2]);
    EXPECT_NO_THROW(buffer[3]);

    buffer.pop_front();
    EXPECT_NO_THROW(buffer[0]);
    EXPECT_NO_THROW(buffer[1]);
    EXPECT_NO_THROW(buffer[2]);

    buffer.pop_front();
    buffer.pop_front();
    buffer.push_back(0);
    buffer.push_back(0);
    buffer.push_back(0);
    buffer.pop_front();
    buffer.pop_front();
    EXPECT_NO_THROW(buffer[0]);
    EXPECT_NO_THROW(buffer[1]);
}

TEST(RingBufferTest, AccessOutOfRange) {
    RingBuffer<long> buffer {4};
    EXPECT_THROW(buffer[0], std::out_of_range);

    buffer.push_back(0l);
    buffer.push_back(0l);
    buffer.push_back(0l);
    EXPECT_THROW(buffer[3], std::out_of_range);
    EXPECT_THROW(buffer[4], std::out_of_range);

    buffer.pop_front();
    EXPECT_THROW(buffer[2], std::out_of_range);
    EXPECT_THROW(buffer[3], std::out_of_range);
} 
