#include <fstream>
#include <vector>
 
int main() {
    std::ios_base::sync_with_stdio(false);
    
    std::ifstream fin("input.txt");
    fin.tie(nullptr);
    
    int n, m;
    fin >> n >> m;
 
    std::vector<std::vector<bool>> matrix(n, std::vector<bool>(n, false));
 
    for (int i = 0; i < m; ++i) {
        int u, v;
        fin >> u >> v;
        --u;
        --v;
        matrix[u][v] = true;
    }
    fin.close();
 
    std::ofstream fout("output.txt");
    fout.tie(nullptr);
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < n; ++j) {
            fout << matrix[i][j] << ' ';
        }
        fout << '\n';
    }
    fout.close();
     
    return 0;
}
