#ifndef PITCHQUEST_RINGBUFFER_HPP_
#define PITCHQUEST_RINGBUFFER_HPP_

#include <format>
#include <vector>

namespace PitchQuestTest {

class RingBuffer_TestFriend;

}   // namespace PitchQuestTest

namespace PitchQuest {

template <typename T>
class RingBuffer {

    friend class PitchQuestTest::RingBuffer_TestFriend;

    public:
        explicit RingBuffer(size_t capacity)
            : m_vector(capacity), m_capacity{capacity}, m_size{0}, m_front{0}, m_back{0} {
        }
        ~RingBuffer() = default;

        constexpr size_t capacity() const noexcept {
            return m_capacity;
        }

        size_t size() const noexcept {
            return m_size;
        }

        bool empty() const noexcept {
            return m_size == 0;
        }

        bool full() const noexcept {
            return m_size == m_capacity;
        }
        
        void push_back(const T& value) {

            if (full()) {
                throw std::overflow_error("RingBuffer is already full");
            }

            m_vector.at(m_back) = value;
            m_back = ++m_back % m_capacity;
            ++m_size;
        }

        void pop_front() {

            if (empty()) {
                throw std::underflow_error("RingBuffer is already empty");
            }

            m_front = ++m_front % m_capacity;
            --m_size;
        }

        T& operator[](size_t index) {

            if (index >= m_size) {
                throw std::out_of_range(std::format("Index {} outside [0, {})", index, m_size));
            }

            return m_vector[(index + m_front) % m_capacity];
        }

    private:
        std::vector<T> m_vector;
        const size_t m_capacity;
        size_t m_size;
        size_t m_front;
        size_t m_back;
};

}   // namespace PitchQuest

#endif  // PITCHQUEST_CLI_HPP_
