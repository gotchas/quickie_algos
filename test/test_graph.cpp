#include <iostream>

#if 1
#include "gmock/gmock.h"
#else
#include "lest.hpp"
using rld::algos::specification;
int
main(int argc, char* argv[]) {
   return lest::run(specification, argc, argv);
}
#endif

#include "rld/algos/graph.h"

namespace rld {
namespace algos {
#if 0
   // clang-format off
const lest::test specification[] = {
    CASE( "Setup creates a fresh fixture for each section" )
    {
        SETUP("Context") 
        {
            int i = 7;

            SECTION("S1") {         i = 42;   }
            SECTION("S2") { EXPECT( i == 7 ); }
        }
        SETUP("context: regular graph") 
        {
      graph_out g{5};
      SECTION("add") 
      {
         EXPECT(not g.connected(0, 1));
         g.add_edge(0, 1);
         EXPECT(g.connected(0, 1));
        }
        SECTION("add_add_remove") 
        {
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
        SECTION("add_remove_add") 
        {
        }
   }
   SETUP("gra") 
   {
        SECTION("dfs") 
        {
        }
        SECTION("dfs2") 
        {
        }
        SECTION("dfs3") 
        {
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
        SECTION("bfs") 
        {
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
           g.bfs(1, [](int v) { std::cout << v << " "; });
            std::cout << "\n";
           g.bfs2(1, [](int v) { std::cout << v << " "; });
        }
   }
   },   
};
#endif
#if 1
    using ::testing::ElementsAreArray;
    using ::testing::UnorderedElementsAreArray;
    using ::testing::Not;

TEST(dfs, forrest) {
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
            };//TODO topo_sort
            std::cout << "\n";
           std::vector<int> result;
           g.dfs(0, [&result](int v) { std::cout << v << "< " ; result.push_back(v); });
           EXPECT_THAT(result, ElementsAreArray(
              //{1,2,3,4,5,6,0,7,8}
              {0,7,8,}
              ));
}
TEST(dfs, regular_graph) {
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
            std::vector<int> result;
           g.dfs(1, [&result](int v) { std::cout << v << " "; result.push_back(v); });
           EXPECT_THAT(result, ElementsAreArray(
              { 1, 9, 10, 5, 8, 6, 7, 2, 3, 4 }
           ));

           result.clear();
           g.dfs2(1, [&result](int v) { std::cout << v << " "; result.push_back(v); });
           EXPECT_THAT(result, ElementsAreArray(
              { 1, 2, 3, 4, 5, 6, 7, 8, 9, 10 }
           ));
}
#endif
   // clang-format on
}  // namespace algos
}  // namespace rld

/*
1 9 10 5 8 6 7 2 3 4 
1 9 10 7 5 8 6 2 3 4 
1 2 3 4 5 6 7 8 9 10 
1 2 5 9 3 6 8 10 4 7 
1 9 5 2 10 8 6 3 7 4 ⏎
*/