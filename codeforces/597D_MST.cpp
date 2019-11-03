#include <bits/stdc++.h>
#define ll long long int
#define LL long long int
#define ULL unsigned long long int
#define sf(a) scanf("%d", &a)
#define sl(a) scanf("%lld", &a)
#define fr first
#define sc second
#define pii pair<int, int>
#define pll pair<LL, LL>
#define vi vector<int>
#define vll vector<LL>
#define vpii vector<pii>
#define rep1(a, b) for (int a = 1; a <= b; a++)
#define rep(a, b, n) for (int a = b; a < n; a++)
#define rep2(a, b) for (int a = 0; a < b; a++)
#define CLR(a, b) memset(a, b, sizeof(a))
#define Clear(a, b) memset(a, b, sizeof(a))
#define pb push_back
#define mp make_pair
#define mod 1000000007
#define LSOne(S) (S & (-S))
#define all(a) a.begin(), a.end()
#define Prime 31
using namespace std;
#define maxn 200100
#define INF 1 << 29
#define inf 1ll << 62
#define mMax 20005
#define nMax 2505
#define SZ(a) a.size()
#define Unique(A) (A.resize(distance(A.begin(), unique(all(A)))))
void printVector(vi a)
{
    for (int ii = 0; ii < SZ(a); ii++)
        cout << a[ii] << endl;
}

ll bigMod(ll a, ll b)
{
    if (b == 0)
        return 1;
    if (b % 2)
        return (a * bigMod(a, b - 1)) % mod;
    ll c = bigMod(a, b / 2);
    return (c * c) % mod;
}
class UnionFind
{ // OOP style
private:
    vi p, rank, setSize; // remember: vi is vector<int>
    int numSets;

public:
    UnionFind(int N)
    {
        setSize.assign(N, 1);
        numSets = N;
        rank.assign(N, 0);
        p.assign(N, 0);
        for (int i = 0; i < N; i++)
            p[i] = i;
    }
    int findSet(int i) { return (p[i] == i) ? i : (p[i] = findSet(p[i])); }
    bool isSameSet(int i, int j) { return findSet(i) == findSet(j); }
    void unionSet(int i, int j)
    {
        if (!isSameSet(i, j))
        {
            numSets--;
            int x = findSet(i), y = findSet(j);
            // rank is used to keep the tree short
            if (rank[x] > rank[y])
            {
                p[y] = x;
                setSize[x] += setSize[y];
            }
            else
            {
                p[x] = y;
                setSize[y] += setSize[x];
                if (rank[x] == rank[y])
                    rank[y]++;
            }
        }
    }
    int numDisjointSets() { return numSets; }
    int sizeOfSet(int i) { return setSize[findSet(i)]; }
};
vector<pair<LL, pii>> Edges;
//vector<vector<pair<int,LL> > >E;
bool cmp(pair<LL, pii> a, pair<LL, pii> b)
{
    return a.fr > b.fr;
}
vi vis;
int rev;
vi powerHouses;
vector<pii> network;
LL mst(int V, int m)
{
    LL mst_cost = 0;
    UnionFind UF(V); // all V are disjoint sets initially
    if (rev == 1)
        sort(Edges.begin(), Edges.end(), cmp);
    else
        sort(Edges.begin(), Edges.end());
    for (int i = 0; i < m; i++)
    { // for each edge, O(E)
        pair<LL, pii> front = Edges[i];
        if (!UF.isSameSet(front.second.first, front.second.second))
        {                            // check
                                     //vis[i]=1;
            mst_cost += front.first; // add the weight of e to MST
            if(front.second.first == 0) {
                powerHouses.push_back(front.sc.sc);
            } else {
                network.push_back(front.sc);
            }
            UF.unionSet(front.second.first, front.second.second); // link them
        }
    }
    return mst_cost;
}
pii pos[2001];
ll costPowerhouse[2001];
ll kValueOfCities[2001];
int dist(pii a, pii b) {
    return max(a.fr, b.fr) - min(a.fr, b.fr)
     + max(a.sc, b.sc) - min(a.sc, b.sc);
}
int main()
{
    int n,x,y;
    Edges.clear();
    scanf("%d", &n);
    for(int i =1 ;i <= n ; i++) {
        scanf("%d %d", &x, &y);
        pos[i] = pii(x,y);
    }
    rep1(i, n) {
        scanf("%lld", &costPowerhouse[i]);
        Edges.push_back(make_pair(costPowerhouse[i], pii(0,i)));
    }
    rep1(i, n) {
        scanf("%lld", &kValueOfCities[i]);
    }

    rep1(i,n)
    rep1(j,n) 
    if(i<j){
        Edges.push_back(make_pair(dist(pos[i], pos[j]) * (kValueOfCities[i] + kValueOfCities[j]), pii(i,j)));
    }
    printf("%lld\n", mst(n+1, Edges.size()));
    printf("%d\n", powerHouses.size());
    rep2(i, powerHouses.size()){
        if(i) printf(" ");
        printf("%d", powerHouses[i]);
        if(i + 1 == powerHouses.size()) {
            printf("\n");
        }
    }
    printf("%d\n", network.size());
    rep2(i, network.size()){
        printf("%d %d\n", network[i].fr, network[i].sc);
    }
    return 0;
}


