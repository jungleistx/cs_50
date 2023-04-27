#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include "wav.h"
#include "../../includes/libft.h"

int check_format(WAVHEADER header);
int get_block_size(WAVHEADER header);

int main(int argc, char *argv[])
{
    int         input_fd;
    int         output_fd;
    WAVHEADER   header;

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
    read(input_fd, &header, sizeof(WAVHEADER));

    // Use check_format to ensure WAV format
    // TODO #4
    if (!check_format(header))
    {
        ft_printf("Input is not a WAV file.\n");
        return (3);
    }

    // Open output file for writing
    // TODO #5
    output_fd = open(argv[2], O_WRONLY | O_CREAT, 0644);
    if (output_fd == -1)
    {
        close(input_fd);
        ft_printf("Error opening %s.\n", argv[2]);
        return (4);
    }

    // Write header to file
    // TODO #6
    write(output_fd, &header, sizeof(WAVHEADER));

    // Use get_block_size to calculate size of block
    // TODO #7

    // Write reversed audio to file
    // TODO #8
}

int check_format(WAVHEADER header)
{
    // TODO #4
    if (header.format[0] == 'W' &&
    header.format[1] == 'A' &&
    header.format[2] == 'V' &&
    header.format[3] == 'E')
        return (1);
    return 0;
}

int get_block_size(WAVHEADER header)
{
    // TODO #7
    return 0;
}