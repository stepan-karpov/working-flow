/*
    Solution for NEERC'2006 Problem H: Hard Life
    (C) Roman Elizarov
    Note: this solution attempts to check correctness of the input
*/

import java.io.*;
import java.util.Arrays;

public class hard_re {
	public static void main(String[] args) throws Exception {
		new hard_re().go();
	}

	int n;
	int m;

	double[][] c;
	double[][] f;
	int[] d;

	boolean[] s;
	int[] p;
	int[] q;
	double[] w;
	int qh;
	int qt;

	void go() throws Exception {
		Scanner in = new Scanner(new File("hard.in"));

		n = in.nextInt();
		m = in.nextInt();
		in.nextLine();

		assert n >= 1 && n <= 100;
		assert m >= 0 && m <= 1000;

		c = new double[n + 2][n + 2];
		f = new double[n + 2][n + 2];
		d = new int[n + 2];

		for (int i = 0; i < m; i++) {
			int a = in.nextInt();
			int b = in.nextInt();
			in.nextLine();
			assert a >= 1 && a <= n && b >= 1 && b <= n && a != b;
			assert c[a][b] == 0 && c[b][a] == 0;
			c[a][b] = 1;
			c[b][a] = 1;
			d[a]++;
			d[b]++;
		}
		in.close();

		s = new boolean[n + 2];
		if (m == 0)
			s[1] = true;
		else
			solve();

		PrintStream out = new PrintStream(new File("hard.out"));
		int cnt = 0;
		for (int i = 1; i <= n; i++)
			if (s[i])
				cnt++;
		out.println(cnt);
		for (int i = 1; i <= n; i++)
			if (s[i])
				out.println(i);
		out.close();
	}

	void solve() {
		for (int i = 1; i <= n; i++)
			c[0][i] = m;

		p = new int[n + 2];
		q = new int[n + 2];
		w = new double[n + 2];

		double l = 0;
		double h = n;
		while (h - l > 1e-8) {
			double g = (l + h) / 2;

			for (int i = 1; i <= n; i++)
				c[i][n + 1] = m + g - d[i];
			for (int i = 0; i <= n + 1; i++)
				Arrays.fill(f[i], 0);

			while (true) {
				Arrays.fill(p, -1);
				p[0] = 0;
				q[0] = 0;
				w[0] = Double.POSITIVE_INFINITY;
				qh = 0;
				qt = 1;
				while (p[n + 1] < 0 && qh != qt) {
					int i = q[qh++];
					for (int j = 0; j <= n + 1; j++) {
						if (p[j] < 0 && f[i][j] < c[i][j]) {
							p[j] = i;
							w[j] = Math.min(w[i], c[i][j] - f[i][j]);
							q[qt++] = j;
						}
					}
				}
				if (p[n + 1] < 0)
					break;
				int t = n + 1;
				double ww = w[n + 1];
				while (t != 0) {
					int u = p[t];
					f[u][t] += ww;
					f[t][u] -= ww;
					t = u;
				}
			}

			int cnt = 0;
			for (int i = 0; i <= n + 1; i++)
				if (p[i] >= 0)
					cnt++;

			if (cnt == 1)
				h = g;
			else {
				l = g;
				for (int i = 0; i <= n + 1; i++)
					s[i] = p[i] >= 0;
			}
		}
	}

//----------------- just for validation ------------------

	/**
	 * Strict scanner to veryfy 100% correspondence between input files and input file format specification.
	 * It is a drop-in replacement for {@link java.util.Scanner} that could added to a soulution source
	 * without breaking its ability to work with {@link java.util.Scanner}.
	 */
	public static class Scanner {
		private final BufferedReader in;
		private String line = "";
		private int pos;
		private int lineNo;

		public Scanner(File source) throws FileNotFoundException {
			in = new BufferedReader(new FileReader(source));
			nextLine();
		}

		public void close() {
			assert line == null : "Extra data at the end of file";
			try {
				in.close();
			} catch (IOException e) {
				throw new AssertionError("Failed to close with " + e);
			}
		}

		public void nextLine() {
			assert line != null : "EOF";
			assert pos == line.length() : "Extra characters on line " + lineNo;
			try {
				line = in.readLine();
			} catch (IOException e) {
				throw new AssertionError("Failed to read line with " + e);
			}
			pos = 0;
			lineNo++;
		}

		public String next() {
			assert line != null : "EOF";
			assert line.length() > 0 : "Empty line " + lineNo;
			if (pos == 0)
				assert line.charAt(0) > ' ' : "Line " + lineNo + " starts with whitespace";
			else {
				assert pos < line.length() : "Line " + lineNo + " is over";
				assert line.charAt(pos) == ' ' : "Wrong whitespace on line " + lineNo;
				pos++;
				assert pos < line.length() : "Line " + lineNo + " is over";
				assert line.charAt(0) > ' ' : "Line " + lineNo + " has double whitespace";
			}
			StringBuilder sb = new StringBuilder();
			while (pos < line.length() && line.charAt(pos) > ' ')
				sb.append(line.charAt(pos++));
			return sb.toString();
		}

		public int nextInt() {
			String s = next();
			assert s.length() == 1 || s.charAt(0) != '0' : "Extra leading zero in number " + s + " on line " + lineNo;
			assert s.charAt(0) != '+' : "Extra leading '+' in number " + s + " on line " + lineNo;
			try {
				return Integer.parseInt(s);
			} catch (NumberFormatException e) {
				throw new AssertionError("Malformed number " + s + " on line " + lineNo);
			}
		}
	}
}
