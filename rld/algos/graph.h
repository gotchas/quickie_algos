#pragma once

#include <vector>
#include <algorithm>

namespace rld {
namespace algos {

   class graph_in {}; //TODO dual to graph_out
   class graph_out {  
      std::vector<std::vector<int>> adj_;//for each vertex outcoming vertices
      /*
      static std::vector<std::vector<int>> 
      from_ilist(std::initializer_list<std::initializer_list<int>> adj) { 
        return std::vector<std::vector<int>>(adj.begin(), adj.end());
      }*/

     public:
      graph_out(int edges) : adj_(edges) {}
      //graph_out(std::initializer_list<std::initializer_list<int>> adj): adj_(from_ilist(adj)) {}
      graph_out(std::initializer_list<std::initializer_list<int>> adj): adj_(adj.begin(), adj.end()) {}
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
      std::vector<int> const &
      outcoming(int s) const { return adj_.at(s); }
   };



}}