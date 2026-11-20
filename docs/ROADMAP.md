# 재구성 로드맵 (기획 · 방향성 기록)

> 이 문서는 `Cpp-exercise` 를 [Warming-Up-for-Python](https://github.com/Devleu0/Warming-Up-for-Python) 의 **C++ 버전**으로 재구성하는 작업의 기획서이자 진행 기록이다.
> 작업은 여러 PR 로 나눠 진행하며, 각 Phase 가 끝날 때마다 아래 [진행 상태](#4-진행-상태)와 [결정 기록](#5-결정-기록-decision-log)을 갱신한다.

---

## 1. 목표

| 목표 | 설명 |
| --- | --- |
| **같은 학습 동선** | Python 레포와 동일하게 `기초 → 코테용 노트 → 알고리즘 구현` 순서로 볼 수 있게 한다. |
| **1:1 대응** | Python 레포의 노트·알고리즘 파일이 C++ 레포의 어디에 있는지 바로 찾을 수 있게 한다 (같은 폴더명·파일명). |
| **검증 가능한 코드** | 모든 알고리즘 파일은 단독 컴파일·실행되고, 예상 출력과 자동 비교되는 테스트를 가진다 (CI). |
| **기존 자료 보존** | 기존 C++ 노트(문법·OOP·STL·문자열·출력 형식 등)는 내용을 살리고 위치·이름만 정리한다. |

### 설계 원칙

* **유지 보수성** — 파일 이름에 공백·한글·대문자를 쓰지 않는다 (URL 인코딩, 셸 따옴표 문제 제거). 번호 접두어로 학습 순서를 표현한다.
* **모듈화** — 알고리즘 1개 = `.cpp` 1개. 각 파일은 외부 의존성 없이 표준 라이브러리만 사용하고, 핵심 로직은 함수/클래스로 분리해 `main()` 은 예제·검증만 담당한다.
* **협업** — 컨벤션은 [CONTRIBUTING.md](../CONTRIBUTING.md) 한 곳에 둔다. 테스트 스크립트와 CI 로 리뷰어가 "돌려보지 않아도" 동작을 확인할 수 있게 한다. PR 은 Phase 단위로 작게 나눈다.

---

## 2. 목표 디렉토리 구조

```text
Cpp-exercise/
├── README.md                 # 폴더 안내, 노트 목차, "이럴 땐 여기" 바로가기
├── CONTRIBUTING.md           # 네이밍 · 코드 스타일 · 테스트 · 커밋/PR 규칙
├── docs/
│   └── ROADMAP.md            # (이 문서) 기획 · 진행 상태 · 결정 기록
├── 01_basics/                # C++ 문법 기초 (기존 노트 이전)
├── 02_ps_notes/              # 코딩 테스트용 치트시트
├── 03_algorithms/            # 알고리즘 · 자료구조 구현 (.cpp) + testdata/
│   ├── sorting/  binary_search/  graph/  dp/  string/
│   ├── data_structure/  math/  geometry/  techniques/
│   └── <category>/testdata/<name>.in|.out
├── 04_projects/              # 콘솔 미니 프로젝트 (기존 예제 코드)
├── scripts/
│   └── run_tests.sh          # 03_algorithms 전체 빌드 + 출력 비교
└── .github/workflows/ci.yml  # g++ / clang++ 빌드 · 테스트
```

---

## 3. Python → C++ 매핑

### 3-1. 기존 파일 이전 (Phase 0)

| 기존 경로 | 새 경로 |
| --- | --- |
| `Learning_cpp/md/1. C++ 기초.md` | `01_basics/01_syntax_and_control_flow.md` |
| `Learning_cpp/md/2. C++ 함수_배열_포인터.md` | `01_basics/02_functions_arrays_pointers.md` |
| `Learning_cpp/md/3. C++ OOP 핵심.md` | `01_basics/03_oop.md` |
| `Learning_cpp/md/4. C++ STL_파일 입출력 .md` | `01_basics/04_stl_and_file_io.md` |
| `Learning_cpp/md/5. C++ 심화 학습.md` | `01_basics/05_modern_cpp_roadmap.md` |
| `Learning_cpp/md/C++ 배열, 벡터 초기화.md` | `01_basics/06_array_vector_init.md` |
| `Learning_cpp/md/C++ 컨테이너.md` | `01_basics/07_containers.md` |
| `Learning_cpp/md/C++ 헤더 파일과 소스 파일.md` | `01_basics/08_header_and_source.md` |
| `Learning_cpp/md/PS. C++ 문자열 다루기.md` | `02_ps_notes/03_strings.md` |
| `Learning_cpp/md/PS. C++ 알고리즘 공략.md` | `02_ps_notes/04_libraries.md` |
| `Learning_cpp/md/PS. C++ 출력 형식.md` | `02_ps_notes/07_output_format.md` |
| `언어별 빠른 입출력(IO) 가이드.md` | `02_ps_notes/08_fast_io_by_language.md` |
| `Learning_cpp/cpp/CppLearning.cpp` | `04_projects/cpp_learning.cpp` |
| `Learning_cpp/cpp/GuessNumber.cpp` | `04_projects/guess_number.cpp` |
| `Learning_cpp/cpp/Hangman.cpp` | `04_projects/hangman.cpp` |
| `Learning_cpp/cpp/SnakeGame.cpp` | `04_projects/snake_game.cpp` |
| `Learning_cpp/cpp/TextDungeonRPG.cpp` | `04_projects/text_dungeon_rpg.cpp` |
| `Learning_cpp/cpp/Tic-Tac-To.cpp` | `04_projects/tic_tac_toe.cpp` |

### 3-2. 01_basics

Python 의 `01_basics` 는 Jupyter 노트북 6개(자료형/제어문/반복문/문자열/컬렉션/내장함수)다.
C++ 는 포인터·OOP·헤더 분리처럼 Python 에 없는 필수 주제가 있으므로 **노트 번호를 1:1 로 맞추지 않고** 기존 C++ 커리큘럼(01~08)을 유지한다.
대응 관계는 다음과 같다.

| Python (`01_basics`) | C++ 에서 다루는 곳 |
| --- | --- |
| 01_data_types | `01_basics/01_syntax_and_control_flow.md` §1 |
| 02_control_flow, 03_loop | `01_basics/01_syntax_and_control_flow.md` §4 |
| 04_string | `01_basics/02_functions_arrays_pointers.md` §2, `02_ps_notes/03_strings.md` |
| 05_list_dict_set_tuple | `01_basics/06_array_vector_init.md`, `01_basics/07_containers.md` |
| 06_built_in_functions | `02_ps_notes/02_stl_algorithms.md` (Phase 2) |

### 3-3. 02_ps_notes

| # | Python | C++ | 작업 |
| --- | --- | --- | --- |
| 1 | `01_io_and_pitfalls.md` | `01_io_and_pitfalls.md` | 신규 작성 (Phase 2) |
| 2 | `02_builtins.md` | `02_stl_algorithms.md` | 신규 작성 — `<algorithm>`·`<numeric>`·정수 연산 함정 (Phase 2) |
| 3 | `03_strings.md` | `03_strings.md` | 기존 노트 이전 |
| 4 | `04_libraries.md` | `04_libraries.md` | 기존 "알고리즘 공략" 이전 → Phase 2 에서 그래프 부분 분리 · Python 대응표 추가 |
| 5 | `05_graph_patterns.md` | `05_graph_patterns.md` | 신규 (04 에서 그래프 템플릿 분리 + 격자 BFS) (Phase 2) |
| 6 | `06_naming.md` | `06_naming.md` | C++ 예제로 포팅 (Phase 2) |
| 7 | — | `07_output_format.md` | C++ 전용 (기존 노트 이전) |
| 8 | — | `08_fast_io_by_language.md` | 기존 노트 이전 |

### 3-4. 03_algorithms (Phase 1)

Python 의 `03_algorithms/<category>/<name>.py` → C++ 의 `03_algorithms/<category>/<name>.cpp` 로 **경로를 그대로 유지**한다 (총 33개).

| 카테고리 | 파일 |
| --- | --- |
| `sorting/` | selection_sort, insertion_sort, quick_sort, counting_sort, sort_builtin |
| `binary_search/` | binary_search, bisect_usage → **lower_upper_bound** (C++ 이름), count_in_range |
| `graph/` | dfs_bfs, connected_components, dijkstra, mst, topological_sort, lca, scc_tarjan, articulation_point |
| `dp/` | lis, bitmask_tsp |
| `string/` | kmp |
| `data_structure/` | disjoint_set, coordinate_compression, fenwick_tree |
| `math/` | gcd, lcm, extended_euclidean, is_prime, divisors, prime_factorization, lucas_theorem |
| `geometry/` | segment_intersection_1d |
| `techniques/` | two_pointers, prefix_sum, rotate_matrix |

---

## 4. 진행 상태

| Phase | 내용 | 브랜치 | 상태 |
| --- | --- | --- | --- |
| 0 | 기획 문서, 컨벤션, 디렉토리 재구성 (파일 이동만, 내용 변경 없음), README 개편 | `refactor/restructure-layout` | ✅ PR 작성 |
| 1 | 테스트 스크립트 · CI · `03_algorithms` 33개 C++ 포팅 + testdata | `feat/algorithms-cpp` | ⏳ |
| 2 | `02_ps_notes` 신규 노트 4개 + `04_libraries` 정리 + README "이럴 땐 여기" | `docs/ps-notes` | ⏳ |
| 3 | 후속 정리 (아래 백로그) | — | 📋 계획 |

PR 은 **스택 방식**으로 올린다 (Phase N 의 PR base = Phase N-1 브랜치). 앞 PR 이 머지되면 GitHub 이 다음 PR 의 base 를 `main` 으로 자동 변경한다 (머지 시 브랜치 삭제 기준). **머지 순서: Phase 0 → 1 → 2.**

### Phase 3 백로그 (후속 작업 후보)

- [ ] `01_basics` 노트 점검: Python 노트북 대비 빠진 주제(자료형 범위·형변환 표 등) 보강, 목차 앵커 정리
- [ ] `04_projects` 이식성: `snake_game.cpp`, `text_dungeon_rpg.cpp` 는 `<windows.h>`/`<conio.h>` 의존 → 플랫폼 분기 또는 README 에 "Windows 전용" 명시. `cpp_learning.cpp` 는 C++20 `<format>` 필요
- [ ] `text_dungeon_rpg.cpp` 4번째 줄 `#include <ctime>` 뒤에 BOM 문자(U+FEFF)가 섞여 있어 컴파일 실패 → 제거 필요
- [ ] `04_projects` 도 CI 빌드 대상에 포함 (이식성 작업 후)
- [ ] 알고리즘 추가 후보: 세그먼트 트리, 플로이드–워셜, 벨만–포드, 에라토스테네스의 체 (Python 레포에도 추가되면 함께)
- [ ] `.clang-format` 도입 여부 결정 (현재는 `.editorconfig` 로 들여쓰기만 통일)

---

## 5. 결정 기록 (Decision Log)

| # | 결정 | 이유 |
| --- | --- | --- |
| D1 | 폴더/파일 이름은 `NN_snake_case` | Python 레포와 통일, 공백·한글로 인한 링크 깨짐(`%20`) 제거 |
| D2 | Phase 0 은 **이동만** 하고 내용은 수정하지 않음 | 리뷰에서 git rename 으로 인식되어 diff 가 0 줄 → 리뷰 부담 최소화. 내용 수정은 후속 PR |
| D3 | 01_basics 번호는 Python 과 1:1 로 맞추지 않음 | C++ 고유 필수 주제(포인터·OOP·헤더)가 있어 억지로 맞추면 오히려 찾기 어려움. 대신 §3-2 대응표 제공 |
| D4 | 표준은 **C++17**, 헤더는 `<bits/stdc++.h>` 대신 필요한 표준 헤더를 명시 | 구조화된 바인딩 등 PS 에 필요한 기능은 C++17 로 충분, 대부분의 코테 플랫폼 지원. `bits/stdc++.h` 는 GCC 전용이라 MSVC/Apple clang 에서 빌드 불가 |
| D5 | 빌드 시스템은 CMake 대신 **셸 스크립트 + g++/clang++** | 파일 하나 = 실행 파일 하나 구조라 CMake 이점이 적고, 학습자가 `g++ file.cpp` 로 바로 따라 할 수 있음 |
| D6 | 테스트는 `testdata/<name>.out` 과 표준 출력 비교 (+ 코드 내 `assert`) | 별도 테스트 프레임워크 없이 "실행 결과 = 문서화된 예제 출력" 을 보장. 입력이 필요하면 `<name>.in` 추가 |
| D7 | Python 쪽 버그는 C++ 포팅 시 바로잡고 파일 주석에 기록 | 예: `is_prime(1)` 이 `True` 를 반환하는 문제 |
| D8 | `bisect_usage` → `lower_upper_bound` 로 이름 변경 | C++ 에는 `bisect` 가 없고 대응 함수가 `lower_bound`/`upper_bound` |
