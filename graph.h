    // FILE: graph.h (part of the namespace main_savitch_15)
// TEMPLATE CLASS PROVIDED: graph<Item> (a class for labeled graphs)
//   The vertices of an n-vertex graph are numbered from zero to n-1. Each vertex
//   has a label of type Item. It may be any of the C++ built-in types (int,
//   char, etc.), or any class with a default constructor and an assignment
//   operator. The graph may not have multiple edges.
//
// MEMBER CONSTANTS for the graph<Item> template class:
//   static const size_t MAXIMUM = ______
//     graph::MAXIMUM is the maximum number of vertices that a graph can have.
//
// CONSTRUCTOR for the graph<Item> template class:
//   graph( )
//     Postcondition: The graph has been initialized with no vertices and no edges.
//
// MODIFICATION MEMBER FUNCTIONS for the graph<Item> template class:
//   void add_vertex(const Item& label)
//     Precondition: size( ) < MAXIMUM.
//     Postcondition: The size of the graph has been increased by adding one new
//     vertex. This new vertex has the specified label and no edges.
//
//   void add_edge(size_t source, size_t target)
//     Precondition: (source < size( )) and (target < size( )).
//     Postcondition: The graph has all the edges that it originally had, and it
//     also has another edge from the specified source to the specified target.
//     (If this edge was already present, then the graph is unchanged.)
//
//   void remove_edge(size_t soure, size_t target)
//     Precondition: (source < size( )) and (target < size( )).
//     Postcondition: The graph has all the edges that it originally had except
//     for the edge from the specified source to the specified target. (If this
//     edge was not originally present, then the graph is unchanged.)
//
//   Item& operator [ ] (size_t vertex)
//     Precondition: vertex < size( ).
//     Postcondition: The return value is a reference to the label of the
//     specified vertex.
//
// CONSTANT MEMBER FUNCTIONS for the graph<Item> template class:
//   size_t size( ) const
//     Postcondition: The return value is the number of vertices in the graph.
//
//   bool is_edge(size_t source, size_t target) const
//     Precondition: (source < size( )) and (target < size( )).
//     Postcondition: The return value is true if the graph has an edge from
//     source to target. Otherwise the return value is false.
//
//   set<size_t> neighbors(size_t vertex) const
//     Precondition: (vertex < size( )).
//     Postcondition: The return value is a set that contains all the vertex
//     numbers of vertices that are the target of an edge whose source is at
//     the specified vertex.
//
//   Item operator [ ] (size_t vertex) const
//     Precondition: vertex < size( ).
//     Postcondition: The return value is a reference to the label of the
//     specified vertex.
//     NOTE: This function differs from the other operator [ ] because its
//     return value is simply a copy of the Item (rather than a reference of
//     type Item&). Since this function returns only a copy of the Item, it is
//     a const member function.
//
// VALUE SEMANTICS for the graph<Item> template class:
//    Assignments and the copy constructor may be used with graph<Item> objects.

#ifndef GRAPH_H
#define GRAPH_H
#include <cstdlib>  // Provides size_t
#include <set>      // Provides set
#include <cassert>
#include <queue>
#include <vector>

    template <class Item>
    class graph
    {
    public:
        // MEMBER CONSTANTS
        static const std::size_t MAXIMUM = 3000;
        // CONSTRUCTOR
        graph( ) { many_vertices = 0; }
        // MODIFICATION MEMBER FUNCTIONS
        void add_vertex(const Item& label);
        void add_edge(std::size_t source, std::size_t target);
        void remove_edge(std::size_t source, std::size_t target);
        Item& operator [ ] (std::size_t vertex);
        // CONSTANT MEMBER FUNCTIONS
        std::size_t size( ) const { return many_vertices; }
        bool is_edge(std::size_t source, std::size_t target) const;
        std::set<std::size_t> neighbors(std::size_t vertex) const;
        Item operator[ ] (std::size_t vertex) const;
        std::vector<int> longest_path(std::size_t start, std::size_t dest);
        std::vector<int> shortest_path(std::size_t start, std::size_t dest);
    private:
        bool edges[MAXIMUM][MAXIMUM];
        Item labels[MAXIMUM];
        std::size_t many_vertices;
        void breadth_first1(std::size_t start, std::vector<int>& path);
        void breadth_first2(std::size_t start, std::size_t dest, std::vector<int>& path);
    };

#endif




// FILE: graph.template (part of the namespace main_savitch_15)
// TEMPLATE CLASS IMPLEMENTED: graph<Item> (See graph.h for documentation.)
// This file is included in the header file and not compiled separately.
// INVARIANT for the graph class:
//   1. The number of vertices in the graph is stored in the member variable
//      many_vertices.
//   1. These vertices are numbered from 0 to many_vertices-1.
//   2. edges is the adjacency matrix for the graph (with true in edges[i][j]
//      to indicate an edge from vertex i to vertex j).
//   3. For each i < many_vertices, labels[i] is the label of vertex i.


    template <class Item>
    void graph<Item>::add_edge(std::size_t source, std::size_t target)
    // Library facilities used: cassert, cstdlib
    {
        assert(source < size( ));
        assert(target < size( ));
        edges[source][target] = true;
    }

    template <class Item>
    void graph<Item>::add_vertex(const Item& label)
    // Library facilities used: cassert, cstdlib
    {
        std::size_t new_vertex_number;
        std::size_t other_number;

        assert(size( ) < MAXIMUM);
        new_vertex_number = many_vertices;
        many_vertices++;
        for (other_number = 0; other_number < many_vertices; ++other_number)
        {
            edges[other_number][new_vertex_number] = false;
            edges[new_vertex_number][other_number] = false;
        }
        labels[new_vertex_number] = label;
    }

    template <class Item>
    bool graph<Item>::is_edge(std::size_t source, std::size_t target) const
    // Library facilities used: cassert, cstdlib
    {
        assert(source < size( ));
        assert(target < size( ));
        return edges[source][target];
    }

    template <class Item>
    Item& graph<Item>::operator[ ] (std::size_t vertex)
    // Library facilities used: cassert, cstdlib
    {
        assert(vertex < size( ));
        return labels[vertex];     // Returns a reference to the label
    }

    template <class Item>
    Item graph<Item>::operator[ ] (std::size_t vertex) const
    // Library facilities used: cassert, cstdlib
    {
        assert(vertex < size( ));
        return labels[vertex];     // Returns only a copy of the label
    }

    template <class Item>
    std::set<std::size_t> graph<Item>::neighbors(std::size_t vertex) const
    // Library facilities used: cassert, cstdlib, set
    {
        std::set<std::size_t> answer;
        std::size_t i;

        assert(vertex < size( ));

        for (i = 0; i < size( ); ++i)
        {
            if (edges[vertex][i])
                answer.insert(i);
        }
        return answer;
    }

    template <class Item>
    void graph<Item>::remove_edge(std::size_t source, std::size_t target)
    // Library facilities used: cassert, cstdlib
    {
        assert(source < size( ));
        assert(target < size( ));
        edges[source][target] = false;
    }


    template <class Item>
    std::vector<int> graph<Item>::longest_path(std::size_t start, std::size_t dest)
    {
      std::vector<int> parent(size(), -1);
      breadth_first2(start, dest, parent);

      if (parent[dest] == -1)
        return std::vector<int>();

      std::vector<int> ans;
      for (int v = dest; v != start; v = parent[v])
      {
        ans.push_back(v);
      }
      ans.push_back(start);
      return ans;
    }


    template <class Item>
    void graph<Item>::breadth_first1(std::size_t start, std::vector<int>& path) //NOTE: use the breadth_first traversal algorithm to find longest path
    // Precondition: start is a vertex number of the labeled graph g.
    // Postcondition: A breadth-first search of g has been executed,
    // starting at the start vertex. The function f has been applied to the
    // label of each vertex visited by the search.
    // Library facilities used: algorithm, cassert, cstdlib, graph.h, queue
    {
      bool marked[MAXIMUM];
      std::set<std::size_t> connections;
      std::set<std::size_t>::iterator it;
      std::queue<std::size_t> vertex_queue;
      assert(start < size( ));
      std::fill_n(marked, size( ), false);
      marked[start] = true;
      path[start] = start;
      vertex_queue.push(start);
      do
      {
         connections = neighbors(vertex_queue.front( ));
         std::size_t front = vertex_queue.front( );
         vertex_queue.pop( );
         // Mark and process the unmarked neighbors,
         // and place them in the queue.
         for (it = connections.begin( ); it != connections.end( ); ++it)
         {
           if (!marked[*it])
           {
            marked[*it] = true;
            path[*it] = front;
            vertex_queue.push(*it);
           }
         }
      }
      while (!vertex_queue.empty( ));
    }

    template <class Item>
    void graph<Item>::breadth_first2(std::size_t start, std::size_t dest, std::vector<int>& path)
    {
      bool marked[MAXIMUM];
      std::set<std::size_t> connections;
      std::set<std::size_t>::iterator it;
      std::queue<std::size_t> vertex_queue;
      assert(start < size( ));
      std::fill_n(marked, size( ), false);
      marked[start] = true;
      path[start] = start;
      vertex_queue.push(start);
      do
      {
         connections = neighbors(vertex_queue.front( ));
         std::size_t front = vertex_queue.front( );
         vertex_queue.pop( );
         // Mark and process the unmarked neighbors,
         // and place them in the queue.
         for (it = connections.begin( ); it != connections.end( ); ++it)
         {
           if (!marked[*it])
           {
            marked[*it] = true;
            path[*it] = front;
            vertex_queue.push(*it);
           }
           else if (path[*it] != start && *it == dest) {
             bool found = false;
             for (int i = path[*it]; i != start; i = path[i]) {
               if (i == *it) {
                 found = true;
               }
             }
             if (!found) {
               path[*it] = front;
             }
           }
         }
      }
      while (!vertex_queue.empty( ));
    }

    template <class Item>
    std::vector<int> graph<Item>::shortest_path(std::size_t start, std::size_t dest)
    {

      std::vector<int> parent(size(), -1);
      breadth_first1(start, parent);

      if (parent[dest] == -1)
        return std::vector<int>();

      std::vector<int> ans;
      for (int v = dest; v != start; v = parent[v])
      {
        ans.push_back(v);
      }
      ans.push_back(start);
      return ans;
    }
