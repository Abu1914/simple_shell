#include <stdlib.h>

/**
 * _str_dup - custom string duplication; excludes beginning bytes
 * @string: string to duplicate (e.g. environmental variable PATH=/bin:/bin/ls)
 * @cs: number of bytes to exclude (e.g. excludes "PATH=")
 * Return: string (e.g. /bin:/bin/ls)
 */
char *_str_dup(char *string, int cs)
{
        char *duplicate_str;
        int a, len = 0;

        if (string == NULL) /* validate str input */
                return (NULL);

        /* calculate len + null terminator to malloc */
        while (*(string + len))
                len++;
        len++;

        if (cs >= len) {
                /* cs is greater than or equal to the length of the string */
                return (NULL);
        }

        /* allocate memory but exclude environmental variable title (PATH) */
        duplicate_str = malloc(sizeof(char) * (len - cs));
        if (duplicate_str == NULL)
                return (NULL);

        a = 0;
        while (a < (len - cs))
        {
                *(duplicate_str + a) = *(string + cs + a);
                a++;
        }
        return (duplicate_str);
}

