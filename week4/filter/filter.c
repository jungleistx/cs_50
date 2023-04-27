#include "../../includes/libft.h"
#include "bmp.h"

void	get_file_size(int *height, int *width, BITMAPINFOHEADER b_info);
void	get_file_info(BITMAPFILEHEADER *b_fileheader, BITMAPINFOHEADER *b_info, int original_fd);
void	get_original_fd(char *filename, int *original_fd);
void 	copy_bmp_header(int *new_fd, BITMAPFILEHEADER *b_fileheader, BITMAPINFOHEADER *b_info, int choice, char *orig_filename);
int		get_new_fd(int choice, char *orig_filename);
int		get_filter_choice(char *filename);
void	check_file_validity(BITMAPFILEHEADER bf, BITMAPINFOHEADER bi, int in_fd);
void	grayscale(int height, int width, int padding, int orig_fd, int new_fd);
void	sepia(int height, int width, int padding, int orig_fd, int new_fd);
void	reflection(int height, int width, int padding, int orig_fd, int new_fd);

int main(int argc, char **argv)
{
	BITMAPFILEHEADER	b_fileheader;
	BITMAPINFOHEADER	b_info;
	int					height;
	int					width;
	int					choice;
	int					padding;
	int					new_fd;
	int					original_fd;

	if (argc != 2)
	{
		ft_printf("Usage: %s image\n", argv[0]);
		return (1);
	}
	get_original_fd(argv[1], &original_fd);
	get_file_info(&b_fileheader, &b_info, original_fd);
	check_file_validity(b_fileheader, b_info, original_fd);
	get_file_size(&height, &width, b_info);
	choice = get_filter_choice(argv[1]);
	copy_bmp_header(&new_fd, &b_fileheader, &b_info, choice, argv[1]);

	padding = (4 - (width * sizeof(RGBTRIPLE)) % 4) % 4;
	if (choice == 1)
		grayscale(height, width, padding, original_fd, new_fd);
	else if (choice == 2)
		sepia(height, width, padding, original_fd, new_fd);
	else if (choice == 3)
		reflection(height, width, padding, original_fd, new_fd);
	// else if (choice == 4)
	// 	blur(height, width, padding, original_fd, new_fd);
	// else if (choice == 5)
	// 	edges(height, width, padding, original_fd, new_fd);

	return (0);
}

void	reflection(int height, int width, int padding, int orig_fd, int new_fd)
{
	RGBTRIPLE	new_pixel[width];
	BYTE		new_red;
	BYTE		new_green;
	BYTE		new_blue;
	int			i;
	int			j;

	i = 0;
	while (i < height)
	{
		read(orig_fd, new_pixel, sizeof(RGBTRIPLE) * width);
		j = width - 1;
		while (j >= 0)
		{
			write(new_fd, &new_pixel[j], sizeof(RGBTRIPLE));
			j--;
		}

		j = 0;
		while (j < padding)
		{
			write(new_fd, 0, 1);
			j++;
		}
		lseek(orig_fd, padding, SEEK_CUR);
		i++;
	}
}

void	sepia(int height, int width, int padding, int orig_fd, int new_fd)
{
	RGBTRIPLE	new_pixel[width];
	BYTE		new_red;
	BYTE		new_green;
	BYTE		new_blue;
	int			i;
	int			j;

	i = 0;
	while (i < height)
	{
		read(orig_fd, new_pixel, sizeof(RGBTRIPLE) * width);
		j = 0;
		while (j < width)
		{
			if ((0.393 * new_pixel[j].rgbtRed + 0.769 * new_pixel[j].rgbtGreen + 0.189 * new_pixel[j].rgbtBlue) > 255)
				new_red = 255;
			else
				new_red = (BYTE) (0.393 * new_pixel[j].rgbtRed + 0.769 * new_pixel[j].rgbtGreen + 0.189 * new_pixel[j].rgbtBlue);

			if ((0.349 * new_pixel[j].rgbtRed + 0.686 * new_pixel[j].rgbtGreen + 0.168 * new_pixel[j].rgbtBlue) > 255)
				new_green = 255;
			else
				new_green = (BYTE) (0.349 * new_pixel[j].rgbtRed + 0.686 * new_pixel[j].rgbtGreen + 0.168 * new_pixel[j].rgbtBlue);

			if ((0.272 * new_pixel[j].rgbtRed + 0.534 * new_pixel[j].rgbtGreen + 0.131 * new_pixel[j].rgbtBlue) > 255)
				new_blue = 255;
			else
				new_blue = (BYTE) (0.272 * new_pixel[j].rgbtRed + 0.534 * new_pixel[j].rgbtGreen + 0.131 * new_pixel[j].rgbtBlue);

			new_pixel[j].rgbtRed = new_red;
			new_pixel[j].rgbtGreen = new_green;
			new_pixel[j].rgbtBlue = new_blue;
			j++;
		}
		write(new_fd, new_pixel, sizeof(RGBTRIPLE) * width);
		j = 0;
		while (j < padding)
		{
			write(new_fd, 0, 1);
			j++;
		}
		lseek(orig_fd, padding, SEEK_CUR);		// skip padding in original file
		i++;
	}
}

void	grayscale(int height, int width, int padding, int orig_fd, int new_fd)
{
	RGBTRIPLE	new_pixel[width];
	BYTE		average;
	int			i;
	int			j;

	i = 0;
	while (i < height)
	{
		read(orig_fd, new_pixel, sizeof(RGBTRIPLE) * width);
		j = 0;
		while (j < width)
		{
			average = (new_pixel[j].rgbtRed + new_pixel[j].rgbtGreen + new_pixel[j].rgbtBlue) / 3;
			new_pixel[j].rgbtRed = average;
			new_pixel[j].rgbtGreen = average;
			new_pixel[j].rgbtBlue = average;
			j++;
		}
		write(new_fd, new_pixel, sizeof(RGBTRIPLE) * width);
		j = 0;
		while (j < padding)
		{
			write(new_fd, 0, 1);
			j++;
		}
		lseek(orig_fd, padding, SEEK_CUR);
		i++;
	}
}

void	check_file_validity(BITMAPFILEHEADER bf, BITMAPINFOHEADER bi, int in_fd)
{
	if (bf.bfType != 0x4d42 || bf.bfOffBits != 54 || bi.biSize != 40 || bi.biBitCount != 24
	|| bi.biCompression != 0)
	{
		close(in_fd);
		ft_printf("Unsupported file format.\n");
		exit (2);
	}
}

int	get_filter_choice(char *filename)
{
	char	*input;
	int		filter_choice;

	filter_choice = 0;
	while (filter_choice < 1 || filter_choice > 5)
	{
		ft_printf("Enter your choice of filter for \'%s\':\n", filename);
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

int	get_new_fd(int choice, char *orig_filename)
{
	int		new_fd;
	char	*filter;
	char	*filename;
	char	*orig_noext;
	size_t	orig_len;

	if (choice == 1)
		filter = "grayscale.bmp";
	else if (choice == 2)
		filter = "sepia.bmp";
	else if (choice == 3)
		filter = "reflection.bmp";
	else if (choice == 4)
		filter = "blur.bmp";
	else if (choice == 5)
		filter = "edges.bmp";

	orig_len = ft_strlen(orig_filename);
	orig_noext = ft_strsub(orig_filename, 0, orig_len - 4);		// without .bmp
	filename = ft_strjoin_three(orig_noext, "_", filter);

	new_fd = open(filename, O_WRONLY | O_CREAT, 0644);
	ft_strdel(&filename);
	ft_strdel(&orig_noext);

	if (new_fd == -1)
	{
		ft_printf("ERROR opening new file\n");
		exit(2);
	}
	else
		return (new_fd);
}

void copy_bmp_header(int *new_fd, BITMAPFILEHEADER *b_fileheader, BITMAPINFOHEADER *b_info, int choice, char *orig_filename)
{
	*new_fd = get_new_fd(choice, orig_filename);
	write(*new_fd, b_fileheader, sizeof(BITMAPFILEHEADER));
	write(*new_fd, b_info, sizeof(BITMAPINFOHEADER));
}

void	get_original_fd(char *filename, int *original_fd)
{
	*original_fd = open(filename, O_RDONLY);
	if (*original_fd == -1)
	{
		ft_printf("ERROR opening file %s\n", filename);
		exit(1);
	}
}

void	get_file_info(BITMAPFILEHEADER *b_fileheader, BITMAPINFOHEADER *b_info, int original_fd)
{
	read(original_fd, b_fileheader, sizeof(BITMAPFILEHEADER));
	read(original_fd, b_info, sizeof(BITMAPINFOHEADER));
}

void	get_file_size(int *height, int *width, BITMAPINFOHEADER b_info)
{
	*height = abs(b_info.biHeight);
	*width = b_info.biWidth;
}
