#ifndef FILE_HPP_INCLUDED
#define FILE_HPP_INCLUDED
#include "utils.hpp"


long int count_symbols          (FILE *file_input);

int      num_of_rows            (char *text);

char    *read_file              (const char *TEXT, char *text_buf);

char    *program_text_normalize (char *text);

#endif