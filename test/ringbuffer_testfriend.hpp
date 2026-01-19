#ifndef PITCHQUESTTEST_RINGBUFFER_TESTFRIEND_HPP_
#define PITCHQUESTTEST_RINGBUFFER_TESTFRIEND_HPP_

#include "ringbuffer.hpp"

namespace PitchQuestTest {

class RingBuffer_TestFriend {
    public:
        RingBuffer_TestFriend() = delete;
        ~RingBuffer_TestFriend() = delete;

        template <typename T>
        static size_t vector_capacity(PitchQuest::RingBuffer<T>& buffer) {
            return buffer.m_vector.capacity();
        }

        template <typename T>
        static T& vector_at(PitchQuest::RingBuffer<T>& buffer, size_t index) {
            return buffer.m_vector.at(index);
        }

        template <typename T>
        static size_t front(PitchQuest::RingBuffer<T>& buffer) {
            return buffer.m_front;
        }

        template <typename T>
        static size_t back(PitchQuest::RingBuffer<T>& buffer) {
            return buffer.m_back;
        }
};

}   // namespace PitchQuestTest

#endif  // PITCHQUESTTEST_RINGBUFFER_TESTFRIEND_HPP_
