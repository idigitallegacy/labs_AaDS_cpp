#include <fstream>
#include <vector>
 
int main() {
    std::ios_base::sync_with_stdio(false);
    std::ifstream fin("input.txt");
    fin.tie(nullptr);
 
    int n;
    fin >> n;
 
    std::vector<std::vector<int>> matrix(n, std::vector<int>(n, 0));
 
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < n; ++j) {
            fin >> matrix[i][j];
        }
    }
    fin.close();
 
    std::ofstream fout("output.txt");
    fout.tie(nullptr);
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < n; ++j) {
            if (matrix[i][j] != matrix[j][i] || matrix[i][i] == 1) {
                fout << "NO";
                return 0;
            }
        }
    }
    fout << "YES";
    fout.close();
 
    return 0;
}
