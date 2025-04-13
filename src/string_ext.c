#include <stdio.h>
#include <stdlib.h>
#include <string.h>

char *replace_str(const char *str, const char *old_sub, const char *new_sub) {
    char *result = NULL;
    int i, count = 0;
    int new_sub_len = strlen(new_sub);
    int old_sub_len = strlen(old_sub);

    // Count occurrences of the old substring
    for (i = 0; str[i] != '\0'; i++) {
        if (strstr(&str[i], old_sub) == &str[i]) {
            count++;
            i += old_sub_len - 1;
        }
    }

    // Allocate memory for the new string
    result = (char*)malloc(i + (new_sub_len - old_sub_len) * count + 1);
    if (!result) {
        perror("Failed to allocate memory");
        return NULL;
    }

    i = 0;
    while (*str) {
        // Check for the old substring
        if (strstr(str, old_sub) == str) {
            strcpy(&result[i], new_sub);
            i += new_sub_len;
            str += old_sub_len;
        } else {
            result[i++] = *str++;
        }
    }

    result[i] = '\0';
    return result;
}
