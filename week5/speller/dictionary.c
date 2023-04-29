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

// Returns true if word is in dictionary, else false
bool check(const char *word)
{
    // TODO
    return false;
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
            new->word = ft_strdup(line);
            new->next = NULL;

            hash_value = hash(line);
            tmp = table[hash_value];

            if (tmp == NULL)
                table[hash_value] = new;
            else
            {
                while (tmp->next)
                    tmp = tmp->next;
                tmp->next = new;
            }
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
    return false;
}
