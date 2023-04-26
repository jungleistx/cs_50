#include "../../includes/libft.h"
#include "bmp.h"

#define R 0
#define G 1
#define B 2

typedef void	(*func_pointer) (int original_fd, int new_fd);

int		get_filter_choice(void);
int		get_new_filefd(int filter_choice);
void	copy_bmp_header(int original_bmp, int new_bmp);
void	filter(int original_fd, int filter_choice);
void	get_file_info(BITMAPFILEHEADER *b_fileheader, BITMAPINFOHEADER *b_info, int original_fd);
void	check_file_validity(BITMAPFILEHEADER bf, BITMAPINFOHEADER bi, int in_fd);
void	get_file_size(int *height, int width, BITMAPINFOHEADER b_info);

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
	int					filter_choice;
	int					original_bmp_fd;
	BITMAPFILEHEADER	b_fileheader;
	BITMAPINFOHEADER	b_info;
	int					height;
	int					width;
	RGBTRIPLE			**image;

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

	get_file_info(&b_fileheader, &b_info, original_bmp_fd);
	check_file_validity(b_fileheader, b_info, original_bmp_fd);
	get_file_size(&height, &width, b_info);
	filter_choice = get_filter_choice();

	allocate_new_image(image, height, width);

	filter(original_bmp_fd, filter_choice);
}

void	allocage_new_image(RGBTRIPLE **image, int height, int width)
{
	int	i;

	image = (RGBTRIPLE**) malloc(sizeof(RGBTRIPLE*) * height);
	if (!image)
	{
		ft_printf("ERROR malloc RGB** in new image.\n");
		exit(3);
	}

	i = 0;
	while (i < height)
	{
		image[i] = (RGBTRIPLE*) malloc(sizeof(RGBTRIPLE) * width);
		if (!(image[i]))
		{
			ft_printf("ERROR malloc RGB* in new image.\n");
			exit(4);
		}
		i++;
	}
}

void	free_new_image(RGBTRIPLE **image, int height)
{
	int	i;

	i = 0;
	while (i < height)
	{
		free(image[i]);
		i++;
	}
	free(image);
}

void	get_file_size(int *height, int width, BITMAPINFOHEADER b_info)
{
	*height = abs(b_info.biHeight);
	*width = b_info.biWidth;
}

void	check_file_validity(BITMAPFILEHEADER bf, BITMAPINFOHEADER bi, int in_fd)
{
	if (bf.bfType != 0x4d42 || bf.bfOffBits != 54 || bi.biSize != 40 ||
		bi.biBitCount != 24 || bi.biCompression != 0)
	{
		close(in_fd);
		ft_printf("Unsupported file format.\n");
		exit (2);
	}
}

void	get_file_info(BITMAPFILEHEADER *b_fileheader, BITMAPINFOHEADER *b_info, int original_fd)
{
	read(original_fd, b_fileheader, sizeof(BITMAPFILEHEADER));
	read(original_fd, b_info, sizeof(BITMAPINFOHEADER));
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

// void	grayscale(int original_fd, int new_fd)
// {
// 	int8_t	pixel[3];
// 	int8_t	average;

// 	while (read(original_fd, pixel, 24) > 0)
// 	{
// 		average = (int8_t)((pixel[R] + pixel[G] + pixel[B]) / 3);
// 		pixel[R] = average;
// 		pixel[G] = average;
// 		pixel[B] = average;
// 		write(new_fd, pixel, 24);
// 	}
// }

// void	sepia(int original_fd, int new_fd)
// {
// 	(void)original_fd;
// 	(void)new_fd;
// }
// void	reflection(int original_fd, int new_fd)
// {
// 	(void)original_fd;
// 	(void)new_fd;
// }
// void	blur(int original_fd, int new_fd)
// {
// 	(void)original_fd;
// 	(void)new_fd;
// }
// void	edges(int original_fd, int new_fd)
// {
// 	(void)original_fd;
// 	(void)new_fd;
// }