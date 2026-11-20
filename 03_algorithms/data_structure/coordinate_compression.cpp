/*
 * 좌표 압축 (Coordinate Compression)
 * - 값의 범위는 크지만 개수가 적을 때, 값을 0..K-1 의 순위로 바꾼다
 * - 정렬 + 중복 제거(unique) + lower_bound
 * - 시간 복잡도: O(N log N)
 *
 * Python 버전: Warming-Up-for-Python/03_algorithms/data_structure/coordinate_compression.py
 */
#include <algorithm>
#include <cassert>
#include <iostream>
#include <map>
#include <vector>

// 방법 1: map 으로 값 → 순위 매핑을 만든다 (매핑 정보가 필요할 때)
std::vector<int> compress_with_map(const std::vector<int>& arr, std::map<int, int>& mapping) {
    for (int x : arr) mapping[x];  // 키만 넣기 (map 은 자동 정렬 + 중복 제거)
    int rank = 0;
    for (auto& [value, idx] : mapping) idx = rank++;

    std::vector<int> compressed;
    compressed.reserve(arr.size());
    for (int x : arr) compressed.push_back(mapping[x]);
    return compressed;
}

// 방법 2: sort + unique + lower_bound (가장 많이 쓰는 C++ 관용구)
std::vector<int> compress(const std::vector<int>& arr) {
    std::vector<int> sorted_unique = arr;
    std::sort(sorted_unique.begin(), sorted_unique.end());
    sorted_unique.erase(std::unique(sorted_unique.begin(), sorted_unique.end()), sorted_unique.end());

    std::vector<int> compressed;
    compressed.reserve(arr.size());
    for (int x : arr) {
        const auto it = std::lower_bound(sorted_unique.begin(), sorted_unique.end(), x);
        compressed.push_back(static_cast<int>(it - sorted_unique.begin()));
    }
    return compressed;
}

void print(const std::vector<int>& v) {
    std::cout << '[';
    for (std::size_t i = 0; i < v.size(); ++i) std::cout << (i ? ", " : "") << v[i];
    std::cout << "]\n";
}

int main() {
    const std::vector<int> data = {2492, 10, 99999999, 10, -500, 2492};  // 격차는 크지만 개수는 적음
    std::cout << "원본 데이터: ";
    print(data);

    std::map<int, int> mapping;
    const auto compressed_map = compress_with_map(data, mapping);
    std::cout << "\n[map 방식]\n압축된 결과: ";
    print(compressed_map);
    std::cout << "매핑 정보(Val->Idx): {";
    bool first = true;
    for (const auto& [value, idx] : mapping) {
        std::cout << (first ? "" : ", ") << value << ": " << idx;
        first = false;
    }
    std::cout << "}\n";

    const auto compressed = compress(data);
    std::cout << "\n[lower_bound 방식]\n압축된 결과: ";
    print(compressed);

    // -500 -> 0, 10 -> 1, 2492 -> 2, 99999999 -> 3
    assert((compressed == std::vector<int>{2, 1, 3, 1, 0, 2}));
    assert(compressed == compressed_map);
}
