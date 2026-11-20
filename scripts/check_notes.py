#!/usr/bin/env python3
"""노트(.md)의 C++ 코드 블록 중 `<!-- check:compile -->` 마커가 붙은 것을 컴파일해 본다.

마커 규칙 (CONTRIBUTING §3):
    <!-- check:compile -->
    ```cpp
    ... 함수 / 전체 프로그램 ...
    ```
- 블록 하나를 독립된 번역 단위로 컴파일한다 (블록끼리 섞지 않음).
- `#include` 가 없어도 되도록 자주 쓰는 표준 헤더를 앞에 붙인다.
- `main` 이 없으면 빈 `main` 을 덧붙인다 → 함수 템플릿만 있는 블록도 검사 가능.
- 문장 조각(함수 밖의 `std::cin >> n;` 등)은 마커를 붙이지 않는다.

usage: scripts/check_notes.py [md 파일 ...]   (기본: 01_basics, 02_ps_notes 의 모든 .md)
env:   CXX (기본 g++), CXXFLAGS (기본 -std=c++17 -fsyntax-only -Wall -Wextra)
"""
import os
import pathlib
import re
import shlex
import subprocess
import sys
import tempfile

ROOT = pathlib.Path(__file__).resolve().parent.parent
MARKER = "<!-- check:compile -->"
BLOCK_RE = re.compile(r"^" + re.escape(MARKER) + r"[ \t]*\n```cpp[^\n]*\n(.*?)^```", re.M | re.S)
PRELUDE = "".join(f"#include <{h}>\n" for h in (
    "algorithm", "cmath", "deque", "functional", "iomanip", "iostream", "limits", "map",
    "numeric", "queue", "set", "stack", "string", "tuple", "unordered_map", "unordered_set",
    "utility", "vector",
))

cxx = os.environ.get("CXX", "g++")
cxxflags = shlex.split(os.environ.get("CXXFLAGS", "-std=c++17 -fsyntax-only -Wall -Wextra"))
paths = [pathlib.Path(p) for p in sys.argv[1:]] or sorted(
    p for d in ("01_basics", "02_ps_notes") for p in (ROOT / d).glob("*.md"))

checked = failed = 0
for md in paths:
    text = md.read_text(encoding="utf-8")
    for match in BLOCK_RE.finditer(text):
        checked += 1
        line_no = text.count("\n", 0, match.start()) + 2  # ```cpp 줄 번호
        code = match.group(1)
        src = PRELUDE + f'#line {line_no + 1} "{md.name}"\n' + code
        if not re.search(r"\bint\s+main\s*\(", code):
            src += "\nint main() {}\n"
        with tempfile.NamedTemporaryFile("w", suffix=".cpp", delete=False, encoding="utf-8") as tmp:
            tmp.write(src)
        result = subprocess.run([cxx, *cxxflags, tmp.name], capture_output=True, text=True)
        os.unlink(tmp.name)
        resolved = md.resolve()
        label = f"{resolved.relative_to(ROOT) if resolved.is_relative_to(ROOT) else md}:{line_no}"
        if result.returncode == 0:
            print(f"✅ {label}")
        else:
            failed += 1
            print(f"❌ {label}")
            print("\n".join("    " + l for l in result.stderr.strip().splitlines()[:20]))

print(f"\nchecked: {checked}, failed: {failed}")
sys.exit(1 if failed or checked == 0 else 0)
