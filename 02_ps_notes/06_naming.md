# 인덱스 네이밍 가이드라인

> 인덱스는 코드의 **의도를 드러내는 가장 중요한 단서**다. `i`, `j` 대신 "무엇을 순회하는 인덱스인지" 를 이름으로 표현하면 인덱스 실수가 줄어든다.
> Python 버전: [Warming-Up-for-Python/02_ps_notes/06_naming.md](https://github.com/Devleu0/Warming-Up-for-Python/blob/main/02_ps_notes/06_naming.md)

---

## 기본 원칙

> **"이 인덱스가 무엇을 가리키는가?"**
> 이름만 보고도 알 수 있게 작성하라.

- `i`, `j`, `k` : 의미 불분명
- `row`, `col`, `char_idx`, `left`, `right` : 역할 명확

---

## 상황별 권장 이름

| 상황 | 권장 이름 | 예시 코드 |
| --- | --- | --- |
| 1차원 배열 | `idx`, `value` | `for (int idx = 0; idx < n; ++idx)` |
| 문자열 | `char_idx`, `ch` | `for (char ch : s)` |
| 2차원 배열 | `row`, `col` | `for (int row = 0; row < n; ++row) for (int col = 0; col < m; ++col)` |
| 투 포인터 | `left`, `right` / `start`, `end` | `while (left < right)` |
| 이분 탐색 | `lo`, `hi`, `mid` | `int mid = lo + (hi - lo) / 2;` |
| 그래프 탐색 (DFS/BFS) | `cur`, `next` | `for (int next : graph[cur])` |
| 방향 배열 | `dir`, `dr`, `dc` | `for (int dir = 0; dir < 4; ++dir)` |
| 정렬된 데이터 | `sorted_nums`, `rank` | `int rank = lower_bound(...) - sorted_nums.begin();` |

---

## 이중 루프 구조

이중 루프에서는 바깥 / 안쪽 인덱스의 의미를 이름에 담는다.

```cpp
for (int row = 0; row < n; ++row) {        // outer
    for (int col = 0; col < m; ++col) {    // inner
        grid[row][col];
    }
}
```

---

## 상태 전이 (DFS, BFS, DP 등)

`cur_` / `next_` 접두어를 적극 활용하라.

```cpp
int cur = q.front();
q.pop();
for (int next : graph[cur]) {
    if (!visited[next]) {
        visited[next] = true;
        q.push(next);
    }
}

auto [row, col] = q.front();
int next_row = row + dr[dir];
int next_col = col + dc[dir];
```

> C++ 에서 `next` 는 `std::next` 와 이름이 같다. `using namespace std;` 를 쓰면 충돌할 수 있으니 그때는 `nxt` 로 줄여 쓴다.

---

## 기타 팁

### 한글로 생각하고 영어로 이름 짓기

- "현재 좌표" → `cur_row`, `cur_col`
- "다음 칸" → `next_row`, `next_col`

### 정렬 · 변환 · 복사된 데이터는 접두어 추가

`sorted_nums`, `filtered`, `prefix_sum`, `compressed`

### 의미가 바뀌면 이름도 바꾼다

`idx` 가 `left` / `right` 로 역할이 바뀌면 즉시 이름을 바꾼다.

### C++ 에서 특히 주의할 이름

| 피할 이름 | 이유 | 대안 |
| --- | --- | --- |
| `count`, `find`, `next`, `distance`, `max`, `min` | `using namespace std;` 와 함께 쓰면 표준 함수와 충돌 | `cnt`, `nxt`, `dist`, `max_value` |
| `l` (소문자 L) | `1` 과 구분이 어려움 | `left`, `lo` |
| `y1`, `j0`, `j1` | `<cmath>` 의 베셀 함수 이름과 충돌 (GCC) | `y_1`, `start_y` |

---

## 예시 비교

### 나쁜 예시

```cpp
for (int i = 0; i < n; ++i)
    for (int j = 0; j < m; ++j)
        if (a[i][j] == 1) q.push({i, j});
```

### 좋은 예시

```cpp
for (int row = 0; row < n; ++row)
    for (int col = 0; col < m; ++col)
        if (grid[row][col] == 1) q.push({row, col});
```

---

## 결론

| 나쁜 이름 | 좋은 이름 | 의미 |
| --- | --- | --- |
| `i`, `j` | `row`, `col` | 2차원 위치 |
| `x`, `y` | `cur_row`, `cur_col` | 현재 좌표 |
| `temp` | `next_value` | 다음 상태 |
| `n`, `m` | `num_rows`, `num_cols` | 크기 명확 |
| `arr2` | `sorted_arr` | 변환된 데이터 |

> **요약:** 인덱스는 짧을 필요보다 명확할 필요가 있다. 이름만 바꿔도 디버깅 시간의 절반이 줄어든다.
