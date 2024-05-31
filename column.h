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

Column *new_col(char *name, TYPE type);

int col_append(Column *column, void *value);
