#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include "wav.h"
#include "../../includes/libft.h"

int check_format(WAVHEADER header);
int get_block_size(WAVHEADER header);

int main(int argc, char *argv[])
{
    int input_fd;

    // Ensure proper usage
    // TODO #1
    if (argc != 3)
    {
        ft_printf("Usage: %s input.wav output.wav\n", argv[0]);
        return (1);
    }

    // Open input file for reading
    // TODO #2
    input_fd = open(argv[1], O_RDONLY);
    if (input_fd == -1)
    {
        ft_printf("Error opening \'%s\'.\n", argv[1]);
        return (2);
    }

    // Read header
    // TODO #3

    // Use check_format to ensure WAV format
    // TODO #4

    // Open output file for writing
    // TODO #5

    // Write header to file
    // TODO #6

    // Use get_block_size to calculate size of block
    // TODO #7

    // Write reversed audio to file
    // TODO #8
}

int check_format(WAVHEADER header)
{
    // TODO #4
    return 0;
}

int get_block_size(WAVHEADER header)
{
    // TODO #7
    return 0;
}