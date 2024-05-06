#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <math.h>

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

int levenshteinDistance(const char *s, const char *t)
{
    int m = strlen(s);
    int n = strlen(t);
    int d[m + 1][n + 1];

    for (int i = 0; i <= m; i++)
    {
        d[i][0] = i;
    }

    for (int j = 0; j <= n; j++)
    {
        d[0][j] = j;
    }

    for (int j = 1; j <= n; j++)
    {
        for (int i = 1; i <= m; i++)
        {
            int substitutionCost;
            if (s[i - 1] == t[j - 1])
            {
                substitutionCost = 0;
            }
            else
            {
                substitutionCost = 1;
            }
            d[i][j] = fmin(fmin(d[i - 1][j] + 1, d[i][j - 1] + 1), d[i - 1][j - 1] + substitutionCost);
        }
    }
    return d[m][n];
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

void usageStrings()
{
    printfColored("Use: %s\n", "\"\" or ''");
    fputs("\
    Usage: \n\
        Single quotes are used for string literals: no string interplation is done\n\
        Doube quotes are used for string interpolation\n\
    Example: \n\
        var=\"world\"\n\
        echo 'Hello $var' // prints Hello $var\n\
        echo \"Hello $var\" // prints Hello world\n",
          stdout);
}

void usageArrays()
{
    printfColored("Use: %s\n", "()");
    fputs("\
    Example: \n\
        varArray=(1 2 3)\n\
        echo ${varArray[0]} // gets first element in array\n\
        echo ${varArray[@]} // gets all elements in array using [@]\n\
        echo ${#varArray[@]} // gets length of array using #\n",
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
        echo \"With stand alone var name no need for {}: $var\"\n\
        # Undeclared vars\n\
        echo \"${undeclaredVar:-Hello}\" // prints Hello if undeclaredVar is not set\n\
        echo \"${undeclaredVar:=Hello}\"  # Outputs: Hello and assigns Hello to var if var is unset or null\n\
        echo \"${var:?Variable not set}\"  # Prints an error message if var is unset or null\n\
        # Length\n\
        echo \"${#var}\"  # Gets lenght of var. In this case it outputs: 2\n\
        # Slicing strings\n\
        var=\"Hello, world\"\n\
        echo \"${var:7:5}\"  # Outputs: world\n\
        # Replace\n\
        var=\"Hello, world\"\n\
        echo \"${var/world/Earth}\"  # Outputs: Hello, Earth\n",
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
        str=\"Hello\"\n\
        file=\"bsb.txt\"\n\
        [ $var -eq 10 ] // sets exit status to 0 (success)\n\
        [ $var -eq 11] // sets exit status to 1 (error)\n\
        [ \"$str\" = \"Hello\" ]\n\
        [ -f \"$file\" ]\n\
    Integer testing:\n\
        -eq: equal\n\
        -ne: not equal\n\
        -gt: greater than\n\
        -lt: less than\n\
        -ge: greater than or equal\n\
        -le: less than or equal\n\
        -z: empty string\n\
        -n: non-empty string\n\
    File testing:\n\
        -e: file exists\n\
        -f: regular file (not a dir or other file types)\n\
        -d: directory\n\
        -r: readable\n\
        -w: writable\n\
        -x: executable\n\
    String testing:\n\
        =: equal\n\
        !=: not equal\n\
        <: less than (in ASCII order)\n\
        >: greater than (in ASCII order)\n",
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

void usageRedirection()
{
    printfColored("Use: %s\n", ">, >>, <");
    fputs("\
    Example: \n\
        echo \"Hello\" > file.txt // writes Hello to file.txt\n\
        echo \"World\" >> file.txt // appends World to file.txt\n\
        cat < file.txt // reads file.txt and prints it to stdout\n\
        grep someString someFile 2> error.txt // writes stderr to error.txt\n\
        grep someString someFile 2>&1 // writes stderr to stdout\n",
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

void usageFunctions()
{
    printfColored("Use: %s\n", "\n\
    function name() {\n\
        ... \n\
    }");
    fputs("\
    Example: \n\
        function hello() {\n\
            echo \"Hello\"\n\
        }\n\
        hello\n\
        ",
          stdout);
}

void usageExitStatus()
{
    printfColored("Use: %s\n", "$?");
    fputs("\
    Example: \n\
        var=10\n\
        [ $var -eq 10 ]\n\
        echo $?\n\
        ",
          stdout);
}

void usageTrap()
{
    printfColored("Use: %s\n", "\n\
    trap 'command' signal\n\
    ");
    fputs("\
    Example: \n\
        trap 'echo \"Caught signal\"' SIGINT\n",
          stdout);
}

void usage()
{
    fputs("Usage: bsb \"[QUERY]\" (make sure to enclose QUERY in quotes)\n\n", stdout);
    fputs("Your query is matched fuzzyly (Levensthein distance) to the queries below.\n\n", stdout);
    fputs("QUERY options:\n\
    \"variable declaration\": how to declare a variable\n\
    \"data types - string integer list\": different data types in bash\n\
    \"strings\": how to work with strings\n\
    \"arrays\": how to work with arrays\n\
    \"string interpolation\": how to interpolate a string (also called parameter expansion)\n\
    \"arithmetic expression\": how to perform arithmetic operations\n\
    \"sequence\": how to create a sequence of numbers\n\
    \"test expression\": how to test the wether statement is true or false\n\
    \"command substitution\": how to subsitute a command for the output of the command\n\
    \"pipe command\": how to send the output of one command to the input of the next\n\
    \"redirection\": how to redirect the output of a command from and to files or commands\n\
    \"conditional statements\": how to perform conditional execution based on a condition\n\
    \"for loop\": repeat a block of code multiple times with for\n\
    \"while loop\": repeat a block of code multiple times with while\n\
    \"until loop\": repeat a block of code multiple times with until\n\
    \"functions\": how to define and use functions\n\
    \"exit status\": how to check the exit status of a command\n\
    \"trap\": how to catch signals\n",
          stdout);
}

int argmin(int *array, int size)
{
    int minIndex = 0;
    int minValue = array[0];

    for (int i = 1; i < size; i++)
    {
        if (array[i] < minValue)
        {
            minValue = array[i];
            minIndex = i;
        }
    }

    return minIndex;
}

char *queries[] = {
    "variable declaration",
    "data types",
    "strings",
    "arrays",
    "string interpolation",
    "arithmetic expression",
    "sequence",
    "test expression",
    "command substitution",
    "pipe command",
    "redirection",
    "conditional statements",
    "for loop",
    "while loop",
    "until loop",
    "functions",
    "exit status",
    "trap"};

void (*usageFn[])() = {
    usageVariableDeclaration,
    usageDataTypes,
    usageStrings,
    usageArrays,
    usageStringInterpolation,
    usageArithmeticExpression,
    usageSequence,
    usageTestExpression,
    usageCommandSubstitution,
    usagePipe,
    usageRedirection,
    usageConditionalStatements,
    usageForLoop,
    usageWhileLoop,
    usageUntilLoop,
    usageFunctions,
    usageExitStatus,
    usageTrap};

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

    int distances[sizeof(queries) / sizeof(queries[0])];
    for (int i = 0; i < sizeof(queries) / sizeof(queries[0]); i++)
    {
        distances[i] = pow(levenshteinDistance(argv[1], queries[i]), 3) + pow(abs((int)strlen(queries[i]) - (int)strlen(argv[1])), 0.5); // penalty for length difference
    }
    int minIndex = argmin(distances, sizeof(queries) / sizeof(queries[0]));
    printfColored("Based on your input the most likely query is: %s\n", queries[minIndex]);
    usageFn[minIndex]();
}