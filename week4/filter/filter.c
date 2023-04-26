#include "../../includes/libft.h"

int		get_filter_choice(void);

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
