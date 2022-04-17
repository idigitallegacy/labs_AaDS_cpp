#include <fstream>
#include <vector>

template<typename value_type>
struct Node {
    std::string key;
    value_type value;

    Node(std::string _key, value_type _value)
            : key(std::move(_key)), value(std::move(_value)) {}
};

template<typename value_type>
class Map {
private:
    const size_t size_ = 100000;
    std::vector<std::vector<Node<value_type>>> array_;

    [[nodiscard]] size_t hash(const std::string &needle) const {
        size_t x = 0;
        for (char i : needle) {
            x = (size_t) (26 * x + (i - 'a') + 1);
            x %= size_;
        }
        return x;
    }

    [[nodiscard]] size_t getIndex(const std::string &x) const {
        size_t index = hash(x);
        for (size_t i = 0; i < array_[index].size(); ++i)
            if (array_[index][i].key == x)
                return i;
        return 0;
    }

public:
    Map() : array_(size_, std::vector<Node<value_type>>()) {}

    [[nodiscard]] std::string find(const std::string &x) const {
        size_t index = hash(x);
        size_t i = getIndex(x);
        if (i == 0 && (array_[index].empty() || array_[index][i].key != x))
            return "none";
        return array_[index][i].value;
    }

    void add(const std::string &key, const std::string &value) {
        size_t index = hash(key);
        size_t i = getIndex(key);
        if (i == 0 && (array_[index].empty() || array_[index][i].key != key)) {
            Node<value_type> tmp(key, value);
            array_[index].push_back(tmp);
        } else {
            array_[index][i].value = value;
        }
    }

    void remove(const std::string &x) {
        int index = hash(x);
        int i = getIndex(x);

        if (i == 0 && (array_[index].empty() || array_[index][i].key != x)) return;
        array_[index].erase(array_[index].begin() + i);
    }
};

int main() {
    std::ios_base::sync_with_stdio(false);

    std::string cmd, tmp_key, tmp_val = "null";

    std::ifstream fin("Map.in");
    std::ofstream fout("Map.out");
    fin.tie(nullptr);
    fout.tie(nullptr);

    Map<std::string> map;

    while (fin >> cmd) {
        if (cmd == "put") {
            fin >> tmp_key >> tmp_val;
            map.add(tmp_key, tmp_val);
        } else if (cmd == "get") {
            fin >> tmp_key;
            fout << map.find(tmp_key) << '\n';
        } else if (cmd == "delete") {
            fin >> tmp_key;
            map.remove(tmp_key);
        }
    }

    fout.close();
    fin.close();

    return 0;
}
