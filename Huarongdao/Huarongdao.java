import java.io.*;
import java.util.*;

public class Solution {

  static int nRow, nCol;
  static int[][] board;

  static boolean valid(int row, int col) {
    return 0 <= row && row < nRow && 0 <= col && col < nCol && board[row][col] == 1;
  }

  static class Node {
    int row, col, len;

    Node() {};

    Node(int r, int c, int l) {
      row = r;
      col = c;
      len = l;
    }
  }

  static int k;
  static boolean[][] visited;
  static int[] dx = {-1, 1, 0, 0};
  static int[] dy = {0, 0, -1, 1};
  static Node[] q = new Node[50000];

  static void bfs(Node t, Node cc, int ret[]) {
      for (boolean[] visited1 : visited) {
          Arrays.fill(visited1, false);
      }

    int tail = 0;
    q[tail++] = t;
    visited[t.row][t.col] = true;

    for (int i = 0; i < 4; i++) {
      ret[i] = -2;
      int nx = cc.row + dx[i];
      int ny = cc.col + dy[i];
      if (t.row == nx && t.col == ny) {
        ret[i] = 0;
      }
      if (!valid(nx, ny)) {
        ret[i] = -1;
      }
    }

    int head = 0;
    while (head < tail) {
      Node tmp = q[head++];

      if (tmp.len == k - 1) {
        break;
      }

      for (int i = 0; i < 4; i++) {
        int nr = tmp.row + dx[i];
        int nc = tmp.col + dy[i];
        int len = tmp.len + 1;
        if (valid(nr, nc) && (nr != cc.row || nc != cc.col) && !visited[nr][nc]) {
          visited[nr][nc] = true;
          Node next = new Node(nr, nc, len);
          for (int j = 0; j < 4; j++) {
            int nx = cc.row + dx[j];
            int ny = cc.col + dy[j];
            if (nr == nx && ny == nc) {
              ret[j] = len;
              break;
            }
          }
          q[tail++] = next;
        }
      }
    }

    for (int i = 0; i < 4; i++) {
      if (ret[i] == -2) {
        ret[i] = k;
      }
    }
  }

  static int[][][][] dist;

  static void initdist() {
    for (int[][][] dist1 : dist) {
      for (int[][] dist2 : dist1) {
        for (int[] dist3 : dist2) {
          Arrays.fill(dist3, -1);
        }
      }
    }

    for (int i = 0; i < nRow; i++) {
      for (int j = 0; j < nCol; j++) {
        if (board[i][j] != 0) {
          for (int d = 0; d < 4; d++) {
            int emptyRow = i + dx[d];
            int emptyCol = j + dy[d];
            if (!valid(emptyRow, emptyCol)) continue;
            Node t = new Node(emptyRow, emptyCol, 0);
            Node cc = new Node(i, j, 0);
            bfs(t, cc, dist[i][j][d]);
          }
        }
      }
    }
  }

  static class Node2 {
    int row, col, dir;

    Node2() {};

    Node2(int r, int c, int d) {
      row = r;
      col = c;
      dir = d;
    }
  }

  static Node2 swapBlocks(Node2 cc) {
    int ndir = cc.dir <= 1 ? 1 - cc.dir : 5 - cc.dir;
    return new Node2(cc.row + dx[cc.dir], cc.col + dy[cc.dir], ndir);
  }

  static int[][][] dist2;
  static int[][][] cnt;
  static final int MAXLEN = 500000;
  static Node2[] q2 = new Node2[MAXLEN];

  static int spfa(Node cc, int[] start, Node target) {
    for (int[][] dist3 : dist2) {
      for (int[] dist4 : dist3) {
        Arrays.fill(dist4, -1);
      }
    }
    for (int[][] cnt1 : cnt) {
      for (int[] cnt2 : cnt1) {
        Arrays.fill(cnt2, 0);
      }
    }

    int tail = 0;
    for (int i = 0; i < 4; i++) {
      if (start[i] != -1) {
        int ex = cc.row + dx[i];
        int ey = cc.col + dy[i];
        if (valid(ex, ey)) {
          Node2 tmp = new Node2(cc.row, cc.col, i);
          dist2[cc.row][cc.col][i] = start[i];
          cnt[cc.row][cc.col][i]++;
          q2[tail++] = tmp;
        }
      }
    }

    int head = 0;
    while (head != tail) {
      Node2 tmp = q2[head];
      head = (head + 1) % MAXLEN;
      int tr = tmp.row;
      int tc = tmp.col;
      int td = tmp.dir;
      cnt[tr][tc][td]--;

      for (int i = 0; i < 4; i++) {
        if (i == td) {
            continue;
        }
        if (dist[tr][tc][td][i] == -1) {
            continue;
        }
        if (dist2[tr][tc][i] == -1
            || (dist2[tr][tc][i] > dist2[tr][tc][td] + dist[tr][tc][td][i])) {
          dist2[tr][tc][i] = dist2[tr][tc][td] + dist[tr][tc][td][i];
          if (cnt[tr][tc][i] == 0) {
            q2[tail] = new Node2(tr, tc, i);
            tail = (tail + 1) % MAXLEN;
            cnt[tr][tc][i]++;
          }
        }
      }

      Node2 swapped = swapBlocks(tmp);
      int r = swapped.row;
      int c = swapped.col;
      int d = swapped.dir;
      if (dist2[r][c][d] == -1 || (dist2[r][c][d] > dist2[tr][tc][td] + 1)) {
        dist2[r][c][d] = dist2[tr][tc][td] + 1;
        if (cnt[r][c][d] == 0) {
          q2[tail] = new Node2(r, c, d);
          tail = (tail + 1) % MAXLEN;
          cnt[r][c][d]++;
        }
      }
    }

    int ret = -1;
    for (int i = 0; i < 4; i++) {
      int val = dist2[target.row][target.col][i];
      if (val != -1 && (ret == -1 || val < ret)) {
          ret = val;
      }
    }

    return ret;
  }

  static class Query {
    int ex;
    int ey;
    int sx;
    int sy;
    int tx;
    int ty;
    public Query(int ex, int ey, int sx, int sy, int tx, int ty) {
      this.ex = ex;
      this.ey = ey;
      this.sx = sx;
      this.sy = sy;
      this.tx = tx;
      this.ty = ty;
    }
    @Override
    public int hashCode() {
      final int prime = 31;
      int result = 1;
      result = prime * result + ex;
      result = prime * result + ey;
      result = prime * result + sx;
      result = prime * result + sy;
      result = prime * result + tx;
      result = prime * result + ty;
      return result;
    }
    @Override
    public boolean equals(Object obj) {
      if (this == obj) return true;
      if (obj == null) return false;
      if (getClass() != obj.getClass()) return false;
      Query other = (Query) obj;
      if (ex != other.ex) return false;
      if (ey != other.ey) return false;
      if (sx != other.sx) return false;
      if (sy != other.sy) return false;
      if (tx != other.tx) return false;
      if (ty != other.ty) return false;
      return true;
    }
    
  }

  public static void main(String[] args) throws IOException {
    BufferedReader br = new BufferedReader(new InputStreamReader(System.in));
    BufferedWriter bw = new BufferedWriter(new FileWriter(System.getenv("OUTPUT_PATH")));

    StringTokenizer st = new StringTokenizer(br.readLine());
    nRow = Integer.parseInt(st.nextToken());
    nCol = Integer.parseInt(st.nextToken());
    k = Integer.parseInt(st.nextToken());
    int q = Integer.parseInt(st.nextToken());

    board = new int[nRow][nCol];
    for (int i = 0; i < nRow; i++) {
        st = new StringTokenizer(br.readLine());
      for (int j = 0; j < nCol; j++) {
        board[i][j] = Integer.parseInt(st.nextToken());
      }
    }
    visited = new boolean[nRow][nCol];
    dist = new int[nRow][nCol][4][4];
    dist2 = new int[nRow][nCol][4];
    cnt = new int[nRow][nCol][4];
    initdist();

    Map<Query, Integer> map = new HashMap<>();
    while (q-- > 0) {
      st = new StringTokenizer(br.readLine());
      int ex = Integer.parseInt(st.nextToken()) - 1;
      int ey = Integer.parseInt(st.nextToken()) - 1;
      int sx = Integer.parseInt(st.nextToken()) - 1;
      int sy = Integer.parseInt(st.nextToken()) - 1;
      int tx = Integer.parseInt(st.nextToken()) - 1;
      int ty = Integer.parseInt(st.nextToken()) - 1;

      Query query = new Query(ex, ey, sx, sy, tx, ty);
      if (map.containsKey(query)) {
        bw.write(String.valueOf(map.get(query)));
        bw.newLine();
        continue;
      }

      Node t = new Node(ex, ey, 0);
      Node cc = new Node(sx, sy, 0);
      int[] ret = new int[4];
      bfs(t, cc, ret);

      Node target = new Node(tx, ty, 0);
      int result = spfa(cc, ret, target);
      bw.write(String.valueOf(result));
      bw.newLine();

      map.put(query, result);
    }

    bw.close();
    br.close();
  }
}
