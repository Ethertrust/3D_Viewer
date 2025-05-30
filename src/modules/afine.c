/**
 * @file afine.c
 * @authors elmatree (https://edu.21-school.ru/profile/elmatree)
 * @authors karstarl (https://edu.21-school.ru/profile/karstarl)
 * @authors shericen (https://edu.21-school.ru/profile/shericen)
 * @brief Module for working with transformation matrix
 * @version 1.0
 * @date 2024-12-19
 *
 * @copyright Copyright (c) 2024
 *
 */

#include "./include/afine.h"

/**
 * @brief Initialize transformation matrices
 *
 * @param[out] mx matrix data struct
 * @retval false - correct memory allocate
 * @retval true - memory allocate failed
 */
int init_afinne(afinne_t *mx) {
  int err = false;

  mx->current = (float *)calloc(4 * 4, sizeof(float));
  mx->identity = (float *)calloc(4 * 4, sizeof(float));
  mx->move = (float *)calloc(4 * 4, sizeof(float));
  mx->scale = (float *)calloc(4 * 4, sizeof(float));
  mx->rotate_x = (float *)calloc(4 * 4, sizeof(float));
  mx->rotate_y = (float *)calloc(4 * 4, sizeof(float));
  mx->rotate_z = (float *)calloc(4 * 4, sizeof(float));

  if (!mx->current || !mx->identity || !mx->move || !mx->scale ||
      !mx->rotate_x || !mx->rotate_y || !mx->rotate_z) {
    err = true;
  } else {
    mx->identity[0] = mx->identity[5] = mx->identity[10] = mx->identity[15] =
        1.0f;
    mx->move[0] = mx->move[5] = mx->move[10] = mx->move[15] = 1.0f;
    mx->scale[0] = mx->scale[5] = mx->scale[10] = mx->scale[15] = 1.0f;
    mx->rotate_x[0] = mx->rotate_x[5] = mx->rotate_x[10] = mx->rotate_x[15] =
        1.0f;
    mx->rotate_y[0] = mx->rotate_y[5] = mx->rotate_y[10] = mx->rotate_y[15] =
        1.0f;
    mx->rotate_z[0] = mx->rotate_z[5] = mx->rotate_z[10] = mx->rotate_z[15] =
        1.0f;
  }

  return err;
}

/**
 * @brief Clears memory allocated for conversion matrices
 *
 * @param[out] mx matrix data struct
 */
void destroy_affine(afinne_t *mx) {
  if (mx->current) {
    free(mx->current);
    mx->current = NULL;
  }

  if (mx->identity) {
    free(mx->identity);
    mx->identity = NULL;
  }

  if (mx->move) {
    free(mx->move);
    mx->move = NULL;
  }

  if (mx->scale) {
    free(mx->scale);
    mx->scale = NULL;
  }

  if (mx->rotate_x) {
    free(mx->rotate_x);
    mx->rotate_x = NULL;
  }

  if (mx->rotate_y) {
    free(mx->rotate_y);
    mx->rotate_y = NULL;
  }

  if (mx->rotate_z) {
    free(mx->rotate_z);
    mx->rotate_z = NULL;
  }
}

/**
 * @brief Normalizes model coordinates to a range [-1;1]
 *
 * @param[out] data models data struct
 */
void normalize_vertex(data_t *data) {
  float *vertex = data->vertexes.matrix;

  for (int i = 0; i < data->vertex_count; i++, vertex += V_CNT) {
    for (int j = 0; j < V_CNT; j++) {
      vertex[j] /= data->max_position;
    }
  }
}

/**
 * @brief Multiplies transformation matrices into one result matrix
 *
 * @param[out] mx struct of transformation matrices
 * @param[in] data bitwise representation of changes in transformation matrices
 */
void transform_mx(afinne_t *mx, unsigned int data) {
  mx_copy(mx->current, mx->identity);

  if (data & SCALE) mx_mult_4x4(mx->current, mx->scale);
  if (data & ROTATE_X) mx_mult_4x4(mx->current, mx->rotate_x);
  if (data & ROTATE_Y) mx_mult_4x4(mx->current, mx->rotate_y);
  if (data & ROTATE_Z) mx_mult_4x4(mx->current, mx->rotate_z);
  if (data & MOVE) mx_mult_4x4(mx->current, mx->move);
}
