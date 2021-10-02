#pragma once

#include <vector>

template <typename T>
class PriorityQueue {
public:
    PriorityQueue() {}
    PriorityQueue(const std::vector<T>& elements) {
        for (const auto& element : elements) {
            Insert(element);
        }
    }

    void Insert(const T& insert_value) {
        priority_queue_.push_back(insert_value);
        SiftUp();
    }

    T& GetFront() {
        if (Empty()) {
            throw "Trying to get element from empty priority queue";
        }

        return priority_queue_.front();
    }

    T PopFront() {
        if (Empty()) {
            throw "Trying to pop element from empty priority queue";
        }

        T res = priority_queue_.front();
        std::swap(priority_queue_.front(), priority_queue_.back());
        priority_queue_.pop_back();
        SiftDown();
        return res;
    }

    inline size_t Size() const {
        return priority_queue_.size();
    }

    inline bool Empty() const {
        return Size() == 0;
    }

    void Print() {
        for (const auto& i : priority_queue_) {
            std::cout << i << ' ';
        }
        std::cout << '\n';
    }

private:
    void SiftUp() {
        if (Empty()) {
            return;
        }

        size_t ptr = Size() - 1;
        while (ptr) {
            size_t parent = (ptr - 1) / 2;
            if (priority_queue_[ptr] > priority_queue_[parent]) {
                std::swap(priority_queue_[ptr], priority_queue_[parent]);
                ptr = parent;
            } else {
                break;
            }
        }
    }

    void SiftDown() {
        if (Empty()) {
            return;
        }

        size_t ptr = 0;
        while (2 * ptr + 1 < Size()) {
            size_t max_child = 2 * ptr + 1;
            if (max_child + 1 < Size()) {
                if (priority_queue_[max_child + 1] > priority_queue_[max_child]) {
                    max_child++;
                }
            }

            if (priority_queue_[ptr] < priority_queue_[max_child]) {
                std::swap(priority_queue_[ptr], priority_queue_[max_child]);
                ptr = max_child;
            } else {
                break;
            }
        }
    }

    void InsertNode(T insert_node) {
        priority_queue_.push_back(insert_node);
        SiftUp();
    }

    std::vector<T> priority_queue_;
};