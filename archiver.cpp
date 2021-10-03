#include "archiver.h"
#include "priority_queue/priority_queue.h"
#include "trie/trie.h"

#include <climits>
#include <vector>

Compressor::Compressor(std::ostream& os) {
    writer_.SetOutputStream(os);
}

void Compressor::AddFile(std::istream& is) {
    reader_.SetInputStream(is);
    std::vector<size_t> cnt_bytes(1 << 8, 0);
    while (!reader_.ReachedEOF()) {
        cnt_bytes[reader_.GetNBit(8)]++;
    }

    PriorityQueue<std::pair<size_t, Trie::Node*>> pq;
    Trie trie;
    for (size_t i = 0; i < (1 << 8); ++i) {
        if (cnt_bytes[i]) {
            pq.Insert({cnt_bytes[i], trie.InsertNode(true)});
        }
    }
    while (pq.Size() > 1) {
        auto v1 = pq.PopFront(), v2 = pq.PopFront();
        pq.Insert({v1.first + v2.first, trie.InsertNode(false, v1.second, v2.second)});
    }
    trie.SetRoot(pq.PopFront().second);


}