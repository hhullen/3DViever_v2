#include "model_frame_loader.h"

namespace S21 {

ModelFrame::ModelFrame() {
  vertexes_.max_values = new double[kAXIS_AMOUNT];
  vertexes_.min_values = new double[kAXIS_AMOUNT];
  SetDefaultValues();
}

ModelFrame::~ModelFrame() {
  RemoveModel();
  delete vertexes_.max_values;
  delete vertexes_.min_values;
}

void ModelFrame::RemoveModel() { SetDefaultValues(); }

unsigned int ModelFrame::get_vertexes_amount() {
  return vertexes_.vertexes.size() / 3;
}

unsigned int ModelFrame::get_facets_amount() { return facets_.facets_n; }

unsigned int ModelFrame::get_indices_amount() { return facets_.indices.size(); }

double ModelFrame::get_max_value(Axis axis) {
  return vertexes_.max_values[axis];
}

double ModelFrame::get_min_value(Axis axis) {
  return vertexes_.min_values[axis];
}

bool ModelFrame::UploadModel(string file_path) {
  bool returnable = false;
  thread *vertexes_thread;
  thread *facets_thread;

  RemoveModel();
  file_path_ = &file_path;
  vertexes_thread = new thread(&ModelFrame::UploadVertexes, this, &vertexes_);
  facets_thread = new thread(&ModelFrame::UploadFacets, this, &facets_);
  vertexes_thread->join();
  facets_thread->join();
  delete vertexes_thread;
  delete facets_thread;

  if (IsCorrectModel()) {
    returnable = true;
  } else {
    RemoveModel();
  }

  return returnable;
}

void ModelFrame::UploadVertexes(Vertexes *data) {
  ifstream file;
  string line;

  file.open(*file_path_);
  if (file.is_open()) {
    while (!file.eof()) {
      if (line == "v") {
        file >> line;
        ReadVertex(file, *data, line);
      } else {
        file >> line;
      }
    }
    file.close();
  }
  if (data->vertexes.size() > 0) {
    SearcMaxMin(*data);
  }
}

void ModelFrame::ReadVertex(ifstream &file, Vertexes &data, string &line) {
  while ((IsAsciiDigit(line[0]) || line[0] == '-') && !file.eof()) {
    data.vertexes.push_back(stod(line));
    file >> line;
  }
}

void ModelFrame::SearcMaxMin(Vertexes &data) {
  size_t vector_size = data.vertexes.size();

  for (int i = 0; i < kAXIS_AMOUNT; ++i) {
    data.max_values[i] = data.vertexes[i];
    data.min_values[i] = data.vertexes[i];
  }

  for (size_t i = 3; i < vector_size; i += 3) {
    IsMax(data.vertexes[i + Axis::X], data.max_values[Axis::X]);
    IsMin(data.vertexes[i + Axis::X], data.min_values[Axis::X]);
    IsMax(data.vertexes[i + Axis::Y], data.max_values[Axis::Y]);
    IsMin(data.vertexes[i + Axis::Y], data.min_values[Axis::Y]);
    IsMax(data.vertexes[i + Axis::Z], data.max_values[Axis::Z]);
    IsMin(data.vertexes[i + Axis::Z], data.min_values[Axis::Z]);
  }
}

void ModelFrame::UploadFacets(Facets *data) {
  ifstream file;
  string line;
  unsigned int first_index = 0;

  file.open(*file_path_);
  if (file.is_open()) {
    while (!file.eof()) {
      if (line == "f") {
        file >> line;
        ReadFacet(file, *data, line);
        ++(*data).facets_n;
      } else {
        file >> line;
      }
    }
    file.close();
  }
}

void ModelFrame::ReadFacet(ifstream &file, Facets &data, string &line) {
  unsigned int first_index = 0;

  if (IsAsciiDigit(line[0]) && !file.eof()) {
    first_index = stod(line) - 1;
    data.indices.push_back(first_index);
  }
  file >> line;

  while (IsAsciiDigit(line[0]) && !file.eof()) {
    data.indices.push_back(stod(line) - 1);
    data.indices.push_back(data.indices.back());
    file >> line;
  }
  data.indices.push_back(first_index);
}

bool ModelFrame::IsAsciiDigit(const char &sym) {
  return sym >= '0' && sym <= '9';
}

void ModelFrame::SetDefaultValues() {
  for (int i = 0; i < kAXIS_AMOUNT; ++i) {
    vertexes_.max_values[i] = 0;
    vertexes_.min_values[i] = 0;
  }
  vertexes_.vertexes.clear();
  vertexes_.vertexes.shrink_to_fit();
  facets_.facets_n = 0;
  facets_.indices.clear();
  facets_.indices.shrink_to_fit();
}

bool ModelFrame::IsCorrectModel() {
  return vertexes_.vertexes.size() > 2 && facets_.facets_n > 0 &&
         facets_.indices.size() > 1 && vertexes_.vertexes.size() % 3 == 0;
}

void ModelFrame::IsMax(const double &value, double &max_value) {
  if (value > max_value) {
    max_value = value;
  }
}

void ModelFrame::IsMin(const double &value, double &min_value) {
  if (value < min_value) {
    min_value = value;
  }
}

}  // namespace S21
