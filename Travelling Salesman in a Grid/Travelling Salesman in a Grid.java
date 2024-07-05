import java.io.*;
import java.util.*;

public class Solution {

  static int[] three;

  static int bit(int s, int i) {
    return s/three[i]%3;
  }

  static final int NS = 5798;
  static int ns = 0;
  static int[] mapping = new int[177147];
  static int[] states = new int[NS];
  
  static void dfs(int k, int x, int s) {
    if (k == 0) {
      if (x == 0) {
        mapping[s] = ns;
        states[ns++] = s;
      }
      return;
    }
    dfs(k-1, x, 3*s);
    if (x > 0) {
      dfs(k-1, x-1, 3*s+1);
    }
    dfs(k-1, x+1, 3*s+2);
  }

  static int n;
  static int[] cur;
  
  static void tr(int j, int s, int g, int opt) {
    s -= three[j]*bit(s, j)+three[j+1]*bit(s, j+1);
    s += three[j]*g;
    if (j == n-1) {
      if (bit(s, n) > 0) {
        return;
      }
      s *= 3;
    }
    cur[mapping[s]] = Math.min(cur[mapping[s]], opt);
  }

  
  public static void main(String[] args) throws IOException {
    BufferedReader br = new BufferedReader(new InputStreamReader(System.in));
    BufferedWriter bw = new BufferedWriter(new FileWriter(System.getenv("OUTPUT_PATH")));

    StringTokenizer st = new StringTokenizer(br.readLine());
    int m = Integer.parseInt(st.nextToken());
    n = Integer.parseInt(st.nextToken());

    if (n%2 > 0 && m%2 > 0) {
      bw.write("0");
      bw.newLine();

      bw.close();
      br.close();
      return;
    }

    int[][] horizontal = new int[m > n ? m : n][n];

    for (int i = 0; i < m; i++) {
      st = new StringTokenizer(br.readLine());

      for (int j = 0; j < n - 1; j++) {
        int item = Integer.parseInt(st.nextToken());
        horizontal[i][j] = item;
      }
    }

    int[][] vertical = new int[m > n ? m : n][n];

    for (int i = 0; i < m - 1; i++) {
      st = new StringTokenizer(br.readLine());

      for (int j = 0; j < n; j++) {
        int item = Integer.parseInt(st.nextToken());
        vertical[i][j] = item;
      }
    }

    three = new int[n+1];
    three[0] = 1;
    for (int i = 0; i < n; i++) {
      three[i+1] = three[i]*3;
    }
    dfs(n+1, 0, 0);

    int[][] tr4 = new int[ns][n];
    int[][] tr8 = new int[ns][n];
    for (int si = 0; si < ns; si++) {
      int s = states[si];
      for (int i = 0; i < n; i++) {
        int g = bit(s, i)+3*bit(s, i+1);
        if (g == 4) {
          int c = 0;
          for (int j = i+1; ; j++) {
            int b = bit(s, j);
            if (b == 1) c++;
            if (b == 2) c--;
            if (c == 0) {
              tr4[si][i] = s-three[i]*g-three[j]; // 1122 -> 0012
              break;
            }
          }
        }
        if (g == 8) {
          int c = 0;
          for (int j = i; ; j--) {
            int b = bit(s, j);
            if (b == 1) c++;
            if (b == 2) c--;
            if (c == 0) {
              tr8[si][i] = s-three[i]*g+three[j]; // 1122 -> 1200
              break;
            }
          }
        }
      }
    }
    
    int[][] dp = new int[2][ns];
    int[] pre = dp[0];
    cur = dp[1];
    Arrays.fill(cur, 0, ns, Integer.MAX_VALUE/2);
    cur[mapping[0]] = 0;
    for (int i = 0; i < m; i++)
      for (int j = 0; j < n; j++) {
        int[] tmp = pre;
        pre = cur;
        cur = tmp;
        Arrays.fill(cur, 0, ns, Integer.MAX_VALUE/2);
        for (int si = 0; si < ns; si++) {
          int s = states[si];
          int g = bit(s, j)+bit(s, j+1)*3;
          int opt = pre[si];
          switch (g) {
          case 0:
            tr(j, s, 1+3*2, opt + vertical[i][j] + horizontal[i][j]);
            break;
          case 1:
          case 3:
            tr(j, s, 1, opt + vertical[i][j]);
            tr(j, s, 3, opt + horizontal[i][j]);
            break;
          case 2:
          case 6:
            tr(j, s, 2, opt + vertical[i][j]);
            tr(j, s, 6, opt + horizontal[i][j]);
            break;
          case 5:
            tr(j, s, 0, opt);
            break;
          case 4:
            tr(j, tr4[si][j], 0, opt);
            break;
          case 8:
            tr(j, tr8[si][j], 0, opt);
            break;
          case 7:
            if (i == m-1 && j == n-1)
              tr(j, s, 0, opt);
            break;
          }
        }
      }
    bw.write(String.valueOf(cur[mapping[0]]));
    bw.newLine();

    bw.close();
    br.close();
  }
}
