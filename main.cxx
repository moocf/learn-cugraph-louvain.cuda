#include <cugraph/algorithms.hpp>




int main() {
  using vertex_t = int32_t;       // or int64_t, whichever is appropriate
  using edge_t = vertex_t;
  using weight_t = float;         // or double, whichever is appropriate
  raft::handle_t handle;          // Must be configured if MG
  auto graph = cugraph::legacy::GraphCOO<vertex_t, edge_t, weight_t>(100, 0);
  auto graph_view = graph.view(); // assumes you have created a graph somehow

  size_t level;
  weight_t modularity;

  rmm::device_uvector<vertex_t> clustering_v(graph_view.get_number_of_vertices(), handle.get_stream());

  // louvain optionally supports two additional parameters:
  //     max_level - maximum level of the Dendrogram
  //     resolution - constant in the modularity computation
  std::tie(level, modularity) = cugraph::louvain(handle, graph_view, clustering_v.data());
  return 0;
}
