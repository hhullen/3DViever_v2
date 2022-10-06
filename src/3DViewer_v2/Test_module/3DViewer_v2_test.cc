#include <gtest/gtest.h>

#include "model_frame_loader.h"
#include "s21_3dViewer_1_0.h"
using std::cout;

TEST(LOADING, C) {
  model_t *model = (model_t *)calloc(1, sizeof(model_t));
  int status = FAILED_LOAD;
  char *path =
      "/Users/hhullen/PROJECTS/github/3DViever_v2/src/models/one_million.obj";

  status = upload_model(path, &model);
}

TEST(LOADING, CPP) {
  S21::ModelFrame m;
  string pth =
      "/Users/hhullen/PROJECTS/github/3DViever_v2/src/models/one_million.obj";
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
}

int main(int argc, char *argv[]) {
  ::testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}