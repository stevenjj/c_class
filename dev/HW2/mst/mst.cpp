/*
PROG: mst
LANG: C++
*/
// Our file input/output headers
#include <fstream>
#include <iostream>

// Used for std::precision (look at main())
#include <iomanip>

// http://www.cplusplus.com/reference/vector/vector/
#include <vector>
// http://www.cplusplus.com/reference/queue/priority_queue/
#include <queue>

// This will store and adjacent node and the distance to that node.
class State {
  size_t _node;
  double _dist;
public:
  State( size_t aNode, double aDist ) : _node{aNode}, _dist{aDist} {}
  inline size_t node() const { return _node; }
  inline double dist() const { return _dist; }
};

/* A wrapper for our vector of vectors which represents an
 * adjacency list. Why didn't we just go with the list of vectors?
 * Notice that once the AdjacencyList is constructed, it contains
 * the data, which is private, and this data is not modifiable by
 * people using the class- better than using a potentially edit-able
 * vector of vectors out in the open.
 */
class AdjacencyList {
  std::vector< std::vector<State> > _vert;
  AdjacencyList() = delete;
public:
  AdjacencyList( std::istream &input );
  inline size_t size() const { return _vert.size(); }
  inline const std::vector<State>& vert( size_t node ) const { return _vert[node]; }
  void print();
};

AdjacencyList::AdjacencyList( std::istream &input ) : _vert{} {
  size_t nNodes; size_t nEdges; input >> nNodes >> nEdges;
  _vert.resize( nNodes );
 
  for( size_t e = 0; e < nEdges; ++e ) {
    size_t v, w; double weight;
    input >> v >> w >> weight;
    // Add this edge to both the v and w lists
    _vert[v].push_back( State{ w, weight } );
    _vert[w].push_back( State{ v, weight } );
  }
}

void AdjacencyList::print() {
  for( size_t i = 0; i < _vert.size(); ++i ) {
    std::cout << i << ": ";
    for( auto state : _vert[i] ) {
      std::cout << "(" << state.node() << ", " << state.dist() << ") ";
    }
    std::cout << "\n";
  }
}


/* The function which computes the minimum spanning tree of the graph.
 * Your job is to implement this!
 */


bool operator<( const State &a, const State &b ){
  if (a.dist() < b.dist()){
    return true;
  }
  return false;
}




double prim( const AdjacencyList &adj ) {
 double weight = 0.0;
 std::priority_queue<State> pq;
 printf("node:%zu, value:%f\n", adj.vert(0)[0].node() , adj.vert(0)[0].dist() );
 printf("node:%zu, value:%f\n", adj.vert(0)[1].node() , adj.vert(0)[1].dist() );
  // Suggested starting point:
  //  std::priority_queue<State> pq;
  //   NOTE: you will need to overload a operator<
  //   for State objects, since priority_queue<> requires that
  //   its members be comparable!
  // pq.push( State{ 0, 0.0 } );
  //
  // while( !pq.empty() ) {
  //    you'll want to pop off the front
  //    element in the priority queue and
  //    then add its neighbors.
  //    Check out http://cplusplus.com
  //    and the suggested resource in the
  //    problem statement!
  // }

  return weight;
}


int main() {
  
  std::ifstream input{ "mst.in" };
  std::ofstream output{ "mst.out" };

  if( input.is_open() ) {
    auto adj = AdjacencyList{ input };
    // So that we print 10 fixed digits of precision
    adj.print();
    output << std::fixed << std::setprecision( 8 );
    output << prim( adj ) << "\n";
  } else {
    std::cerr << "Could not open mst.in\n";
    return 1;
  }
    
  return 0;
}
