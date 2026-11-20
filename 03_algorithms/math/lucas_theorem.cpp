/*
 * 이항 계수 nCr mod p — 페르마의 소정리 & 뤼카 정리 (Lucas Theorem)
 * - 페르마: p 가 소수이면 a^(p-2) ≡ a^(-1) (mod p)
 *           → nCr = n! * (r! (n-r)!)^(p-2)  (n < p 일 때, 팩토리얼 전처리 O(N))
 * - 뤼카: n, r 을 p 진법으로 나타낸 각 자릿수의 조합을 곱한다
 *           → n, r 이 매우 크고 p 가 작을 때 사용, O(p log_p n)
 *
 * Python 버전: Warming-Up-for-Python/03_algorithms/math/lucas_theorem.py
 */
#include <cassert>
#include <iostream>
#include <vector>

// 분할 정복 거듭제곱: a^b mod m, O(log b)
long long power(long long a, long long b, long long m) {
    long long res = 1;
    a %= m;
    while (b > 0) {
        if (b & 1) res = res * a % m;
        a = a * a % m;
        b >>= 1;
    }
    return res;
}

// 팩토리얼 전처리 + 페르마의 소정리 (mod 는 소수, n < mod)
class Combination {
public:
    Combination(int max_n, long long mod) : mod_(mod), fact_(max_n + 1, 1) {
        for (int i = 2; i <= max_n; ++i) fact_[i] = fact_[i - 1] * i % mod_;
    }

    long long nCr(int n, int r) const {
        if (r < 0 || r > n) return 0;
        const long long numerator = fact_[n];
        const long long denominator = fact_[r] * fact_[n - r] % mod_;
        return numerator * power(denominator, mod_ - 2, mod_) % mod_;
    }

private:
    long long mod_;
    std::vector<long long> fact_;
};

// 뤼카 정리: nCr % p = Π (n_i C r_i) % p   (n_i, r_i: p 진법의 i 번째 자릿수)
long long lucas(long long n, long long r, long long p) {
    if (r == 0) return 1;

    const long long cur_n = n % p;
    const long long cur_r = r % p;
    if (cur_r > cur_n) return 0;

    // 한 자릿수 조합 (cur_n < p) 은 직접 계산
    long long numerator = 1;
    long long denominator = 1;
    for (long long i = 0; i < cur_r; ++i) {
        numerator = numerator * (cur_n - i) % p;
        denominator = denominator * (i + 1) % p;
    }
    const long long base_comb = numerator * power(denominator, p - 2, p) % p;

    return base_comb * lucas(n / p, r / p, p) % p;  // 다음 자릿수
}

int main() {
    const long long MOD = 13;  // 작은 소수

    // 1) 페르마: 5C2 = 10 → 10 % 13 = 10
    const Combination solver(12, MOD);
    std::cout << "[Fermat] 5C2 % " << MOD << " = " << solver.nCr(5, 2) << '\n';

    // 2) 뤼카: 100C5 % 13
    //    100 = 7*13 + 9,  5 = 0*13 + 5  →  (9C5) * (7C0) = 126 * 1 → 126 % 13 = 9
    std::cout << "[Lucas] 100C5 % " << MOD << " = " << lucas(100, 5, MOD) << '\n';

    // 검증: 100C5 = 75287520 → % 13 = 9
    assert(75287520 % MOD == lucas(100, 5, MOD));
}
