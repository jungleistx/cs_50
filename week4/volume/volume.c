// Modifies the volume of an audio file

#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <unistd.h>
#include "../../includes/libft.h"

// Number of bytes in .wav header
const int HEADER_SIZE = 44;

int main(int argc, char *argv[])
{
    // Check command-line arguments
    if (argc != 4)
    {
        ft_printf("Usage: ./volume input.wav output.wav factor\n");
        return 1;
    }

    // Open files and determine scaling factor
    int input_fd = open(argv[1], O_RDONLY);
    if (input_fd == -1)
    {
        ft_printf("Could not open file.\n");
        return 1;
    }

    int output_fd = open(argv[2], O_WRONLY | O_CREAT, 0644);
    if (output_fd == -1)
    {
       ft_printf("Could not open file.\n");
        return 1;
    }

    float factor = atof(argv[3]);

    // TODO: Copy header from input file to output file
    uint8_t buf[HEADER_SIZE];

    read(input_fd, buf, HEADER_SIZE);
    write(output_fd, buf, HEADER_SIZE);

    // TODO: Read samples from input file and write updated data to output file
    int16_t sample;

    while (read(input_fd, &sample, 2) > 0)
    {
        if ((sample * factor) > 32767) // over max int
            sample = 32767;
        else if ((sample * factor) < -32768)   // under min int
            sample = -32768;
        else
            sample = (int16_t)(sample * factor);

        write(output_fd, &sample, 2);
    }

    // Close files
    close(input_fd);
    close(output_fd);
}
