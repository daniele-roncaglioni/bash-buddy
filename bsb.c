#include <stdio.h>
#include <string.h>
#include <stdlib.h>

void printfColored(char *textWithFormatPlaceholder, char *coloredText)
{
    const char *COLOR = "\033[0;35m";
    const char *ENDCOLOR = "\033[0m";
    const char *placeholder = "%s";
    const char *formatSpecifierLocation = strstr(textWithFormatPlaceholder, placeholder);
    if (formatSpecifierLocation == NULL)
        return;
    size_t resultLength = strlen(textWithFormatPlaceholder) + strlen(coloredText) + strlen(COLOR) + strlen(ENDCOLOR) - 2;
    char *interpolatedText = (char *)malloc((resultLength + 1) * sizeof(char));
    if (interpolatedText == NULL)
        return;
    strncpy(interpolatedText, textWithFormatPlaceholder, formatSpecifierLocation - textWithFormatPlaceholder);
    strcat(interpolatedText, COLOR);
    strcat(interpolatedText, coloredText);
    strcat(interpolatedText, ENDCOLOR);
    strcat(interpolatedText, formatSpecifierLocation + 2);
    interpolatedText[resultLength] = '\0';
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

void usageDataTypes()
{
    printfColored("Use: %s\n", "string, integer, list");
    fputs("\
    Example: \n\
        varStr=\"hello\"\n\
        varInt=2\n\
        varArray=(1 2 3)\n",
          stdout);
}

void usageSequence()
{
    printfColored("Use: %s\n", "{start..end}");
    fputs("\
    Example: \n\
        varArray=({1..3})\n\
        for i in ${varArray[@]}; do\n\
            echo $i\n\
        done\n\
        for i in {1..3}; do\n\
            echo $i\n\
        done\n",
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
void usageArithmeticExpression()
{
    printfColored("Use: %s\n", "$((expression))");
    fputs("\
    Example: \n\
        var=$((1+2))\n\
        echo $var\n",
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

void usageConditionalStatements()
{
    printfColored("Use: %s\n", "\n\
    if [ condition ]; then\n\
        ... \n\
    else\n\
        ...\n\
    fi");
    fputs("\
    Example: \n\
        if [ $var -eq 10 ]; then\n\
            echo \"var is 10\"\n\
        fi\n\
        \n\
        if[$var - eq 10]; then\n\
              echo \"var is 10\"\n\
        else\n\
            echo \"var is not 10\"\n\
        fi\n\
        ",
          stdout);
}
void usageForLoop()
{
    printfColored("Use: %s\n", "\n\
    for var in list; do\n\
        ... \n\
    done");
    fputs("\
    Example: \n\
        varArray=(1 \"h\" 3) // can mix int and string\n\
        for value in ${varArray[@]}; do\n\
            echo $value\n\
        done\n\
        \n\
        for i in 1 2 3; do\n\
            echo $i\n\
        done\n\
        \n\
        for i in {1..3}; do\n\
            echo $i\n\
        done\n\
        \n\
        for i in $(seq 1 3); do\n\
            echo $i\n\
        done\n\
        ",
          stdout);
}

void usageWhileLoop()
{
    printfColored("Use: %s\n", "\n\
    while [ condition ]; do\n\
        ... \n\
    done");
    fputs("\
    Example: \n\
        var=0\n\
        while [ $var -lt 3 ]; do\n\
            echo $var\n\
            var=$((var+1))\n\
        done\n\
        ",
          stdout);
}

void usageUntilLoop()
{
    printfColored("Use: %s\n", "\n\
    until [ condition ]; do\n\
        ... \n\
    done");
    fputs("\
    Example: \n\
        var=0\n\
        until [ $var -eq 3 ]; do\n\
            echo $var\n\
            var=$((var+1))\n\
        done\n\
        ",
          stdout);
}
void usage()
{
    fputs("Usage: bsb \"[QUERY]\" (make sure to enclose QUERY in quotes)\n\n", stdout);
    fputs("Your query is matched fuzzyly (Levensthein distance) to the queries below.\n\n", stdout);
    fputs("QUERY options:\n\
    \"variable declaration\": how to declare a variable\n\
    \"data types - string integer list\": different data types in bash\n\
    \"string interpolation\": how to interpolate a string\n\
    \"arithmetic expression\": how to perform arithmetic operations\n\
    \"sequence\": how to create a sequence of numbers\n\
    \"test expression\": how to test the wether statement is true or false\n\
    \"command substitution\": how to subsitute a command for the output of the command\n\
    \"pipe commands\": how to send the output of one command to the input of the next\n\
    \"conditional statements\": how to perform conditional execution based on a condition\n\
    \"for loop\": repeat a block of code multiple times with for\n\
    \"while loop\": repeat a block of code multiple times with while\n\
    \"until loop\": repeat a block of code multiple times with until\n\
    \"functions\": how to define and use functions\n\
    \"file operations\": how to read from and write to files\n\
    \"command line arguments\": how to pass arguments to a script or command\n\
    \"environment variables\": how to access and modify environment variables\n",
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
    else if (strcmp(closestString, "arithmetic expression") == 0)
    {
        usageArithmeticExpression();
    }
    else if (strcmp(closestString, "data types - string integer list") == 0)
    {
        usageDataTypes();
    }
    else if (strcmp(closestString, "sequence") == 0)
    {
        usageSequence();
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
    else if (strcmp(closestString, "conditional statement") == 0)
    {
        usageConditionalStatements();
    }
    else if (strcmp(closestString, "for loop") == 0)
    {
        usageForLoop();
    }
    else if (strcmp(closestString, "while loop") == 0)
    {
        usageWhileLoop();
    }
    else if (strcmp(closestString, "until loop") == 0)
    {
        usageUntilLoop();
    }
    else
    {
        fputs("No match found for your query.\n", stdout);
        usage();
    }
}