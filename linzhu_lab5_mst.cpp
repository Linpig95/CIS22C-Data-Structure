#include "Linzhu_lab_util.h"
#include <vector>
#include <list>
#include <limits>
#include <string>
#include <utility>  
#include <fstream>
#include <unordered_map>
#include <limits>
using namespace std;

DynamicArray<string> cities;


template <class T>
class Edge
{
private:
    int v_;
    int w_;
    T weight_;
public:
    Edge()
        : v_(0),
          w_(0),
          weight_(T())
    {}
    Edge(int v, int w, T weight)
        : v_(v),
          w_(w),
          weight_(weight)
    {
    }
    Edge(const Edge<T> &other)
        : v_(other.v_),
          w_(other.w_),
          weight_(other.weight_)
    {
    }
    T weight() { return weight_; }
    int either() { return v_; }
    int other(int vertex) { return vertex == v_ ? w_ : v_; }
    bool operator==(const Edge &other) { return other.weight_ == weight_; }
    bool operator>(const Edge &other) { return other.weight_ > weight_; }
    bool operator<(const Edge &other) { return other.weight_ < weight_; }

};

template <class T>
class EdgeWeightedGraph
{
private:
    int V_;
    int E_;
    DynamicArray<DynamicArray<Edge<T>>> adj_;
public:
    EdgeWeightedGraph(int V)
        : V_(V),
          E_(0)
    {
        for (int i = 0; i < V_; i++)
        {
            adj_.push_back(DynamicArray<Edge<T>>());
        }
    }
    int V() { return V_; }
    int E() { return E_; }
    void add_edge(Edge<T> e)
    {
        int v = e.either();
        int w = e.other(v);
        adj_[v].push_back(e);
        adj_[w].push_back(e);
        E_++;
    }
    int degree(int vertex)
    {
        return adj_[vertex].size();
    }
    void set_E(int E) { E_ = E; }
    DynamicArray<Edge<T>>& adj(int i)
    {
        return adj_[i];
    }
};

template <class T>
class PrimMST
{
private:
    DynamicArray<Edge<T>> edge_to_;
    DynamicArray<double> dist_to_;
    DynamicArray<bool> marked_;
    PriorityQueue<double> pq_;
public:
    void scan(EdgeWeightedGraph<T>& graph, int v)
    {
        marked_[v] = true;
        for (int i = 0; i < graph.adj(v).size(); i++)
        {
            Edge<T> e = graph.adj(v)[i];
            int w = e.other(v);
            if (marked_[w]) continue;
            if (e.weight() < dist_to_[w]) {
                dist_to_[w] = e.weight();
                edge_to_[w] = e;
                if (pq_.contains(w)) pq_.decrease_key(w, dist_to_[w]);
                else pq_.push(w, dist_to_[w]);
            }
        }
    }
    void prim(EdgeWeightedGraph<T>& graph, int s)
    {
        dist_to_[s] = 0.0;
        pq_.push(s, dist_to_[s]);
        while (!pq_.empty())
        {
            int v = pq_.pop();
            scan(graph, v);
        }
    }
    PrimMST(EdgeWeightedGraph<T>& graph)
        : pq_(graph.V())
    {
        edge_to_.resize(graph.V());
        dist_to_.resize(graph.V());
        marked_.resize(graph.V());
        for (int i = 0; i < graph.V(); i++)
        {
            dist_to_[i] = numeric_limits<double>::max();
        }
        for (int i = 0; i < graph.V(); i++)
        {
            if (!marked_[i]) prim(graph, i);
        }
    }
    DynamicArray<Edge<T>> edges()
    {
        DynamicArray<Edge<T>> queue;
        for (int v = 0; v < edge_to_.size(); v++)
        {
            Edge<T> e = edge_to_[v];
            if (e.weight() > 0)
                queue.push_back(e);
        }
        return queue;
    }
    double weight()
    {
        double weight = 0.0;
        DynamicArray<Edge<T>> es = edges();
        for (int i = 0; i < es.size(); i++)
        {
            weight += es[i].weight();
        }
        return weight;
    }
};

int main()
{
    unordered_map<string, int> city_vertex_mapping;
    unordered_map<int, string> vertex_city_mapping;
    ifstream fin("traveling_graph.txt");
    int V;
    fin >> V;
    int E;
    fin >> E;
    int i = 0;
    fin.get();
    fin.get();
    DynamicArray<Edge<int>> edges;
    EdgeWeightedGraph<int> graph(V);
    graph.set_E(E);
    while (fin.good())
    {
        string city1;
        getline(fin, city1, ',');
        string city2;
        getline(fin, city2, ',');
        string weight_str;
        getline(fin, weight_str, '\n');
        int weight = stoi(weight_str);
        cout << city1 << '\t' << city2 << '\t' << weight << endl;
        int v, w;
        if (city_vertex_mapping.find(city1) == city_vertex_mapping.end()) {
            cout << city1 << " not found. Existing cities are" << endl;
            for (auto city : city_vertex_mapping)
            {
                cout << city.first << ", ";
            }
            cout << endl;

            city_vertex_mapping[city1] = i;
            vertex_city_mapping[i] = city1;
            v = i;
            i++;
            cout << i << " cities added" << endl;
        } else {
            v = city_vertex_mapping[city1];
        }
        if (city_vertex_mapping.find(city2) == city_vertex_mapping.end()) {
            cout << city2 << " not found. Existing cities are" << endl;
            for (auto city : city_vertex_mapping)
            {
                cout << city.first << ", ";
            }
            cout << endl;
            city_vertex_mapping[city2] = i;
            vertex_city_mapping[i] = city2;
            w = i;
            i++;
            cout << i << " cities added" << endl;
        } else {
            w = city_vertex_mapping[city2];
        }
        edges.push_back(Edge<int>(v, w, weight));
        graph.add_edge(edges.back());
    }
    PrimMST<int> mst(graph);
    auto es = mst.edges();
    cout << "MST is: " << endl;
    for (int i = 0; i < es.size(); i++)
    {
        int v = es[i].either();
        int w = es[i].other(v);
        cout << "(" << vertex_city_mapping[v] << ", "
             << vertex_city_mapping[w] << ", "
             << es[i].weight() << ")" << endl;
    }
    cout << mst.weight() << endl;
    return 0;

}