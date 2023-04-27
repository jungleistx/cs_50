#include <stdio.h>
#include <stdlib.h>
#include "../../includes/libft.h"

int main(int argc, char *argv[])
{
	int		fd;
	int		new_fd;
	int		image_nr;
	int		bytes_read;
	char	*image_str;
	char	*filename;
	unsigned char	buffer[512];

	if (argc != 2)
	{
		ft_printf("Usage: %s IMAGE\n", argv[0]);
		return (1);
	}
	fd = open(argv[1], O_RDONLY);
	if (fd == -1)
	{
		ft_printf("File \'%s\' cannot be opened.\n", argv[1]);
		return (2);
	}

	while (1)
	{
		read(fd, buffer, 512);
		if (buffer[0] == 0xff && buffer[1] == 0xd8 && buffer[2] == 0xff && (buffer[3] & 0xf0) == 0xe0)		// first jpg
		{
			image_nr = 0;
			image_str = ft_strdup("000.jpg");
			new_fd = open(image_str, O_WRONLY | O_CREAT, 0644);
			if (new_fd == -1)
			{
				ft_printf("ERROR opening %s.\n", image_str);
				return (2);
			}
			ft_strdel(&image_str);
			write(new_fd, buffer, 512);

			while (read(fd, buffer, 512) > 0)
			{
				if (buffer[0] == 0xff && buffer[1] == 0xd8 && buffer[2] == 0xff && (buffer[3] & 0xf0) == 0xe0)	 // new file
				{
					close(new_fd);
					image_nr++;
					image_str = ft_itoa(image_nr);
					if (image_nr < 10)
						filename = ft_strjoin_three("00", image_str, ".jpg");
					else
						filename = ft_strjoin_three("0", image_str, ".jpg");

					new_fd = open(filename, O_WRONLY | O_CREAT, 0644);
					if (new_fd == -1)
					{
						ft_printf("ERROR opening %s.\n", filename);
						return (3);
					}
					ft_strdel(&image_str);
					ft_strdel(&filename);
				}
				write(new_fd, buffer, 512);
			}
			break ;
		}
	}

	close(new_fd);
	close(fd);
	return (0);
}
