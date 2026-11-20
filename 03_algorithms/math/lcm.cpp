/*
 * 최소공배수 (LCM, Least Common Multiple)
 * - lcm(a, b) = a / gcd(a, b) * b   (a * b 를 먼저 하면 오버플로 위험)
 * - C++17 부터는 <numeric> 의 std::lcm 을 쓰면 된다
 *
 * Python 버전: Warming-Up-for-Python/03_algorithms/math/lcm.py
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

long long lcm(long long a, long long b) {
    return a / gcd(a, b) * b;
}

int main() {
    std::cout << lcm(24, 32) << '\n';  // 96
    assert(lcm(24, 32) == std::lcm(24, 32));
}
