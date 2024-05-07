#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <math.h>

void printf_colored(char *text_with_format_placeholder, char *colored_text)
{
    const char *COLOR = "\033[0;35m";
    const char *ENDCOLOR = "\033[0m";
    const char *placeholder = "%s";
    const char *format_specifier_location = strstr(text_with_format_placeholder, placeholder);
    if (format_specifier_location == NULL)
        return;
    size_t resultLength = strlen(text_with_format_placeholder) + strlen(colored_text) + strlen(COLOR) + strlen(ENDCOLOR) - 2;
    char *interpolated_text = (char *)malloc((resultLength + 1) * sizeof(char));
    if (interpolated_text == NULL)
        return;
    strncpy(interpolated_text, text_with_format_placeholder, format_specifier_location - text_with_format_placeholder);
    strcat(interpolated_text, COLOR);
    strcat(interpolated_text, colored_text);
    strcat(interpolated_text, ENDCOLOR);
    strcat(interpolated_text, format_specifier_location + 2);
    interpolated_text[resultLength] = '\0';
    fputs(interpolated_text, stdout);
    free(interpolated_text);
}

int levenshtein_distance(const char *s, const char *t)
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
            int substitution_cost;
            if (s[i - 1] == t[j - 1])
            {
                substitution_cost = 0;
            }
            else
            {
                substitution_cost = 1;
            }
            d[i][j] = fmin(fmin(d[i - 1][j] + 1, d[i][j - 1] + 1), d[i - 1][j - 1] + substitution_cost);
        }
    }
    return d[m][n];
}

void usage_variable_declaration()
{
    printf_colored("Use: %s (Note: no spaces before or after the =)\n", "=");
    fputs("\
    Example: \n\
        var1=\"hello\"\n\
        var2=2\n",
          stdout);
}

void usage_data_types()
{
    printf_colored("Use: %s\n", "string, integer, list");
    fputs("\
    Example: \n\
        varStr=\"hello\"\n\
        varInt=2\n\
        varArray=(1 2 3)\n",
          stdout);
}

void usage_strings()
{
    printf_colored("Use: %s\n", "\"\" or ''");
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

void usage_arrays()
{
    printf_colored("Use: %s\n", "()");
    fputs("\
    Example: \n\
        varArray=(1 2 3)\n\
        echo ${varArray[0]} // gets first element in array\n\
        echo ${varArray[@]} // gets all elements in array using [@]\n\
        echo ${#varArray[@]} // gets length of array using #\n",
          stdout);
}

void usage_sequence()
{
    printf_colored("Use: %s\n", "{start..end}");
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
    printf_colored("Use: %s\n", "${}");
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
    printf_colored("Use: %s\n", "$((expression))");
    fputs("\
    Example: \n\
        var=$((1+2))\n\
        echo $var\n\
    Arithmetic comparison operators:\n\
        >: greater than\n\
        <: less than\n\
        >=: greater than or equal\n\
        <=: less than or equal\n\
        ==: equal\n",
          stdout);
}

void usage_test_expression()
{
    printf_colored("Use: %s (Note: need spaces after and before [ and ])\n", "[ expression ]");
    fputs("\
    Example:\n\
        var=10\n\
        str=\"Hello\"\n\
        file=\"bsb.txt\"\n\
        [ $var -eq 10 ] // sets exit status to 0 (success)\n\
        [ $var -eq 11] // sets exit status to 1 (error)\n\
        [ \"$str\" = \"Hello\" ]\n\
        [ -f \"$file\" ]\n\
    Arithmetic operators:\n\
        -eq: equal\n\
        -ne: not equal\n\
        -gt: greater than\n\
        -lt: less than\n\
        -ge: greater than or equal\n\
        -le: less than or equal\n\
    File operators:\n\
        -e: file exists\n\
        -f: is regular file (not a dir or other file types)\n\
        -d: is directory\n\
        -h: is symbolic link\n\
        -b: is block device\n\
        -c: is character device\n\
        -S: is socket\n\
        -p: is pipe\n\
        -t: is file descriptor (e.g. stdin, stdout, stderr)\n\
        -N: is modified (newer than last read)\n\
        -O: you own file\n\
        -G: group id matches yours\n\
        -g: set-group-id\n\
        -k: sticky bit\n\
        -u: setuid\n\
        -r: readable\n\
        -w: writable\n\
        -x: executable\n\
    String operators:\n\
        -z: empty string\n\
        -n: non-empty string\n\
        =: equal\n\
        !=: not equal\n\
        <: less than (in ASCII order)\n\
        >: greater than (in ASCII order)\n",
          stdout);
}

void usage_command_substitution()
{
    printf_colored("Use: %s\n", "$(command)");
    fputs("\
    Example: \n\
        var=$(ls) // replaces $(ls) with output of the command ls\n\
        echo \"Output of ls command: $var\"\n",
          stdout);
}

void usage_pipe()
{
    printf_colored("Use: command1 %s command2\n", "|");
    fputs("\
    Usage: Sends stdout of one command/process to stdin of \n\
           Note that not all commands read from stdin or write to stdout!\n\
    Example: \n\
        cat file.txt | grep \"pattern\"",
          stdout);
}

void usage_redirection()
{
    printf_colored("Use: %s\n", ">, >>, <");
    fputs("\
    Example: \n\
        echo \"Hello\" > file.txt // writes Hello to file.txt\n\
        echo \"World\" >> file.txt // appends World to file.txt\n\
        cat < file.txt // reads file.txt and prints it to stdout\n\
        grep someString someFile 2> error.txt // writes stderr to error.txt\n\
        grep someString someFile 2>&1 // writes stderr to stdout\n",
          stdout);
}

void usage_conditional_statements()
{
    printf_colored("Use: %s\n", "\n\
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
void usage_for_loop()
{
    printf_colored("Use: %s\n", "\n\
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

void usage_while_loop()
{
    printf_colored("Use: %s\n", "\n\
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

void usage_until_loop()
{
    printf_colored("Use: %s\n", "\n\
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

void usage_functions()
{
    printf_colored("Use: %s\n", "\n\
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

void usage_exit_status()
{
    printf_colored("Use: %s\n", "$?");
    fputs("\
    Example: \n\
        var=10\n\
        [ $var -eq 10 ]\n\
        echo $?\n\
        ",
          stdout);
}

void usage_trap()
{
    printf_colored("Use: %s\n", "\n\
    trap 'command' signal\n\
    ");
    fputs("\
    Example: \n\
        trap 'echo \"Caught signal\"' SIGINT\n",
          stdout);
}

void usage_special_variables()
{
    printf_colored("Use: %s\n", "$<symbol>");
    fputs("\
    Example: \n\
        echo $0 // prints the name of the script\n\
        echo $1 // prints the first argument\n\
        echo $2-9 // prints the n-th argument\n\
        echo $@ // prints all arguments\n\
        echo $# // prints the number of arguments\n\
        echo $* // prints all arguments as a single word\n\
        echo \"$@\" // prints all arguments as separate strings\n\
        echo ${#*} // prints the number of arguments\n\
        echo ${#@} // prints the number of arguments\n\
        echo $? // prints the return value / exit code\n\
        echo $$ // prints the process ID (PID) of the script\n\
        echo $- // prints the flags passed to the script\n\
        echo $_ // prints the last argument of the previous command\n\
        echo $! // prints the process ID (PID) of the last job run in background\n",
          stdout);
}

void usage()
{
    fputs("Usage: bsb \"[QUERY]\" (make sure to enclose QUERY in quotes)\n\n", stdout);
    fputs("Your query is matched fuzzily (Levenshtein distance) to the queries below.\n\n", stdout);
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
    \"trap\": how to catch signals\n\
    \"special variables\": special variables in bash\n",
          stdout);
}

int arg_min(int *array, int size)
{
    int min_index = 0;
    int minValue = array[0];

    for (int i = 1; i < size; i++)
    {
        if (array[i] < minValue)
        {
            minValue = array[i];
            min_index = i;
        }
    }

    return min_index;
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
    "trap",
    "special variables"};

void (*usageFn[])() = {
    usage_variable_declaration,
    usage_data_types,
    usage_strings,
    usage_arrays,
    usageStringInterpolation,
    usageArithmeticExpression,
    usage_sequence,
    usage_test_expression,
    usage_command_substitution,
    usage_pipe,
    usage_redirection,
    usage_conditional_statements,
    usage_for_loop,
    usage_while_loop,
    usage_until_loop,
    usage_functions,
    usage_exit_status,
    usage_trap,
    usage_special_variables};

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
        distances[i] = pow(levenshtein_distance(argv[1], queries[i]), 3) + pow(abs((int)strlen(queries[i]) - (int)strlen(argv[1])), 0.5); // penalty for length difference
    }
    int min_index = arg_min(distances, sizeof(queries) / sizeof(queries[0]));
    printf_colored("Based on your input we guessed your query is about: %s\n", queries[min_index]);
    usageFn[min_index]();
    fputs("\n", stdout);
}