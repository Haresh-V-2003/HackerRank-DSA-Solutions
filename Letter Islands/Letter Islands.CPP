#include <algorithm>
#include <climits>
#include <cstdio>
#include <cstring>
#include <map>
#include <set>
#include <stack>
#include <utility>
using namespace std;
#include <ext/pb_ds/assoc_container.hpp>
#include <ext/pb_ds/tree_policy.hpp>
using namespace __gnu_pbds;

typedef long long ll;
typedef pair<int, int> pii;
#define FOR(i, a, b) for (int i = (a); i < (b); i++)
#define REP(i, n) for (int i = 0; i < (n); i++)
#define ROF(i, a, b) for (int i = (b); --i >= (a); )

struct Pos {
  static int id;
  set<int> a;
  tree<pii, null_type, less<pii>, rb_tree_tag, tree_order_statistics_node_update> d;
  int countLT(int key) { return d.order_of_key(pii(key, 0)); }
  size_t size() { return a.size(); }
  void insert(int i) {
    a.insert(i);
    auto it = a.lower_bound(i);
    auto prev = it, next = it;
    if (it != a.begin()) --prev;
    if (it != a.end()) ++next;
    if (it != prev) {
      d.insert(pii{*it-*prev, id++});
      if (it != next && next != a.end())
        d.erase(d.lower_bound(pii{*next-*prev, 0}));
    }
    if (it != next && next != a.end())
      d.insert(pii{*next-*it, id++});
  }
  void join(Pos &b) {
    for (int x: b.a)
      insert(x);
  }
  Pos() = default;
  Pos(Pos &&b) {
    a.swap(b.a);
    d.swap(b.d);
  }
  Pos &operator=(Pos &&b) noexcept {
    a.swap(b.a);
    d.swap(b.d);
    return *this;
  }
};

int Pos::id = 0, n, k;
ll ans;

namespace KoAluru
{
  bool *t;
  int *b;

  template<typename T>
  void bucket(T a[], int n, int k, bool end)
  {
    fill_n(b, k, 0);
    REP(i, n) b[a[i]]++;
    if (end)
      FOR(i, 1, k) b[i] += b[i-1];
    else {
      int s = 0;
      REP(i, k)
        s += b[i], b[i] = s-b[i];
    }
  }

  template<typename T>
  void plus_to_minus(T a[], int sa[], int n, int k)
  {
    bucket(a, n, k, false);
    sa[b[a[n-1]]++] = n-1;
    REP(i, n-1) {
      int j = sa[i]-1;
      if (j >= 0 && ! t[j])
        sa[b[a[j]]++] = j;
    }
  }

  template<typename T>
  void minus_to_plus(T a[], int sa[], int n, int k)
  {
    bucket(a, n, k, true);
    ROF(i, 0, n) {
      int j = sa[i]-1;
      if (j >= 0 && t[j])
        sa[--b[a[j]]] = j;
    }
  }

  template<typename T>
  void ka(T a[], int sa[], int n, int k)
  {
    t[n-1] = false;
    ROF(i, 0, n-1)
      t[i] = a[i] < a[i+1] || a[i] == a[i+1] && t[i+1];
    bool minor = 2 * count(t, t+n, false) > n;

    bucket(a, n, k, minor);
    fill_n(sa, n, -1);
    if (minor) {
      REP(i, n)
        if (t[i])
          sa[--b[a[i]]] = i;
      plus_to_minus(a, sa, n, k);
      minus_to_plus(a, sa, n, k);
    } else {
      sa[b[a[n-1]]++] = n-1;
      REP(i, n-1)
        if (! t[i])
          sa[b[a[i]]++] = i;
      minus_to_plus(a, sa, n, k);
      plus_to_minus(a, sa, n, k);
    }

    int last = -1, name = 0, nn = count(t, t+n, minor);
    int *sa2, *pi;
    if (minor)
      sa2 = sa, pi = sa+n-nn;
    else
      sa2 = sa+n-nn, pi = sa;
    fill_n(b, n, -1);
    REP(i, n)
      if (sa[i] >= 0 && minor == t[sa[i]]) {
        bool diff = last == -1;
        int p = sa[i];
        if (! diff)
          REP(j, n) {
            if (last+j >= n || p+j >= n || a[last+j] != a[p+j] || t[last+j] != t[p+j]) {
              diff = true;
              break;
            } else if (j > 0 && (minor == t[last+j] || minor == t[p+j]))
              break;
          }
        if (diff) {
          name++;
          last = p;
        }
        b[p] = name-1;
      }
    nn = 0;
    REP(i, n)
      if (b[i] >= 0)
        pi[nn++] = b[i];

    if (name < nn)
      ka(pi, sa2, nn, name);
    else
      REP(i, nn)
        sa2[pi[i]] = i;

    ROF(i, 0, nn)
      t[i] = a[i] < a[i+1] || a[i] == a[i+1] && t[i+1];

    nn = 0;
    bucket(a, n, k, minor);
    if (minor) {
      REP(i, n)
        if (minor == t[i])
          pi[nn++] = i;
      REP(i, nn)
        sa[i] = pi[sa2[i]];
      ROF(i, 0, nn) {
        int j = sa[i];
        sa[i] = -1;
        sa[--b[a[j]]] = j;
      }
    } else {
      REP(i, n)
        if (minor == t[i])
          pi[nn++] = i;
      ROF(i, 0, nn)
        sa[n-nn+i] = pi[sa2[i]];
      REP(i, nn) {
        int j = sa[n-nn+i];
        sa[n-nn+i] = -1;
        sa[b[a[j]]++] = j;
      }
    }
    if (minor)
      plus_to_minus(a, sa, n, k);
    else
      minus_to_plus(a, sa, n, k);
  }

  template<typename T>
  void main(T a[], int sa[], int b[], int n, int k)
  {
    if (n > 0) {
      KoAluru::b = b;
      t = new bool[n];
      ka(a, sa, n, k);
      delete[] t;
    }
  }

  template<typename T>
  void calc_rank_lcp(T a[], int sa[], int n, int rank[], int lcp[])
  {
    REP(i, n)
      rank[sa[i]] = i;
    int k = 0;
    lcp[0] = 0;
    FOR(i, 0, n)
      if (rank[i]) {
        for (int j = sa[rank[i]-1]; i+k < n && j+k < n && a[i+k] == a[j+k]; k++);
        lcp[rank[i]] = k;
        k && k--;
      }
  }

  void calc_child(int lcp[], int n, int child[]) {
    stack<int> st;
    st.push(0);
    int last = -1;
    fill_n(child, n, -1);
    FOR(i, 1, n) {
      while (lcp[i] < lcp[st.top()]) {
        last = st.top();
        st.pop();
        if (lcp[i] <= lcp[st.top()] && lcp[st.top()] != lcp[last])
          child[st.top()] = last;
      }
      if (last != -1) {
        child[i-1] = last;
        last = -1;
      }
      st.push(i);
    }
    while (0 < lcp[st.top()]) {
      last = st.top();
      st.pop();
      if (0 <= lcp[st.top()] && lcp[st.top()] != lcp[last])
        child[st.top()] = last;
    }

    while (! st.empty())
      st.pop();
    st.push(0);
    FOR(i, 1, n) {
      while (lcp[i] < lcp[st.top()])
        st.pop();
      if (lcp[i] == lcp[st.top()]) {
        child[st.top()] = i;
        st.pop();
      }
      st.push(i);
    }
  }

  void top_down(int sa[], int lcp[], int child[], int l, int h, int ht, Pos &data)
  {
    int ht2;
    if (l == h-1) {
      ht2 = n-sa[l];
      data.insert(sa[l]);
    } else {
      int i = l < child[h-1] && child[h-1] < h ? child[h-1] : child[l];
      ht2 = lcp[i];
      {
        Pos cur;
        top_down(sa, lcp, child, l, i, ht2, cur);
        if (cur.size() > data.size()) swap(cur, data);
        data.join(cur);
      }
      for (; child[i] > i && lcp[child[i]] == lcp[i]; i = child[i]) {
        Pos cur;
        top_down(sa, lcp, child, i, child[i], ht2, cur);
        if (cur.size() > data.size()) swap(cur, data);
        data.join(cur);
      }
      {
        Pos cur;
        top_down(sa, lcp, child, i, h, ht2, cur);
        if (cur.size() > data.size()) swap(cur, data);
        data.join(cur);
      }
    }
    l = ht+1;
    h = ht2+1;
    while (l < h) {
      int mi = l+h >> 1;
      if (k < data.size()-data.countLT(mi+1))
        l = mi+1;
      else
        h = mi;
    }
    int from = l;
    h = ht2+1;
    while (l < h) {
      int mi = l+h >> 1;
      if (k <= data.size()-data.countLT(mi+1))
        l = mi+1;
      else
        h = mi;
    }
    ans += l-from;
  }
};

const int N = 100000;
char a[N+1];
int b[N], sa[N], rnk[N], lcp[N], child[N];

int main()
{
  scanf("%s%d", a, &k);
  n = strlen(a);
  KoAluru::main(a, sa, b, n, 127);
  KoAluru::calc_rank_lcp(a, sa, n, rnk, lcp);
  KoAluru::calc_child(lcp, n, child);
  Pos data;
  KoAluru::top_down(sa, lcp, child, 0, n, 0, data);
  printf("%lld\n", ans);
}
