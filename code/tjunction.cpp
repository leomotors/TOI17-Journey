// * Using WTF Algorithm

#include <bits/stdc++.h>
using namespace std;

int N;

vector<pair<int, int>> adjList[80005];
vector<int> dfsArray;
set<int> seen;

void dfs(int n) {
    if (seen.find(n) != seen.end())
        return;
    seen.insert(n);
    for (auto &p : adjList[n]) {
        if (seen.find(p.first) != seen.end())
            continue;
        dfsArray.push_back(p.second);
        dfs(p.first);
    }
}

bool checkAns(int64_t x) {
    int currW = 0;
    int groups = 0;
    for (auto w : dfsArray) {
        currW += w;

        if (currW >= x) {
            groups++;
            currW = 0;
            if (groups >= 3)
                return true;
        }
    }

    return false;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);

    cin >> N;

    int lenSum = 0;
    for (int i = 0; i < N; i++) {
        int u, v, l;
        cin >> u >> v >> l;
        adjList[u].push_back({v, l});
        adjList[v].push_back({u, l});
        lenSum += l;
    }

    for (int i = 0; i < N; i++) {
        sort(adjList[i].begin(), adjList[i].end(),
             [](const pair<int, int> &a, const pair<int, int> &b) {
                 return a.second < b.second;
             });
    }

    int leaf = -1;
    for (int i = 0; i < N; i++) {
        if (adjList[i].size() == 1) {
            leaf = i;
            break;
        }
    }

    dfs(leaf);

    int64_t l = 0;
    int64_t r = lenSum;
    while (l < r) {
        int64_t mid = (l + r) / 2 + (l + r) % 2;

        if (checkAns(mid)) {
            l = mid;
        } else {
            r = mid - 1;
        }
    }

    cout << l << "\n";
}
