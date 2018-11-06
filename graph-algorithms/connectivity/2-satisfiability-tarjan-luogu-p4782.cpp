#include <bits/stdc++.h>
using namespace std;

inline int geti() {
    int x, f = 0;
    char c;
    while (!isdigit(c = getchar()))
        if (c == '-') f = 1;
    for (x = c - '0'; isdigit(c = getchar()); x = x * 10 + c - '0')
        ;
    return f ? -x : x;
}

template <typename T>
void puti(T x) {
    if (x < 0) {
        putchar('-');
        x = -x;
    }
    if (x > 9) puti(x / 10);
    putchar(x % 10 + '0');
}

template <typename T>
void putsp(T x) {
    puti(x);
    putchar(' ');
}

template <typename T>
void putln(T x) {
    puti(x);
    putchar('\n');
}

const int N = 2000010;
int n, m, e0[N], e1[N], dst[N], dfn[N], low[N], disc = 0, stk[N], top = 0, ord[N], scc = 0;
bool vis[N], ans[N];

void tarjan(int u) {
    dfn[u] = low[u] = ++disc;
    stk[++top] = u;
    vis[u] = true;
    for (int e = e0[u]; e; e = e1[e]) {
        int v = dst[e];
        if (!dfn[v]) {
            tarjan(v);
            low[u] = min(low[u], low[v]);
        } else if (vis[v])
            low[u] = min(low[u], dfn[v]);
    }
    if (dfn[u] == low[u]) {
        ++scc;
        while (int p = stk[top--]) {
            ord[p] = scc;
            vis[p] = false;
            if (p == u) break;
        }
    }
}

int main() {
    n = geti();
    m = geti();
    for (int e = 1; e <= m; ++e) {
        int i = geti(), a = geti(), j = geti(), b = geti();
        int x1 = i << 1 ^ a, x2 = j << 1 ^ b;
        e1[e << 1] = e0[x1 ^ 1];
        e0[x1 ^ 1] = e << 1;
        dst[e << 1] = x2;
        e1[e << 1 | 1] = e0[x2 ^ 1];
        e0[x2 ^ 1] = e << 1 | 1;
        dst[e << 1 | 1] = x1;
    }
    for (int i = 2; i < (n + 1) << 1; ++i)
        if (!dfn[i]) tarjan(i);
    for (int i = 1; i <= n; ++i)
        if (ord[i << 1] == ord[i << 1 | 1]) {
            puts("IMPOSSIBLE");
            return 0;
        }
    puts("POSSIBLE");
    for (int i = 1; i <= n; ++i) putsp(ord[i << 1 | 1] < ord[i << 1]);
    putchar('\n');
    return 0;
}
