/*
** EPITECH PROJECT, 2024
** myprintf
** File description:
** my_strings
*/

#ifndef MY_STRINGS_H_
    #define MY_STRINGS_H_

// String Length/Comparison Functions
int my_strlen(char const *);
int my_strcmp(char const *, char const *);
int my_strncmp(char const *, char const *, int n);
int my_isalnum(char);
int my_strarray_len(char **);

// String Manipulation Functions
char *my_strcat(char *, char const *);
char *my_strncat(char *, char const *, int n);
char *my_strcpy(char *, char const *);
char *my_strncpy(char *, char const *, int n);
char *my_revstr(char *);
char *my_strstr(char *, char const *);
char *my_strdup(char const *);
char *my_strndup(char const *, int);
char *my_strchr(char *, char);
char *my_strrchr(char *, char);
char *my_strnchr(char *, char, int);
char **split_string(char const *, char const *);
void my_free_word_array(char **);

// String Case Functions
char *my_strcapitalize(char *);
char *my_strlowcase(char *);
char *my_strupcase(char *);

// String Property Functions
int my_str_isalpha(char const *);
int my_str_islower(char const *);
int my_str_isnum(char const *);
int my_str_isprintable(char const *);
int my_str_isupper(char const *);

#endif /* !MY_STRINGS_H_ */
