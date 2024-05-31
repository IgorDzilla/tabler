#include "column.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int type_check(TYPE type) {
  for (int i = INT; i <= STRING; i++)
    if (type == i)
      return i;

  return -1;
}

Column *new_col(char *name, TYPE type) {
  if (type_check(type) == -1) {
    fprintf(stderr, "\033[31mnew_col() - uknown data type\n\033[0m");
    return NULL;
  }
  if (!name) {
    fprintf(stderr, "\033[31mnew_col() - name is NULL\n\033[0m");
    return NULL;
  }

  Column *col = (Column *)malloc(sizeof(Column));
  if (!col) {
    perror("\033[31mnew_col() - malloc failed");
    fprintf(stderr, "\033[0m\n");
    return NULL;
  }

  col->type = type;
  col->col_name = strdup(name);
  if (!col->col_name) {
    perror("\033[31mnew_col() - strdup failed");
    fprintf(stderr, "\033[0m\n");
    free(col);
    return NULL;
  }

  col->print_width = strlen(name);
  col->col_size = 0;
  col->str_items = NULL;

  return col;
}

int col_append_int(Column *col, int *value);
int col_append_float(Column *col, float *value);
int col_append_str(Column *col, char **name);

int col_append(Column *column, void *value) {
  switch (column->type) {
  case INT:
    return col_append_int(column, (int *)value);
  case FLOAT:
    return col_append_float(column, (float *)value);
  case STRING:
    return col_append_str(column, (char **)value);
  default:
    fprintf(stderr, "Uknown data type");
    return 1;
  }
}

int col_append_int(Column *col, int *value) {
  int *new_data =
      (int *)realloc(col->int_items, (col->col_size + 1) * sizeof(int));
  if (!new_data) {
    perror("\033[31mcol_append() - realloc failed");
    fprintf(stderr, "\033[0m\n");
    return 1;
  }

  new_data[col->col_size++] = *value;
  col->int_items = new_data;

  char buff[256];
  sprintf(buff, "%d", *value);
  int val_width = strlen(buff);

  if (col->print_width < val_width)
    col->print_width = val_width;

  return 0;
}

int col_append_float(Column *col, float *value) {
  float *new_data =
      (float *)realloc(col->int_items, (col->col_size + 1) * sizeof(float));
  if (!new_data) {
    perror("\033[31mcol_append() - realloc failed");
    fprintf(stderr, "\033[0m\n");
    return 1;
  }

  new_data[col->col_size++] = *value;
  col->float_items = new_data;

  char buff[256];
  sprintf(buff, "%f", *value);
  int val_width = strlen(buff);

  if (col->print_width < val_width)
    col->print_width = val_width;

  return 0;
}

int col_append_str(Column *col, char **value) {
  char **new_data =
      (char **)realloc(col->int_items, (col->col_size + 1) * sizeof(char *));
  if (!new_data) {
    perror("\033[31mcol_append() - realloc failed");
    fprintf(stderr, "\033[0m\n");
    return 1;
  }

  new_data[col->col_size] = strdup(*value);
  if (!new_data[col->col_size]) {
    perror("\033[31mcol_append() - strdup failed");
    fprintf(stderr, "\033[0m\n");
    return 1;
  }
  col->str_items = new_data;
  col->col_size++;

  int val_width = strlen(*value);

  if (col->print_width < val_width)
    col->print_width = val_width;

  return 0;
}
