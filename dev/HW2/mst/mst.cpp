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
  if (b.dist() < a.dist()){
    return true;
  }
  return false;
}


struct my_compare {
  bool operator()(const State &a, const State &b){
    if (b.dist() <= a.dist()){
      return true;
    }else{
      return false;
    }

  }
};


bool in_list_of_vectors(const std::vector<size_t>  visited_nodes, const size_t node){
  bool in_vector = false;
  for(size_t i = 0 ; i < visited_nodes.size(); i++){
    if (visited_nodes[i] == node){
      in_vector = true;
      break;
    }
  }
  return in_vector;
    /*
  if(std::find(visited_nodes.begin(), visited_nodes.end(), node) != visited_nodes.end()) {
    //    std::cout << "Node:" << node << " is in list of vectors\n" ;
     return true;
  } else {
    // std::cout << "Node:" << node << " is NOT in list of vectors\n" ;
     return false;
  }
    */
}

void initialize_pq( std::priority_queue<State, std::vector<State>, my_compare> &pq, 
                    std::vector<size_t> &visited_nodes, const AdjacencyList &adj, const size_t &initial_node,  
                    std::vector<State> &inpq){
  visited_nodes.push_back(initial_node);
  for(size_t i = 0; i < adj.vert(initial_node).size(); ++i){
    pq.push(adj.vert(initial_node)[i]);
    inpq.push_back(adj.vert(initial_node)[i]);
    // std::cout << adj.vert(initial_node)[i].node() << "ADD THIS NODE TO INITIALIZED PQ\n";
  }
	    
}



void print_inpq(const std::vector<State> inpq){
  std::cout << "PQ has:\n";
  for( size_t i = 0; i < inpq.size(); ++i){
     std::cout << "(" << inpq[i].node() << ", " << inpq[i].dist() << ") \n";
    }
  
}

double prim( const AdjacencyList &adj ) {
 double weight = 0.0;

  std::priority_queue<State, std::vector<State>, my_compare> pq;
 // printf("node:%zu, value:%f\n", adj.vert(0)[0].node() , adj.vert(0)[0].dist() );
 // printf("node:%zu, value:%f\n", adj.vert(0)[1].node() , adj.vert(0)[1].dist() ); 
 // std::cout << "Size of Adjacency is:" << adj.size() << "\n" ;

 if (adj.size() == 0){
   return weight; // Return 0.0
 }

 std::vector<size_t> visited_nodes;
 std::vector<State> inpq;

 // Initialize priority queue with one node.
 size_t current_node = 0;
 initialize_pq(pq, visited_nodes, adj, current_node, inpq);
 // print_inpq(inpq);
 

  while( !pq.empty() ){
    //    std::cout << "Top node is " <<  pq.top().node() << "\n";
    // std::cout << "Size of pq is " << pq.size() << "\n";
    //std::cout << "Number of neighbors of top node is " << adj.vert(pq.top().node()).size() << "\n";
    
    size_t node = pq.top().node(); // Store minimum dist node
    double dist = pq.top().dist(); // Store distance from prev node to to minimum dist node

    pq.pop(); // Remove node in priority queue;

    
       if ( !in_list_of_vectors(visited_nodes, node)){ // Check if it's in visited nodes
    	 visited_nodes.push_back( node ) ; // Mark node as visited so we don't check its edges again
	 weight += dist;
	 //  Add its neightbors
        for(size_t i = 0; i < adj.vert(node).size(); ++i){
	  State neighbor = adj.vert(node)[i];
	  if (!in_list_of_vectors(visited_nodes, neighbor.node())){ 
	     pq.push(neighbor); // Add neighbor to pq if it it hasn't been visited	    
	     inpq.push_back(neighbor);

	      }
	}
	//	print_inpq(inpq);
	//std::cout << "current weight is = " << weight << "\n";

	    }
    

  }


  // Suggested starting point:
  //  std::priority_queue<State> pq;r
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

  //  std::cout << weight << "\n";
  return weight;
}
 

int main() {
  
  std::ifstream input{ "mst.in" };
  std::ofstream output{ "mst.out" };

  if( input.is_open() ) {
    auto adj = AdjacencyList{ input };
    // So that we print 10 fixed digits of precision
    //    adj.print();
    output << std::fixed << std::setprecision( 8 );
        output << prim( adj ) << "\n";
  } else {
    std::cerr << "Could not open mst.in\n";
    return 1;
  }
    
  return 0;
}
