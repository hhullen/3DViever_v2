#ifndef VUVER
#define VUVER

#include <fstream>
#include <iostream>
#include <string>
#include <thread>
#include <vector>

using std::ifstream;
using std::stod;
using std::stoi;
using std::string;
using std::thread;
using std::vector;

namespace S21 {

const int kAXIS_AMOUNT = 3;

enum Axis { X, Y, Z };

class ModelFrame {
 public:
  ModelFrame();
  ~ModelFrame();
  bool UploadModel(string file_path);
  void RemoveModel();

  unsigned int get_vertexes_amount();
  unsigned int get_facets_amount();
  unsigned int get_indices_amount();
  double get_max_value(Axis axis);
  double get_min_value(Axis axis);

 private:
  struct Vertexes {
    double *max_values;
    double *min_values;
    vector<double> vertexes;
  } vertexes_;

  struct Facets {
    unsigned int facets_n;
    vector<unsigned int> indices;
  } facets_;

  string *file_path_;

  void UploadVertexes(Vertexes *data);
  void ReadVertex(ifstream &file, Vertexes &data, string &line);
  void SearcMaxMin(Vertexes &data);
  void UploadFacets(Facets *data);
  void ReadFacet(ifstream &file, Facets &data, string &line);
  bool IsAsciiDigit(const char &sym);
  void SetDefaultValues();
  bool IsCorrectModel();
  void IsMax(const double &value, double &max_value);
  void IsMin(const double &value, double &min_value);
};

}  // namespace S21

#endif  // VUVER
