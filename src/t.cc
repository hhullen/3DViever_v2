#include <iostream>

#include "model_frame_loader.h"
using std::cout;

int main() {
  S21::ModelFrame m;
  // string pth = "/Users/hhullen/cube.obj";
  string pth = "/Users/hhullen/PROJECTS/99others/models/one_million.obj";
  bool is_load = m.UploadModel(pth);
  cout << "facets " << m.get_facets_amount() << "\n";
  cout << "indices " << m.get_indices_amount() << "\n";
  cout << "x max " << m.get_max_value(S21::Axis::X) << "\n";
  cout << "y max " << m.get_max_value(S21::Axis::Y) << "\n";
  cout << "z max " << m.get_max_value(S21::Axis::Z) << "\n";
  cout << "x min " << m.get_min_value(S21::Axis::X) << "\n";
  cout << "y min " << m.get_min_value(S21::Axis::Y) << "\n";
  cout << "z min " << m.get_min_value(S21::Axis::Z) << "\n";
  cout << "vertexes " << m.get_vertexes_amount() << "\n";
  cout << "loaded? " << is_load << "\n";
  return 0;
}
