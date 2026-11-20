/*
 * 소인수분해 (Prime Factorization)
 * - 2 부터 √x 까지 나누면서, 나누어 떨어지는 동안 계속 나눈다
 * - 마지막에 1 보다 큰 수가 남으면 그 자체가 소인수
 * - 시간 복잡도: O(√x)
 * - 참고: 1 은 소수도 합성수도 아니다 → 빈 결과
 *
 * Python 버전: Warming-Up-for-Python/03_algorithms/math/prime_factorization.py
 */
#include <cassert>
#include <iostream>
#include <utility>
#include <vector>

using Factor = std::pair<long long, int>;  // (소인수, 지수)

std::vector<Factor> prime_factorization(long long x) {
    std::vector<Factor> result;
    for (long long i = 2; i * i <= x; ++i) {
        if (x % i != 0) continue;
        int count = 0;
        while (x % i == 0) {  // i 로 몇 번 연속 나눌 수 있는지
            ++count;
            x /= i;
        }
        result.emplace_back(i, count);
    }
    if (x > 1) result.emplace_back(x, 1);
    return result;
}

void print(const std::vector<Factor>& factors) {
    std::cout << '[';
    for (std::size_t i = 0; i < factors.size(); ++i) {
        std::cout << (i ? ", " : "") << '(' << factors[i].first << ", " << factors[i].second << ')';
    }
    std::cout << "]\n";
}

int main() {
    print(prime_factorization(32));  // [(2, 5)]
    print(prime_factorization(45));  // [(3, 2), (5, 1)]
    print(prime_factorization(75));  // [(3, 1), (5, 2)]

    assert(prime_factorization(1).empty());
}
