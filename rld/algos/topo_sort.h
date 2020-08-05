#pragma once

#include "graph.h"

namespace rld {
namespace algos {

   // Adjacency List, directed, acyclic
   // continuous ids for nodes starting from 0 - Int()
   std::vector<int>
   topo_sort(graph_out const& adj) {
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
