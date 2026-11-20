/*
 * 누적 합 (Prefix Sum)
 * - prefix[i] = data[0] + ... + data[i-1]  (prefix[0] = 0)
 * - 구간 [left, right] (1-based) 의 합 = prefix[right] - prefix[left - 1]
 * - 전처리 O(N), 구간 합 질의 O(1)
 *
 * Python 버전: Warming-Up-for-Python/03_algorithms/techniques/prefix_sum.py
 */
#include <iostream>
#include <numeric>
#include <vector>

std::vector<long long> make_prefix_sum(const std::vector<int>& data) {
    std::vector<long long> prefix(data.size() + 1, 0);
    for (std::size_t i = 0; i < data.size(); ++i) prefix[i + 1] = prefix[i] + data[i];
    return prefix;
}

int main() {
    const std::vector<int> data = {10, 20, 30, 40, 50};
    const auto prefix = make_prefix_sum(data);

    const int left = 2;
    const int right = 4;
    std::cout << prefix[right] - prefix[left - 1] << '\n';  // 20 + 30 + 40 = 90

    // 표준 라이브러리: std::partial_sum 으로 한 줄에 만들 수도 있다 (prefix[0]=0 은 직접)
    std::vector<long long> prefix2(data.size() + 1, 0);
    std::partial_sum(data.begin(), data.end(), prefix2.begin() + 1);
    std::cout << prefix2[right] - prefix2[left - 1] << '\n';  // 90
}
