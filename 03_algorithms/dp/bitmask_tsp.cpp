/*
 * 외판원 순회 (TSP, Traveling Salesman Problem) — 비트마스크 DP
 * - dp[mask][cur] = 방문 집합이 mask 이고 현재 cur 에 있을 때, 남은 도시를 돌고 0 번으로 돌아가는 최소 비용
 * - 시간 복잡도: O(2^N * N^2), N 은 16 정도까지
 * - w[i][j] == 0 이면 이동 불가
 *
 * Python 버전: Warming-Up-for-Python/03_algorithms/dp/bitmask_tsp.py
 */
#include <algorithm>
#include <cassert>
#include <iostream>
#include <utility>
#include <vector>

class TspSolver {
public:
    static constexpr int INF = 1'000'000'000;

    explicit TspSolver(std::vector<std::vector<int>> w)
        : n_(static_cast<int>(w.size())), w_(std::move(w)), dp_(1 << n_, std::vector<int>(n_, -1)) {}

    // 0 번 도시에서 출발해 모든 도시를 한 번씩 방문하고 돌아오는 최소 비용 (불가능하면 -1)
    int solve() {
        const int result = dfs(1, 0);
        return result >= INF ? -1 : result;
    }

private:
    int dfs(int mask, int cur) {
        if (mask == (1 << n_) - 1) {               // 모든 도시 방문
            return w_[cur][0] ? w_[cur][0] : INF;  // 시작 도시로 돌아갈 수 있는가
        }
        int& memo = dp_[mask][cur];
        if (memo != -1) return memo;               // 메모이제이션

        memo = INF;
        for (int next = 0; next < n_; ++next) {
            if ((mask & (1 << next)) || w_[cur][next] == 0) continue;  // 방문했거나 길이 없음
            const int cost = dfs(mask | (1 << next), next);
            if (cost < INF) memo = std::min(memo, cost + w_[cur][next]);
        }
        return memo;
    }

    int n_;
    std::vector<std::vector<int>> w_;
    std::vector<std::vector<int>> dp_;
};

int main() {
    const std::vector<std::vector<int>> w = {
        {0, 10, 15, 20},
        {5, 0, 9, 10},
        {6, 13, 0, 12},
        {8, 8, 9, 0},
    };

    // 경로: 0 -> 1 -> 3 -> 2 -> 0,  비용: 10 + 10 + 9 + 6 = 35
    TspSolver solver(w);
    const int min_cost = solver.solve();
    std::cout << "도시 개수: " << w.size() << '\n';
    std::cout << "TSP 최소 비용: " << min_cost << '\n';

    assert(min_cost == 35);
}
