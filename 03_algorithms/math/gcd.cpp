/*
 * 최대공약수 (GCD, Greatest Common Divisor) — 유클리드 호제법
 * - gcd(a, b) = gcd(b, a % b),  gcd(a, 0) = a
 * - 시간 복잡도: O(log min(a, b))
 * - C++17 부터는 <numeric> 의 std::gcd 를 쓰면 된다
 *
 * Python 버전: Warming-Up-for-Python/03_algorithms/math/gcd.py
 */
#include <cassert>
#include <iostream>
#include <numeric>

long long gcd(long long a, long long b) {
    while (b != 0) {
        const long long mod = a % b;
        a = b;
        b = mod;
    }
    return a;
}

int main() {
    std::cout << gcd(24, 32) << '\n';  // 8
    assert(gcd(24, 32) == std::gcd(24, 32));
}
