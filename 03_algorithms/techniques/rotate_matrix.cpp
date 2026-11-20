/*
 * 2차원 배열 시계 방향 90도 회전 (Rotate Matrix)
 * - (r, c) → (c, row_length - 1 - r)
 * - N x M 행렬은 M x N 이 된다
 * - 시간 복잡도: O(N * M)
 *
 * Python 버전: Warming-Up-for-Python/03_algorithms/techniques/rotate_matrix.py
 */
#include <iostream>
#include <vector>

using Matrix = std::vector<std::vector<int>>;

Matrix rotate_90(const Matrix& a) {
    const std::size_t row_length = a.size();
    const std::size_t column_length = a[0].size();

    Matrix res(column_length, std::vector<int>(row_length, 0));
    for (std::size_t r = 0; r < row_length; ++r) {
        for (std::size_t c = 0; c < column_length; ++c) {
            res[c][row_length - 1 - r] = a[r][c];
        }
    }
    return res;
}

void print(const Matrix& m) {
    for (const auto& row : m) {
        for (std::size_t c = 0; c < row.size(); ++c) std::cout << (c ? " " : "") << row[c];
        std::cout << '\n';
    }
}

int main() {
    const Matrix a = {
        {1, 2, 3, 4},
        {5, 6, 7, 8},
        {9, 10, 11, 12},
    };
    print(rotate_90(a));
}
