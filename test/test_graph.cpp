#include <iostream>

#include "lest.hpp"
#include "rld/algos/graph.h"

namespace rld {
namespace algos {
   // clang-format off
const lest::test specification[] = {
    CASE( "Setup creates a fresh fixture for each section" )
    {
        SETUP("Context") {
            int i = 7;

            SECTION("S1") {         i = 42;   }
            SECTION("S2") { EXPECT( i == 7 ); }
        }
        SETUP("context: regular graph") {
      graph_out g{5};
      SECTION("add") {
         EXPECT(not g.connected(0, 1));
         g.add_edge(0, 1);
         EXPECT(g.connected(0, 1));
        }
        SECTION("add_add_remove") {
         EXPECT(not g.connected(0, 1));
         EXPECT(not g.connected(0, 2));
         g.add_edge(0, 1);
         EXPECT(g.connected(0, 1));
         g.add_edge(0, 2);
         EXPECT(g.connected(0, 2));
         g.remove_edge(0, 1);
         EXPECT(not g.connected(0, 1));
         EXPECT(g.connected(0, 2));
        }
        SECTION("add_remove_add") {
        }
        
   }
   SETUP("dfs") {
      //?
        SECTION("dfs") {
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
            std::cout << "\n";
           g.dfs(0, [](int v) { std::cout << v << " "; });
        }


        SECTION("dfs2") {
            graph_out g{
               {},  //0
               {2,5,9,},  //1
               {3,},  //2
               {4,},  //3
               {},  //4
               {6,8,},  //5
               {7,},   //6
               {},   //7
               {},   //8
               {10,},   //9
               {},   //10
            };
            std::cout << "\n";
           g.dfs(1, [](int v) { std::cout << v << " "; });
        }
        SECTION("dfs3") {
            graph_out g{
               {},  //0
               {2,5,9,},  //1
               {3,},  //2
               {4,},  //3
               {},  //4
               {6,8,},  //5
               {7,},   //6
               {},   //7
               {},   //8
               {10,},   //9
               {7},   //10     <- vs dfs2
            };
            std::cout << "\n";
           g.dfs(1, [](int v) { std::cout << v << " "; });
            std::cout << "\n";
           g.dfs2(1, [](int v) { std::cout << v << " "; });
        }

   }
   },   

};
// clang-format on
}
}
using rld::algos::specification;
int
main(int argc, char* argv[]) {
   return lest::run(specification, argc, argv);
}