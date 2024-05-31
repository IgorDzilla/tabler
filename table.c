#include "table.h"
#include <stdio.h>
#include <stdlib.h>

Table *new_table(void) {
  Table *table = (Table *)malloc(sizeof(Table));
  if (!table) {
    perror("new_table() - malloc failed");
    return NULL;
  }

  return table;
}

int table_push_col(Table *table, Column *new_col) {
  Column **table_upd =
      (Column **)realloc(table->cols, (table->cols_num + 1) * sizeof(Column *));
  if (!table_upd) {
    perror("table_push() - realloc failed");
    return 1;
  }

  table_upd[table->cols_num++] = new_col;

  return 0;
}
