#include "s21_3dViewer_1_0.h"

// uploading model
int upload_model(char *file_path, model_t **data) {
  int returnable = FAILED_LOAD;
  FILE *file = NULL;

  if ((*data)) init_default_data(data);
  file = fopen(file_path, "r");
  if (file) calculate_needs(file, data);

  file = fopen(file_path, "r");
  if (file && (*data)->vertexes_n > 0) {
    (*data)->data_3d =
        (double *)malloc(((*data)->vertexes_n * 3 + 1) * sizeof(double));
    (*data)->indices =
        (unsigned int *)malloc((*data)->indices_n * sizeof(unsigned int));
  }

  if (file && (*data)->indices && (*data)->data_3d) {
    upload_file(file, data);
    if ((*data)->vertexes_n > 0 && (*data)->facets_n > 0) {
      returnable = SUCCESS_LOAD;
    } else {
      remove_model(data);
    }
  }

  return returnable;
}

void init_default_data(model_t **data) {
  (*data)->facets_n = 0;
  (*data)->indices_n = 0;
  (*data)->vertexes_n = 0;
  (*data)->maxX = 0;
  (*data)->maxY = 0;
  (*data)->maxZ = 0;
  (*data)->minX = 0;
  (*data)->minY = 0;
  (*data)->minZ = 0;
  if ((*data)->data_3d) free((*data)->data_3d);
  (*data)->data_3d = NULL;
  if ((*data)->indices) free((*data)->indices);
  (*data)->indices = NULL;
}

void remove_model(model_t **data) {
  if ((*data)) {
    if ((*data)->data_3d) {
      free((*data)->data_3d);
      (*data)->data_3d = NULL;
    }
    if ((*data)->indices) {
      free((*data)->indices);
      (*data)->indices = NULL;
    }
    free((*data));
    (*data) = NULL;
  }
}

void upload_file(FILE *file, model_t **data) {
  unsigned int v_iter = 0, f_iter = 0;
  char *buffer = NULL;
  size_t N = 0;

  while (getline(&buffer, &N, file) != EOF) {
    unsigned int curr_start_f_iter = f_iter;
    if (buffer[0] == 'v' && buffer[1] == ' ') {
      sscanf(buffer, "v %lf %lf %lf", &(**data).data_3d[v_iter],
             &(**data).data_3d[v_iter + 1], &(**data).data_3d[v_iter + 2]);
      check_min_max(data, v_iter);
      v_iter += 3;
    } else if (buffer[0] == 'f' && buffer[1] == ' ' &&
               (*data)->vertexes_n > 1) {
      facets_data_parsing(buffer, data, &f_iter, curr_start_f_iter);
    } else if ((*data)->vertexes_n <= 1) {
      (*data)->facets_n = 0;
    }
  }
  if (buffer) free(buffer);
  if (file) fclose(file);
}

void check_min_max(model_t **data, unsigned int v_iter) {
  if ((**data).data_3d[v_iter] > (*data)->maxX) {
    (*data)->maxX = (**data).data_3d[v_iter];
  } else if ((**data).data_3d[v_iter] < (*data)->minX) {
    (*data)->minX = (**data).data_3d[v_iter];
  }

  if ((**data).data_3d[v_iter + 1] > (*data)->maxY) {
    (*data)->maxY = (**data).data_3d[v_iter + 1];
  } else if ((**data).data_3d[v_iter + 1] < (*data)->minY) {
    (*data)->minY = (**data).data_3d[v_iter + 1];
  }

  if ((**data).data_3d[v_iter + 2] > (*data)->maxZ) {
    (*data)->maxZ = (**data).data_3d[v_iter + 2];
  } else if ((**data).data_3d[v_iter + 2] < (*data)->minZ) {
    (*data)->minZ = (**data).data_3d[v_iter + 2];
  }
}

void facets_data_parsing(char *buffer, model_t **data, unsigned int *f_iter,
                         unsigned int start_f_iter) {
  for (unsigned int i = 2; buffer[i] != '\0'; i += 1) {
    if ((*f_iter - start_f_iter) > 0 && buffer[i - 1] == ' ' &&
        is_digit(buffer[i])) {
      (**data).indices[*f_iter] = atoi(&buffer[i]) - 1;
      (**data).indices[*f_iter + 1] = (**data).indices[*f_iter];
      *f_iter += 2;
    } else if ((*f_iter - start_f_iter) == 0 && buffer[i - 1] == ' ' &&
               is_digit(buffer[i])) {
      (**data).indices[*f_iter] = atoi(&buffer[i]) - 1;
      *f_iter += 1;
    }
  }
  (**data).indices[*f_iter] = (**data).indices[start_f_iter];
  *f_iter += 1;
}

void calculate_needs(FILE *file, model_t **data) {
  char *buffer = NULL;
  size_t N = 0;

  while (getline(&buffer, &N, file) != EOF) {
    if (buffer[0] == 'v' && buffer[1] == ' ') {
      (*data)->vertexes_n += 1;
    } else if (buffer[0] == 'f' && buffer[1] == ' ') {
      (*data)->facets_n += 1;
      calculate_facets_vertex_indices(buffer, &(*data)->indices_n);
    }
  }
  if (buffer) free(buffer);
  fclose(file);
  (*data)->indices_n *= 2;
}

void calculate_facets_vertex_indices(char *buffer, unsigned int *indices_n) {
  for (unsigned int i = 1; buffer[i] != '\n'; i += 1) {
    if (buffer[i - 1] == ' ' && is_digit(buffer[i])) *indices_n += 1;
  }
}

int is_digit(char sym) {
  int returnable = FALSE;

  if (sym >= '0' && sym <= '9') returnable = TRUE;

  return returnable;
}

// affine transformation
void move_model(model_t **data, int axis, double shift) {
  unsigned int vertexes_values = (*data)->vertexes_n * 3;

  for (unsigned int i = axis; i < vertexes_values; i += 3) {
    (*data)->data_3d[i] += shift;
  }
}

void rotate_model(model_t **data, int axis, double ang) {
  int changeable_1 = 0, changeable_2 = 0;
  unsigned int vertexes_values = (*data)->vertexes_n * 3;

  ang = ang / 180 * M_PI;
  if (axis == X_AXIS) {
    changeable_1 = 1;  // Y
    changeable_2 = 2;  // Z
  } else if (axis == Y_AXIS) {
    changeable_1 = 0;  // X
    changeable_2 = 2;  // Z
  } else if (axis == Z_AXIS) {
    changeable_1 = 0;  // X
    changeable_2 = 1;  // Y
  }

  for (unsigned int i = 0; i < vertexes_values; i += 3) {
    double temp_1 = (*data)->data_3d[i + changeable_1];
    double temp_2 = (*data)->data_3d[i + changeable_2];

    (*data)->data_3d[i + changeable_1] = temp_1 * cos(ang) + temp_2 * sin(ang);
    (*data)->data_3d[i + changeable_2] = temp_1 * -sin(ang) + temp_2 * cos(ang);
  }
}

void scale_model(model_t **data, double coeff) {
  unsigned int vertexes_values = (*data)->vertexes_n * 3;

  for (unsigned int i = 0; i < vertexes_values; i += 1) {
    (*data)->data_3d[i] *= coeff;
  }
}
