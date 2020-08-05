#include <string>
#include <benchmark/benchmark.h>

#include "rld/algos/graph.h"

rld::algos::graph_out g{
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
 
static void dfs(benchmark::State& state) {
  for (auto _ : state)
    g.dfs(1, [](int v) {});
}
BENCHMARK(dfs);

static void dfs2(benchmark::State& state) {
  for (auto _ : state)
    g.dfs2(1, [](int v) {});
}
BENCHMARK(dfs2);



static void bfs(benchmark::State& state) {
  for (auto _ : state)
    g.bfs(1, [](int v) {});
}
BENCHMARK(bfs);

static void bfs2(benchmark::State& state) {
  for (auto _ : state)
    g.bfs2(1, [](int v) {});
}
BENCHMARK(bfs2);


BENCHMARK_MAIN();
