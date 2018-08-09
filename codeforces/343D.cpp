#include <bits/stdc++.h>
#define ll long long int
#define LL long long int
#define ULL unsigned long long int
#define sf(a) scanf("%d",&a)
#define sl(a) scanf("%lld",&a)
#define fr first
#define sc second
#define pii pair<int,int>
#define pll pair<LL,LL>
#define vi vector<int>
#define vll vector<LL>
#define vpii  vector<pii>
#define rep1(a,b) for(int a=1;a<=b;a++)
#define rep2(a,b) for(int a=0;a<b;a++)
#define CLR(a,b) memset(a,b,sizeof(a))
#define Clear(a,b) memset(a,b,sizeof(a))
#define pb push_back
#define mp make_pair
#define mod 1000000007
#define  LSOne(S) (S & (-S))
#define all(a) a.begin(),a.end()
#define Prime 31
using namespace std;
#define maxn 200100
#define INF 1<<29
#define inf 1ll<<62
#define mMax 20005
#define nMax 2505
#define SZ(a) a.size()
#define  Unique(A) (A.resize(distance(A.begin(),unique(all(A)))))
void printVector(vi a) {for (int ii = 0; ii < SZ(a); ii++) cout << a[ii] << endl;}

class SegmentTree {
private: vi fill, empty;
	int n;
	int left (int p) { return p << 1; }
	int right(int p) { return (p << 1) + 1; }

	void propagate(int p, int L, int R) {
		if (fill[p] > -1) {
			int p1 = left(p);
			int p2 = right(p);
			fill[p1] = max(fill[p1], fill[p]);
			fill[p2] = max(fill[p2], fill[p]);
			fill[p] = -1;
		}
	}

	int maxfillquery(int p, int L, int R, int i) {
		if (i > R || i < L) return -1;
		if (L == i && R == i) return fill[p];
		propagate(p, L, R);
		int p1 = maxfillquery(left(p) , L              , (L + R) / 2, i);
		int p2 = maxfillquery(right(p), (L + R) / 2 + 1, R          , i);
		return max(p1, p2);
	}

	int maxemptyquery(int p, int L, int R, int i, int j) {
		if (i > R || j < L) return -1;
		if (L >= i && R <= j) return empty[p];

		int p1 = maxemptyquery(left(p) , L              , (L + R) / 2, i, j);
		int p2 = maxemptyquery(right(p), (L + R) / 2 + 1, R          , i, j);
		return max(p1, p2);
	}

	int update_point(int p, int L, int R, int idx, int new_value) {
		int i = idx, j = idx;

		if (i > R || j < L)
			return empty[p];

		if (L == i && R == j) {
			return empty[p] = new_value;
		}

		int p1, p2;
		p1 = update_point(left(p) , L              , (L + R) / 2, idx, new_value);
		p2 = update_point(right(p), (L + R) / 2 + 1, R          , idx, new_value);

		return empty[p] = max(p1, p2);
	}

	void update_range(int p, int L, int R, int i, int j, int new_value) {
		if (i > R || j < L)
			return ;

		if (i <= L && R <= j) {
			fill[p] = new_value;
			return;
		}

		propagate(p, L, R);

		int p1, p2;
		update_range(left(p) , L              , (L + R) / 2, i, j, new_value);
		update_range(right(p), (L + R) / 2 + 1, R          , i, j, new_value);
	}

public:
	SegmentTree(int a, int b = 0) {
		n = a;
		fill.assign(4 * n, b);
		empty.assign(4 * n, b);
	}

	int maxfillquery(int i) { return maxfillquery(1, 0, n - 1, i); }
	int maxemptyquery(int i, int j) { return maxemptyquery(1, 0, n - 1, i, j); }

	int update_point(int idx, int new_value) {
		return update_point(1, 0, n - 1, idx, new_value);
	}

	void update_range(int i, int j, int new_value) {
		update_range(1, 0, n - 1, i, j, new_value);
	}
};

int timeCount = 0;
struct entry {
	int start;
	int end;
	entry() {}
	entry(int a, int b) {
		start = a;
		end = b;
	}
} visitTime[500100];

vector<vi> adjList;

void dfs(int u, int par) {
	visitTime[u].start = timeCount++;
	for (auto v : adjList[u])
		if (v != par) {
			dfs(v, u);
		}
	visitTime[u].end = timeCount++;
}

int main()
{
	int n;
	cin >> n;
	adjList.assign(n + 10, vi());
	int u, v;
	rep1(i, n - 1) {
		scanf("%d %d", &u, &v);
		adjList[u].push_back(v);
		adjList[v].push_back(u);
	}
	dfs(1, 0);
	SegmentTree A(timeCount , -1);
	int q;
	cin >> q;
	rep1(i, q) {
		scanf("%d %d", &u, &v);
		if (u == 1) {
			A.update_range(visitTime[v].start, visitTime[v].end, i);
		}	else if (u == 2) {
			A.update_point(visitTime[v].start, i);
		}	else {
			int x = A.maxemptyquery(visitTime[v].start, visitTime[v].end);
			int y = A.maxfillquery(visitTime[v].start);
			printf("%d\n",  (x > y || y == -1) ? 0 : 1);
		}
	}
	return 0;
}
