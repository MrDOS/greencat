#include <ctype.h>
#include <signal.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <unistd.h>

#define BUF_SIZE 1024

#define COLOR_GREEN "\033[0;32m"
#define COLOR_RED "\033[0;31m"
#define COLOR_RESET "\033[0m"

#define SLOW_SLEEP (10 * 1000) /* 10ms */

int failures = 0;

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

void color_print(FILE *file, bool slow)
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

        if (slow)
        {
            usleep(SLOW_SLEEP);
        }
    }

    color_reset();
}

void cleanup_and_exit()
{
    color_reset();
    _exit(failures);
}

int main(int argc, char *argv[])
{
    bool slow = false;

    int c;
    while ((c = getopt (argc, argv, "s")) != -1)
    {
        if (c == 's')
        {
            slow = true;
        }
    }

    srand(time(NULL));
    signal(SIGINT, cleanup_and_exit);
    setbuf(stdout, NULL);

    if (argc > 1)
    {
        for (int i = optind; i < argc; i++)
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

            color_print(file, slow);

            fclose(file);
        }
    }
    else
    {
        color_print(stdin, slow);
    }

    return failures;
}
