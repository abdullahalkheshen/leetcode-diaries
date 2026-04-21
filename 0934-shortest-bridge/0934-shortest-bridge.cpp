class Solution {
public:
    void dfs(vector<vector<int>>& grid, int r, int c, unordered_set<string>& visited, vector<tuple<int,int>>& island1) {
        bool rInbounds = 0 <= r && r < grid.size();
        bool cInbounds = 0 <= c && c < grid[0].size();
        if (!rInbounds || !cInbounds) return;

        string pos = to_string(r) + "," + to_string(c);
        if (visited.count(pos) > 0) return;
        if (grid[r][c] == 0) return;

        visited.insert(pos);
        island1.push_back({r, c});

        dfs(grid, r + 1, c, visited, island1);
        dfs(grid, r - 1, c, visited, island1);
        dfs(grid, r, c + 1, visited, island1);
        dfs(grid, r, c - 1, visited, island1);
    }

    int shortestBridge(vector<vector<int>>& grid) {
        unordered_set<string> visited;
        vector<tuple<int, int>> island1;

        // Phase 1 — DFS to find Island 1
        bool found = false;
        for (int r = 0; r < grid.size() && !found; r++) {
            for (int c = 0; c < grid[0].size() && !found; c++) {
                if (grid[r][c] == 1) {
                    dfs(grid, r, c, visited, island1);
                    found = true;
                }
            }
        }

        // Phase 2 — BFS outward from Island 1
        queue<tuple<int, int, int>> q;
        for (auto [r, c] : island1) {
            q.push({r, c, -1});
            visited.insert(to_string(r) + "," + to_string(c));
        }

        while (!q.empty()) {
            auto [r, c, dist] = q.front();
            q.pop();

            if (grid[r][c] == 1 && dist != -1) {
                return dist;
            }

            vector<tuple<int,int>> deltas = {{1,0},{-1,0},{0,1},{0,-1}};
            for (auto [dr, dc] : deltas) {
                int nr = r + dr;
                int nc = c + dc;
                string nPos = to_string(nr) + "," + to_string(nc);

                bool rInbounds = 0 <= nr && nr < grid.size();
                bool cInbounds = 0 <= nc && nc < grid[0].size();

                if (rInbounds && cInbounds && visited.count(nPos) == 0) {
                    visited.insert(nPos);
                    q.push({nr, nc, dist + 1});
                }
            }
        }
        return -1;
    }
};