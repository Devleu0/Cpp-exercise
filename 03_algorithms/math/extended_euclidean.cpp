/*
 * 확장 유클리드 호제법 (Extended Euclidean Algorithm) & 모듈러 역원
 * - ax + by = gcd(a, b) 를 만족하는 (g, x, y) 를 구한다
 * - a 와 m 이 서로소이면 a * x ≡ 1 (mod m) 인 x(모듈러 역원)가 존재
 * - 시간 복잡도: O(log min(a, b))
 *
 * Python 버전: Warming-Up-for-Python/03_algorithms/math/extended_euclidean.py
 */
#include <cassert>
#include <iostream>
#include <optional>
#include <tuple>

struct ExtGcdResult {
    long long g;  // gcd(a, b)
    long long x;
    long long y;
};

ExtGcdResult extended_gcd(long long a, long long b) {
    if (b == 0) return {a, 1, 0};  // a*1 + 0*0 = a

    const auto [g, x1, y1] = extended_gcd(b, a % b);
    // b*x1 + (a%b)*y1 = g
    // b*x1 + (a - (a/b)*b)*y1 = g
    // a*y1 + b*(x1 - (a/b)*y1) = g
    // 따라서 x = y1, y = x1 - (a/b)*y1
    return {g, y1, x1 - (a / b) * y1};
}

// a * x ≡ 1 (mod m) 인 x. 서로소가 아니면 역원 없음
std::optional<long long> mod_inverse(long long a, long long m) {
    const auto [g, x, y] = extended_gcd(a, m);
    (void)y;
    if (g != 1) return std::nullopt;
    return (x % m + m) % m;  // x 가 음수일 수 있으므로 양수로 보정
}

int main() {
    // 예제 1: 3x + 11y = gcd(3, 11) = 1
    const long long a = 3;
    const long long b = 11;
    const auto [g, x, y] = extended_gcd(a, b);
    std::cout << "Extended GCD(" << a << ", " << b << ") -> GCD: " << g << ", x: " << x << ", y: " << y << '\n';
    std::cout << "검증: " << a << '*' << x << " + " << b << '*' << y << " = " << a * x + b * y << '\n';

    // 예제 2: 3 * x ≡ 1 (mod 11) → 3 * 4 = 12 ≡ 1 이므로 4
    const auto inv = mod_inverse(a, b);
    assert(inv.has_value());
    std::cout << '\n' << a << "의 mod " << b << " 역원: " << *inv << '\n';
    assert((a * *inv) % b == 1);

    assert(!mod_inverse(4, 8).has_value());  // gcd(4, 8) = 4 → 역원 없음
}
