/*
 * 표준 라이브러리 정렬 (std::sort / std::stable_sort)
 * - std::sort        : 평균·최악 O(N log N), 안정 정렬 아님
 * - std::stable_sort : O(N log N), 같은 키는 원래 순서 유지 (파이썬 sort 와 같은 성질)
 * - 비교 함수(람다)로 기준을 바꿀 수 있다 → 파이썬의 key= 에 해당
 *
 * Python 버전: Warming-Up-for-Python/03_algorithms/sorting/sort_builtin.py
 */
#include <algorithm>
#include <functional>
#include <iostream>
#include <string>
#include <utility>
#include <vector>

using Person = std::pair<int, std::string>;  // (나이, 이름)

void print(const std::vector<Person>& people) {
    for (const auto& [age, name] : people) std::cout << '(' << age << ", '" << name << "')\n";
}

int main() {
    // 1) 기본 정렬 (오름차순)
    std::vector<int> data = {8, 5, 4, 7, 2};
    std::sort(data.begin(), data.end());
    for (int x : data) std::cout << x << '\n';
    std::cout << "---------------\n";

    // 2) 기준(key) 지정 + 안정 정렬: 나이만 비교, 나이가 같으면 입력 순서 유지
    std::vector<Person> people = {{25, "Na"}, {20, "Kim"}, {23, "Seo"}, {28, "Park"}, {20, "Ahn"}};
    std::stable_sort(people.begin(), people.end(),
                     [](const Person& a, const Person& b) { return a.first < b.first; });
    print(people);  // (20, 'Kim') 이 (20, 'Ahn') 보다 앞
    std::cout << "---------------\n";

    // 3) pair 기본 비교: first → second 순으로 사전식 비교
    people = {{25, "Na"}, {20, "Kim"}, {23, "Seo"}, {28, "Park"}, {20, "Ahn"}};
    std::sort(people.begin(), people.end());
    print(people);  // (20, 'Ahn') 이 (20, 'Kim') 보다 앞
    std::cout << "---------------\n";

    // 4) 내림차순
    std::sort(data.begin(), data.end(), std::greater<int>());
    for (int x : data) std::cout << x << ' ';
    std::cout << '\n';
}
