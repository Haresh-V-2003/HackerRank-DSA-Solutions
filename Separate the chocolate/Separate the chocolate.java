import java.util.ArrayList;
import java.util.HashMap;
import java.util.HashSet;
import java.util.List;
import java.util.Scanner;
import java.util.Set;

public class SeparateChoco {

    static int T = 0;
    static int D = 1;
    static int U = -1;
    // yes, Go language style...
    static class MapIntLong extends HashMap<Integer, Long> {
    }

    static class MapStringMapIntLong extends HashMap<String, MapIntLong> {
    }

    static class MapStringRow extends HashMap<String, Row> {

    }

    static class MapStringSetString extends HashMap<String, Set<String>> {

    }

    static class Piece {
        int id;
        int groupIdx;

        public Piece(int piece, int groupIndex) {
            this.id = piece;
            this.groupIdx = groupIndex;
        }

        public String toString() {
            if (id == 0) {
                return "" + (char) ('a' + groupIdx);
            } else {
                return "" + (char) ('A' + groupIdx);
            }
        }

        public boolean equals(Object o) {
            Piece other = (Piece) o;
            return id == other.id && groupIdx == other.groupIdx;
        }

        public int hashCode() {
            return 31 * id + groupIdx;
        }

        public Piece copy() {
            return new Piece(id, groupIdx);
        }
    }

    static class Row {
        Piece[] pieces;
        boolean isHiding = false;

        public Row(Piece[] pieces) {
            this.pieces = pieces.clone();
        }

        public Row(int template, int width) {
            pieces = new Piece[width];
            for (int i = 0; i < width; i++) {
                pieces[i] = new Piece(template % 2, -1);
                template /= 2;
            }
        }

        public boolean hasMatch(int[] constraint) {
            for (int i = 0; i < pieces.length; i++) {
                if (constraint[i] >= 0 && constraint[i] != pieces[i].id) {
                    return false;
                }
            }
            return true;
        }

        public int countOnes() {
            int c = 0;
            for (int i = 0; i < pieces.length; i++) {
                c += pieces[i].id;
            }
            return c;
        }

        public boolean isOfTwoPieces() {
            if (isHiding && isUniform())
                return true;
            for (int i = 0; i < pieces.length; i++) {
                if (pieces[i].groupIdx > 0)
                    return false;
            }
            return true;
        }

        public String toString() {
            StringBuilder sb = new StringBuilder();
            for (Piece c : pieces) {
                sb.append(c);
            }
            if (isHiding) {
                sb.append("!");
            }
            return sb.toString();
        }

        public boolean equals(Object o) {
            Row other = (Row) o;
            return toString().equals(other.toString());
        }

        public Row copy() {
            Piece[] pcs = new Piece[pieces.length];
            for (int i = 0; i < pcs.length; i++) {
                pcs[i] = pieces[i].copy();
            }
            Row copy = new Row(pcs);
            copy.isHiding = isHiding;
            return copy;
        }

        boolean isUniform() {
            int p = pieces[0].id;
            for (int i = 1; i < pieces.length; i++) {
                if (pieces[i].id != p)
                    return false;
            }
            return true;
        }

        public void validate() {
            int groupOne = 20;
            int groupTwo = 20;

            for (int i = 0; i < pieces.length; i++) {
                int curGroup = pieces[i].groupIdx;
                if (curGroup >= 0) {
                    continue;
                }
                int p = pieces[i].id;
                if (p == 0) {
                    for (int j = i; j < pieces.length && pieces[j].id == p && pieces[j].groupIdx < 0; j++) {
                        pieces[j].groupIdx = groupOne;
                    }
                    groupOne++;
                } else {
                    for (int j = i; j < pieces.length && pieces[j].id == p && pieces[j].groupIdx < 0; j++) {
                        pieces[j].groupIdx = groupTwo;
                    }
                    groupTwo++;
                }
            }

            int[] movesOne = new int[pieces.length + 20];
            int[] movesTwo = new int[pieces.length + 20];
            for (int i = 0; i < movesOne.length; i++) {
                movesOne[i] = -1;
                movesTwo[i] = -1;
            }
            groupOne = 0;
            groupTwo = 0;

            for (int i = 0; i < pieces.length; i++) {
                int curGroup = pieces[i].groupIdx;
                if (curGroup < 0) {
                    continue;
                }
                if (pieces[i].id == 0) {
                    if (movesOne[curGroup] >= 0) {
                        pieces[i].groupIdx = movesOne[curGroup];
                    } else {
                        movesOne[curGroup] = groupOne;
                        pieces[i].groupIdx = groupOne;
                        groupOne++;
                    }
                } else {
                    if (movesTwo[curGroup] >= 0) {
                        pieces[i].groupIdx = movesTwo[curGroup];
                    } else {
                        movesTwo[curGroup] = groupTwo;
                        pieces[i].groupIdx = groupTwo;
                        groupTwo++;
                    }
                }
            }

        }
    }

    public void setSize(int width, int height, int diff) {
        this.width = width;
        this.height = height;
        this.diff = diff;
    }

    public void setConstraint(int[][] constraint) {
        this.constraint = constraint;
    }

    public List<Row> createRow() {
        List<Row> rows = new ArrayList<>();
        int cnt = 0;
        Piece[] pcs = new Piece[width];
        int[] solution = new int[width + 1];
        int[] solutionsCount = new int[width + 1];
        Piece[][] solutions = new Piece[width + 1][width + 1];
        solutions[0][0] = new Piece(0, 0);
        solutions[0][1] = new Piece(1, 0);
        solutionsCount[0] = 2;
        solution[cnt] = -1;
        while (true) {
            while (solution[cnt] == solutionsCount[cnt] - 1) {
                if (cnt == 0) {
                    return rows;
                }
                cnt--;
            }
            solution[cnt]++;
            pcs[cnt] = solutions[cnt][solution[cnt]];
            cnt++;
            solutionsCount[cnt] = 0;
            if (cnt < width) {
                int curPc = pcs[cnt - 1].id;
                solutions[cnt][0] = new Piece(curPc, pcs[cnt - 1].groupIdx); //same
                solutionsCount[cnt]++;
                List<Piece> pcsStack = new ArrayList<>();
                int grpId = -1;
                for (int i = 0; i < cnt; i++) {
                    int j = pcsStack.indexOf(pcs[i]);
                    if (j >= 0) {
                        while (pcsStack.size() > j + 1) {
                            pcsStack.remove(pcsStack.size() - 1);
                        }
                    } else {
                        pcsStack.add(pcs[i]);
                        if (pcs[i].id == 1 - curPc) {
                            if (pcs[i].groupIdx > grpId) {
                                grpId = pcs[i].groupIdx;
                            }
                        }
                    }
                }
                for (Piece c : pcsStack) {
                    if (c.id == 1 - curPc) {
                        solutions[cnt][solutionsCount[cnt]] = c;
                        solutionsCount[cnt]++;
                    }
                }
                solutions[cnt][solutionsCount[cnt]] = new Piece(1 - curPc, grpId + 1);
                solutionsCount[cnt]++;
            } else {
                rows.add(new Row(pcs));
            }
            solution[cnt] = -1;
        }
    }

    public Row move(Row from, Row to) {
        if (from.isHiding) {
            if (width == 1 && from.pieces[0].id == to.pieces[0].id) {
                to = to.copy();
                to.isHiding = true;
                to.validate();
                return to;
            }
            return null;
        }
        for (int i = 0; i < from.pieces.length - 1; i++) {
            int p = from.pieces[i].id;
            if (p == from.pieces[i + 1].id && p == to.pieces[i].id && p == to.pieces[i + 1].id) {
                return null;
            }
        }
        from = from.copy();
        to = to.copy();
        for (int i = 0; i < from.pieces.length; i++) {
            to.pieces[i].groupIdx = -1;
        }
        for (int i = 0; i < from.pieces.length; i++) {
            int p = from.pieces[i].id;
            int grpId1 = from.pieces[i].groupIdx;
            int grpId2 = to.pieces[i].groupIdx;
            if (p == to.pieces[i].id && grpId1 != grpId2) {
                if (grpId2 >= 0) {
                    for (int j = 0; j < from.pieces.length; j++) {
                        int ga = (grpId1 < grpId2) ? grpId1 : grpId2;
                        int gb = (grpId1 > grpId2) ? grpId1 : grpId2;
                        if (p == from.pieces[j].id && gb == from.pieces[j].groupIdx) {
                            from.pieces[j].groupIdx = ga;
                        }
                        if (p == to.pieces[j].id && gb == to.pieces[j].groupIdx) {
                            to.pieces[j].groupIdx = ga;
                        }
                    }
                } else {
                    to.pieces[i].groupIdx = grpId1;
                    int j = i + 1;
                    while (j < from.pieces.length && to.pieces[j].id == p) {
                        to.pieces[j].groupIdx = grpId1;
                        j++;
                    }
                    j = i - 1;
                    while (j >= 0 && to.pieces[j].id == p) {
                        to.pieces[j].groupIdx = grpId1;
                        j--;
                    }
                }
            }
        }
        Set<Piece> accounted = new HashSet<>();
        for (int i = 0; i < from.pieces.length; i++) {
            if (from.pieces[i].id == to.pieces[i].id) {
                accounted.add(from.pieces[i]);
            }
        }
        Set<Piece> unaccounted = new HashSet<>();
        for (int i = 0; i < from.pieces.length; i++) {
            if (!accounted.contains(from.pieces[i]) && !unaccounted.contains(from.pieces[i])) {
                unaccounted.add(from.pieces[i]);
            }
        }
        if (unaccounted.size() > 1) {
            return null;
        }
        to.validate();
        if (unaccounted.size() == 1) {
            if (!to.isUniform()) {
                return null;
            } else {
                to.isHiding = true;
            }
        }
        return to;
    }

    public void build() {
        int powOfTwo = 1;
        for (int i = 0; i < width; i++) {
            powOfTwo *= 2;
        }
        List<Row> rows = createRow();
        for (Row row : rows) {
            this.rows.put(row.toString(), row);
            if (row.isUniform()) {
                Row s1 = row.copy();
                s1.isHiding = true;
                this.rows.put(s1.toString(), s1);
            }
        }
        for (Row s : this.rows.values()) {
            Set<String> ts = new HashSet<>();
            for (int i = 0; i < powOfTwo; i++) {
                Row t = new Row(i, width);
                t = move(s, t);
                if (t != null)
                    ts.add(t.toString());
            }
            moves.put(s.toString(), ts);
        }
        for (int i = 0; i < powOfTwo; i++) {
            Row newRow = new Row(i, width);
            newRow.validate();
            if (!newRow.hasMatch(constraint[0])) {
                continue;
            }
            MapIntLong v = new MapIntLong();
            v.put(newRow.countOnes(), 1l);
            counts.put(newRow.toString(), v);
        }
        for (int i = 0; i < height - 1; i++) {
            counts = addRow(counts, constraint[i + 1]);
        }
        long sum = sum(counts, diff, width * height);
        System.out.println(sum);
    }

    MapStringMapIntLong addRow(MapStringMapIntLong counts, int[] cs) {
        MapStringMapIntLong next = new MapStringMapIntLong();
        for (String s : counts.keySet()) {
            MapIntLong vs = counts.get(s);
            for (String n : moves.get(s)) {
                Row t = rows.get(n);
                if (!t.hasMatch(cs)) {
                    continue;
                }
                int dk = t.countOnes();
                if (!next.containsKey(n)) {
                    MapIntLong v = new MapIntLong();
                    for (int k : vs.keySet()) {
                        v.put(k + dk, vs.get(k));
                    }
                    next.put(n, v);
                } else {
                    MapIntLong v = next.get(n);
                    for (int k : vs.keySet()) {
                        if (!v.containsKey(k + dk)) {
                            v.put(k + dk, vs.get(k));
                        } else {
                            v.put(k + dk, v.get(k + dk) + vs.get(k));
                        }
                    }
                }
            }
        }
        return next;
    }

    long sum(MapStringMapIntLong counts, int diff, int size) {
        long result = 0;
        for (String s : counts.keySet()) {
            Row state = rows.get(s);
            if (state.isOfTwoPieces()) {
                for (int k : counts.get(s).keySet()) {
                    int k1 = size - k;
                    if (Math.abs(k - k1) <= diff) {
                        long d = counts.get(s).get(k);
                        result += d;
                    }
                }
            }
        }
        return result;
    }

    int width;
    int height;
    int diff;
    int[][] constraint;

    MapStringRow rows = new MapStringRow();
    MapStringSetString moves = new MapStringSetString();
    MapStringMapIntLong counts = new MapStringMapIntLong();

    public void run() {
        Scanner in = new Scanner(System.in);
        int m = in.nextInt(), n = in.nextInt(), k = in.nextInt();
        if (m == 0 || n == 0) {
            System.out.println(1);
            return;
        }
        setSize(n, m, k);
        int[][] cs = new int[m][n];
        for (int i = 0; i < m; i++) {
            String s = in.next();
            for (int j = 0; j < n; j++) {
                char ch = s.charAt(j);
                cs[i][j] = ch == 'T' ? T : ch == 'D' ? D : U;
            }
        }
        setConstraint(cs);
        build();
    }

    public static void main(String[] args) {
        new SeparateChoco().run();
    }
}
