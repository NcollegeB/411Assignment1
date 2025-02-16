#include <iostream>
#include <vector>
#include <stack>
#include <set>

using namespace std;

void dfs(int curr, const vector<vector<int>> &adj, vector<bool> &vis, stack<int> &finishOrder)
{
    vis[curr] = true;
    for (int neighbor : adj[curr])
    {
        if (!vis[neighbor])
        {
            dfs(neighbor, adj, vis, finishOrder);
        }
    }
    finishOrder.push(curr);
}

void dfsTranspose(int node, const vector<vector<int>> &transposedAdj, vector<bool> &vis, vector<int> &scc)
{
    vis[node] = true;
    scc.push_back(node);

    for (int neighbor : transposedAdj[node])
    {
        if (!vis[neighbor])
        {
            dfsTranspose(neighbor, transposedAdj, vis, scc);
        }
    }
}

vector<vector<int>> findSCCs(int n, vector<vector<int>> &adj, vector<int> &sccMap)
{
    stack<int> finishOrder;
    vector<bool> vis(n, false);

    for (int i = 0; i < n; i++)
    {
        if (!vis[i])
        {
            dfs(i, adj, vis, finishOrder);
        }
    }

    vector<vector<int>> transposedAdj(n);
    for (int j = 0; j < n; j++)
    {
        for (int vert : adj[j])
        {
            transposedAdj[vert].push_back(j);
        }
    }

    fill(vis.begin(), vis.end(), false);
    vector<vector<int>> sccs;

    int sccID = 0;
    while (!finishOrder.empty())
    {
        int node = finishOrder.top();
        finishOrder.pop();

        if (!vis[node])
        {
            vector<int> scc;
            dfsTranspose(node, transposedAdj, vis, scc);
            for (int v : scc)
            {
                sccMap[v] = sccID;
            }
            sccs.push_back(scc);
            sccID++;
        }
    }
    return sccs;
}

vector<vector<int>> buildCondensedGraph(int n, const vector<vector<int>> &adj, const vector<int> &sccMap, int numSCCs)
{
    vector<set<int>> condensedGraphSet(numSCCs);
    vector<vector<int>> condensedGraph(numSCCs);
    vector<int> inDegree(numSCCs, 0);
    vector<int> outDegree(numSCCs, 0);

    for (int u = 0; u < n; u++)
    {
        for (int v : adj[u])
        {
            int sccU = sccMap[u], sccV = sccMap[v];
            if (sccU != sccV) // Only add edges between SCCs
            {
                if (condensedGraphSet[sccU].count(sccV) == 0)
                {
                    condensedGraphSet[sccU].insert(sccV);
                    outDegree[sccU]++;
                    inDegree[sccV]++;
                }
            }
        }
    }

    for (int i = 0; i < numSCCs; i++)
    {
        condensedGraph[i] = vector<int>(condensedGraphSet[i].begin(), condensedGraphSet[i].end());
    }

    return condensedGraph;
}

void classifySCCs(int numSCCs, const vector<vector<int>> &condensedGraph, vector<int> &inDegree, vector<int> &outDegree, vector<int> &setA, vector<int> &setB, vector<int> &setC)
{
    for (int i = 0; i < numSCCs; i++)
    {
        if (inDegree[i] == 0 && outDegree[i] > 0) // No incoming edges but has outgoing → Set A
        {
            setA.push_back(i);
        }
        else if (outDegree[i] == 0) // No outgoing edges → Set B
        {
            setB.push_back(i);
        }
        else // Otherwise → Set C
        {
            setC.push_back(i);
        }
    }

    // Special case: If there's only **one SCC** containing **all nodes**, it's **entirely Set C**
    if (numSCCs == 1)
    {
        setA.clear();
        setB.clear();
        setC.push_back(0);
    }
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

    vector<int> sccMap(n, -1);
    vector<vector<int>> sccs = findSCCs(n, adj, sccMap);

    vector<vector<int>> condensedGraph = buildCondensedGraph(n, adj, sccMap, sccs.size());

    vector<int> inDegree(sccs.size(), 0), outDegree(sccs.size(), 0);
    for (int u = 0; u < condensedGraph.size(); u++)
    {
        for (int v : condensedGraph[u])
        {
            outDegree[u]++;
            inDegree[v]++;
        }
    }

    vector<int> setA, setB, setC;
    classifySCCs(sccs.size(), condensedGraph, inDegree, outDegree, setA, setB, setC);

    cout << "SCCs:\n";
    for (const auto &scc : sccs)
    {
        cout << "{ ";
        for (int node : scc)
        {
            cout << (node + 1) << " ";
        }
        cout << "}\n";
    }

    int aCount = 0;
    cout << "\nSet A (No Incoming Edges): ";
    for (int sccID : setA)
    {
        cout << "{ ";
        for (int node : sccs[sccID])
        {
            cout << (node + 1) << " ";
            aCount += 1;
        }
        cout << "} ";
    }
    cout << endl;

    int bCount = 0;
    cout << "Set B (Remaining SCCs): ";
    for (int sccID : setB)
    {
        cout << "{ ";
        for (int node : sccs[sccID])
        {
            cout << (node + 1) << " ";
            bCount += 1;
        }
        cout << "} ";
    }
    cout << endl;

    int cCount = 0;
    cout << "Set C (At Least One Outgoing Edge): ";
    for (int sccID : setC)
    {
        cout << "{ ";
        for (int node : sccs[sccID])
        {
            cout << (node + 1) << " ";
            cCount += 1;
        }

        cout << "} ";
    }
    cout << endl;

    cout << "|A| = " << aCount << ", |B| = " << bCount << ", |C| = " << cCount << endl;

    return 0;
}
