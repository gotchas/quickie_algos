#pragma once
#include <algorithm>
#include <vector>

namespace rld {
namespace algos {

   class Graph {  // TODO
      std::vector<std::vector<int>> adj_;

     public:
      Graph(int edges) : adj_(edges) {}
      // Graph(std::initializer_list<std::initializer_list<int>> adj): adj_{adj} {}
      Graph(std::vector<std::vector<int>>&& adj) : adj_{std::move(adj)} {}

      Graph&
      add_edge(int s, int e) {
         adj_[s].push_back(e);
         return *this;
      }
      Graph&
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
      std::vector<int> const &
      outcoming(int s) const { return adj_.at(s); }
   };

   // Adjacency List, directed, acyclic
   // continuous ids for nodes starting from 0 - Int()
   std::vector<int>
   topo_sort(Graph const& adj) {
      namespace ranges = std::ranges;
      std::vector<int> indegrees{adj.indegrees()};

      std::vector<int> result;
      // look for nodes without incoming edges
      for (auto f = ranges::find(indegrees, 0); f !=indegrees.end(); f = ranges::find(indegrees, 0)) { 
        auto const s = std::distance(indegrees.begin(), f);
        result.push_back( s );
        ranges::for_each(adj.outcoming(s), [&indegrees](int e){ --indegrees[e]; });
        *f=-1;//MAX_INT we do not remove processed nodes but mark as done with -1
      }
      if (result.size() != indegrees.size()) 
        return {};
      else
        return result;
   }

}  // namespace algos
}  // namespace rld
