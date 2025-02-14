#include <iostream>
#include <vector>
#include <fstream>
#include <tuple>

using namespace std;

// standard dfs to determine reachability
void dfs(int curr, const vector<vector<int>> &adj, vector<bool> &vis)
{
    // curr is visited
    vis[curr] = 1;

    // check each edge if unvisited then run dfs
    for (int neighbor : adj[curr])
    {
        if (vis[neighbor] == 0)
        {
            dfs(neighbor, adj, vis);
        }
    }
}

vector<vector<bool>> isReachable(int n, const vector<vector<int>> adj)
{
    // initialize all values to false and makes matrix
    vector<vector<bool>> reachable(n, vector<bool>(n, false));

    for (int u = 0; u < n; u++)
    {
        vector<bool> visited(n, false);
        dfs(u, adj, visited); // fun DFS from node u

        for (int v = 0; v < n; v++)
        {
            if (visited[v])
            {
                reachable[u][v] = true; // mark as reachable
            }
        }
    }
    return reachable;
}

int main()
{

    int n, m, u, v;

    cin >> n >> m;

    vector<vector<int>> adj(n);

    for (int i = 0; i < m; i++)
    {
        cin >> u >> v;
        u--;
        v--;
        adj[u].push_back(v);
    }

    vector<vector<bool>> reachable = isReachable(n, adj);

    cout << "Reachability Matrix:\n";
    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < n; j++)
        {
            cout << (reachable[i][j] ? "1" : "0");
        }
        cout << endl;
    }

    return 0;
}