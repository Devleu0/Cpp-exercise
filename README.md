# ➕ Cpp-exercise
![C++ logo](https://img.shields.io/badge/C++-00599C?style=for-the-badge&logo=cplusplus&logoColor=white)

C++ 를 공부하면서 만든 학습 자료입니다. **C++ 기초 → 코테용 노트 → 알고리즘 구현** 순서로 구성했습니다.

| 폴더 | 내용 | 이런 사람에게 |
| --- | --- | --- |
| [01_basics](./01_basics) | C++ 문법 기초 (포인터 · OOP · STL 포함) | C++ 가 처음 |
| [02_ps_notes](./02_ps_notes) | 코딩 테스트용 치트시트 | 다른 언어는 익숙하고, 코테 전에 C++ 를 훑고 싶음 |
| [03_algorithms](./03_algorithms) | 알고리즘 · 자료구조 구현 코드 | 특정 알고리즘 구현을 보고 싶음 |
| [04_projects](./04_projects) | 콘솔 미니 프로젝트 | 배운 문법으로 작은 프로그램을 만들어 보고 싶음 |

---

## 01. Basics

순서대로 보면 됩니다.

1. [기본 문법 · 연산자 · 입출력 · 제어문](./01_basics/01_syntax_and_control_flow.md)
2. [함수 · 배열과 문자열 · 포인터와 참조](./01_basics/02_functions_arrays_pointers.md)
3. [클래스와 OOP (캡슐화 · 상속 · 다형성)](./01_basics/03_oop.md)
4. [템플릿 · STL · 예외 처리 · 파일 입출력](./01_basics/04_stl_and_file_io.md)
5. [모던 C++ 와 이후 학습 로드맵](./01_basics/05_modern_cpp_roadmap.md)
6. [배열 · 벡터 초기화](./01_basics/06_array_vector_init.md)
7. [STL 컨테이너 정리](./01_basics/07_containers.md)
8. [헤더 파일과 소스 파일](./01_basics/08_header_and_source.md)

## 02. PS Notes (코테 워밍업)

다른 언어(특히 Python)에 익숙한 개발자가 코테 전에 훑어보는 노트입니다. 시간이 없으면 1 → 2 → 4 순서로.

| # | 노트 | 내용 |
| --- | --- | --- |
| 1 | [입출력과 함정](./02_ps_notes/01_io_and_pitfalls.md) | 빠른 입출력, TLE 원인, 오버플로·UB 등 흔한 버그, 코테 템플릿 |
| 2 | [STL 알고리즘 치트시트](./02_ps_notes/02_stl_algorithms.md) | Python 내장함수 ↔ `<algorithm>`/`<numeric>`, 정렬 비교 함수, 정수 연산 함정 |
| 3 | [문자열 다루기](./02_ps_notes/03_strings.md) | 찾기 · 자르기 · 치환 · 변환 · 역방향 접근 |
| 4 | [라이브러리](./02_ps_notes/04_libraries.md) | Python 라이브러리 ↔ STL 대응표, 컨테이너, 자주 쓰는 조합, 상황별 추천 |
| 5 | [그래프 패턴](./02_ps_notes/05_graph_patterns.md) | BFS / DFS / 격자 BFS / 다익스트라 / 크루스칼 / 위상 정렬 템플릿 |
| 6 | [인덱스 · 네이밍](./02_ps_notes/06_naming.md) | 루프 변수 이름 짓는 법, C++ 에서 피해야 할 이름 |
| 7 | [출력 형식](./02_ps_notes/07_output_format.md) | `printf` · `iomanip` · `std::format` |
| 8 | [언어별 빠른 입출력](./02_ps_notes/08_fast_io_by_language.md) | C/C++/Java/Python/Rust 빠른 I/O |

**이럴 땐 여기**
* 입력이 많아서 느리다 → [입출력과 함정 §1, §3](./02_ps_notes/01_io_and_pitfalls.md)
* 답이 이상하게 음수가 나온다 / 큰 수에서만 틀린다 → [입출력과 함정 §4-1 오버플로](./02_ps_notes/01_io_and_pitfalls.md#4-1-정수-오버플로)
* 음수 나눗셈 / 나머지가 Python 과 다르다 → [STL 알고리즘 §6](./02_ps_notes/02_stl_algorithms.md#6-정수-연산-함정)
* 최소 힙 / lower_bound 가 필요하다 → [라이브러리 · 한눈에 보기](./02_ps_notes/04_libraries.md#한눈에-보기-python--c)
* Python 의 무엇이 C++ 의 무엇인지 → [STL 알고리즘 · 한눈에 보기](./02_ps_notes/02_stl_algorithms.md#한눈에-보기-python--c), [라이브러리 · 한눈에 보기](./02_ps_notes/04_libraries.md#한눈에-보기-python--c)
* Segmentation fault 가 난다 → [입출력과 함정 §4-3 ~ §4-4, §4-9](./02_ps_notes/01_io_and_pitfalls.md#4-흔한-버그-모음)

## 03. Algorithms

모든 파일은 단독 컴파일·실행됩니다 (C++17, 표준 라이브러리만 사용).

```bash
g++ -std=c++17 -O2 03_algorithms/graph/dijkstra.cpp -o dijkstra
./dijkstra < 03_algorithms/graph/testdata/dijkstra.in

./scripts/run_tests.sh          # 전체 빌드 + 예상 출력(testdata/*.out) 비교
```

#### 정렬 `sorting/`
* [선택 정렬](./03_algorithms/sorting/selection_sort.cpp) · [삽입 정렬](./03_algorithms/sorting/insertion_sort.cpp) · [퀵 정렬 (+퀵 셀렉트)](./03_algorithms/sorting/quick_sort.cpp) · [계수 정렬](./03_algorithms/sorting/counting_sort.cpp)
* [`std::sort` / `std::stable_sort` 사용법](./03_algorithms/sorting/sort_builtin.cpp)

#### 이진 탐색 `binary_search/`
* [이진 탐색](./03_algorithms/binary_search/binary_search.cpp)
* [`lower_bound` / `upper_bound` 사용법](./03_algorithms/binary_search/lower_upper_bound.cpp) — 이상/이하/초과/미만 위치 찾기 (Python `bisect_usage`)
* [정렬된 배열에서 값이 [left, right] 인 원소 개수](./03_algorithms/binary_search/count_in_range.cpp)

#### 그래프 `graph/`
* [DFS & BFS](./03_algorithms/graph/dfs_bfs.cpp)
* [연결 요소 개수 (격자 BFS)](./03_algorithms/graph/connected_components.cpp)
* [다익스트라](./03_algorithms/graph/dijkstra.cpp)
* [최소 신장 트리 (Kruskal)](./03_algorithms/graph/mst.cpp)
* [위상 정렬](./03_algorithms/graph/topological_sort.cpp)
* [LCA (Binary Lifting)](./03_algorithms/graph/lca.cpp)
* [SCC (Tarjan)](./03_algorithms/graph/scc_tarjan.cpp)
* [단절점](./03_algorithms/graph/articulation_point.cpp)

#### 동적 계획법 `dp/`
* [LIS (O(N log N))](./03_algorithms/dp/lis.cpp)
* [비트마스크 TSP](./03_algorithms/dp/bitmask_tsp.cpp)

#### 문자열 `string/`
* [KMP](./03_algorithms/string/kmp.cpp)

#### 자료구조 `data_structure/`
* [Union-Find (Disjoint Set)](./03_algorithms/data_structure/disjoint_set.cpp)
* [좌표 압축](./03_algorithms/data_structure/coordinate_compression.cpp)
* [펜윅 트리 (BIT)](./03_algorithms/data_structure/fenwick_tree.cpp) — 구간 합 + 역전수 예제

#### 수학 `math/`
* [최대공약수 GCD](./03_algorithms/math/gcd.cpp) · [최소공배수 LCM](./03_algorithms/math/lcm.cpp) · [확장 유클리드](./03_algorithms/math/extended_euclidean.cpp)
* [소수 판정](./03_algorithms/math/is_prime.cpp) · [약수 구하기](./03_algorithms/math/divisors.cpp) · [소인수분해](./03_algorithms/math/prime_factorization.cpp)
* [뤼카 정리 (nCr mod p)](./03_algorithms/math/lucas_theorem.cpp)

#### 기하 `geometry/`
* [1차원 두 선분의 교점 개수](./03_algorithms/geometry/segment_intersection_1d.cpp)

#### 기법 `techniques/`
* [투 포인터 — 합이 M인 구간 개수](./03_algorithms/techniques/two_pointers.cpp)
* [누적 합](./03_algorithms/techniques/prefix_sum.cpp)
* [2차원 배열 90도 회전](./03_algorithms/techniques/rotate_matrix.cpp)

## 04. Projects

입력을 받는 대화형 콘솔 프로그램입니다. Windows 전용 파일은 Visual Studio 등 Windows 환경에서 빌드하세요.

```bash
g++ -std=c++20 04_projects/hangman.cpp -o hangman && ./hangman
./scripts/build_projects.sh      # Windows 전용을 제외한 전체 빌드 확인 (CI 에서도 실행)
```

| 파일 | 내용 | 비고 |
| --- | --- | --- |
| [cpp_learning.cpp](./04_projects/cpp_learning.cpp) | 문법 연습 스크래치 | C++20 (`<format>`) |
| [guess_number.cpp](./04_projects/guess_number.cpp) | 숫자 맞히기 | |
| [hangman.cpp](./04_projects/hangman.cpp) | 행맨 | |
| [tic_tac_toe.cpp](./04_projects/tic_tac_toe.cpp) | 틱택토 | |
| [snake_game.cpp](./04_projects/snake_game.cpp) | 스네이크 게임 | Windows 전용 (`<conio.h>`, `<windows.h>`) |
| [text_dungeon_rpg.cpp](./04_projects/text_dungeon_rpg.cpp) | 텍스트 던전 RPG | Windows 전용 (`<windows.h>`) |
