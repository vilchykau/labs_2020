// lesson_04_03_2020.cpp : Этот файл содержит функцию "main". Здесь начинается и заканчивается выполнение программы.
//

#include <iostream>
#include <vector>
#include <fstream>
#include <algorithm>
#include <iterator>

struct Vertex {
    int id;
    int weight;
    bool operator<(const Vertex& other) {
        return id < other.id;
    }
};

std::ostream& operator<<(std::ostream& os, const Vertex& v) {
    os << "v(" << v.id << "," << v.weight << ")";
    return os;
}

std::istream& operator>>(std::istream& is, Vertex& v) {
    is >> v.id >> v.weight;
    return is;
}

struct Edge {
    int start;
    int end;
    int weight;
};

std::ostream& operator<<(std::ostream& os, const Edge& e) {
    os << "e(" << e.start << "," << e.end << "," << e.weight << ")";
    return os;
}

std::istream& operator>>(std::istream& is, Edge& e) {
    is >> e.start >> e.end >> e.weight;
    return is;
}

template <typename T>
void readFromFile(std::vector<T>& v, const std::string& file_name) {
    std::ifstream file(file_name);
    std::copy(std::istream_iterator<T>(file),
        std::istream_iterator<T>(),
        std::back_inserter(v));
}

int main()
{
    std::vector<Vertex> vv;
    std::vector<Edge> ve;

    readFromFile(vv, "inv.txt");
    readFromFile(ve, "ine.txt");

    auto max_it = std::max_element(vv.begin(), vv.end(), [](const auto& l, const auto& r) {
        return l.id < r.id;
    });
     
    std::vector<Vertex> vi(max_it->id + 1);

    std::for_each(vv.begin(), vv.end(), [&vi](const auto& i) {
        vi[i.id] = i;
    });

    std::cout << "Hello World!\n";
}