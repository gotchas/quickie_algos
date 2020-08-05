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