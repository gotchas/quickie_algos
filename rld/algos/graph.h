#pragma once

#include <algorithm>
#include <queue>
#include <stack>
#include <vector>

namespace rld {
namespace algos {

   class graph_in {};  // TODO dual to graph_out
   class graph_out {
      std::vector<std::vector<int>> adj_;  // for each vertex outcoming vertices
                                           /*
                                           static std::vector<std::vector<int>>
                                           from_ilist(std::initializer_list<std::initializer_list<int>> adj) {
                                             return std::vector<std::vector<int>>(adj.begin(), adj.end());
                                           }*/
      // iterator for range of consecutive integers
      struct irange {
         int const*    first;
         unsigned long lenght;
         bool empty() const { return not lenght; }
         int pop_front() {  return --lenght, *(first++); } 
         int pop_back() {  return first[--lenght]; } 
         //TODO pop_random() - swap with back
      };
      // overload to implement both dfs and bfs using common interface to stack and queue
      // the fix is to use common name front(container) for queue::front() and stack::pop()
      static int const & front(std::queue<int> const & q) { return q.front(); }
      static int const & front(std::stack<int> const & s) { return s.top(); }

      static irange & front(std::queue<irange> & q) { return q.front(); }
      static irange & front(std::stack<irange> & s) { return s.top(); }

      /* 
      --- DFS---
      procedure DFS_iterative(G, v) is
          let S be a stack
          S.push(v)
          while S is not empty do
              v = S.pop()
              if v is not labeled as discovered then
                  label v as discovered
                  for all edges from v to w in G.adjacentEdges(v) do
                      S.push(w)

      list nodes_to_visit = {root};
      while( nodes_to_visit isn't empty ) {
        currentnode = nodes_to_visit.take_first();
        nodes_to_visit.prepend( currentnode.children );  //prepend == stack
        //do something
      }

      --- BFS ---
      list nodes_to_visit = {root};
      while( nodes_to_visit isn't empty ) {
        currentnode = nodes_to_visit.take_first();
        nodes_to_visit.append( currentnode.children );    / append -> queue
        //do something
      }*/

      template <class Next_Vertices,class Visitor>
      void
      xfs_impl(int iv, Visitor visit) const {
         std::vector<bool> discovered(adj_.size(), false);

         Next_Vertices backtrack; // queue for bfs, stack for dfs
         backtrack.push(iv);

         while (not backtrack.empty()) {
            int v = front(backtrack);//.top();
            backtrack.pop();

            if (not discovered[v]) {
               discovered[v] = true;
               visit(v);//other option is CRTP                                                            
               std::ranges::for_each(adj_[v], [&backtrack](int e) { backtrack.push(e); });  // indeterminism, can push in various orders
               // xfs2: here we can "compress" all neightbours with iterator/variable range - bag.pop_one()
            }
         }
      }
      enum { TAKE_FROM_FRONT = true, TAKE_FROM_BACK = false,}; //TODO 3rd option take random
      template <class Next_Vertices, bool Take_From_Front, class Visitor>
      void
      xfs2_impl(int s, Visitor visit) const {
         std::vector<bool> discovered(adj_.size(), false);

         Next_Vertices backtrack; // queue for bfs, std::stack<irange> for dfs
         backtrack.push({&s, 1LU}); // one element range

         while (not backtrack.empty()) {
            if (front(backtrack).empty()) {
               backtrack.pop();
            } else {
               int v;
               if constexpr(Take_From_Front) // many strategies possible e.g. take random
                  v = front(backtrack).pop_front();
               else
                  v = front(backtrack).pop_back();
               if (not discovered[v]) {
                  discovered[v] = true;
                  visit(v);  //? CRTP
                  auto& children = adj_[v];
                  backtrack.push({children.data(), children.size()});
               }
            }
         }
      }

     public:
      graph_out(int edges) : adj_(edges) {}
      graph_out(std::initializer_list<std::initializer_list<int>> adj) : adj_(adj.begin(), adj.end()) {}
      graph_out(std::vector<std::vector<int>>&& adj) : adj_{std::move(adj)} {}//TODO test it

      graph_out& add_edge(int s, int e) { adj_[s].push_back(e); return *this; }
      graph_out& remove_edge(int s, int e) {
         auto& v = adj_.at(s);
         auto  f = std::find(v.begin(), v.end(), e);
         if (f != v.end()) {
            *f = v.back();
            v.pop_back();
         }
         return *this;
      }
      ///////
      bool
      connected(int s, int e) const {
         auto const& v = adj_.at(s);
         return std::find(v.begin(), v.end(), e) != v.end();
      }
      std::vector<int>
      indegrees() const {
         std::vector<int> ret(adj_.size());
         namespace ranges = std::ranges;
         ranges::for_each(std::as_const(adj_),
                          [&ret](std::vector<int> const& v) { ranges::for_each(v, [&ret](int e) { ++ret[e]; }); });
         return ret;
      }
      std::vector<int> const&
      outcoming(int s) const { return adj_.at(s); }
/////////////////////////////////////////////////////////
      template <class Visitor>
      void
      dfs(int iv, Visitor visit) const { return xfs_impl<std::stack<int> >(iv, visit); }
      
      template <class Visitor>
      void
      dfs2(int s, Visitor visit) const { return xfs2_impl<std::stack<irange>, TAKE_FROM_FRONT >(s,visit); }
/////////////////////////////////////////////////////////
      template <class Visitor>
      void
      bfs(int s, Visitor visit) const { return xfs_impl<std::queue<int> >(s, visit); }
      template <class Visitor>
      void
      bfs2(int s, Visitor visit) const { return xfs2_impl<std::queue<irange>, TAKE_FROM_BACK >(s, visit); }
   };
}  // namespace algos
}  // namespace rld