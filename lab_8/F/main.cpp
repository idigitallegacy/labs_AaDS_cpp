#include <fstream>
#include <iostream>
#include <vector>
#include <string>

struct Point {
    long long x = 0;
    long long y = 0;
    char move = '\0';
    
    explicit Point(const long long _x = 0, const long long _y = 0, const char _move = '\0')
    : x(_x)
    , y(_y)
    , move(_move) {}
};

bool find(const std::vector<Point> &queue, const Point &needle) {
    for (auto &i : queue) {
        if (i.x == needle.x && i.y == needle.y)
            return true;
    }
    return false;
}

int main() {
    std::ios_base::sync_with_stdio(false);
    
    std::ifstream fin("input.txt");
    fin.tie(nullptr);

    long long n, m;
    const long long INF = 1e12;

    fin >> n >> m;

    std::pair<long long, long long> source;
    std::pair<long long, long long> target;

    std::vector<std::vector<bool>> matrix(n, std::vector<bool>(m, false));
    std::vector<std::vector<bool>> visited(n, std::vector<bool>(m, false));
    std::vector<std::vector<long long>> distances(n, std::vector<long long>(m, INF));

    long long source_x = 0, source_y = 0;
    long long dest_x = 0, dest_y = 0;

    std::vector<char> dx = {0, 0, 1, -1};
    std::vector<char> dy = {1, -1, 0, 0};

    int counter = 0;
    for (int i = 0; i < n; ++i) {
        std::string tmp;
        fin >> tmp;
        for (int j = 0; j < m; ++j) {
            int top_y = i - 1, top_x = j;
            int left_y = i, left_x = j - 1;

            if (tmp[j] == '.' || tmp[j] == 'S' || tmp[j] == 'T')
                matrix[i][j] = true;
            else
                matrix[i][j] = false;

            if (tmp[j] == 'S') {
                source_y = i;
                source_x = j;
                distances[source_y][source_x] = 0;
            }
            if (tmp[j] == 'T') {
                dest_y = i;
                dest_x = j;
            }
        }
    }
    fin.close();

    Point current(source_x, source_y);
    std::vector<Point> queue = {current};

    std::vector<std::vector<std::string>> path(n, std::vector<std::string>(m, ""));
    visited[current.y][current.x] = true;

    while (!queue.empty()) { // Пока очерень не пуста (еще есть вершины для посещения)
        current = queue.front();
        queue.erase(queue.begin());

        for (int i = 0; i < 4; ++i) {
            Point tmp(current.x + dx[i], current.y + dy[i]);
            
            if ((tmp.y > -1) && (tmp.y < n) && (tmp.x > -1) && (tmp.x < m) &&
            matrix[tmp.y][tmp.x] && distances[tmp.y][tmp.x] > distances[current.y][current.x] &&
            !find(queue, tmp)) {
                distances[tmp.y][tmp.x] = distances[current.y][current.x] + 1;
                if (i == 0) current.move = 'D';
                else if (i == 1) current.move = 'U';
                else if (i == 2) current.move = 'R';
                else if (i == 3) current.move = 'L';
                path[tmp.y][tmp.x] = path[current.y][current.x] + current.move;
                queue.push_back(tmp);
                visited[tmp.y][tmp.x] = true;
            }
        }
    }

    std::ofstream fout("output.txt");
    fout.tie(nullptr);

    if (visited[dest_y][dest_x])
        fout << path[dest_y][dest_x].size() << '\n' << path[dest_y][dest_x];
    else
        fout << "-1";

    fout.close();
    return 0;
}
