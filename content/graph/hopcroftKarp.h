/**
 * Author: Chen Xing
 * Date: 2009-10-13
 * License: CC0
 * Source: N/A
 * Description: Fast bipartite matching algorithm. Graph $g$ should be a list
 * of neighbors of the left partition, and $btoa$ should be a vector full of
 * -1's of the same size as the right partition. Returns the size of
 * the matching. $btoa[i]$ will be the match for vertex $i$ on the right side,
 * or $-1$ if it's not matched.
 * Usage: vi btoa(m, -1); hopcroftKarp(g, btoa);
 * Time: O(\sqrt{V}E)
 * Status: stress-tested by MinimumVertexCover, and tested on oldkattis.adkbipmatch and SPOJ:MATCHING
 */
#pragma once

struct HopcroftKarp {
  vector<int> g, l, r;
  int ans;
  HopcroftKarp(int n, int m, const vector<pair<int, int>> &e)
      : g(e.size()), l(n, -1), r(m, -1), ans(0) {
    std::vector<int> deg(n + 1);
    for (auto &[x, y] : e) deg[x]++;
    for (int i = 1; i <= n; i++) deg[i] += deg[i - 1];
    for (auto &[x, y] : e) g[--deg[x]] = y;

    std::vector<int> a, p, q(n);
    for (;;) {
      a.assign(n, -1), p.assign(n, -1);
      int t = 0;
      for (int i = 0; i < n; i++)
        if (l[i] == -1) q[t++] = a[i] = p[i] = i;

      bool match = false;
      for (int i = 0; i < t; i++) {
        int x = q[i];
        if (~l[a[x]]) continue;
        for (int j = deg[x]; j < deg[x + 1]; j++) {
          int y = g[j];
          if (r[y] == -1) {
            while (~y) r[y] = x, swap(l[x], y), x = p[x];
            match = true, ans++;
            break;
          }

          if (p[r[y]] == -1)
            q[t++] = y = r[y], p[y] = x, a[y] = a[x];
        }
      }

      if (!match) break;
    }
  }
};