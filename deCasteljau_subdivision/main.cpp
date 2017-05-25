#include <vector>
#include <iterator>
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

#include "deCasteljau_subdivision.h"
typedef pair<double,double>          dd;


/* typedef vector<pair<double,double>> vdd;

vdd deCasteljau_subdivide( 
    const vector<double> && x,
    const vector<double> && y,
    double x0,
    const int    mode = 1 ){
  // a Bezier curve defined by control points {x,y}. 
  // subdivide the curve at the fraction of x0.
  // the output is a new set of control points defining the portion of the curve.
  //
  // mode = 1, get left part,
  // mode = 2, get right part
  // mode = 3, get both parts
  // 0 < x0 < 1
  assert( x.size() > 2 );
  assert( x.size() == y.size() );
  assert( mode > 0 );
  assert( x0 > 0 && x0 < 1 );
  vdd  l,r;
  auto u = x;
  auto v = y;
  int  m = x.size();
  while( m -- > 0 ){
    if( mode&1 ) l.pb( mp( u[0],v[0] ) );
    if( mode&2 ) r.pb( mp( u[m],v[m] ) );
    for( int k = 1; k <= m; ++k ){
      u[k-1] = (x0)*u[k] + (1.0-x0)*u[k-1];
      v[k-1] = (x0)*v[k] + (1.0-x0)*v[k-1];
    }
  }
  switch( mode ){
    case 1:
      return l;
    case 2:
      reverse(all(r));
      return r;
    default:
      l.insert(l.end(), make_move_iterator(r.rbegin()),
                      make_move_iterator(r.rend()));
      return l;
  }
}

*/
int main( int argc, char * argv[] ){
  vector<double> x,y;
  double scale = 3.0;
  forall( i,0,11 ){
    x.pb( scale * 1.0*i/10.0 );
    y.pb( sin(5.0/scale*x.back()) );
  }
  print_(x);
  print_(y);

  auto rst1 = deCasteljau_subdivide( move(x), move(y), 0.6, 1 );
  for( auto p : rst1 ){
    cout << p.first << ',' ;
  }cout << '\n';
  for( auto p : rst1 ){
    cout << p.second << ',' ;
  }cout << '\n';
  printPair_(rst1);
  print_(y);

  auto rst2 = deCasteljau_subdivide( move(x), move(y), 0.6, 2 );
  printPair_(rst2);
  print_(y);

  for( auto p : rst2 ){
    cout << p.first << ',' ;
  }cout << '\n';
  for( auto p : rst2 ){
    cout << p.second << ',' ;
  }cout << '\n';


  return 0;
}
