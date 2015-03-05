#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <ctype.h>

#define BUF_SIZE 1024

#define COLOR_GREEN "\033[0;32m"
#define COLOR_RED "\033[0;31m"
#define COLOR_RESET "\033[0m"

void color_reset()
{
    printf(COLOR_RESET);
}

void pick_color()
{
    if (rand() & 1)
    {
        printf(COLOR_RED);
    }
    else
    {
        printf(COLOR_GREEN);
    }
}

void color_print(FILE *file)
{
    pick_color();

    int c;
    while ((c = getc(file)) != EOF)
    {
        if (isspace(c))
        {
            pick_color();
        }

        putc(c, stdout);
    }

    color_reset();
}

int main(int argc, char *argv[])
{
    srand(time(NULL));

    int failures = 0;

    if (argc > 1)
    {
        for (int i = 1; i < argc; i++)
        {
            FILE *file = fopen(argv[i], "r");
            if (!file)
            {
                fprintf(stderr,
                        "greencat: %s: Could not open file\n",
                        argv[i]);
                failures++;
                continue;
            }

            color_print(file);

            fclose(file);
        }
    }
    else
    {
        color_print(stdin);
    }

    return failures;
}
