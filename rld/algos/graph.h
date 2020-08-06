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
         bool
         empty() const {
            return not lenght;
         }
         int
         pop_front() {  // may be random element from the range
            return --lenght, *(first++);
         }  // indeterminism - any elem from the range pop_one()
         int
         pop_back() {  // may be random element from the range
            return first[--lenght];
         }  // indeterminism - any elem from the range pop_one()
      };
      // overload to implement both dfs and bfs using common interface to stack and queue
      // the fix is to use common name front(container) for queue::front() and stack::pop()
      static int front(std::queue<int> const & q) { return q.front(); }
      static int front(std::stack<int> const & s) { return s.top(); }

     public:
      graph_out(int edges) : adj_(edges) {}
      // graph_out(std::initializer_list<std::initializer_list<int>> adj): adj_(from_ilist(adj)) {}
      graph_out(std::initializer_list<std::initializer_list<int>> adj) : adj_(adj.begin(), adj.end()) {}
      graph_out(std::vector<std::vector<int>>&& adj) : adj_{std::move(adj)} {}

      graph_out&
      add_edge(int s, int e) {
         adj_[s].push_back(e);
         return *this;
      }
      graph_out&
      remove_edge(int s, int e) {
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
      outcoming(int s) const {
         return adj_.at(s);
      }

      /*
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
      */
      template <class Visitor>
      void
      dfs(int iv, Visitor visit) const {
         std::vector<bool> discovered(adj_.size(), false);

         std::stack<int> trace;
         trace.push(iv);

         while (not trace.empty()) {
            int v = trace.top();
            trace.pop();

            if (not discovered[v]) {
               discovered[v] = true;
               visit(v);                                                            //? CRTP
               std::ranges::for_each(adj_[v], [&trace](int e) { trace.push(e); });  // indeterminism/random for_each
                                                                                    // !freedom to push in various orders
               // dfs2: here we can "compress" all neightbours with iterator/variable range - bag ; pop_one()
            }
         }
      }
      template <class Visitor>
      void
      dfs2(int s, Visitor visit) const {
         std::vector<bool> discovered(adj_.size(), false);
         // iterator range: stack of consecutive children "compressed" with range //TODO test with google benchmark

         std::stack<irange> trace;
         trace.push({&s, 1LU});

         while (not trace.empty()) {
            if (trace.top().empty()) {
               trace.pop();
            } else {
               int v = trace.top().pop_front();

               if (not discovered[v]) {
                  discovered[v] = true;
                  visit(v);  //? CRTP
                  auto& children = adj_[v];
                  trace.push({children.data(), children.size()});
               }
            }
         }
      }
      /*
      list nodes_to_visit = {root};
      while( nodes_to_visit isn't empty ) {
        currentnode = nodes_to_visit.take_first();
        nodes_to_visit.append( currentnode.children );    / append == queue
        //do something
      }*/
      template <class Visitor>
      void
      bfs(int iv, Visitor visit) const {
         std::vector<bool> discovered(adj_.size(), false);

         std::queue<int> trace;
         trace.push(iv);

         while (not trace.empty()) {
            int v = trace.front();
            trace.pop();  // ! the only difference vs bfs is front() instead top()

            if (not discovered[v]) {
               discovered[v] = true;
               visit(v);                                                            //? CRTP
               std::ranges::for_each(adj_[v], [&trace](int e) { trace.push(e); });  // indeterminism/random for_each
               // here we can "compress" all neightbours with iterator/variable range - bag ; pop_one()
            }
         }
      }
      template <class Visitor>
      void
      bfs2(int s, Visitor visit) const {
         std::vector<bool> discovered(adj_.size(), false);
         // iterator range: stack of consecutive children "compressed" with range //TODO test with google benchmark

         std::queue<irange> trace;
         trace.push({&s, 1LU});

         while (not trace.empty()) {
            if (trace.front().empty()) {  // front/top
               trace.pop();
            } else {
               int v = trace.front().pop_back();  // front/top

               if (not discovered[v]) {
                  discovered[v] = true;
                  visit(v);  //? CRTP
                  auto& children = adj_[v];
                  trace.push({children.data(), children.size()});
               }
            }
         }
      }
   };

}  // namespace algos
}  // namespace rld