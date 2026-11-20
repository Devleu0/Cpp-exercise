#!/usr/bin/env bash
# 04_projects 의 콘솔 프로젝트를 컴파일만 해 본다 (대화형 프로그램이라 실행은 하지 않음).
# <windows.h> / <conio.h> 를 쓰는 파일은 Windows 전용이므로 자동으로 건너뛴다.
#
# usage: scripts/build_projects.sh
# env:
#   CXX      : 컴파일러 (기본 g++)
#   CXXFLAGS : 컴파일 옵션 (기본 -std=c++20 -Wall -Wextra)  ← cpp_learning.cpp 가 <format> 사용
set -uo pipefail

ROOT="$(cd "$(dirname "${BASH_SOURCE[0]}")/.." && pwd)"
BUILD_DIR="$ROOT/build/04_projects"
CXX="${CXX:-g++}"
CXXFLAGS="${CXXFLAGS:--std=c++20 -Wall -Wextra}"

mkdir -p "$BUILD_DIR"
fail=0

for src in "$ROOT"/04_projects/*.cpp; do
    name="$(basename "$src" .cpp)"
    if grep -qE '#include[[:space:]]*<(windows|conio)\.h>' "$src"; then
        echo "⏭️  $name (Windows 전용, 건너뜀)"
        continue
    fi
    # shellcheck disable=SC2086
    if "$CXX" $CXXFLAGS "$src" -o "$BUILD_DIR/$name" 2> "$BUILD_DIR/$name.log"; then
        echo "✅ $name"
    else
        echo "❌ $name"
        sed 's/^/    /' "$BUILD_DIR/$name.log" | head -20
        fail=$((fail + 1))
    fi
done

exit $(( fail > 0 ))
