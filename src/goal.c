#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
char *trim(char *str) {
    while (isspace((unsigned char)*str)) str++;
    if (*str == 0) return str;
    char *end = str + strlen(str) - 1;
    while (end > str && isspace((unsigned char)*end)) end--;
    end[1] = '\0';
    return str;
}
void execute_print(const char *args) {
size_t len = strlen(args);
if (len >= 2 && args[0] == '"' && args[len - 1] == '"') {
char output[len - 1];
strncpy(output, args + 1, len - 2); output[len - 2] = '\0'; printf("%s\n", output);} else {printf("Syntax Error: Invalid string format '%s'\n", args);}}
void parse_and_execute(char *command) {
command = trim(command);
if (strncmp(command, "print(", 6) == 0) {
char *start = strchr(command, '(') + 1;
char *end = strrchr(command, ')');
if (start && end && end > start) {
char args[256];
strncpy(args, start, end - start);
            args[end - start] = '\0';
            execute_print(trim(args));
        } else {
            printf("Syntax Error: Missing parentheses in '%s'\n", command);
        }
    } else {
        printf("Error: Unknown command '%s'\n", command);
    }
}
char *read_file(const char *filename) {
    FILE *file = fopen(filename, "r");
    if (!file) {
        printf("Error: Could not open file '%s'\n", filename);
        exit(EXIT_FAILURE);
    }
    fseek(file, 0, SEEK_END);
    long file_size = ftell(file);
    rewind(file);
    char *content = (char *)malloc(file_size + 1);
    if (!content) {
        printf("Error: Memory allocation failed\n");
        fclose(file);
        exit(EXIT_FAILURE);
    }
    fread(content, 1, file_size, file);
    content[file_size] = '\0';    fclose(file);
    return content;
}
int main() {
    const char *filename = "code.capps";
    char *code = read_file(filename);
    char *command = strtok(code, ";");
    while (command != NULL) {
        parse_and_execute(command);        command = strtok(NULL, ";");
    }
   free(code);

    return 0;
}

