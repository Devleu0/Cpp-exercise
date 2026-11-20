/*
 * KMP 문자열 매칭 (Knuth–Morris–Pratt)
 * - pi[i] = pattern[0..i] 에서 "접두사 == 접미사" 인 가장 긴 길이 (실패 함수)
 * - 불일치 시 pi 를 이용해 이미 비교한 부분을 건너뛴다
 * - 시간 복잡도: O(N + M)
 * - 겹치는 매칭도 모두 찾는다 (예: "ABABABABC" 에서 "ABAB" → 0, 2, 4)
 *
 * Python 버전: Warming-Up-for-Python/03_algorithms/string/kmp.py
 */
#include <cassert>
#include <iostream>
#include <string>
#include <vector>

std::vector<int> get_pi(const std::string& pattern) {
    const int m = static_cast<int>(pattern.size());
    std::vector<int> pi(m, 0);
    int j = 0;
    for (int i = 1; i < m; ++i) {
        while (j > 0 && pattern[i] != pattern[j]) j = pi[j - 1];  // 이전 일치 상태로 되돌림
        if (pattern[i] == pattern[j]) pi[i] = ++j;
    }
    return pi;
}

std::vector<int> kmp_search(const std::string& text, const std::string& pattern) {
    const std::vector<int> pi = get_pi(pattern);
    const int n = static_cast<int>(text.size());
    const int m = static_cast<int>(pattern.size());
    std::vector<int> result;
    int j = 0;
    for (int i = 0; i < n; ++i) {
        while (j > 0 && text[i] != pattern[j]) j = pi[j - 1];  // 실패 함수로 점프
        if (text[i] != pattern[j]) continue;
        if (j == m - 1) {             // 패턴 끝까지 일치
            result.push_back(i - m + 1);
            j = pi[j];                // 다음(겹치는) 매칭 준비
        } else {
            ++j;
        }
    }
    return result;
}

void print(const std::vector<int>& v) {
    std::cout << '[';
    for (std::size_t i = 0; i < v.size(); ++i) std::cout << (i ? ", " : "") << v[i];
    std::cout << "]\n";
}

int main() {
    const std::string text = "ABABABABC";
    const std::string pattern = "ABAB";

    std::cout << "텍스트: " << text << '\n';
    std::cout << "패턴: " << pattern << '\n';
    std::cout << "실패 함수(Pi): ";
    print(get_pi(pattern));  // [0, 0, 1, 2]

    const auto matches = kmp_search(text, pattern);
    std::cout << "매칭된 인덱스: ";
    print(matches);          // [0, 2, 4]

    assert((matches == std::vector<int>{0, 2, 4}));
}
