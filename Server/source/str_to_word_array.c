/*
** EPITECH PROJECT, 2023
** B-YEP-400-PAR-4-1-zappy-alberick.mahoussi
** File description:
** str_to_word_array
*/

#include <unistd.h>
#include <sys/types.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stddef.h>
#include <ctype.h>

int verif(char c)
{
    if (c == '\t' || c == '\n' || c == ' ' || c == '\0')
        return (1);
    return (0);
}

int count_word(char const *str)
{
    int count_word = 0;
    int i = 0;

    for (; str[i] != '\0'; i++) {
        if (str[i] == ' ' || str[i] == '\t' || str[i] == '\n')
            i++;
        if (verif(str[i]) == 0 && verif(str[i + 1]) == 1) {
            count_word++;
        }
    }
    return (count_word);
}

char **size_array(char const *str)
{
    int i = 0;
    int word_count = count_word(str);
    char **array = malloc(sizeof(char *) * (word_count + 1));

    for (; isspace(str[i]); i++);
    for (int j = 0; j < word_count; j++) {
        int k = i;
        while (str[k] && !isspace(str[k]))
            k++;
        array[j] = malloc(k - i + 1);
        strncpy(array[j], str + i, k - i);
        array[j][k - i] = '\0';
        i = k + 1;
    }
    array[word_count] = NULL;
    return array;
}

char *copy_word(char *str)
{
    char *word = malloc((strlen(str) + 1) * sizeof(char));
    if (word == NULL) {
        fprintf(stderr, "Erreur d'allocation de mÃ©moire\n");
        exit(EXIT_FAILURE);
    }
    strcpy(word, str);
    return word;
}

char **my_str_to_word_array(char const *str, char *delim)
{
    char **words = size_array(str);
    char *p = strtok(strdup(str), delim);
    int i = 0;
    while (p != NULL) {
        words[i] = copy_word(p);
        i++;
        p = strtok(NULL, delim);
    }
    words[i] = NULL;

    return words;
}
