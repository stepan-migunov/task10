#include <stdio.h>
#include <string.h>


char* reverse(char string[])
{
    size_t string_length = strlen(string);
    for (int i = 0; i < string_length / 2; ++i)
    {
        char t = string[i];
        string[i] = string[string_length - i - 1];
        string[string_length - i - 1] = t;
    }
    return string;
}

int main(int argc, char **argv)
{
///CHECKING IF WE HAVE INVALID NUMBER OF FILES
    if (argc <= 2)
    {
        printf("Use two files' names as arguments of this program: "
               "first file as an input of this program;\n second file as an output of this program\n");
        return 1;
    }
///REPARING FILES TO WORK WITH
    FILE *f_in = freopen(argv[1], "r", stdin);
    if (f_in == NULL)
    {
        printf("Unable to open file %s\n", argv[1]);
        return 1;
    }
    char string[256], input;
    int string_length = 0;
    while ((input = (char) fgetc(f_in)) != EOF && input != '\n')
        string[string_length++] = input;
    string[string_length] = '\0';
    FILE *f_out = freopen(argv[2], "w", stdout);
    if (f_out == NULL)
    {
        printf("Unable to create file %s\n", argv[2]);
        return 1;
    }

///WRITING


///DELETING DOUBLE SPACES
    char *finder = NULL;
    while ((finder = strstr(string, "  ")) != NULL)
    {
        char string_[256];
        for (int i = 0;; ++i)
        {
            string_[i] = finder[i];
            if (finder[i] == '\0')
                break;
        }
        strcpy(finder, string_ + 1);
        string[--string_length] = '\0';
    }

///DELETING SPACES-DOT
    while ((finder = strstr(string, " .")) != NULL)
    {
        char string_[256];
        for (int i = 0;; ++i)
        {
            string_[i] = finder[i];
            if (finder[i] == '\0')
                break;
        }
        strcpy(finder, string_ + 1);
        string[--string_length] = '\0';
    }
    if (strchr(string, ' ') == string && string_length--)
        strcpy(string, string + 1);
    if (string[string_length - 1] == ' ')
        string[string_length - 1] = '\0';
    fprintf(f_out, "===>The string without unwanted spaces:\n--->%s\n", string);


    char string_prime[256];
    string_prime[0] = string_prime[1] = 0;

///FINDING LAST WORD
    char s = string[string_length - 1];
    int s_last_index = string_length - 1;
    while (s == '.')
        s = string[--s_last_index];
    int s_first_index = s_last_index;
    while (s != ' ')
        s = string[--s_first_index];
    int lastword_length = s_last_index - ++s_first_index + 1;
    char lastword[256];
    for (int i = s_first_index; i <= s_last_index; ++i)
        lastword[i - s_first_index] = string[i];
    lastword[lastword_length] = '\0';


///PUSHING TO NEW STRING WORDS THAT DIFFER FROM LASTWORD
    char *pch = strtok(string, " .");
    while (pch != NULL)
    {
        if (strcmp(lastword, pch) != 0)
        {
            strcat(string_prime, pch);
            strcat(string_prime, " ");
        }
        pch = strtok(NULL, " .");
    }

///WRITING TO THE FILE
    fprintf(f_out, "===>The words except the ones, which are equal to the last word\n--->%s\n", string_prime);

    size_t string_prime_length = strlen(string_prime);
    char string_2prime[string_prime_length + 1];
    for(int i = 0; i <= string_prime_length; ++i)
        string_2prime[i]=0;

    pch = strtok(string_prime, " ");
    while (pch != NULL)
    {
        strcat(string_2prime, reverse(pch));
        strcat(string_2prime, " ");
        pch = strtok(NULL, " ");
    }
    fprintf(f_out, "===>Reversed words\n--->%s\n", string_2prime);
    return 0;
}
