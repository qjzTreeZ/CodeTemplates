#include <bits/stdc++.h>
using namespace std;

//{{{
inline int gi() {
    int x, f = 0;
    char c;
    while (!isdigit(c = getchar())) c == '-' && (f = 1);
    for (x = c - '0'; isdigit(c = getchar()); x = x * 10 + c - '0')
        ;
    return f ? -x : x;
}

inline long long gll() {
    int f = 0;
    long long x;
    char c;
    while (!isdigit(c = getchar())) c == '-' && (f = 1);
    for (x = c - '0'; isdigit(c = getchar()); x = x * 10 + c - '0')
        ;
    return f ? -x : x;
}

template <typename T>
void puti(T x) {
    if (x < 0) putchar('-'), x = -x;
    if (x > 9) puti(x / 10);
    putchar(x % 10 + '0');
}

template <typename T>
inline void putsp(T x) {
    puti(x), putchar(' ');
}

template <typename T>
inline void putln(T x) {
    puti(x), putchar('\n');
}
//}}}

const int N = 55;
const double eps = 1e-7;
int n;
double a[N][N];
bool f1, f2;

int main() {
    n = gi();
    for (int i = 1; i <= n; ++i)
        for (int j = 1; j <= n + 1; ++j) a[i][j] = gi();
    for (int i = 1; i <= n; ++i) {
        int r = i;
        for (int j = i + 1; j <= n; ++j)
            if (fabs(a[j][i]) > fabs(a[r][i])) r = j;
        if (r != i)
            for (int k = 1; k <= n + 1; ++k) swap(a[r][k], a[i][k]);
        if (fabs(a[i][i]) < eps) continue;
        double c = a[i][i];
        for (int k = 1; k <= n + 1; ++k) a[i][k] /= c;
        for (int j = 1; j <= n; ++j)
            if (i != j) {
                c = a[j][i];
                for (int k = 1; k <= n + 1; ++k) a[j][k] -= a[i][k] * c;
            }
    }
    for (int i = 1; i <= n; ++i) {
        bool f = 1;
        for (int j = 1; j <= n; ++j) f &= fabs(a[i][j]) < eps;
        if (f) {
            if (fabs(a[i][n + 1]) < eps)
                f1 = 1;
            else
                f2 = 1;
        }
    }
    if (f2) {
        puts("-1");
        return 0;
    }
    if (f1) {
        puts("0");
        return 0;
    }
    for (int i = n; i; --i)
        for (int j = i + 1; j <= n; ++j) a[i][n + 1] -= a[i][j] * a[j][n + 1];
    for (int i = 1; i <= n; ++i)
        if (fabs(a[i][n + 1]) < eps)
            printf("x%d=0\n", i);
        else
            printf("x%d=%.2lf\n", i, a[i][n + 1]);
    return 0;
}
