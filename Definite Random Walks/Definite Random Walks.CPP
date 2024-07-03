#include <bits/stdc++.h>
using namespace std;
#define sz(x) ((int) (x).size())
#define forn(i,n) for (int i = 0; i < int(n); ++i)
typedef long long ll;
typedef long long i64;
typedef long double ld;
typedef pair<int, int> pii;
const int inf = int(1e9) + int(1e5);
const ll infl = ll(2e18) + ll(1e10);

const int mod = 998244353;
const int root = 787603194;
const int LG = 19;

int add(int a, int b) {
    a += b;
    if (a >= mod)
        a -= mod;
    return a;
}

int sub(int a, int b) {
    return add(a, mod - b);
}

void addTo(int &a, int b) {
    a += b;
    if (a >= mod)
        a -= mod;
}

int mul(ll a, ll b) {
    return a * b % mod;
}

int binpow(int a, int deg) {
    int res = 1;
    while (deg) {
        if (deg & 1)
            res = mul(res, a);
        deg >>= 1;
        a = mul(a, a);
    }
    return res;
}

int rev(int x) {
    assert(x != 0);
    return binpow(x, mod - 2);
}

int divide(int a, int b) {
    return mul(a, rev(b));
}

vector<int> ang[2][LG + 1];

void initFFT() {
    int rroot = rev(root);
    int x0 = 1, x1 = 1;
    ang[0][LG].resize(1 << LG);
    ang[1][LG].resize(1 << LG);
    forn (i, 1 << LG) {
        ang[0][LG][i] = x0;
        ang[1][LG][i] = x1;
        x0 = mul(x0, root);
        x1 = mul(x1, rroot);
    }
    for (int lg = LG - 1; lg >= 0; --lg) {
        forn (q, 2) {
            ang[q][lg].resize(1 << lg);
            forn (i, 1 << lg)
                ang[q][lg][i] = ang[q][lg + 1][i * 2];
        }
    }
}

void recFFT(int *a, int lg, bool inv) {
    if (lg == 0)
        return;
    int hlen = (1 << lg) >> 1;
    recFFT(a, lg - 1, inv);
    recFFT(a + hlen, lg - 1, inv);
    forn (i, hlen) {
        int u = a[i];
        int v = mul(ang[inv][lg][i], a[i + hlen]);
        a[i] = add(u, v);
        a[i + hlen] = sub(u, v);
    }
}

void FFT(int *a, int n, bool inv) {
    int lg = 0;
    while ((1 << lg) < n)
        ++lg;
    assert(n == (1 << lg));
    int j = 0, bit;
    for (int i = 1; i < n; ++i) {
        for (bit = n >> 1; j & bit; bit >>= 1)
            j ^= bit;
        j ^= bit;
        if (i < j)
            swap(a[i], a[j]);
    }
    recFFT(a, lg, inv);
    if (inv) {
        int rn = rev(n);
        forn (i, n)
            a[i] = mul(a[i], rn);
    }
}

void mul(int *a, int *b, int n) {
    FFT(a, n, false);
    if (a != b)
        FFT(b, n, false);
    forn (i, n)
        a[i] = mul(a[i], b[i]);
    FFT(a, n, true);
}

void cyclicMul(int *a, int *b, int n, int pre, int len) {
    mul(a, b, n);
    int j = 0;
    forn (i, n) {
        if (j < i) {
            addTo(a[j], a[i]);
            a[i] = 0;
        }
        ++j;
        if (j == pre + len)
            j -= len;
    }
}

const int maxn = 100100;
int ans[maxn];
int to[maxn];
vector<int> g[maxn];
int p[maxn];
bool used[maxn];
map<int, vector<int>> byLen;
int a[1 << LG];
int _a[1 << LG];
int cur[1 << LG];
int N, M, K;

int calcSize(int u, int root) {
    int cnt = 1;
    for (int v: g[u])
        if (v != root)
            cnt += calcSize(v, root);
    return cnt;
}

int tmp[1 << LG];
void powk(int n, int pre, int len) {
    forn (i, n)
        a[i] = 0;
    a[0] = rev(N);
    int deg = K;
    while (deg) {
        if (deg & 1) {
            forn (i, n)
                tmp[i] = cur[i];
            cyclicMul(a, tmp, n, pre, len);
        }
        deg >>= 1;
        cyclicMul(cur, cur, n, pre, len);
    }
}

int ROOT;
int in[maxn];
int out[maxn];
int ord[maxn];
int byh[maxn];
int h[maxn];
int timer;

void dfs1(int u, int ch) {
    ord[timer] = u;
    in[u] = timer++;
    h[u] = ch;
    for (int v: g[u]) {
        if (v == ROOT)
            continue;
        dfs1(v, ch + 1);
    }
    out[u] = timer;
}

const int bs = 3500;

const int blocks = maxn / bs + 2;
int bl[blocks][1 << LG];

void calcBlock(int l, int r, int cnt, int lg, int *to) {
    forn (i, 1 << lg)
        to[i] = 0;
    for (int i = l; i < r; ++i) {
        int ch = h[ord[i]];
        to[cnt - ch]++;
    }
    FFT(to, 1 << lg, false);
    forn (i, 1 << lg)
        to[i] = mul(to[i], _a[i]);
    FFT(to, 1 << lg, true);
}

void solveComponent(int root, int m) {
    ROOT = root, timer = 0;
    dfs1(root, 0);
    const int cnt = timer;
    forn (i, cnt)
        byh[i] = 0;
    forn (i, cnt) {
        int u = ord[i];
        byh[h[u]]++;
    }
    int lg = 0;
    while ((1 << lg) < m + cnt)
        ++lg;
    assert(lg <= LG);
    forn (i, m)
        _a[i] = a[i];
    for (int i = m; i < (1 << lg); ++i)
        _a[i] = 0;
    FFT(_a, 1 << lg, false);

    for (int l = 0; l + bs <= cnt; l += bs)
        calcBlock(l, l + bs, cnt, lg, bl[l / bs]);
    forn (ii, cnt) {
        int u = ord[ii];
        int ch = h[u];

        int l = in[u];
        int r = out[u];
        int lto = min(r, ((l + bs - 1) / bs) * bs);
        for (; l < lto; ++l)
            addTo(ans[u], a[h[ord[l]] - ch]);
        int rto = max(l, (r / bs) * bs);
        for (; r > rto; --r)
            addTo(ans[u], a[h[ord[r - 1]] - ch]);
        while (l < r) {
            addTo(ans[u], bl[l / bs][cnt - ch]);
            l += bs;
        }
    }
    calcBlock(0, cnt, cnt, lg, bl[blocks - 1]);
    int u = root;
    for (int i = cnt + 1; i < (1 << lg); ++i) {
        u = to[u];
        addTo(ans[u], bl[blocks - 1][i]);
    }
}

void solveLen(int len) {
    //cerr << "solveLen " << len << ":";
    //for (int x: byLen[len])
        //cerr << ' ' << x + 1;
    //cerr << '\n';

    vector<pii> v;
    for (int u: byLen[len])
        v.emplace_back(calcSize(u, u), u);
    sort(v.begin(), v.end());
    reverse(v.begin(), v.end());
    int pre = v[0].first;

    int lg = 0;
    while ((1 << lg) < (pre + len) * 2)
        ++lg;
    assert(lg <= LG);
    forn (i, 1 << lg)
        cur[i] = 0;
    int j = 0;
    forn (i, M) {
        addTo(cur[j], p[i]);
        ++j;
        if (j == pre + len)
            j -= len;
    }
    powk(1 << lg, pre, len);
    for (auto p: v) {
        while (p.first <= pre - len) {
            for (int i = pre - len; i < pre; ++i) {
                addTo(a[i], a[i + len]);
                a[i + len] = 0;
            }
            pre -= len;
        }
        solveComponent(p.second, pre + len);
    }
}

void solve() {
    forn (i, N) {
        int u = i;
        vector<int> st;
        while (!used[u]) {
            st.push_back(u);
            used[u] = true;
            u = to[u];
        }
        int len = 1;
        while (!st.empty() && st.back() != u)
            st.pop_back(), ++len;
        if (!st.empty())
            byLen[len].push_back(u);
    }
    for (const auto &p: byLen)
        solveLen(p.first);
}

int main() {
    #ifdef LOCAL
    assert(freopen("test.in", "r", stdin));
    #else
    #endif
    initFFT();

    scanf("%d%d%d", &N, &M, &K);
    forn (i, N) {
        scanf("%d", &to[i]);
        --to[i];
        g[to[i]].push_back(i);
    }
    int sum = 0;
    forn (i, M) {
        scanf("%d", &p[i]);
        addTo(sum, p[i]);
    }
    assert(sum == 1);
    solve();
    sum = 0;
    forn (i, N) {
        cout << ans[i] << '\n';
        addTo(sum, ans[i]);
    }
    assert(sum == 1);
    cerr << "time: " << clock() / 1000 << "ms\n";
}
