#include "column.h"

#ifndef TABLE_H_
#define TABLE_H_

/*Table struct definition*/
typedef struct Table {
  Column **cols;
  int cols_num;
} Table;

/*Creates a new empty table.
 *Returns pointer to the table or NULL in case of error*/
Table *new_table(void);

/*Adds a new col to the table.
 *Returns 0 if success or 1 if error occured. */
int table_push_col(Table *table, Column *col);

/*Frees all the memory allocated for the table, including columns. */
void terminate_table(Table *table);

#endif
