#include <iostream>
#include <vector>

using ll = long long;

const int N = 1e5 + 10;
int BIG = 350;

std::vector<int> less[N];
std::vector<int> big[N];

struct vertex{
    std::vector<int> neig;
    ll value;
};

void Optimize() {
    std::cin.tie(NULL);
    std::cout.tie(NULL);
    std::ios_base::sync_with_stdio(false);
}

int main () {
    Optimize();
    int n, m, q;
    std::cin >> n >> m >> q;

    std::vector<vertex> graph(n);
    std::vector<int> deg(n, 0);

    for (int i = 0; i < n; ++i) std::cin >> graph[i].value;

    for (int i = 0; i < m; ++i) {
        int u, v;
        std::cin >> u >> v;
        --u; --v;
        graph[u].neig.push_back(v);
        graph[v].neig.push_back(u);
        ++deg[u]; ++deg[v];
    }

    for (int i = 0; i < n; ++i) {
        for (auto v : graph[i].neig) {
            if (deg[v] > BIG) big[i].push_back(v);
            else less[i].push_back(v);
        }
    }

    std::vector<ll> persist(n, 0);

    for (int i = 0; i < q; ++i) {
        char req;
        std::cin >> req;
        if (req == '?') {
            int v;
            std::cin >> v; --v;

            if (deg[v] > BIG) {
                std::cout << graph[v].value << "\n";
                continue;
            }
            ll res = graph[v].value;
            for (auto u : graph[v].neig) {
                res += persist[u];
            }
            std::cout << res << "\n";

        } else {
            int v;
            int x;
            std::cin >> v >> x; --v;

            if (deg[v] > BIG) {
                persist[v] += x;
            } else {
                for (int u : less[v]) {
                    graph[u].value += x;
                }
            }

            for (auto u : big[v]) {
                graph[u].value += x;
            }
        }
    }


    return 0;
}