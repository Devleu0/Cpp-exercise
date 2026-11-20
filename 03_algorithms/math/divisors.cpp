/*
 * 약수 구하기 (All Divisors)
 * - i 가 약수면 x / i 도 약수 → √x 까지만 확인
 * - 시간 복잡도: O(√x)
 *
 * Python 버전: Warming-Up-for-Python/03_algorithms/math/divisors.py
 */
#include <algorithm>
#include <iostream>
#include <vector>

std::vector<long long> divisors(long long x) {
    std::vector<long long> result;
    for (long long i = 1; i * i <= x; ++i) {
        if (x % i == 0) {
            result.push_back(i);
            if (i * i != x) result.push_back(x / i);  // 제곱수일 때 중복 방지
        }
    }
    return result;
}

void print(const std::vector<long long>& v) {
    std::cout << '[';
    for (std::size_t i = 0; i < v.size(); ++i) std::cout << (i ? ", " : "") << v[i];
    std::cout << "]\n";
}

int main() {
    auto result = divisors(12);
    print(result);  // [1, 12, 2, 6, 3, 4]

    std::sort(result.begin(), result.end());
    print(result);  // [1, 2, 3, 4, 6, 12]  (정렬이 필요하면 따로)
}
