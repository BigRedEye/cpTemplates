#include <bits/stdc++.h>

using namespace std;

#define int int64_t

#define pb push_back
#define mp make_pair
#define all(container) (container).begin(), (container).end()
#define F first
#define S second
#define endl '\n'
#define INPUT "input.txt"
#define OUTPUT "output.txt"
#define YN(ans) cout << ((ans) ? "YES" : "NO") << endl

#define FILES(input, output) freopen(input,"r",stdin); freopen(output,"w",stdout);

#ifndef LOCAL_MACHINE

#define FASTIO cin.tie(NULL); cout.tie(NULL); ios_base::sync_with_stdio(false);
#define __DEBUG if (0) {
#define DEBUG__ }
#define std::cerr if (0) std::cerr
#define cerr if (0) cerr
#define SERVER_FILES(input, output) FILES(intput, output)
#define LOCAL_FILES(input, output)

#else //LOCAL_MACHINE

#define FASTIO
#define __DEBUG
#define DEBUG__
#define SERVER_FILES(input, output)
#define LOCAL_FILES(input, output) FILES(intput, output)

#endif // LOCAL_MACHINE

#define forn(i,n)         for (int (i) = 0; (i)<(int)(n); ++(i))
#define fornd(i,n)        for (int (i) = (int)(n-1); (i) >= 0; --(i))
#define forkn(i,k,n)      for (int (i) = (int)(k); (i)<(int)(n); ++(i))
#define forv(i,container) for (auto (i) : (container))

void debug()
{
#ifdef LOCAL_MACHINE
    std::cout << "\n";
#endif //LOCAL_MACHINE
}

template<typename T, typename ...Next>
void debug(const T &arg, const Next & ...next)
{
#ifdef LOCAL_MACHINE
    std::cout << arg << ' ';
    debug(next...);
#endif //LOCAL_MACHINE
}

/** Types **/

typedef long double ld;
typedef long long ll;

typedef pair<int,int> pii;
typedef pair<ll,ll> pll;
typedef pair<ld,ld> pld;

typedef vector<int> vi;
typedef vector<pii> vpii;
typedef vector<ll> vll;
typedef vector<pll> vpll;
typedef vector<ld> vld;
typedef vector<pld> vpld;

typedef vector<vi> graph;
typedef vector<vpii> wgraph;

/** Constants **/

const int     MAXN    = 148822;
const int     MAXM    = 1488228;
const int     INF     = 0x3f3f3f3f;
const int64_t INFLL   = 0x3f3f3f3f3f3f3f3fll;
const int     MOD     = 1000000007;
const int     HASHMOD = 793877113;
const int     SQRT    = 320;
const int     ALPH    = 26;
const ld      PI      = 3.141592653589;
const ld      EPS     = 1e-9;

int32_t main(int argc, char *argv[])
{
    int kek = 1234;
    debug(1,"qwe",kek);
}
