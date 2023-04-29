// Implements a dictionary's functionality

#include <ctype.h>
#include <stdbool.h>

#include "dictionary.h"
#include "../../includes/libft.h"
#include <stdio.h>

// Represents a node in a hash table
typedef struct node
{
    char word[LENGTH + 1];
    struct node *next;
}
node;

// TODO: Choose number of buckets in hash table
const unsigned int N = 26 * 26;

// Hash table
node *table[N];

// convert str to all lowercase
char    *to_lower(const char *str)
{
    int     i;
    char    *str_lower;
    size_t  len;

    str_lower = NULL;
    len = 0;

    if (str)
        len = ft_strlen(str);
    if (len > 0)
    {
        str_lower = (char *) malloc(sizeof(char) * len + 1);
        if (!str_lower)
        {
            ft_printf("Error allocating new str_lower.\n");
            exit(4);
        }
        i = 0;
        while (str[i])
        {
            if (str[i] >= 65 && str[i] <= 90)       // A-Z
                str_lower[i] = str[i] + 32;
            else
                str_lower[i] = str[i];
            i++;
        }
        str_lower[i] = '\0';
    }
    if (str_lower)
        return (str_lower);
    else
    {
        ft_printf("Error in to_lower.\n");
        exit(5);
    }
}

// Returns true if word is in dictionary, else false
bool check(const char *word)
{
    // TODO
    node            *tmp;
    char            *word_lower;
    unsigned int    hash_value;

    if (!word)
        return (false);

    word_lower = to_lower(word);
    hash_value = hash(word_lower);
    tmp = table[hash_value];
    if (tmp == NULL)            // empty hashtable
    {
        free(word_lower);
        return (false);
    }
    else
    {
        while (tmp)
        {
            if (tmp->word[0] < word_lower[0])   // gone over
            {
                free(word_lower);
                return (false);
            }
            else if (tmp->word[0] == word_lower[0])
            {
                if (ft_strequ(tmp->word, word_lower))
                {
                    free(word_lower);
                    return (true);
                }
            }
            tmp = tmp->next;
        }
    }
    free(word_lower);
    return (false);
}

// Hashes word to a number
unsigned int hash(const char *word)
{
    // TODO: Improve this hash function
    unsigned int    sum;
    int             i;

    i = -1;
    sum = word[0] * 235;

    while (word[++i])
        sum += word[i];

    return (sum % 676);
}

// Loads dictionary into memory, returning true if successful, else false
bool load(const char *dictionary)
{
    // TODO
    char    *line;
    int     fd;
    int     i;
    int     hash_value;
    node    *new;
    node    *tmp;

    fd = open(dictionary, O_RDONLY);
    if (fd == -1)
        return (false);

    i = 0;
    while (i < N)       // set all node* to NULL
    {
        table[i] = NULL;
        i++;
    }

    while (get_next_line(fd, &line) > 0)    // read and load
    {
        if (line)
        {
            new = (node *) malloc(sizeof(node));
            if (!new)
            {
                ft_printf("Error allocating new node.\n");
                exit(3);
            }
            ft_strcpy(new->word, line);
            new->next = NULL;

            hash_value = hash(line);
            tmp = table[hash_value];

            if (tmp != NULL)
                new->next = table[hash_value];      // to not lose list
            table[hash_value] = new;                // new node to front

            free(line);
        }
    }
    close(fd);
    return (true);
}

// Returns number of words in dictionary if loaded, else 0 if not yet loaded
unsigned int size(void)
{
    // TODO
    unsigned int    words;
    node            *tmp;
    int             i;

    words = 0;
    i = 0;
    while (i < N)
    {
        if (table[i])
        {
            tmp = table[i];
            while (tmp)
            {
                words++;
                tmp = tmp->next;
            }
        }
        i++;
    }
    return (words);
}

// Unloads dictionary from memory, returning true if successful, else false
bool unload(void)
{
    // TODO
    int     i;
    node    *tmp;

    i = 0;
    while (i < N)
    {
        if (table[i])
        {
            tmp = table[i];
            while (tmp)
            {
                tmp = tmp->next;
                free(table[i]);
                table[i] = tmp;
            }
        }
        i++;
    }
    return (true);
}
