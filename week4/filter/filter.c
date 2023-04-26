#include "../../includes/libft.h"

typedef void	(*func_pointer) (int original_fd, int new_fd);

int		get_filter_choice(void);
int		get_new_filefd(int filter_choice);
void	copy_bmp_header(int original_bmp, int new_bmp);
void	filter(int original_fd, int filter_choice);

void	grayscale(int original_fd, int new_fd);
void	sepia(int original_fd, int new_fd);
void	reflection(int original_fd, int new_fd);
void	blur(int original_fd, int new_fd);
void	edges(int original_fd, int new_fd);

static const func_pointer	dispatch_table[5] = {
	grayscale,
	sepia,
	reflection,
	blur,
	edges
};

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
	filter(original_bmp_fd, filter_choice);
}

void	filter(int original_fd, int filter_choice)
{
	int	new_fd;

	new_fd = get_new_filefd(filter_choice);
	copy_bmp_header(original_fd, new_fd);

	dispatch_table[filter_choice - 1](original_fd, new_fd);	// call the correct filter
}

void	copy_bmp_header(int original_bmp, int new_bmp)
{
	char	buffer[54];		// sizeof 24-bit bmp header

	read(original_bmp, buffer, 54);
	write(new_bmp, buffer, 54);
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
