#ifndef SRC_S21_3DVIEWER_1_0_H_
#define SRC_S21_3DVIEWER_1_0_H_

// includes
#define _GNU_SOURCE
#include <math.h>
#include <stdio.h>
#include <stdlib.h>

// standart function returnable
#define TRUE 1
#define FALSE 0

#define DOUBLE_T 21
#define UINT_T 42

// status of uploading process result
#define SUCCESS_LOAD 0
#define FAILED_LOAD 1

// typedef axises
typedef enum { X_AXIS, Y_AXIS, Z_AXIS } axis_e;

// model struct
typedef struct model_t {
  unsigned int vertexes_n;
  unsigned int facets_n;
  unsigned int indices_n;
  double minX, minY, minZ;
  double maxX, maxY, maxZ;
  double *data_3d;
  unsigned int *indices;
} model_t;

// file uploading functions
int upload_model(char *file_path, model_t **data);
void init_default_data(model_t **data);
void remove_model(model_t **data);
void upload_file(FILE *file, model_t **data);
void check_min_max(model_t **data, unsigned int v_iter);
void facets_data_parsing(char *buffer, model_t **data, unsigned int *f_iter,
                         unsigned int start_f_iter);
void calculate_needs(FILE *file, model_t **data);
void calculate_facets_vertex_indices(char *buffer, unsigned int *indices_n);
int is_digit(char sym);

// affinne transformation functions
void move_model(model_t **data, int axis, double shift);
void rotate_model(model_t **data, int axis, double ang);
void scale_model(model_t **data, double coeff);

#endif  // SRC_S21_3DVIEWER_1_0_H_
