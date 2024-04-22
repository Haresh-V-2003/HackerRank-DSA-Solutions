import java.io.BufferedReader;
import java.io.BufferedWriter;
import java.io.FileInputStream;
import java.io.FileWriter;
import java.io.IOException;
import java.io.InputStreamReader;
import java.util.StringTokenizer;

public class Solution {

  static final int MOD = 1_000_003;
  static long[] d;
  static long[] p;
  static long[] dp;
  static long[] dlt;

  static long power(long a, long n) {
    long r = 1;
    for (; n > 0; n >>= 1, a = (a*a) % MOD) {
      if ((n & 1) > 0) {
        r = (r*a) % MOD;
      }
    }
    return r;
  }

  static void apply(int n, int i, long v) {
    dlt[i] += v;
    p[i] += v << Integer.numberOfLeadingZeros(i) - Integer.numberOfLeadingZeros(n);
    dp[i] = (dp[i]*power(d[i], v))%MOD;
  }

  static void mconcat(int i) {
    p[i] = p[2*i]+p[2*i+1];
    dp[i] = (dp[2*i]*dp[2*i+1])%MOD;
  }

  static void untag(int n, int i) {
    if (i < 0 || n <= i) return;
    i += n;
    for (int j, h = 31 - Integer.numberOfLeadingZeros(n); h>0; h--)
      if ((dlt[j = i >> h]) > 0) {
        apply(n, 2*j, dlt[j]);
        apply(n, 2*j+1, dlt[j]);
        dlt[j] = 0;
      }
  }

  static void add(int n, int l, int r, long v) {
    boolean lf = false;
    boolean rf = false;
    untag(n, l-1);
    untag(n, r);
    for (l += n, r += n; l < r; ) {
      if ((l & 1) > 0) {
        lf = true;
        apply(n, l++, v);
      }
      l >>= 1;
      if (lf) {
        mconcat(l-1);
      }
      if ((r & 1) > 0) {
        rf = true;
        apply(n, --r, v);
      }
      r >>= 1;
      if (rf) {
        mconcat(r);
      }
    }
    for (l--; (l >>= 1) > 0 && (r >>= 1) > 0; ) {
      if (lf || l == r) {
        mconcat(l);
      }
      if (rf && l != r) {
        mconcat(r);
      }
    }
  }
  
  static long[] query(int n, int l, int r) {
    long ps = 0;
    long dps = 1;
    untag(n, l-1);
    untag(n, r);
    for (l += n, r += n; l < r; l >>= 1, r >>= 1) {
      if ((l & 1) > 0) {
        ps += p[l];
        dps = dps*dp[l]%MOD;
        l++;
      }
      if ((r & 1) > 0) {
        r--;
        ps += p[r];
        dps = dps*dp[r]%MOD;
      }
    }
    return new long[] {ps, dps};
  }
  
  static int[] factorial(final int n) {
    final int[] vFactorial = new int[n];
    vFactorial[0] = 1;
    for (int i = 1; i < n; i++) {
        vFactorial[i] = (int)(((long)vFactorial[i - 1] * i) % MOD);
    }
    return vFactorial;
  }

  public static void main(String[] args) throws IOException {
    BufferedReader br = new BufferedReader(new InputStreamReader(System.in));
    BufferedWriter bw = new BufferedWriter(new FileWriter(System.getenv("OUTPUT_PATH")));

    int[] fact = factorial(MOD);
    
    StringTokenizer st = new StringTokenizer(br.readLine());
    int n = Integer.parseInt(st.nextToken());
    int nn = 1;
    while (nn < n) nn *= 2;
    
    d = new long[2 * nn];
    p = new long[2 * nn];
    dp = new long[2 * nn];
    dlt = new long[2 * nn];
    
    for (int i = 0; i < n; i++) {
      st = new StringTokenizer(br.readLine());
      st.nextToken();
      d[nn+i] = Integer.parseInt(st.nextToken());
      p[nn+i] = Integer.parseInt(st.nextToken());
      dp[nn+i] = power(d[nn+i], p[nn+i]);
    }
    for (int i = nn; --i >= 1; ) {
      d[i] = (d[2*i]*d[2*i+1])%MOD;
      mconcat(i);
    }
    
    st = new StringTokenizer(br.readLine());
    int q = Integer.parseInt(st.nextToken());
    for (int i = 0; i < q; i++) {
      st = new StringTokenizer(br.readLine());
      int op = Integer.parseInt(st.nextToken());
      int l = Integer.parseInt(st.nextToken()) - 1;
      int r = Integer.parseInt(st.nextToken());
      if (op > 0) {
        int num = Integer.parseInt(st.nextToken());
        add(nn, l, r, num);
      }
      else {
        long[] ans = query(nn, l, r);
        int ps = (int) ans[0];
        long dps = (ans[1]+MOD)%MOD;
        bw.write(ps + " " + (ps >= MOD ? 0 : fact[ps]*dps%MOD) + "\n");
      }
    }
    
    bw.newLine();
    bw.close();
    br.close();
  }
}
