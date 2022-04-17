#include <fstream>
#include <vector>

template<typename value_type>
struct Node {
    std::string key;
    value_type value;
    size_t order;

    Node(std::string _key, value_type _value, size_t _order)
    : key(std::move(_key)), value(std::move(_value)), order(_order) {}
};

template<typename value_type>
class LinkedMap {
private:
    const size_t size_ = 100000;
    size_t counter_;

    std::vector<std::vector<Node<value_type>>> array_;
    std::vector<std::string> queue_;

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
    LinkedMap() : array_(size_, std::vector<Node<value_type>>()), queue_(), counter_(0) {}

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
            Node<value_type> tmp(key, value, counter_);
            array_[index].push_back(tmp);
            queue_.push_back(key);
            ++counter_;
        } else
            array_[index][i].value = value;
    }

    void remove(const std::string &x) {
        size_t index = hash(x);
        size_t i = getIndex(x);

        if (i == 0 && (array_[index].empty() || array_[index][i].key != x))
            return;

        size_t j = array_[index][i].order;
        for (size_t k = j; k < queue_.size(); ++k) {
            size_t index_tmp = hash(queue_[k]);
            size_t i_tmp = getIndex(queue_[k]);
            array_[index_tmp][i_tmp].order -= 1;
        }
        queue_.erase(queue_.begin() + j);
        --counter_;
        array_[index].erase(array_[index].begin() + i);
    }

    [[nodiscard]] std::string before(const std::string &x) const {
        if (queue_.empty() || queue_[0] == x)
            return "none";

        size_t index = hash(x);
        size_t i = getIndex(x);
        if (i == 0 && (array_[index].empty() || array_[index][i].key != x))
            return "none";

        i = array_[index][i].order;
        if (i < 1)
            return "none";
        return find(&queue_[i - 1]);
    }

    [[nodiscard]] std::string after(const std::string &x) const {
        if (queue_.empty() || queue_[queue_.size() - 1] == x)
            return "none";

        int index = hash(x);
        int i = getIndex(x);
        if (i == 0 && (array_[index].empty() || array_[index][i].key != x))
            return "none";

        i = array_[index][i].order;
        if (i > queue_.size() - 1)
            return "none";
        return find(&queue_[i + 1]);
    }
};

int main() {
    std::ios_base::sync_with_stdio(false);

    std::string cmd, tmp_key, tmp_val = "null";

    std::ifstream fin("Map.in");
    std::ofstream fout("Map.out");
    fin.tie(nullptr);
    fout.tie(nullptr);

    LinkedMap<std::string> linkedMap;

    while (fin >> cmd) {
        if (cmd == "put") {
            fin >> tmp_key >> tmp_val;
            linkedMap.add(tmp_key, tmp_val);
        } else if (cmd == "get") {
            fin >> tmp_key;
            fout << linkedMap.find(tmp_key) << '\n';
        } else if (cmd == "delete") {
            fin >> tmp_key;
            linkedMap.remove(tmp_key);
        } else if (cmd == "prev") {
            fin >> tmp_key;
            fout << linkedMap.before(tmp_key) << '\n';
        } else if (cmd == "next") {
            fin >> tmp_key;
            fout << linkedMap.after(tmp_key) << '\n';
        }
    }

    fout.close();
    fin.close();

    return 0;
}
