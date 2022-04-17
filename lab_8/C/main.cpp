#include <fstream>
#include <vector>
 
int main() {
    std::ios_base::sync_with_stdio(false);
    std::ifstream fin("input.txt");
    fin.tie(nullptr);
 
    int n, m;
    fin >> n >> m;
 
    std::vector<std::vector<int>> matrix(n, std::vector<int>(n, 0));
 
    for (int i = 0; i < m; ++i) {
        int u, v;
        fin >> u >> v;
        --u;
        --v;
        matrix[u][v] += 1;
        matrix[v][u] += 1;
    }
 
    fin.close();
 
    std::ofstream fout("output.txt");
    fout.tie(nullptr);
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < n; ++j) {
            if (matrix[i][j] > 1 && i != j) {
                fout << "YES";
                return 0;
            }
        }
    }
    fout << "NO";
    fout.close();
     
    return 0;
}
