#include "../../includes/libft.h"

int		get_filter_choice(void);
int		get_new_filefd(int filter_choice);

int	main(int argc, char **argv)
{
	int		filter_choice;
	int		original_bmp_fd;

	if (argc != 2)
	{
		ft_printf("Usage: %s image\n", argv[0]);
		return (1);
	}

	original_bmp_fd = open(argv[1], O_RDONLY);
	if (original_bmp_fd == -1)
	{
		ft_printf("ERROR opening file %s\n", argv[1]);
		exit(1);
	}

	filter_choice = get_filter_choice();
}

int	get_new_filefd(int filter_choice)
{
	char	*filename;
	int		new_fd;

	new_fd = -1;
	if (filter_choice == 1)
		filename = "grayscale.bmp";
	else if (filter_choice == 2)
		filename = "sepia.bmp";
	else if (filter_choice == 3)
		filename = "reflection.bmp";
	else if (filter_choice == 4)
		filename = "blur.bmp";
	else if (filter_choice == 5)
		filename = "edges.bmp";

	new_fd = open(filename, O_WRONLY | O_CREAT, 0644);
	if (new_fd != -1)			// return valid file_fd
		return (new_fd);
	else
	{
		ft_printf("ERROR opening new file\n");
		exit(2);
	}
}

int	get_filter_choice(void)
{
	char	*input;
	int		filter_choice;

	filter_choice = 0;
	while (filter_choice < 1 || filter_choice > 5)
	{
		ft_printf("Enter your choice of filter:\n");
		ft_printf("\t1: Grayscale\n");
		ft_printf("\t2: Sepia\n");
		ft_printf("\t3: Reflection\n");
		ft_printf("\t4: Blur\n");
		ft_printf("\t5: Edges\n");

		get_next_line(0, &input);
		if (input)
		{
			filter_choice = ft_atoi(input);
			ft_strdel(&input);
		}
	}
	return (filter_choice);
}
