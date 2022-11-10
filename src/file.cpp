#include "../include/file.hpp"

char *read_file(const char *TEXT, char *text_buf) {
    FILE *file_input = fopen(TEXT, "r");

    assert(file_input != nullptr && "coudn't open file");

    if (file_input == NULL)
        printf("Could not open file.\n");
    
    long int SYMBOLS = count_symbols(file_input);

    text_buf = (char *) calloc(SYMBOLS + 1, sizeof(char)); 

    assert(text_buf != nullptr && "null pointer");

    fread(text_buf, sizeof(char), SYMBOLS, file_input);

    fclose(file_input);
    text_buf = program_text_normalize(text_buf);
    return text_buf;

}

int num_of_rows(char *text)  {
    int count = 0;
    char *point = text;

    while (*point != '\0')  {
        if (*point == '\n')
            count++;
        point++;
    }
    return count;
}

long int count_symbols(FILE *file_input)  {
    fseek(file_input, 0, SEEK_END);
    
    long int number = ftell(file_input);

    fseek(file_input, 0, SEEK_SET);

    return number;
}



char *program_text_normalize(char *text)  {
    assert(text != nullptr && "null pointer");
   
    char *point = text;

    for (; *(point) != '\0'; point++)  { 
        if (*point == '\n')  
            *point = ' ';
        
        if (*point == ' ')
            point++;
    }
    return text;
}

