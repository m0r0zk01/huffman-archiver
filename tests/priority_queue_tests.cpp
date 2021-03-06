#include "../priority_queue/priority_queue.h"

#include <algorithm>
#include <gtest/gtest.h>
#include <iostream>

TEST(PriorityQueueTest, TestSize) {
    PriorityQueue<std::pair<double, int>> pq;
    pq.Insert({10.5, 1});
    pq.Insert({20.3, 2});
    pq.Insert({123, 123});
    pq.PopFront();
    ASSERT_EQ(pq.Size(), 2);
    pq.PeekFront();
    ASSERT_EQ(pq.Size(), 2);
    pq.PopFront();
    pq.PopFront();
    ASSERT_ANY_THROW(pq.PeekFront());
    ASSERT_ANY_THROW(pq.PopFront());
    ASSERT_TRUE(pq.Empty());
}

TEST(PriorityQueueTest, TestSort) {
    std::vector<int> values;
    PriorityQueue<int> pq;
    for (size_t i = 0; i < 1000; ++i) {
        int x = rand();
        pq.Insert(x);
        values.push_back(x);
    }
    std::sort(values.rbegin(), values.rend());
    while (!values.empty()) {
        ASSERT_TRUE(values.back() == pq.PopFront());
        values.pop_back();
    }
    ASSERT_TRUE(pq.Empty());
}

int main(int argc, char** argv) {
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}