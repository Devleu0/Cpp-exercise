/*
 * 연결 요소 개수 (격자 BFS) — '0' 으로만 이루어진 덩어리의 수
 * - 아직 방문하지 않은 '0' 칸에서 BFS 를 시작할 때마다 개수 +1
 * - 시간 복잡도: O(N * M)
 *
 * Python 버전: Warming-Up-for-Python/03_algorithms/graph/connected_components.py
 */
#include <iostream>
#include <queue>
#include <string>
#include <utility>
#include <vector>

class GridComponents {
public:
    explicit GridComponents(std::vector<std::string> grid)
        : grid_(std::move(grid)),
          rows_(static_cast<int>(grid_.size())),
          cols_(static_cast<int>(grid_[0].size())),
          visited_(rows_, std::vector<bool>(cols_, false)) {}

    int count(char target) {
        int result = 0;
        for (int row = 0; row < rows_; ++row) {
            for (int col = 0; col < cols_; ++col) {
                if (grid_[row][col] == target && !visited_[row][col]) {
                    bfs(row, col, target);
                    ++result;
                }
            }
        }
        return result;
    }

private:
    void bfs(int start_row, int start_col, char target) {
        static constexpr int dr[] = {-1, 1, 0, 0};
        static constexpr int dc[] = {0, 0, -1, 1};

        std::queue<std::pair<int, int>> q;
        q.emplace(start_row, start_col);
        visited_[start_row][start_col] = true;
        while (!q.empty()) {
            const auto [row, col] = q.front();
            q.pop();
            for (int dir = 0; dir < 4; ++dir) {
                const int next_row = row + dr[dir];
                const int next_col = col + dc[dir];
                if (next_row < 0 || next_col < 0 || next_row >= rows_ || next_col >= cols_) continue;
                if (grid_[next_row][next_col] == target && !visited_[next_row][next_col]) {
                    visited_[next_row][next_col] = true;
                    q.emplace(next_row, next_col);
                }
            }
        }
    }

    std::vector<std::string> grid_;
    int rows_;
    int cols_;
    std::vector<std::vector<bool>> visited_;
};

int main() {
    const std::vector<std::string> data = {
        "00000111100000",
        "11111101111110",
        "11011101101110",
        "11011101100000",
        "11011111111111",
        "11011111111100",
        "11000000011111",
        "01111111111111",
        "00000000011111",
        "01111111111000",
        "00011111111000",
        "00000001111000",
        "11111111110011",
        "11100011111111",
        "11100011111111",
    };

    GridComponents solver(data);
    std::cout << solver.count('0') << '\n';
}
