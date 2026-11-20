# ➕ Cpp-exercise
![C++ logo](https://img.shields.io/badge/C++-00599C?style=for-the-badge&logo=cplusplus&logoColor=white)

C++ 를 공부하면서 만든 학습 자료입니다. **C++ 기초 → 코테용 노트 → 알고리즘 구현** 순서로 구성했습니다.
[Warming-Up-for-Python](https://github.com/Devleu0/Warming-Up-for-Python) 의 C++ 버전으로, 같은 주제는 같은 폴더 · 같은 파일명에 있습니다.

| 폴더 | 내용 | 이런 사람에게 |
| --- | --- | --- |
| [01_basics](./01_basics) | C++ 문법 기초 (포인터 · OOP · STL 포함) | C++ 가 처음 |
| [02_ps_notes](./02_ps_notes) | 코딩 테스트용 치트시트 | 다른 언어는 익숙하고, 코테 전에 C++ 를 훑고 싶음 |
| [03_algorithms](./03_algorithms) | 알고리즘 · 자료구조 구현 코드 | 특정 알고리즘 구현을 보고 싶음 |
| [04_projects](./04_projects) | 콘솔 미니 프로젝트 | 배운 문법으로 작은 프로그램을 만들어 보고 싶음 |

> 재구성 작업의 기획 · 진행 상태는 [docs/ROADMAP.md](./docs/ROADMAP.md), 기여 규칙은 [CONTRIBUTING.md](./CONTRIBUTING.md) 에 있습니다.

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

| # | 노트 | 내용 |
| --- | --- | --- |
| 3 | [문자열 다루기](./02_ps_notes/03_strings.md) | 찾기 · 자르기 · 치환 · 변환 · 역방향 접근 |
| 4 | [라이브러리](./02_ps_notes/04_libraries.md) | STL 컨테이너 · `<algorithm>` · 그래프 템플릿 |
| 7 | [출력 형식](./02_ps_notes/07_output_format.md) | `printf` · `iomanip` · `std::format` |
| 8 | [언어별 빠른 입출력](./02_ps_notes/08_fast_io_by_language.md) | C/C++/Java/Python/Rust 빠른 I/O |

> 1 · 2 · 5 · 6 번 노트(입출력과 함정, STL 알고리즘, 그래프 패턴, 네이밍)는 [ROADMAP Phase 2](./docs/ROADMAP.md#4-진행-상태) 에서 추가됩니다.

## 03. Algorithms

> [ROADMAP Phase 1](./docs/ROADMAP.md#4-진행-상태) 에서 Python 레포의 알고리즘 33개를 C++ 로 포팅합니다.

## 04. Projects

| 파일 | 내용 | 비고 |
| --- | --- | --- |
| [cpp_learning.cpp](./04_projects/cpp_learning.cpp) | 문법 연습 스크래치 | C++20 (`<format>`) |
| [guess_number.cpp](./04_projects/guess_number.cpp) | 숫자 맞히기 | |
| [hangman.cpp](./04_projects/hangman.cpp) | 행맨 | |
| [tic_tac_toe.cpp](./04_projects/tic_tac_toe.cpp) | 틱택토 | |
| [snake_game.cpp](./04_projects/snake_game.cpp) | 스네이크 게임 | Windows 전용 (`<conio.h>`, `<windows.h>`) |
| [text_dungeon_rpg.cpp](./04_projects/text_dungeon_rpg.cpp) | 텍스트 던전 RPG | Windows 전용 (`<windows.h>`) |
