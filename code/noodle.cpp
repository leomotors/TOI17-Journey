#include <bits/stdc++.h>
using namespace std;

int N, M, K;
int noodles[100005];

bool checkAns(int64_t x) {
    priority_queue<int, vector<int>, greater<int>> selected;
    int currAmount = 0;
    int totalRes = 0;

    for (int i = 0; i < N; i++) {
        currAmount += noodles[i];
        selected.push(noodles[i]);

        // * Keep track of sum of top K values
        if (selected.size() > K) {
            currAmount -= selected.top();
            selected.pop();
        }

        if (currAmount >= x && selected.size() == K) {
            currAmount = 0;
            totalRes++;
            while (!selected.empty())
                selected.pop();

            if (totalRes >= M)
                return true;
        }
    }
    return false;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);

    cin >> N >> M >> K;

    for (int i = 0; i < N; i++) {
        cin >> noodles[i];
    }

    int64_t l = 0;
    int64_t r = 2e9;

    // * Binary Search
    while (l < r) {
        int64_t mid = (l + r) / 2 + (l + r) % 2;

        bool res = checkAns(mid);

        if (res) {
            l = mid;
        } else {
            r = mid - 1;
        }
    }

    cout << l << "\n";
}
