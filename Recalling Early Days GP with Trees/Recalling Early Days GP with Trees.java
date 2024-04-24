import java.io.BufferedReader;
import java.io.BufferedWriter;
import java.io.FileInputStream;
import java.io.FileWriter;
import java.io.IOException;
import java.io.InputStreamReader;
import java.util.Deque;
import java.util.LinkedList;
import java.util.List;
import java.util.StringTokenizer;

public class Solution2 {

  static final int LOGN = 17;
  static final int MOD = 100_711_433;

  static long power(long a, int n) {
    long r = 1;
    for (; n > 0; n >>= 1, a = a*a%MOD) {
      if ((n & 1) > 0) {
        r = r*a%MOD;
      }
    }
    return r;
  }

  static long add(long x, long y) {
    return (x+y)%MOD;
  }

  static int inv(int x) {
    long r = 1;
    for (; x > 1; x = MOD%x) {
      r = MOD/x * -r % MOD;
    }
    return (int) r;
  }

  static int[] dep;
  static int[][] par;
  static List<Integer>[] e;
  
  static class Node {
    int d;
    int v;
    int p;
    Node(int d, int v, int p) {
      this.d = d;
      this.v = v;
      this.p = p;
    }
  }
  
  static void dfs(int d, int v, int p) {
    Deque<Node> queue = new LinkedList<>();
    queue.add(new Node(d, v, p));
    while (!queue.isEmpty()) {
      Node node = queue.poll();
      dep[node.v] = node.d;
      par[0][node.v] = node.p;
      for (int u: e[node.v]) {
        if (u != node.p) {
          queue.add(new Node(node.d+1, u, node.v));
        }
      }
    }
  }

  static int r;
  static int invr;
  static long[] d;
  static long[] dd;
  
  static class Node2 {
    int v;
    int p;
    boolean start = true;
    Node2(int v, int p) {
      this.v = v;
      this.p = p;
    }
  }
  
  static void dfs2(int v, int p) {
    Deque<Node2> queue = new LinkedList<>();
    queue.add(new Node2(v, p));
    while (!queue.isEmpty()) {
      Node2 node = queue.peek();
      if (node.start) {
        for (int u: e[node.v]) {
          if (u != node.p) {
            queue.push(new Node2(u, node.v));
          }
        }
        node.start = false;
      } else {
        if (node.p >= 0) {
          d[node.p] = add(d[node.p], d[node.v] * r);
          dd[node.p] = add(dd[node.p], dd[node.v] * invr);
        }
        queue.remove();
      }
    }
  }

  static long[] path;

  static class Node3 {
    int v;
    int p;
    long s;
    Node3(int v, int p, long s) {
      this.v = v;
      this.p = p;
      this.s = s;
    }
  }
  
  static void dfs3(int v, int p, long s) {
    Deque<Node3> queue = new LinkedList<>();
    queue.add(new Node3(v, p, s));
    while (!queue.isEmpty()) {
      Node3 node = queue.poll();
      path[node.v] = (node.s+d[node.v]+dd[node.v])%MOD;
      for (int u: e[node.v]) {
        if (u != node.p) {
          queue.push(new Node3(u, node.v, (node.s+d[node.v]+dd[node.v])%MOD));
        }
      }
    }    
  }

  static int lca(int v, int u) {
    if (dep[v] < dep[u]) {
      int temp = v;
      v = u;
      u = temp;
    }
    for (int i = LOGN; --i >= 0; ) {
      if (1 << i <= dep[v]-dep[u]) {
        v = par[i][v];
      }
    }
    if (v == u) {
      return v;
    }
    for (int i = LOGN; --i >= 0; ) {
      if (par[i][v] != par[i][u]) {
        v = par[i][v];
        u = par[i][u];
      }
    }
    return par[0][v];
  }

  public static void main(String[] args) throws IOException {
    BufferedReader br = new BufferedReader(new InputStreamReader(System.in));
    BufferedWriter bw = new BufferedWriter(new FileWriter(System.getenv("OUTPUT_PATH")));

    StringTokenizer st = new StringTokenizer(br.readLine());
    int n = Integer.parseInt(st.nextToken());
    r = Integer.parseInt(st.nextToken()) % MOD;
    invr = r > 0 ? inv(r) : 0;
    e = new List[n];
    for (int i = 0; i < n; i++) {
      e[i] = new LinkedList<>();
    }
    for (int i = 0; i < n-1; i++) {
      st = new StringTokenizer(br.readLine());
      int u = Integer.parseInt(st.nextToken())-1;
      int v = Integer.parseInt(st.nextToken())-1;
      e[v].add(u);
      e[u].add(v);
    }
    dep = new int[n];
    par = new int[LOGN][n];
    dfs(0, 0, -1);    
    for (int j = 1; j < LOGN; j++) {
      for (int i = 0; i < n; i++) {
        par[j][i] = par[j-1][i] < 0 ? -1 : par[j-1][par[j-1][i]];
      }
    }
    st = new StringTokenizer(br.readLine());
    int upd = Integer.parseInt(st.nextToken());
    int q = Integer.parseInt(st.nextToken());
    d = new long[n];
    dd = new long[n];
    for (int i=0; i < upd; i++) {
      st = new StringTokenizer(br.readLine());
      int v = Integer.parseInt(st.nextToken()) - 1;
      int u = Integer.parseInt(st.nextToken()) - 1;
      int w = lca(v, u);
      int x = Integer.parseInt(st.nextToken());

      if (r > 0) {
        long xl = power(r, dep[v]-dep[w]), xr = power(r, dep[u]-dep[w]);
        d[v] = add(d[v], x);
        if (w > 0) {
          d[par[0][w]] = add(d[par[0][w]], - (x * xl % MOD * r));
        }
        dd[u] = add(dd[u], x * xl % MOD * xr);
        dd[w] = add(dd[w], - x * xl);
      } else {
        d[v] = add(d[v], x);
      }
    }
    dfs2(0, -1);
    path = new long[n];
    dfs3(0, -1, 0);
    for (int i=0; i < q; i++) {
      st = new StringTokenizer(br.readLine());
      int v = Integer.parseInt(st.nextToken()) - 1;
      int u = Integer.parseInt(st.nextToken()) - 1;
      int w = lca(v, u);
      long result = ((path[v]+path[u]-path[w]-(w > 0 ? path[par[0][w]] : 0)) % MOD + MOD) % MOD;
      bw.write(String.valueOf(result) + "\n");
    }
    
    bw.newLine();
    bw.close();
    br.close();
  }  
}
