#include <stdio.h>
#include <string.h>
#include <stdlib.h>

void printfColored(char *textWithFormatPlaceholder, char *coloredText)
{
    const char *COLOR = "\033[0;35m";
    const char *ENDCOLOR = "\033[0m";
    const char *placeholder = "%s";
    const char *format_specifier_location = strstr(textWithFormatPlaceholder, placeholder);
    if (format_specifier_location == NULL)
        return;
    size_t result_length = strlen(textWithFormatPlaceholder) + strlen(coloredText) + strlen(COLOR) + strlen(ENDCOLOR) - 2;
    char *interpolatedText = (char *)malloc((result_length + 1) * sizeof(char));
    if (interpolatedText == NULL)
        return;
    strncpy(interpolatedText, textWithFormatPlaceholder, format_specifier_location - textWithFormatPlaceholder);
    strcat(interpolatedText, COLOR);
    strcat(interpolatedText, coloredText);
    strcat(interpolatedText, ENDCOLOR);
    strcat(interpolatedText, format_specifier_location + 2);
    interpolatedText[result_length] = '\0';
    fputs(interpolatedText, stdout);
    free(interpolatedText);
}
void usageVariableDeclaration()
{
    printfColored("Use: %s (Note: no spaces before or after the =)\n", "=");
    fputs("\
    Example: \n\
        var1=\"hello\"\n\
        var2=2\n",
          stdout);
}
void usageStringInterpolation()
{
    printfColored("Use: %s\n", "${}");
    fputs("\
    Example: \n\
        var=\"ld\"\n\
        echo \"Hello wor${var}\"\n\
        echo \"With tand alone var name no need for {}: $var\"\n",
          stdout);
}
void usageTestExpression()
{
    printfColored("Use: %s (Note: need spaces after and before [ and ])\n", "[ expression ]");
    fputs("\
    Example:\n\
        var=10\n\
        [ $var -eq 10 ] // sets exit status to 0 (success)\n\
        [ $var - eq 11] // sets exit status to 1 (error)\n",
          stdout);
}

void usage()
{
    fputs("Usage: bsb \"[QUERY]\" (make sure to enclose QUERY in quotes)\n\n", stdout);
    fputs("Your query is matched fuzzyly (Levensthein distance) to the queries below.\n\n", stdout);
    fputs("QUERY options:\n\
    \"variable declaration\" how to declare a variable\n\
    \"string interpolation\" how to interpolate a string\n\
    \"test expression\" how to test the wether statement is true or false\n",
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

    const char *closestString = argv[1];

    if (strcmp(closestString, "variable declaration") == 0)
    {
        usageVariableDeclaration();
    }
    if (strcmp(closestString, "string interpolation") == 0)
    {
        usageStringInterpolation();
    }
    if (strcmp(closestString, "test expression") == 0)
    {
        usageTestExpression();
    }
    return 0;
}