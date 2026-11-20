/*
 * 소수 판정 (Primality Test)
 * - 2 부터 √x 까지 나누어 떨어지는 수가 있는지 확인
 * - 시간 복잡도: O(√x)
 * - i * i <= x 로 비교해 sqrt 의 실수 오차를 피한다
 * - 참고: Python 버전은 1 을 소수로 판정하는 문제가 있어 x < 2 처리를 추가함
 *
 * Python 버전: Warming-Up-for-Python/03_algorithms/math/is_prime.py
 */
#include <cassert>
#include <iostream>

bool is_prime(long long x) {
    if (x < 2) return false;  // 0, 1 은 소수가 아님
    for (long long i = 2; i * i <= x; ++i) {
        if (x % i == 0) return false;
    }
    return true;
}

int main() {
    std::cout << std::boolalpha;
    std::cout << is_prime(4) << '\n';  // false
    std::cout << is_prime(7) << '\n';  // true

    assert(!is_prime(1));
    assert(is_prime(2));
    assert(is_prime(1'000'000'007));
}
