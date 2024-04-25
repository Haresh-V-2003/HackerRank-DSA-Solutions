#include <cstdio>
#include <map>
#include <utility>
#include <vector>
using namespace std;

#define REP(i, n) for (int i = 0; i < (n); i++)
#define ROF(i, a, b) for (int i = (b); --i >= (a); )
#define pb push_back
#define se second

int ri()
{
  int x;
  scanf("%d", &x);
  return x;
}

const int N = 100000;
int color[N], dfn_in[N], dfn_out[N], preorder[N], nxt[N], fenwick[N], ans[N];
vector<int> e[N];

void add(int n, int i, int v)
{
  for (; i < n; i |= i+1)
    fenwick[i] += v;
}

int getSum(int i)
{
  int s = 0;
  for (; i; i &= i-1)
    s += fenwick[i-1];
  return s;
}

void dfs(int v, int p)
{
  static int tick = 0;
  preorder[tick] = v;
  dfn_in[v] = tick++;
  for (int u: e[v])
    if (u != p)
      dfs(u, v);
  dfn_out[v] = tick;
}

void dfs2(int n, int v, int p)
{
  ans[v] = getSum(dfn_out[v]);
  add(n, dfn_in[v], -1);
  if (nxt[v] >= 0)
    add(n, dfn_in[nxt[v]], 1);
  for (int u: e[v])
    if (u != p)
      dfs2(n, u, v);
}

int main()
{
  int n = ri(), m = ri(), root = ri()-1;
  REP(i, n-1) {
    int v = ri()-1, u = ri()-1;
    e[v].pb(u);
    e[u].pb(v);
  }
  REP(i, n)
    color[i] = ri();

  dfs(root, -1);
  map<int, int> last;
  ROF(i, 0, n) {
    int col = color[preorder[i]];
    nxt[preorder[i]] = last.count(col) ? last[col] : -1;
    last[col] = preorder[i];
  }
  for (auto x: last)
    add(n, dfn_in[x.se], 1);
  dfs2(n, root, -1);

  while (m--)
    printf("%d\n", ans[ri()-1]);
}
