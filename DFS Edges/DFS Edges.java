import java.io.*;
import java.util.*;

public class Solution {

  static List<Integer>[] g;

  static boolean left(int nodes, int f, int b) {
    for (int i = 1; i < nodes; i++) {
      g[i].add(i + 1);
    }
    int f0 = f;
    int b0 = b;
    int start = 1;
    while (f0 > 0 || b0 > 0) {
      int next = start + 1;
      if (next > nodes) {
        return false;
      }
      if (b0 > 0) {
        g[next].add(start);
        b0--;
      }      
      next++;
      while ((f0 > 0 || b0 > 0) && next <= nodes) {
        if (f0 > 0) {
          g[start].add(next);
          f0--;
        }
        if (b0 > 0) {
          g[next].add(start);
          b0--;
        }
        next++;
      }
      start++;
    }
    return true;
  }

  static boolean right(int start, int nodes, int c) {
    for (int i = start; i <= nodes; i++) {
      g[1].add(i);
    }
    int c0 = c;
    for (int i = nodes; i >= start; i--) {
      for (int j = i - 1; j > 1; j--) {
        g[i].add(j);
        c0--;
        if (c0 == 0) {
          break;
        }
      }
      if (c0 == 0) {
        break;
      }
    }
    if (c0 > 0) {
      return false;
    }
    return true;
  }

  static boolean complexn(int nodes, int t, int b, int f, int c) {
    int n = 1;
    int egges = nodes - n - 1;
    int last = nodes - n - 1;
    while (egges < c) {
      n++;
      last = egges;
      egges += nodes - n - 1;
    }
    n--;
    int left = nodes - n;
    for (int i = 1; i < left - 1; i++) {
      g[i].add(i + 1);
    }
    int crossNode = left - (c - last) - 1;
    g[crossNode].add(left);
    n = left - 1;
    int f0 = f;
    int b0 = b;
    int start = 1;
    while (f0 > 0 || b0 > 0) {
      int next = start + 1;
      if (next > n) {
        break;
      }
      if (b0 > 0) {
        g[next].add(start);
        b0--;
      }
      next++;
      while ((f0 > 0 || b0 > 0) && next <= n) {
        if (f0 > 0) {
          g[start].add(next);
          f0--;
        }
        if (b0 > 0) {
          g[next].add(start);
          b0--;
        }
        next++;
      }
      start++;
    }

    if (b0 > 0) {
      for (int i = 1; b0 > 0 && i <= crossNode; i++) {
        g[left].add(i);
        b0--;
      }
    }
    for (int i = 0; i < (c - last); i++) {
      g[left].add(crossNode + i + 1);
    }
    for (int i = 1; i < left && f0 > 0; i++) {
      g[i].add(left);
      f0--;
    }
    if (!right(left + 1, nodes, last)) {
      return false;
    }
    if (b0 > 0) {
      for (int i = left+1; b0 > 0 && i <= nodes; i++) {
        g[i].add(1);
        b0--;
      }
    }

    return true;
  }  

  static boolean complex1(int nodes, int t, int b, int f, int c) {
    int n = nodes - 1;
    for (int i = 1; i < n; i++) {
      g[i].add(i + 1);
    }
    int crossNode = nodes - c-1;
    g[crossNode].add(nodes);
    int f0 = f;
    int b0 = b;
    int start = 1;
    while (f0 > 0 || b0 > 0) {
      int next = start + 1;
      if (next > n) {
        break;
      }
      if (b0 > 0) {
        g[next].add(start);
        b0--;
      }
      next++;
      while ((f0 > 0 || b0 > 0) && next <= n) {
        if (f0 > 0) {
          g[start].add(next);
          f0--;
        }
        if (b0 > 0) {
          g[next].add(start);
          b0--;
        }
        next++;
      }
      start++;
    }

    for (int i = 1; i <= b0; i++) {
      g[nodes].add(i);
    }
    for (int i = 0; i < c; i++) {
      g[nodes].add(crossNode+i+1);
    }
    for (int i = 1; i <= f0; i++) {
      g[i].add(nodes);
    }

    return true;
  }
  
  @SuppressWarnings("unchecked")
  static boolean solve(int t, int b, int f, int c) {
    int nodes = t + 1;
    int maxEdges = nodes * (nodes - 1);
    if (t + b + f + c > maxEdges
        || f > maxEdges/2 
        || b + c > maxEdges/2) {
      return false;
    }
    g = new List[nodes + 1];
    for (int i = 1; i < g.length; i++) {
      g[i] = new ArrayList<>();
    }
    if (b + f + c == 0) {
      for (int i = 1; i < nodes; i++) {
        g[i].add(i + 1);
      }
      return true;
    }
    if (c == 0) {
      if (!left(nodes, f, b)) {
        return false;
      }
      return true;
    }
    if (b + f == 0) {
      if (!right(2, nodes, c)) {
        return false;
      }
      return true;
    }

    int n = 1;
    int egges = nodes - n-1;
    while (egges < c) {
      n++;
      egges += nodes - n-1;
    }
    int left = nodes - n;
    int tot = ((left - 1) * (left - 2)) / 2;
    if (b <= tot && f <= tot) {
      if (!left(left, f, b)) {
        return false;
      }
  
      if (!right(left + 1, nodes, c)) {
        return false;
      }
      return true;
    }
    
    if (n == 1 && complex1(nodes, t, b, f, c)) {
      return true;
    }

    if (left <= 2 && f == 0 && b < nodes) {
      if (!right(2, nodes, c)) {
        return false;
      }
      for (int i = 2; i <= b+1; i++) {
        g[i].add(1);
      }
      return true;
    }

    if (complexn(nodes, t, b, f, c)) {
      return true;
    }

    return false;
  }

  public static void main(String[] args) throws Exception {
    BufferedReader br = new BufferedReader(new InputStreamReader(System.in));
    BufferedWriter bw = new BufferedWriter(new FileWriter(System.getenv("OUTPUT_PATH")));

    StringTokenizer st = new StringTokenizer(br.readLine());

    int t = Integer.parseInt(st.nextToken());
    int b = Integer.parseInt(st.nextToken());
    int f = Integer.parseInt(st.nextToken());
    int c = Integer.parseInt(st.nextToken());

    if (solve(t, b, f, c)) {
      bw.write((g.length - 1) + "\n");
      for (int i = 1; i < g.length; i++) {
        bw.write(String.valueOf(g[i].size()));
        for (int x : g[i]) {
          bw.write(" " + x);
        }
        bw.write("\n");
      }
    } else {
      bw.write("-1");
    }

    bw.newLine();

    bw.close();
    br.close();
  }

}
