#!/usr/bin/env bash
# 03_algorithms 의 모든 .cpp 를 빌드하고, testdata/<name>.out 과 실행 결과를 비교한다.
#
# usage: scripts/run_tests.sh [filter]
#   filter : 경로에 이 문자열이 포함된 파일만 테스트 (예: graph, dijkstra)
# env:
#   CXX      : 컴파일러 (기본 g++)
#   CXXFLAGS : 컴파일 옵션 (기본 -std=c++17 -O2 -Wall -Wextra -Wpedantic -Werror)
set -uo pipefail

ROOT="$(cd "$(dirname "${BASH_SOURCE[0]}")/.." && pwd)"
SRC_DIR="$ROOT/03_algorithms"
BUILD_DIR="$ROOT/build"
CXX="${CXX:-g++}"
CXXFLAGS="${CXXFLAGS:--std=c++17 -O2 -Wall -Wextra -Wpedantic -Werror}"
FILTER="${1:-}"

mkdir -p "$BUILD_DIR"
pass=0
fail=0
failed=()

while IFS= read -r src; do
    rel="${src#"$SRC_DIR"/}"              # graph/dijkstra.cpp
    [[ -n "$FILTER" && "$rel" != *"$FILTER"* ]] && continue

    dir="$(dirname "$src")"
    name="$(basename "$src" .cpp)"
    bin="$BUILD_DIR/${rel%.cpp}"
    expected="$dir/testdata/$name.out"
    input="$dir/testdata/$name.in"
    mkdir -p "$(dirname "$bin")"

    # shellcheck disable=SC2086
    if ! "$CXX" $CXXFLAGS "$src" -o "$bin" 2> "$bin.compile.log"; then
        echo "❌ $rel (compile error)"
        sed 's/^/    /' "$bin.compile.log" | head -20
        fail=$((fail + 1)); failed+=("$rel"); continue
    fi

    if [[ ! -f "$expected" ]]; then
        echo "❌ $rel (missing testdata/$name.out)"
        fail=$((fail + 1)); failed+=("$rel"); continue
    fi

    [[ -f "$input" ]] || input=/dev/null
    if ! actual="$(timeout 10 "$bin" < "$input")"; then
        echo "❌ $rel (runtime error / assert / timeout)"
        fail=$((fail + 1)); failed+=("$rel"); continue
    fi

    # 줄 끝 공백 차이는 무시 (출력 형식 학습용 코드가 아니므로)
    if diff -u <(sed 's/[[:space:]]*$//' "$expected") <(printf '%s\n' "$actual" | sed 's/[[:space:]]*$//') > "$bin.diff"; then
        echo "✅ $rel"
        pass=$((pass + 1))
    else
        echo "❌ $rel (output mismatch)"
        sed 's/^/    /' "$bin.diff" | head -20
        fail=$((fail + 1)); failed+=("$rel")
    fi
done < <(find "$SRC_DIR" -name '*.cpp' | LC_ALL=C sort)

echo
echo "passed: $pass, failed: $fail"
if (( fail > 0 )); then
    printf '  - %s\n' "${failed[@]}"
    exit 1
fi
