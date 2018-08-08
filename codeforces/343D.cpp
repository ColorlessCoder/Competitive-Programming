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
private: vi st, A;
	int n;
	int left (int p) { return p << 1; }
	int right(int p) { return (p << 1) + 1; }
	int rmq(int p, int L, int R, int i, int j) {
		if (i >  R || j <  L) return -1;
		if (L >= i && R <= j) return st[p];

		int p1 = rmq(left(p) , L              , (L + R) / 2, i, j);
		int p2 = rmq(right(p), (L + R) / 2 + 1, R          , i, j);

		if (p1 == -1) return p2;
		if (p2 == -1) return p1;
		return (A[p1] <= A[p2]) ? p1 : p2;
	}

	int update_point(int p, int L, int R, int idx, int new_value) {
		int i = idx, j = idx;

		if (i > R || j < L)
			return st[p];

		if (L == i && R == j) {
			A[i] = new_value;
			return st[p] = L;
		}

		int p1, p2;
		p1 = update_point(left(p) , L              , (L + R) / 2, idx, new_value);
		p2 = update_point(right(p), (L + R) / 2 + 1, R          , idx, new_value);

		return st[p] = (A[p1] >= A[p2]) ? p1 : p2;
	}

public:
	SegmentTree(int a, int b = 0) {
		n = a;
		A.assign(n, b);
		st.assign(4 * n, b);
	}

	int rmq(int i, int j) { return A[rmq(1, 0, n - 1, i, j)]; }

	int update_point(int idx, int new_value) {
		return update_point(1, 0, n - 1, idx, new_value);
	}
};

int timeCount = 0;
struct entry{
	int start;
	int end;
	entry(){}
	entry(int a,int b){
		start=a;
		end= b;
	}
} visitTime[500100];

vector<vi> adjList;

void dfs(int u,int par) {
	visitTime[u].start = timeCount++;
	for(auto v:adjList[u])
		if(v!=par){
			dfs(v,u);
		}
	visitTime[u].end=timeCount++;
}

int main()
{
	int n;
	cin>>n;
	adjList.assign(n+10,vi());
	int u,v;
	rep1(i,n-1){
		scanf("%d %d",&u,&v);
		adjList[u].push_back(v);
		adjList[v].push_back(u);
	}
	dfs(1,0);
	// rep1(i,n){
	// 	cout<<visitTime[i].start<<" "<<visitTime[i].end<<endl;
	// }
	return 0;
}
