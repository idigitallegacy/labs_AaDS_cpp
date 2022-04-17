#include <fstream>
#include <vector>
 
bool find(const std::vector<int> &source, const int needle) {
    for (const int &i : source) {
        if (i == needle) return true;
    }
    return false;
}
 
int main() {
    std::ios_base::sync_with_stdio(false);
    std::ifstream fin("pathbge1.in");
    fin.tie(nullptr);
 
    int n, m;
    const int INF = 1e9;
 
    std::vector<std::vector<int>> matrix(n, std::vector<int>());
    std::vector<bool> visited(n, false);
    std::vector<int> distances(n, INF);
 
    for (int i = 0; i < m; ++i) {
        int u, v;
        fin >> u >> v;
        --u;
        --v;
        matrix[u].push_back(v);
        matrix[v].push_back(u);
    }
    fin.close();
 
    std::ofstream fout("pathbge1.out");
    fout.tie(nullptr);
 
    std::vector<int> queue = {0};
    distances[0] = 0;
 
    while (!queue.empty()) {
        int v = queue[0];
        queue.erase(queue.begin());
        visited[v] = true;
 
        for (int i : matrix[v]) {
            if (!visited[i] || (distances[i] > distances[v] + 1 && !find(queue, i))) {
                queue.push_back(i);
                visited[i] = true;
            } else
                distances[v] = std::min(distances[v], distances[i] + 1);
        }
    }
 
    for (int i = 0; i < n; ++i) {
        fout << distances[i] << ' ';
    }
 
    fout.close();
 
    return 0;
}
