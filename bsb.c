#include <stdio.h>
#include <string.h>

void usageStringInterpolation()
{
    fputs("Use: ${} \n\
    Example: \n\
        var=\"ld\"\n\
        echo \"Hello wor${var}\"\n\
        echo \"With stand alone var name no need for {}: $var\"\n",
          stdout);
}

void usage()
{
    fputs("Usage: bsb [QUERY]\n\n", stdout);
    fputs("Your query is matched fuzzyly (Levensthein distance) to the queries below.\n\n", stdout);
    fputs("QUERY options:\n\
    \"string interpolation\" how to interpolate a string\n\
    \"variable declaration\" how to declare a variable\n\
    \"variable assignment\" how to assign a value to var that already exists\n",
          stdout);
}

int main(int argc, char *argv[])
{
    if (argc != 2)
    {
        fputs("You need to provide exactly one argument.\n", stdout);
        usage();
        return 0;
    }
    if (strcmp(argv[1], "--help") == 0)
    {
        usage();
        return 0;
    }

    char *closestString = argv[1];

    if (strcmp(closestString, "string interpolation") == 0)
    {
        usageStringInterpolation();
    }
    return 0;
}