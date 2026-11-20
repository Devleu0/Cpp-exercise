# 기여 가이드 (CONTRIBUTING)

이 레포에 노트나 코드를 추가할 때 지키는 규칙입니다. 전체 방향은 [docs/ROADMAP.md](./docs/ROADMAP.md) 를 참고하세요.

## 1. 네이밍

| 대상 | 규칙 | 예 |
| --- | --- | --- |
| 폴더 | `NN_snake_case` (학습 순서가 있으면 번호) | `02_ps_notes/`, `03_algorithms/graph/` |
| 노트 | `NN_snake_case.md` | `05_graph_patterns.md` |
| 코드 | `snake_case.cpp` (Python 레포와 같은 이름) | `dijkstra.cpp` |
| 테스트 데이터 | `<category>/testdata/<name>.in`, `<name>.out` | `graph/testdata/dijkstra.in` |

* 이름에 **공백 · 한글 · 대문자 · 하이픈**을 쓰지 않습니다.
* Python 레포에 같은 항목이 있으면 **같은 폴더 · 같은 파일명**을 씁니다.

## 2. 알고리즘 코드 (`03_algorithms/`)

### 2-1. 규칙

* **C++17**, 표준 라이브러리만 사용. `<bits/stdc++.h>` 대신 필요한 헤더를 직접 include.
* 파일 하나로 단독 컴파일 가능해야 합니다: `g++ -std=c++17 -O2 dijkstra.cpp`.
* 핵심 로직은 **함수/클래스**로 분리하고 `main()` 은 입력 · 예제 · 검증만 담당합니다.
* 전역 변수는 피하고, 필요한 상태는 인자나 클래스 멤버로 넘깁니다.
* `using namespace std;` 는 쓰지 않고 `std::` 를 붙입니다 (헤더로 옮겨도 안전한 코드 유지).
* 경고 없이 빌드되어야 합니다 (`-Wall -Wextra -Wpedantic -Werror`).

### 2-2. 파일 템플릿

```cpp
/*
 * 알고리즘 이름 (English Name)
 * - 핵심 아이디어 한두 줄
 * - 시간 복잡도: O(...)
 *
 * Python 버전: Warming-Up-for-Python/03_algorithms/<category>/<name>.py
 */
#include <iostream>
#include <vector>

// 핵심 로직: 다른 문제에 그대로 복사해 쓸 수 있는 단위
int solve(const std::vector<int>& data) {
    // ...
}

int main() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);

    // 예제 실행 + 검증
}
```

### 2-3. 테스트

* 모든 `.cpp` 는 `testdata/<name>.out` (예상 표준 출력) 을 가집니다.
* 표준 입력을 받는 프로그램은 `testdata/<name>.in` 도 추가합니다. (없으면 빈 입력으로 실행)
* 출력으로 확인하기 어려운 성질은 코드 안에서 `assert` 로 검증합니다.
* 로컬 실행:

```bash
./scripts/run_tests.sh                 # 전체
./scripts/run_tests.sh graph           # 경로에 'graph' 가 포함된 것만
CXX=clang++ ./scripts/run_tests.sh     # 컴파일러 변경
```

## 3. 노트 (`01_basics/`, `02_ps_notes/`)

* 맨 위에 `# 제목` 과 한 줄 요약(`> ...`)을 둡니다.
* 코드 블록에는 언어 태그(` ```cpp `)를 붙입니다.
* 다른 노트로 링크할 때는 상대 경로(`./04_libraries.md#...`)를 씁니다.
* 새 노트를 추가하면 [README.md](./README.md) 목차에도 추가합니다.

## 4. 브랜치 · 커밋 · PR

* 브랜치: `<type>/<short-description>` — 예) `feat/algorithms-cpp`, `docs/ps-notes`, `fix/kmp-off-by-one`
* 커밋 메시지: [Conventional Commits](https://www.conventionalcommits.org/ko/) 형식
  * `feat:` 새 코드, `docs:` 노트/문서, `fix:` 버그 수정, `refactor:` 구조 변경, `test:` 테스트, `ci:` CI 설정
* PR 은 한 가지 주제만 담습니다. 큰 작업은 [ROADMAP](./docs/ROADMAP.md) 의 Phase 단위로 나눕니다.
* PR 체크리스트
  - [ ] `./scripts/run_tests.sh` 통과
  - [ ] README / ROADMAP 링크·진행 상태 갱신
  - [ ] 새 파일 이름이 네이밍 규칙을 따름
