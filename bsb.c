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
void usageCommandSubstitution()
{
    printfColored("Use: %s\n", "$(command)");
    fputs("\
    Example: \n\
        var=$(ls) // replaces $(ls) with output of the command ls\n\
        echo \"Output of ls command: $var\"\n",
          stdout);
}

void usagePipe()
{
    printfColored("Use: command1 %s command2\n", "|");
    fputs("\
    Usage: Sends stdout of one command/process to stdin of \n\
           Note that not all commands read from stdin or write to stdout!\n\
    Example: \n\
        cat file.txt | grep \"pattern\"",
          stdout);
}

void usage()
{
    fputs("Usage: bsb \"[QUERY]\" (make sure to enclose QUERY in quotes)\n\n", stdout);
    fputs("Your query is matched fuzzyly (Levensthein distance) to the queries below.\n\n", stdout);
    fputs("QUERY options:\n\
    \"variable declaration\": how to declare a variable\n\
    \"string interpolation\": how to interpolate a string\n\
    \"test expression\": how to test the wether statement is true or false\n\
    \"command substitution\": how to subsitute a command for the output of the command\n\
    \"pipe commands\": how to send the output of one command to the input of the next\n",
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
    else if (strcmp(closestString, "string interpolation") == 0)
    {
        usageStringInterpolation();
    }
    else if (strcmp(closestString, "test expression") == 0)
    {
        usageTestExpression();
    }
    else if (strcmp(closestString, "command substitution") == 0)
    {
        usageCommandSubstitution();
    }
    else if (strcmp(closestString, "pipe command") == 0)
    {
        usagePipe();
    }
}