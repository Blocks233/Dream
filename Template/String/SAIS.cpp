/**
 * Ensure that str[n] is the unique lexicographically smallest character in str.
 * time complexity: O(n)
 */
namespace SA {
	const static int N = 100000 + 10;
	int sa[N], rk[N], ht[N], s[N<<1], t[N<<1], p[N], cnt[N], cur[N];
#define pushS(x) sa[cur[s[x]]--] = x
#define pushL(x) sa[cur[s[x]]++] = x
#define inducedSort(v) std::fill_n(sa, n, -1); std::fill_n(cnt, m, 0);      \
	for (int i = 0; i < n; i++) cnt[s[i]]++;                                  \
	for (int i = 1; i < m; i++) cnt[i] += cnt[i-1];                           \
	for (int i = 0; i < m; i++) cur[i] = cnt[i]-1;                            \
	for (int i = n1-1; ~i; i--) pushS(v[i]);                                  \
	for (int i = 1; i < m; i++) cur[i] = cnt[i-1];                            \
	for (int i = 0; i < n; i++) if (sa[i] > 0 &&  t[sa[i]-1]) pushL(sa[i]-1); \
	for (int i = 0; i < m; i++) cur[i] = cnt[i]-1;                            \
	for (int i = n-1;  ~i; i--) if (sa[i] > 0 && !t[sa[i]-1]) pushS(sa[i]-1)
	void sais(int n, int m, int *s, int *t, int *p) {
		int n1 = t[n-1] = 0, ch = rk[0] = -1, *s1 = s+n;
		for (int i = n-2; ~i; i--) t[i] = s[i] == s[i+1] ? t[i+1] : s[i] > s[i+1];
		for (int i = 1; i < n; i++) rk[i] = t[i-1] && !t[i] ? (p[n1] = i, n1++) : -1;
		inducedSort(p);
		for (int i = 0, x, y; i < n; i++) if (~(x = rk[sa[i]])) {
			if (ch < 1 || p[x+1] - p[x] != p[y+1] - p[y]) ch++;
			else for (int j = p[x], k = p[y]; j <= p[x+1]; j++, k++)
				if ((s[j]<<1|t[j]) != (s[k]<<1|t[k])) {ch++; break;}
			s1[y = x] = ch;
		}
		if (ch+1 < n1) sais(n1, ch+1, s1, t+n, p+n1);
		else for (int i = 0; i < n1; i++) sa[s1[i]] = i;
		for (int i = 0; i < n1; i++) s1[i] = p[sa[i]];
		inducedSort(s1);
	}
	template<typename T>
		int mapCharToInt(int n, const T *str) {
			int m = *max_element(str, str+n);
			std::fill_n(rk, m+1, 0);
			for (int i = 0; i < n; i++) rk[str[i]] = 1;
			for (int i = 0; i < m; i++) rk[i+1] += rk[i];
			for (int i = 0; i < n; i++) s[i] = rk[str[i]] - 1;
			return rk[m];
		}
	template<typename T>
		void suffixArray(int n, const T *str) {
			int m = mapCharToInt(++n, str);
			sais(n, m, s, t, p);
			for (int i = 0; i < n; i++) rk[sa[i]] = i;
			for (int i = 0, h = ht[0] = 0; i < n-1; i++) {
				int j = sa[rk[i]-1];
				while (i+h < n && j+h < n && s[i+h] == s[j+h]) h++;
				if (ht[rk[i]] = h) h--;
			}
		}
};
// 出现 i 次的子串有 c[i] 个
namespace S {
	int top;
	int sta[N<<1], cnt[N<<1];
	ll c[N];
	inline int gao(int k) {
		int cc = 0;
		while(top && sta[top] > k) {
			cc += cnt[top];
			cnt[top] = 0;
			c[cc] += sta[top] - max(k, sta[top-1]);
			--top;
		}
		return cc;
	}
	inline void push(int x, int y) {
		if(!top || sta[top] != x) sta[++top] = x;
		cnt[top] += y;
	}
	inline void build(int n) {
		top = 0;
		fill_n(c+1, n, 0);
		rep(i, 1, n+1) {
			int lcp = SA::ht[i], cc = gao(lcp);
			push(lcp, cc);
			push(n - SA::sa[i], 1);
		}
		gao(0);
	}
};