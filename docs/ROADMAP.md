# 로드맵

> 이 문서는 재구성 작업의 기획서이자 진행 기록이다.
> 작업은 여러 PR 로 나눠 진행하며, 각 Phase 가 끝날 때마다 아래 [진행 상태](#4-진행-상태)와 [결정 기록](#5-결정-기록-decision-log)을 갱신한다.

---

## 1. 목표

| 목표 | 설명 |
| **1:1 대응** | Python 레포의 노트·알고리즘 파일이 C++ 레포의 어디에 있는지 바로 찾을 수 있게 한다 (같은 폴더명·파일명). |
| **검증 가능한 코드** | 모든 알고리즘 파일은 단독 컴파일·실행되고, 예상 출력과 자동 비교되는 테스트를 가진다 (CI). |
| **기존 자료 보존** | 기존 C++ 노트(문법·OOP·STL·문자열·출력 형식 등)는 내용을 살리고 위치·이름만 정리한다. |

### 설계 원칙

* **유지 보수성** — 파일 이름에 공백·한글·대문자를 쓰지 않는다 (URL 인코딩, 셸 따옴표 문제 제거). 번호 접두어로 학습 순서를 표현한다.
* **모듈화** — 알고리즘 1개 = `.cpp` 1개. 각 파일은 외부 의존성 없이 표준 라이브러리만 사용하고, 핵심 로직은 함수/클래스로 분리해 `main()` 은 예제·검증만 담당한다.

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
│   ├── run_tests.sh          # 03_algorithms 전체 빌드 + 출력 비교
│   ├── build_projects.sh     # 04_projects 컴파일 확인 (Windows 전용 제외)
│   └── check_notes.py        # 노트의 마커 붙은 코드 블록 컴파일 확인
└── .github/workflows/ci.yml  # g++ / clang++ 빌드 · 테스트
```

## 4. 진행 상태

| Phase | 내용 | 브랜치 | 상태 |
| --- | --- | --- | --- |
| 0 | 기획 문서, 컨벤션, 디렉토리 재구성 (파일 이동만, 내용 변경 없음), README 개편 | `refactor/restructure-layout` | ✅ PR #1 |
| 1 | 테스트 스크립트 · CI · `03_algorithms` 33개 C++ 포팅 + testdata | `feat/algorithms-cpp` | ✅ PR #2 (g++ 15 / clang++ 22 에서 33/33 통과) |
| 2 | `02_ps_notes` 신규 노트 4개 + `04_libraries` 정리 + README "이럴 땐 여기" | `docs/ps-notes` | ✅ PR #3 |
| 3-1 | `04_projects` 빌드 정리: BOM 제거, 이식 가능한 프로젝트 CI 빌드 | `fix/projects-build` | ✅ PR #4 |
| 3-2 | 노트 코드 블록 컴파일 검사 (`<!-- check:compile -->` 마커 + CI) | `ci/check-notes` | ✅ PR #5 |
| 3-x | 나머지 후속 정리 (아래 백로그) | — | 📋 계획 |

PR 은 **스택 방식**으로 올린다 (Phase N 의 PR base = Phase N-1 브랜치). 앞 PR 이 머지되면 GitHub 이 다음 PR 의 base 를 `main` 으로 자동 변경한다 (머지 시 브랜치 삭제 기준). **머지 순서: Phase 0 → 1 → 2 → 3-1 → 3-2.**

### Phase 3 백로그 (후속 작업 후보)

- [ ] `01_basics` 노트 점검: Python 노트북 대비 빠진 주제(자료형 범위·형변환 표 등) 보강, 목차 앵커 정리
- [x] `04_projects` 이식성: Windows 전용 2개는 README 표시만 하고 코드는 유지 (D15). `cpp_learning.cpp` 는 C++20 으로 빌드
- [x] `text_dungeon_rpg.cpp` 4번째 줄 `#include <ctime>` 뒤에 BOM 문자(U+FEFF)가 섞여 있어 컴파일 실패 → 제거 필요
- [x] `04_projects` 도 CI 빌드 대상에 포함 → `scripts/build_projects.sh` (Windows 전용 자동 제외)
- [ ] 알고리즘 추가 후보: 세그먼트 트리, 플로이드–워셜, 벨만–포드, 에라토스테네스의 체 (Python 레포에도 추가되면 함께)
- [ ] `.clang-format` 도입 여부 결정 (현재는 `.editorconfig` 로 들여쓰기만 통일)
- [ ] `02_ps_notes/03_strings.md`: 절 번호가 20 → 24 로 건너뜀, Python 노트와 절 대응 점검
- [x] 노트 코드 블록 컴파일 검사를 CI 에 추가 → `scripts/check_notes.py` (현재 01 의 2개, 05 의 6개 블록)
- [ ] 기존 노트(01_basics, 03·04·07)의 완결된 코드 블록에도 `check:compile` 마커 확대
- [ ] Python 레포 쪽 버그 제보: `is_prime(1) == True`
