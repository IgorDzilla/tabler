#ifndef COLUMN_H_
#define COLUMN_H_

/*Definition of available data types. */
typedef enum TYPE { INT = 0, FLOAT = 1, STRING = 2 } TYPE;

typedef struct Column {
  TYPE type;
  union {
    int *int_items;
    float *float_items;
    char **str_items;
  };
  char *col_name;
  int print_width;
  int col_size;
} Column;

/*Creates a new empty column with given name and type.
 *Returns pointer to the column or NULL in case of error. */
Column *new_col(char *name, TYPE type);

/*Adds a new item to the column.
 *value is a pointer to the value in the order to make one function instead of
 *multiple. Returns 0 or 1 in case of error. */
int col_push(Column *column, void *value);

/*Frees all memory allocated for the column. */
void terminate_col(Column *column);

#endif
