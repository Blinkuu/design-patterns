#include <iostream>
#include <variant>
#include <vector>

struct vec2 {

  std::string get_formatted() {
    return "[" + std::to_string(x) + ", " + std::to_string(y) + "]";
  }

  float x = 0.0f;
  float y = 0.0f;
};

struct circle {
  void render() {
    printf("Rendering circle at %s with radius %f\n",
           m_position.get_formatted().c_str(), m_radius);
  }

  vec2 m_position;
  float m_radius = 5.0f;
};

struct triangle {
  void render() {
    printf("Rendering triangle A = %s, B = %s, C = %s\n",
           m_vertexA.get_formatted().c_str(), m_vertexB.get_formatted().c_str(),
           m_vertexC.get_formatted().c_str());
  }

  vec2 m_vertexA = {.x = 0.0f, .y = 0.0f};
  vec2 m_vertexB = {.x = 3.0f, .y = 7.0f};
  vec2 m_vertexC = {.x = 0.0f, .y = 5.0f};
};

struct call_render {
  void operator()(circle &renderable) { renderable.render(); }

  void operator()(triangle &renderable) { renderable.render(); }
};

struct scene {

  void render() {
    for (auto &node : m_nodes)
      std::visit(call_render{}, node);
  }

  template <typename shape_t> void add_node(shape_t node) {
    m_nodes.push_back(std::move(node));
  }

  std::vector<std::variant<circle, triangle>> m_nodes;
};

int main() {
  scene s{};

  for (std::size_t i = 0; i < 10; i++) {
    i % 2 ? s.add_node(circle{}) : s.add_node(triangle{});
  }

  s.render();

  return 0;
}
