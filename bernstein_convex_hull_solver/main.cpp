#include <vector>
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
#include "monotone_chain_convex_hull.h"
#include "deCasteljau_subdivision.h"

inline
double intersect_at( std::pair<double,double> p1,
    std::pair<double,double> p2 ){
  double dy = p2.second - p1.second; 
  double dx = p2.first - p1.first;
  return p2.first - p2.second * (dx/dy);
}
/* find the left most root */
double find_roots( 
    std::vector<double> && x,
    std::vector<double> && y,
    double eps = 1e-9 ){
  vector<double> rst; 
  assert( x.size() > 2 );
  assert( x.size() == y.size() );
  assert( std::is_sorted( x.begin(), x.end() ) );
  int m = x.size();
  int idx1 = -1;
  int idx2 = -1;
  for( int i = 0 ; i < m; ++i ){
    if( abs( y[i] ) > eps ){
      idx1 = i;
      break;
    }
  }
  if( idx1 == -1 ) return -1.0; // not exist
  
  for( int i = m-1; i >= 0; --i ){
    if( abs( y[i] ) > eps ){
      idx2 = i;
      break;
    }
  }
  
  if( y[idx1] * y[idx2] < 0 ){ //  one root in between and idx1 != idx2
    if( idx2 - idx1 == 1 ){  // just two points
      return intersect_at( std::make_pair( x[idx1], y[idx1] ), 
          std::make_pair( x[idx2], y[idx2] ) );
    }
    std::pair< std::vector<double> , std::vector<double> > tmp1,tmp;
    if( x[idx1] > 0 ){
      double frac1 = (x[idx1] - x.front()) / (x.back() - x.front());
      debug("frac1 = ", frac1);
      tmp1 = deCasteljau_subdivide(move(x), move(y), frac1, 2);
    }else{
      tmp1 = std::make_pair( x, y );
    }
    if( x[idx2] < 1 ){
      double frac2 =
          (x[idx2] - tmp1.first.front()) / (x.back() - tmp1.first.front());
      debug("frac2 = ", frac2);
      tmp = 
        deCasteljau_subdivide(move(tmp1.first), move(tmp1.second), frac2, 1);
    }else{
      tmp = move(tmp1);
    }
    double xmax = x[idx2];
    debug( "xmax = ", xmax );

    debug("before while loop, control points are ");
    print_(tmp.first);
    print_(tmp.second);

    while( std::abs( tmp.second.front() ) > eps ){
      auto convex_hull = monotone_chain( move(tmp.first), move(tmp.second) );
      double x1, x2;
      x1 = x2 = 1;
      debug( "convex_hull = ");
      printPair_(convex_hull);
      if( convex_hull[0].second > 0 ){
        if( convex_hull[1].second < 0 ){
          x1 = intersect_at( convex_hull[0] , convex_hull[1] );
          debug("x1 = ", x1, " Lower ");
        }else{
          std::cerr << "ERROR: " << __PRETTY_FUNCTION__ << '\n';
        }
      }else if( convex_hull[0].second < 0 ){
        x1 = intersect_at( convex_hull.front(), convex_hull.back() );
        debug("x1 = ", x1, " Upper ");
      }else{
        std::cerr << "ERROR: " << __PRETTY_FUNCTION__ << '\n';
        exit(1);
      }
      debug("x1 = ", x1,
            "frac = ", (x1 - tmp.first.front()) / (xmax - tmp.first.front()));
      tmp = deCasteljau_subdivide( move(tmp.first), move(tmp.second), 
          (x1-tmp.first.front())/( xmax - tmp.first.front() ), 2 );
      debug("control points are ");
      print_(tmp.first);
      print_(tmp.second);
    }
    return tmp.first.front();
  }else if( y[idx1] > 0 && y[idx2] > 0 ){
    return 1.0;
  }else{ // both < 0
    return 0.0;
  }
}

int main( int argc, char * argv[] ){
  double sol = find_roots( {0,0.5,1.0}, {1.0/3, 1.0/3,-2.0/3} );
  cout << sol << '\n';

  return 0;
}
