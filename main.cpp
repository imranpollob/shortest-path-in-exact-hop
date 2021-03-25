#include <iostream>
#include <vector>
#include <map>

using namespace std;

// Used to defined edge between nodes
class Edge
{
public:
    int to;
    int weight;
    Edge(int _to, int _weight) : to(_to), weight(_weight) {}
};

class Graph
{
public:
    Graph(vector<vector<Edge>> _edges,
          int _nodeCount,
          int _source,
          int _destination, int _hop)
        : edges(_edges),
          nodeCount(_nodeCount),
          source(_source),
          destinaton(_destination),
          hop(_hop)
    {
        next.resize(_edges.size());
        for (int i = 0; i < next.size(); i++)
        {
            next[i] = -1;
        }
    }

    int findShortesPath()
    {
        map<int, bool> mp;
        // If hop count is greater than total nodes then path is not possible
        if (hop >= nodeCount)
        {
            return 1000000000;
        }

        return findPathRecursively(source, hop, mp);
    }

    void printPath()
    {
        printPathHelper(source);
    }

private:
    vector<vector<Edge>> edges;
    vector<int> next;
    int source;
    int destinaton;
    int hop;
    int nodeCount;

    int findPathRecursively(int pos, int remainingHop, map<int, bool> &mp)
    {
        if (remainingHop == 0)
        {
            // Base case to check hope usage
            // if reached node is destination, return 0
            // return INF otherwise
            return (pos == destinaton) ? 0 : 1000000000;
        }
        // Define initial result as INF
        int res = 1000000000;
        // Mark current node in visited stack
        mp.insert({pos, true});

        // Iterate over the adjacent nodes
        for (int i = 0; i < edges[pos].size(); i++)
        {
            if (mp.find(edges[pos][i].to) == mp.end())
            {
                // If current adjacent node is not in visited stack, calculate result recursively from curernt adjacent node
                int currentRes = edges[pos][i].weight +
                                 findPathRecursively(edges[pos][i].to, remainingHop - 1, mp);
                if (currentRes < res)
                {
                    // Got better result so updating result and path
                    res = currentRes;
                    next[pos] = edges[pos][i].to;
                }
            }
        }
        // Remove current node from visited stack
        mp.erase(pos);

        return res;
    }

    // Used to print path from source to destination
    void printPathHelper(int current)
    {
        if (current == destinaton || current == -1)
        {
            cout << destinaton << endl;
            return;
        }

        cout << current << " ";

        printPathHelper(next[current]);
    }
};

int main()
{
    int n, m;
    cout << "Enter number of node: ";
    cin >> n;

    cout << "Enter number of edge: ";
    cin >> m;

    n = 5;
    m = 8;

    vector<vector<Edge>> edges(n);

    for (int i = 0; i < m; i++)
    {
        int from, to, weight;

        cout << "Enter edge " << (i + 1) << endl;
        cout << "Enter start vertex: ";
        cin >> from;

        cout << "Enter to vertex: ";
        cin >> to;

        cout << "Enter weight: ";
        cin >> weight;

        edges[from].push_back(Edge(to, weight));
    }

    int source, destination, hop;
    cout << "Enter source vertex: ";
    cin >> source;

    cout << "Enter destination vertex: ";
    cin >> destination;

    cout << "Enter number of hop: ";
    cin >> hop;

    Graph graph(edges, n, source, destination, hop);

    int shortestPathWight = graph.findShortesPath();

    if (shortestPathWight == 1000000000)
    {
        cout << "No path possible path with selected hop" << endl;
    }
    else
    {
        cout << "Shortest weighted path sum: " << shortestPathWight << endl;
        cout << "Selected path: ";
        graph.printPath();
    }

    return 0;
}