#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Function to stop execution and display an error message in red.
void errStop(char * msg, char * src){
    printf("\033[1;31mError: %s in %s\033[0m\n", msg, src);
    exit(EXIT_FAILURE);
}

// Structure for an integer column.
typedef struct IntCol{
    int id;         // Unique identifier for the column.
    char * name;    // Name of the column.
    int * array;    // Dynamic array to store integer values.
} IntCol;

// Structure for a string column.
typedef struct StrCol{
    int id;         // Unique identifier for the column.
    char * name;    // Name of the column.
    char ** strings; // Dynamic array of string pointers.
} StrCol;

// Structure for a floating-point number column.
typedef struct FloatCol{
    int id;         // Unique identifier for the column.
    char * name;    // Name of the column.
    float * array;  // Dynamic array to store float values.
} FloatCol;

// Structure for the table containing all types of columns.
typedef struct Table{
    IntCol ** int_cols;     // Pointer to an array of integer column pointers.
    int int_cols_num;       // Number of integer columns.
    StrCol ** str_cols;     // Pointer to an array of string column pointers.
    int str_cols_num;       // Number of string columns.
    FloatCol ** float_cols; // Pointer to an array of float column pointers.
    int float_cols_num;     // Number of float columns.
    int width;
    int height;
} Table;

// Enumeration for column types.
typedef enum TYPE{
    INT,    // Integer column type.
    STR,    // String column type.
    FLOAT,  // Float column type.
    UKNOWN
} TYPE;

// Function to initialize the table.
Table * initTable(void){
    Table * table = malloc(sizeof(Table)); // Allocate memory for the table.
    // Initialize the table with no columns.
    table->int_cols_num = 0;
    table->int_cols = NULL;
    table->float_cols_num = 0;
    table->float_cols = NULL;
    table->str_cols_num = 0;
    table->str_cols = NULL;
    table->height = 0;
    table->width = 0;

    return table; // Return the pointer to the newly created table.
}

void freeIntCol(IntCol *col) {
    free(col->array);
    free(col);
}

void freeFloatCol(FloatCol *col) {
    free(col->array);
    free(col);
}

void freeStrCol(Table * table, StrCol *col) {
    for (int i = 0; i < table->height; i++) {
        free(col->strings[i]);
    }
    free(col->strings);
    free(col);
}

// Placeholder for a function to free the table's allocated memory.
void freeTable(Table * table){
  for(int i = 0; i < table->int_cols_num; i++)
    freeIntCol(table->int_cols[i]);
  for(int i = 0; i < table->float_cols_num; i++)
    freeFloatCol(table->float_cols[i]);
  for(int i = 0; i < table->str_cols_num; i++)
    freeStrCol(table, table->str_cols[i]);
}

// Function to create and add an integer column.
void addIntCol(Table * table , char * name){
    IntCol * col = malloc(sizeof(IntCol)); // Allocate memory for the new column.
    col->id = table->width; // Set the column ID.
    col->name = name;    // Set the column name.
    col->array = NULL;   // Initialize the column array.

    IntCol ** old_data = table->int_cols;
    table->int_cols = realloc(table->int_cols, (table->int_cols_num + 1) * sizeof(IntCol*));
    if (table->int_cols == NULL){ // Check for reallocation failure.
        free(old_data);
        errStop("Memory reallocation error", "addIntColTable");
    }
    
    // Add the new column and increment the column count.
    table->int_cols[table->int_cols_num] = col;
    table->int_cols_num++;
}

// Placeholder functions for adding float and string columns.
void addFloatCol(Table * table, char * name){    
    FloatCol * col = malloc(sizeof(FloatCol)); // Allocate memory for the new column.
    col->id = table->width; // Set the column ID.
    col->name = name;    // Set the column name.
    col->array = NULL;   // Initialize the column array.

    FloatCol ** old_data = table->float_cols;
    table->float_cols = realloc(table->float_cols, (table->float_cols_num + 1) * sizeof(FloatCol));
    if (table->float_cols == NULL){ // Check for reallocation failure.
        free(old_data);
        errStop("Memory reallocation error", "addFloatColTable");
    }
    
    // Add the new column and increment the column count.
    table->float_cols[table->float_cols_num] = col;
    table->float_cols_num++;
}

void addStrCol(Table * table, char * name){
    StrCol * col = malloc(sizeof(StrCol)); // Allocate memory for the new column.
    col->id = table->width; // Set the column ID.
    col->name = name;    // Set the column name.
    col->strings = NULL;   // Initialize the column array.

    StrCol ** old_data = table->str_cols;
    table->str_cols = realloc(table->str_cols, (table->str_cols_num + 1) * sizeof(StrCol*));
    if (table->str_cols == NULL){ // Check for reallocation failure.
        free(old_data);
        errStop("Memory reallocation error", "addStrColTable");
    }
    
    // Add the new column and increment the column count.
    table->str_cols[table->str_cols_num] = col;
    table->str_cols_num++;
}

// Function to create new columns based on user input.
void newCol(Table * table, TYPE type, char * name){
    // Add the column based on its type.
    switch(type){
        case INT:
            addIntCol(table, name);
            break;
        case STR:
            addStrCol(table, name);
            break;
        case FLOAT:
            addFloatCol(table, name);
            break;
        case UKNOWN:
            printf("Invalid data type.\n");
    }
    table->width++; // Increment the total column count.
}

void headPrint(Table * table){
    for(int i = 0; i < table->width; i++){
        for(int j = 0; j < table->int_cols_num; j++)
            if(table->int_cols[j]->id == i)
                printf("%10s", table->int_cols[j]->name);
        
        for(int j = 0; j < table->float_cols_num; j++)
             if(table->float_cols[j]->id == i)
                printf("%10s", table->float_cols[j]->name);           
        
        for(int j = 0; j < table->str_cols_num; j++)
            if(table->str_cols[j]->id == i)
                printf("%10s", table->str_cols[j]->name);
    }
    printf("\n");
}



// Main function to demonstrate table initialization.
int main(void){
    Table * table = initTable(); // Initialize the table.

    //add id col
    newCol(table, INT, "id");

    //add surname col
    newCol(table, STR, "surname");

    //add name col
    newCol(table, STR, "name");

    //add salary col
    newCol(table, INT, "salary");

    //add some float shit
    newCol(table, FLOAT, "shit");

    headPrint(table);    
    
    freeTable(table);
}
