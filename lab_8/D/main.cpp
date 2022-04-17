#include <fstream>
#include <vector>

void dfs(const std::vector<std::vector<int>> &matrix, std::vector<bool> &visited, std::vector<int> &components, const int v,
         const int counter) {
    visited[v] = true;
    components[v] = counter;
    if (matrix[v].empty()) return;
    for (int i : matrix[v]) {
        if (!visited[i]) {
            dfs(matrix, visited, components, i, counter);
        }
    }
}

int main() {
    std::ios_base::sync_with_stdio(false);
    std::ifstream fin("components.in");
    fin.tie(nullptr);

    int n, m;
    fin >> n >> m;

    std::vector<std::vector<int>> matrix(n, std::vector<int>());
    std::vector<bool> visited(n, false);
    std::vector<int> components(n, 0);

    for (int i = 0; i < m; ++i) {
        int u, v;
        fin >> u >> v;
        --u;
        --v;
        matrix[u].push_back(v);
        matrix[v].push_back(u);
    }
    fin.close();
    
    int componentCounter = 0;
    for (int i = 0; i < n; ++i) {
        if (!visited[i]) {
            dfs(matrix, visited, components, i, ++componentCounter);
        }
    }
    
    std::ofstream fout("components.out");
    fout.tie(nullptr);
    fout << componentCounter << '\n';
    componentCounter = 0;
    for (int i = 0; i < n; ++i) {
        if (visited[i] != 0) {
            fout << components[i] << ' ';
        } else {
            fout << ++componentCounter << ' ';
        }
    }
    fout.close();

    return 0;
}
