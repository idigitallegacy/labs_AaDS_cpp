#include <fstream>
#include <utility>
#include <vector>

template<typename value_type>
struct Node {
    std::string key;
    value_type value;

    Node(std::string _key, value_type _value)
    : key(std::move(_key))
    , value(std::move(_value))
    {}
};

template<typename value_type>
class Set {
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
    Set() : array_(size_, std::vector<Node<value_type>>()) {}

    [[nodiscard]] bool find(const std::string &x) const {
        size_t index = hash(x);
        size_t i = getIndex(x);

        if (i == 0 && (array_[index].empty() || array_[index][i].key != x))
            return false;
        return true;
    }

    void push(const std::string &key, const value_type &value) {
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
        size_t index = hash(x);
        size_t i = getIndex(x);

        if (i == 0 && (array_[index].empty() || array_[index][i].key != x))
            return;

        array_[index].erase(array_[index].begin() + i);
    }
};

int main() {
    std::ios_base::sync_with_stdio(false);

    std::string cmd, tmp_key, tmp_val = "null";

    std::ifstream fin("set.in");
    std::ofstream fout("set.out");
    fin.tie(nullptr);
    fout.tie(nullptr);

    Set<std::string> set;

    while (fin >> cmd) {
        if (cmd == "insert") {
            fin >> tmp_key;
            set.push(tmp_key, tmp_val);
        } else if (cmd == "exists") {
            fin >> tmp_key;
            if (set.find(tmp_key))
                fout << "true\n";
            else
                fout << "false\n";
        } else if (cmd == "delete") {
            fin >> tmp_key;
            set.remove(tmp_key);
        }
    }

    fout.close();
    fin.close();

    return 0;
}
