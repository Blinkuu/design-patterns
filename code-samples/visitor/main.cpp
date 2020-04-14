#include <iostream>
#include <memory>

#include "graph.hpp"
#include "visitor.hpp"

int main() {
  graph city_graph{};

  for (std::size_t i = 0; i < 10; i++) {
    i % 2 ? city_graph.add_node(std::make_unique<city_node>())
          : city_graph.add_node(std::make_unique<village_node>());
  }

  printing_visitor p_visitor{};
  city_graph.accept(p_visitor);

  accumulating_visitor a_visitor{};
  city_graph.accept(a_visitor);

  std::cout << "sum: " << a_visitor.get_sum() << std::endl;

  return 0;
}
