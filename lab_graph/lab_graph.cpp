#include <iostream>
#include <map>
#include <set>
#include <tuple>
#include <algorithm>
#include <fstream>
#include <iterator>
#include <sstream>

struct Edge
{
    int a;
    int b;
    bool operator<(const Edge& e) const{
        return std::tie(a, b) < std::tie(e.a, e.b);
    }
};

std::istream& operator>>(std::istream& is, Edge& e) {
    is >> e.a >> e.b;
    return is;
}

std::ostream& operator<<(std::ostream& os, const Edge& e) {
    os << "(" << e.a << "," << e.b << ")";
    return os;
}

template<typename InsertIterator>
void readFromFile(InsertIterator it, const std::string& file_name) {
    std::ifstream in_file(file_name);
    if (in_file.is_open()) {
        std::copy(
            std::istream_iterator<Edge>(in_file),
            std::istream_iterator<Edge>(),
            it
        );
    }
    else {
        std::stringstream ss;
        ss << "Can't open the file \"" << file_name << "\"!";
        throw std::runtime_error(ss.str());
    }
}

template<typename Iterator>
void fillMap(std::map<int, std::set<int>>& m, Iterator it_b, Iterator it_e) {
    while (it_b != it_e) {
        const auto& edge = *it_b;
        m[edge.a].insert(edge.b);
        m[edge.b].insert(edge.a);
        ++it_b;
    }
}

std::ostream& operator<<(std::ostream& os, const std::map<int, std::set<int>>& m) {
    for (const auto& p : m) {
        os << "Node #" << p.first << std::endl;
        for (const auto& other : p.second) {
            os << "   " << other << std::endl;
        }
        os << std::endl;
    }
    return os;
}

void pause() {
    system("pause");
}


int main()
{
    std::set<Edge> es;
    std::map<int, std::set<int>> m;

    try {
        readFromFile(std::inserter(es, es.begin()), "in.txt");
    }
    catch (std::exception & e) {
        std::cerr << e.what();
        exit(1);
    }

    fillMap(m, es.begin(), es.end());
    std::cout << m;


    pause();
    return 0;
}
