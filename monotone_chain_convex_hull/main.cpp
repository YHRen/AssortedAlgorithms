#include <vector>
#include <iterator>
#include <list>
#include <set>
#include <map>
#include <queue>
#include <stack>
#include <unordered_map>
#include <limits>
#include <iostream> 
#include <iomanip>  
#include <string>
#include <sstream>  
#include <algorithm>
#include <numeric>
#include <functional>
#include <cmath>
#include <cassert>

#define INF                         (int)1000000007
#define EPS                         1e-9

#define bg     begin()
#define pb     push_back
#define mp     make_pair

#define all(c)                      c.begin(), c.end()
#define forall(i,a,b)               for(int i=a;i<b;i++)
#define in(a,b)                     ( (b).find(a) != (b).end())

using namespace std;

typedef vector<int> vi;
typedef pair<int,int> ii;
typedef vector<vi>  vvi;
typedef vector<ii>  vii;

#ifdef DEBUG
#define debug(args...)            {dbg,args; clog<<endl;}
#define print_( a )               for( auto & x : a ) clog << x << ' '; clog << '\n';
#define printPair_( a )           for( auto & x : a ) clog << '(' << x.first << ',' << x.second << ')' << ' '; clog << '\n';
#else
#define debug(args...)             // Just strip off all debug tokens
#define print_( a )               // skip
#define printPair_( a )           // skip
#endif
struct debugger
{
  template<typename T> debugger& operator , (const T& x)
  {    
    clog << x << " ";    
    return *this;    
  }
} dbg;

// std::ios::sync_with_stdio(false);
/******* Actual Code Starts Here *********/

typedef pair<double,double>          dd;
typedef vector<pair<double,double>> vdd;

inline bool is_positive( const dd p1, const dd p2, const dd p3 ){
  return (p2.first - p1.first) * ( p3.second - p1.second ) - 
    ( p2.second - p1.second ) * ( p3.first - p1.first ) > 0;
}

vdd monotone_chain(const vector<double>&& x, const vector<double>&& y) {
  // points have been sorted via x values.
  // N > 2;
  assert(x.size() > 2);
  assert(x.size() == y.size());
  assert(is_sorted(all(x)));

  int N = x.size();
  list<pair<double, double>> U, L;
  forall(i, 0, N) {
    while (L.size() > 1 &&
           !is_positive(*++L.rbegin(), *L.rbegin(), mp(x[i], y[i]))) {
      debug("poping L.back(): (", L.back().first, ",", L.back().second, ")");
      L.pop_back();
    }
    L.pb(mp(x[i], y[i]));
  }

  debug("L=");
  printPair_(L);

  for( int i = N-1; i >= 0; --i ){
    while (U.size() > 1 &&
           !is_positive(*++U.rbegin(), *U.rbegin(), mp(x[i], y[i]))) {
      debug("poping U.back(): (", U.back().first, ",", U.back().second, ")");
      U.pop_back();
    }
    U.pb(mp(x[i], y[i]));
  }

  debug("U=");
  printPair_(U);

  L.pop_back();
  U.pop_back();
  vdd rtn;
  rtn.reserve(L.size() + U.size());
  copy(all(L), back_inserter(rtn));
  copy(all(U), back_inserter(rtn));
  return rtn;
}

int main(int argc, char* argv[]) {
  dd p1 = {1,0};
  dd p2 = {2,-1};
  dd p3 = {3,1};
  cout << is_positive( p1, p2, p3 ) << '\n';
  dd p4 = {4,-2};
  cout << is_positive( p2, p3, p4 ) << '\n';
  dd p5 = {5,0};

  auto rtn = monotone_chain({1, 2, 3, 4, 5}, {0, -1, 1, -2, 0});
  for( const auto & p : rtn ){
    cout << '(' << p.first << ',' << p.second << ')' << ' ';
  }cout << '\n';
  rtn = monotone_chain({1, 2, 2.5, 3, 3.5, 4, 5}, {0, -1, 0.5, 1, -1, -2, 0});
  for( const auto & p : rtn ){
    cout << '(' << p.first << ',' << p.second << ')' << ' ';
  }cout << '\n';

  return 0;
}
