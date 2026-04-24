class Solution {
public:
    int shortestBridge(vector<vector<int>>& grid) {
        int n = grid.size();
        vector<pair<int,int>> dirs = {{0,1}, {0,-1}, {1,0}, {-1,0}};
        queue<pair<int,int>> q;
        bool found = false;
        
        // DFS to find and mark the first island (change 1 to 2)
        function<void(int, int)> dfs = [&](int r, int c) {
            if (r < 0 || r >= n || c < 0 || c >= n || grid[r][c] != 1) return;
            grid[r][c] = 2;  // Mark as visited (part of first island)
            q.push({r, c});  // Add to BFS queue
            for (auto& [dr, dc] : dirs) {
                dfs(r + dr, c + dc);
            }
        };
        
        // Find any cell of the first island and mark the entire island
        for (int i = 0; i < n && !found; i++) {
            for (int j = 0; j < n && !found; j++) {
                if (grid[i][j] == 1) {
                    dfs(i, j);
                    found = true;
                }
            }
        }
        
        // BFS from all cells of the first island to find shortest path to second island
        int steps = 0;
        while (!q.empty()) {
            int size = q.size();
            for (int i = 0; i < size; i++) {
                auto [r, c] = q.front();
                q.pop();
                for (auto& [dr, dc] : dirs) {
                    int nr = r + dr, nc = c + dc;
                    if (nr < 0 || nr >= n || nc < 0 || nc >= n || grid[nr][nc] == 2) continue;
                    if (grid[nr][nc] == 1) return steps;  // Found second island
                    grid[nr][nc] = 2;  // Mark water as visited
                    q.push({nr, nc});
                }
            }
            steps++;
        }
        
        return -1;  // Should never reach here given problem constraints
    }
};