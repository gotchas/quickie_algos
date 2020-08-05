#include <iostream>
#include "lest.hpp"
#include "rld/algos/topo_sort.h"

namespace rld {
namespace algos {
   // clang-format off
const lest::test specification[] = {
   CASE( "Setup creates a fresh fixture for each section" )
   {
      SETUP("context: regular graph") 
      {
         //graph_out g{10};
         graph_out g{
            {7,},  //0
            {6,},  //1
            {5,},  //2
            {5,},  //3
            {5,7,},  //4
            {6,},  //5
            {7,},   //6
            {8,},   //7
            {},   //8
            {7,},   //9
         };
         SECTION("topo sort") {/*
            g.add_edge(0,7);
            g.add_edge(1,6); 
            g.add_edge(2,5); 
            g.add_edge(3,5); 
            g.add_edge(4,5); 
            g.add_edge(5,6); 
            g.add_edge(4,7); 
            g.add_edge(6,7); 
            g.add_edge(7,8); 
            g.add_edge(9,7);)*/
            auto result = topo_sort(g);
            //for(auto c: result)
            //  std::cout << c << " ";
            auto expected = {0, 1, 2, 3, 4, 5, 6, 9, 7, 8,};
            auto [res, exp] = std::ranges::mismatch(result,expected);
            if(exp != expected.end()) {
               EXPECT(res!=result.end());
               EXPECT(*res == *exp);
            }
         }
      }
   }
};
// clang-format on
}
}
using rld::algos::specification;
int
main(int argc, char* argv[]) {
   return lest::run(specification, argc, argv);
}
