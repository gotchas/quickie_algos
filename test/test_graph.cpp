#include <iostream>

#include "gmock/gmock.h"

#include "rld/algos/graph.h"

namespace rld {
namespace algos {
#if 1
    using ::testing::ElementsAreArray;
    using ::testing::UnorderedElementsAreArray;
    using ::testing::Not;

TEST(dfs_bfs, forrest_with_cros_edges) {
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
           std::vector<int> result;

           g.dfs(4, [&result](int v) { result.push_back(v); });
           EXPECT_THAT(result, ElementsAreArray(
              //{1,2,3,4,5,6,0,7,8}
              { 4, 7, 8, 5, 6 }
              ));

              result.clear();
           g.dfs2(4, [&result](int v) { result.push_back(v); });
           EXPECT_THAT(result, ElementsAreArray(
              //{1,2,3,4,5,6,0,7,8}
              { 4, 5, 6, 7, 8 }
              ));

            result.clear();
           g.bfs(4, [&result](int v) { result.push_back(v); });
           EXPECT_THAT(result, ElementsAreArray(
              //{1,2,3,4,5,6,0,7,8}
              { 4, 5, 7, 6, 8 }
              ));

              result.clear();
           g.bfs2(4, [&result](int v) { result.push_back(v); });
           EXPECT_THAT(result, ElementsAreArray(
              //{1,2,3,4,5,6,0,7,8}
              { 4, 7, 5, 8, 6 }
              ));
}

TEST(dfs_bfs, regular_graph) {
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

           g.dfs(1, [&result](int v) { result.push_back(v); });
           EXPECT_THAT(result, ElementsAreArray(
              { 1, 9, 10, 5, 8, 6, 7, 2, 3, 4 }
           ));

           result.clear();
           g.dfs2(1, [&result](int v) { result.push_back(v); });
           EXPECT_THAT(result, ElementsAreArray(
              { 1, 2, 3, 4, 5, 6, 7, 8, 9, 10 }
           ));

           result.clear();
           g.bfs(1, [&result](int v) { result.push_back(v); });
           EXPECT_THAT(result, ElementsAreArray(
              { 1, 2, 5, 9, 3, 6, 8, 10, 4, 7 }
           ));

           result.clear();
           g.bfs2(1, [&result](int v) { result.push_back(v); });
           EXPECT_THAT(result, ElementsAreArray(
              { 1, 9, 5, 2, 10, 8, 6, 3, 7, 4 }
           ));
}
TEST(dfs_bfs, graph_with_cross_edges) {
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
            std::vector<int> result;
           g.dfs(1, [&result](int v) { result.push_back(v); });
           EXPECT_THAT(result, ElementsAreArray(
              { 1, 9, 10, 7, 5, 8, 6, 2, 3, 4 }
           ));

           result.clear();
           g.dfs2(1, [&result](int v) { result.push_back(v); });
           EXPECT_THAT(result, ElementsAreArray(
              { 1, 2, 3, 4, 5, 6, 7, 8, 9, 10 }
           ));

           result.clear();
           g.bfs(1, [&result](int v) { result.push_back(v); });
           EXPECT_THAT(result, ElementsAreArray(
              { 1, 2, 5, 9, 3, 6, 8, 10, 4, 7 }
           ));

           result.clear();
           g.bfs2(1, [&result](int v) { result.push_back(v); });
           EXPECT_THAT(result, ElementsAreArray(
              { 1, 9, 5, 2, 10, 8, 6, 3, 7, 4 }
           ));
}
#endif
   // clang-format on
}  // namespace algos
}  // namespace rld

