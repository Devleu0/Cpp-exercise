/*
 * lower_bound / upper_bound 활용 — 이상 · 이하 · 초과 · 미만 위치 찾기
 * - std::lower_bound(b, e, x) : x 이상인 첫 위치  (파이썬 bisect_left)
 * - std::upper_bound(b, e, x) : x 초과인 첫 위치  (파이썬 bisect_right)
 * - 시간 복잡도: O(log N), 배열은 정렬되어 있어야 함
 * - 조건을 만족하는 원소가 없으면 -1 반환
 *
 * Python 버전: Warming-Up-for-Python/03_algorithms/binary_search/bisect_usage.py
 */
#include <algorithm>
#include <cassert>
#include <iostream>
#include <vector>

using Vec = std::vector<int>;

int lower(const Vec& a, int x) {
    return static_cast<int>(std::lower_bound(a.begin(), a.end(), x) - a.begin());
}
int upper(const Vec& a, int x) {
    return static_cast<int>(std::upper_bound(a.begin(), a.end(), x) - a.begin());
}

// x 와 같은 값 중 가장 왼쪽
int index_of_x(const Vec& a, int x) {
    const int i = lower(a, x);
    return (i != static_cast<int>(a.size()) && a[i] == x) ? i : -1;
}

// x 미만인 값 중 가장 오른쪽
int index_of_less_than_x(const Vec& a, int x) {
    const int i = lower(a, x);
    return i ? i - 1 : -1;
}

// x 이하인 값 중 가장 오른쪽
int index_of_less_or_equal_x(const Vec& a, int x) {
    const int i = upper(a, x);
    return i ? i - 1 : -1;
}

// x 초과인 값 중 가장 왼쪽
int index_of_greater_than_x(const Vec& a, int x) {
    const int i = upper(a, x);
    return i != static_cast<int>(a.size()) ? i : -1;
}

// x 이상인 값 중 가장 왼쪽
int index_of_greater_or_equal_x(const Vec& a, int x) {
    const int i = lower(a, x);
    return i != static_cast<int>(a.size()) ? i : -1;
}

int main() {
    const Vec array = {1, 3, 5, 7, 9, 11, 13, 15, 17, 19};
    const int target = 13;

    const int result = index_of_x(array, target);
    if (result == -1) {
        std::cout << "None\n";
    } else {
        std::cout << result + 1 << '\n';  // 7
    }

    // 나머지 함수 동작 확인 (오른쪽 주석: 찾은 위치의 값)
    assert(index_of_less_than_x(array, 10) == 4);         // 9
    assert(index_of_less_or_equal_x(array, 11) == 5);     // 11
    assert(index_of_greater_than_x(array, 11) == 6);      // 13
    assert(index_of_greater_or_equal_x(array, 10) == 5);  // 11
    assert(index_of_less_than_x(array, 1) == -1);
    assert(index_of_greater_than_x(array, 19) == -1);

    // std::binary_search 는 존재 여부(bool)만 알려준다
    assert(std::binary_search(array.begin(), array.end(), 13));
}
