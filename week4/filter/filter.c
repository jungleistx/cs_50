#include "../../includes/libft.h"
#include "bmp.h"
#include <math.h>

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
void	blur(int height, int width, int padding, int orig_fd, int new_fd);
void	edges(int height, int width, int padding, int orig_fd, int new_fd);

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
	else if (choice == 4)
		blur(height, width, padding, original_fd, new_fd);
	else if (choice == 5)
		edges(height, width, padding, original_fd, new_fd);

	close(original_fd);
	close(new_fd);
	return (0);
}

void	edges(int height, int width, int padding, int orig_fd, int new_fd)
{
	RGBTRIPLE	image[height][width];
	RGBTRIPLE	new;
	int			i;
	int			j;
	int			k;
	int32_t		gx;
	int32_t		gy;

	i = 0;
	while (i < height)
	{
		read(orig_fd, image[i], sizeof(RGBTRIPLE) * width);
		lseek(orig_fd, padding, SEEK_CUR);
		i++;
	}

	i = 0;
	while (i < height)
	{
		j = 0;
		while (j < width)
		{
			if (i == 0)				// first row
			{
				if (j == 0)
				{
					gx = (2 * image[i][j + 1].rgbtRed) + (image[i + 1][j + 1].rgbtRed);
					gy = (2 * image[i + 1][j].rgbtRed) + (image[i + 1][j + 1].rgbtRed);
					if (sqrt(gx * gx + gy * gy) > 255)
						new.rgbtRed = 255;
					else
						new.rgbtRed = sqrt(gx * gx + gy * gy);

					gx = (2 * image[i][j + 1].rgbtGreen) + (image[i + 1][j + 1].rgbtGreen);
					gy = (2 * image[i + 1][j].rgbtGreen) + (image[i + 1][j + 1].rgbtGreen);
					if (sqrt(gx * gx + gy * gy) > 255)
						new.rgbtGreen = 255;
					else
						new.rgbtGreen = sqrt(gx * gx + gy * gy);

					gx = (2 * image[i][j + 1].rgbtBlue) + (image[i + 1][j + 1].rgbtBlue);
					gy = (2 * image[i + 1][j].rgbtBlue) + (image[i + 1][j + 1].rgbtBlue);
					if (sqrt(gx * gx + gy * gy) > 255)
						new.rgbtBlue = 255;
					else
						new.rgbtBlue = sqrt(gx * gx + gy * gy);
				}
				else if (j < width - 1)
				{
					gx = (-2 * image[i][j - 1].rgbtRed) + (2 * image[i][j + 1].rgbtRed) + (-1 * image[i + 1][j - 1].rgbtRed) + (image[i + 1][j + 1].rgbtRed);
					gy = (image[i + 1][j - 1].rgbtRed) + (2 * image[i + 1][j].rgbtRed) + (image[i + 1][j + 1].rgbtRed);
					if (sqrt(gx * gx + gy * gy) > 255)
						new.rgbtRed = 255;
					else
						new.rgbtRed = sqrt(gx * gx + gy * gy);

					gx = (-2 * image[i][j - 1].rgbtGreen) + (2 * image[i][j + 1].rgbtGreen) + (-1 * image[i + 1][j - 1].rgbtGreen) + (image[i + 1][j + 1].rgbtGreen);
					gy = (image[i + 1][j - 1].rgbtGreen) + (2 * image[i + 1][j].rgbtGreen) + (image[i + 1][j + 1].rgbtGreen);
					if (sqrt(gx * gx + gy * gy) > 255)
						new.rgbtGreen = 255;
					else
						new.rgbtGreen = sqrt(gx * gx + gy * gy);

					gx = (-2 * image[i][j - 1].rgbtBlue) + (2 * image[i][j + 1].rgbtBlue) + (-1 * image[i + 1][j - 1].rgbtBlue) + (image[i + 1][j + 1].rgbtBlue);
					gy = (image[i + 1][j - 1].rgbtBlue) + (2 * image[i + 1][j].rgbtBlue) + (image[i + 1][j + 1].rgbtBlue);
					if (sqrt(gx * gx + gy * gy) > 255)
						new.rgbtBlue = 255;
					else
						new.rgbtBlue = sqrt(gx * gx + gy * gy);
				}
				else
				{
					gx = (-2 * image[i][j - 1].rgbtRed) + (-1 * image[i + 1][j - 1].rgbtRed);
					gy = (image[i + 1][j - 1].rgbtRed) + (2 * image[i + 1][j].rgbtRed);
					if (sqrt(gx * gx + gy * gy) > 255)
						new.rgbtRed = 255;
					else
						new.rgbtRed = sqrt(gx * gx + gy * gy);

					gx = (-2 * image[i][j - 1].rgbtGreen) + (-1 * image[i + 1][j - 1].rgbtGreen);
					gy = (image[i + 1][j - 1].rgbtGreen) + (2 * image[i + 1][j].rgbtGreen);
					if (sqrt(gx * gx + gy * gy) > 255)
						new.rgbtGreen = 255;
					else
						new.rgbtGreen = sqrt(gx * gx + gy * gy);

					gx = (-2 * image[i][j - 1].rgbtBlue) + (-1 * image[i + 1][j - 1].rgbtBlue);
					gy = (image[i + 1][j - 1].rgbtBlue) + (2 * image[i + 1][j].rgbtBlue);
					if (sqrt(gx * gx + gy * gy) > 255)
						new.rgbtBlue = 255;
					else
						new.rgbtBlue = sqrt(gx * gx + gy * gy);
				}
			}
			else if (i < height - 1)	// mid rows
			{
				if (j == 0)
				{
					gx = (image[i - 1][j + 1].rgbtRed) + (2 * image[i][j + 1].rgbtRed) + (image[i + 1][j + 1].rgbtRed);
					gy = (-2 * image[i - 1][j].rgbtRed) + (-1 * image[i - 1][j + 1].rgbtRed) + (2 * image[i + 1][j].rgbtRed) + (image[i + 1][j + 1].rgbtRed);
					if (sqrt(gx * gx + gy * gy) > 255)
						new.rgbtRed = 255;
					else
						new.rgbtRed = sqrt(gx * gx + gy * gy);

					gx = (image[i - 1][j + 1].rgbtGreen) + (2 * image[i][j + 1].rgbtGreen) + (image[i + 1][j + 1].rgbtGreen);
					gy = (-2 * image[i - 1][j].rgbtGreen) + (-1 * image[i - 1][j + 1].rgbtGreen) + (2 * image[i + 1][j].rgbtGreen) + (image[i + 1][j + 1].rgbtGreen);
					if (sqrt(gx * gx + gy * gy) > 255)
						new.rgbtGreen = 255;
					else
						new.rgbtGreen = sqrt(gx * gx + gy * gy);

					gx = (image[i - 1][j + 1].rgbtBlue) + (2 * image[i][j + 1].rgbtBlue) + (image[i + 1][j + 1].rgbtBlue);
					gy = (-2 * image[i - 1][j].rgbtBlue) + (-1 * image[i - 1][j + 1].rgbtBlue) + (2 * image[i + 1][j].rgbtBlue) + (image[i + 1][j + 1].rgbtBlue);
					if (sqrt(gx * gx + gy * gy) > 255)
						new.rgbtBlue = 255;
					else
						new.rgbtBlue = sqrt(gx * gx + gy * gy);
				}
				else if (j < width - 1)
				{
					gx = (-1 * image[i - 1][j - 1].rgbtRed) + (image[i - 1][j + 1].rgbtRed) + (-2 * image[i][j - 1].rgbtRed) + (2 * image[i][j + 1].rgbtRed) + (-1 * image[i + 1][j - 1].rgbtRed) + (image[i + 1][j + 1].rgbtRed);
					gy = (-1 * image[i - 1][j - 1].rgbtRed) + (-2 * image[i - 1][j].rgbtRed) + (-1 * image[i - 1][j + 1].rgbtRed) + (image[i + 1][j - 1].rgbtRed) + (2 * image[i + 1][j].rgbtRed) + (image[i + 1][j + 1].rgbtRed);
					if (sqrt(gx * gx + gy * gy) > 255)
						new.rgbtRed = 255;
					else
						new.rgbtRed = sqrt(gx * gx + gy * gy);

					gx = (-1 * image[i - 1][j - 1].rgbtGreen) + (image[i - 1][j + 1].rgbtGreen) + (-2 * image[i][j - 1].rgbtGreen) + (2 * image[i][j + 1].rgbtGreen) + (-1 * image[i + 1][j - 1].rgbtGreen) + (image[i + 1][j + 1].rgbtGreen);
					gy = (-1 * image[i - 1][j - 1].rgbtGreen) + (-2 * image[i - 1][j].rgbtGreen) + (-1 * image[i - 1][j + 1].rgbtGreen) + (image[i + 1][j - 1].rgbtGreen) + (2 * image[i + 1][j].rgbtGreen) + (image[i + 1][j + 1].rgbtGreen);
					if (sqrt(gx * gx + gy * gy) > 255)
						new.rgbtGreen = 255;
					else
						new.rgbtGreen = sqrt(gx * gx + gy * gy);

					gx = (-1 * image[i - 1][j - 1].rgbtBlue) + (image[i - 1][j + 1].rgbtBlue) + (-2 * image[i][j - 1].rgbtBlue) + (2 * image[i][j + 1].rgbtBlue) + (-1 * image[i + 1][j - 1].rgbtBlue) + (image[i + 1][j + 1].rgbtBlue);
					gy = (-1 * image[i - 1][j - 1].rgbtBlue) + (-2 * image[i - 1][j].rgbtBlue) + (-1 * image[i - 1][j + 1].rgbtBlue) + (image[i + 1][j - 1].rgbtBlue) + (2 * image[i + 1][j].rgbtBlue) + (image[i + 1][j + 1].rgbtBlue);
					if (sqrt(gx * gx + gy * gy) > 255)
						new.rgbtBlue = 255;
					else
						new.rgbtBlue = sqrt(gx * gx + gy * gy);
				}
				else
				{
					gx = (-1 * image[i - 1][j - 1].rgbtRed) + (-2 * image[i][j - 1].rgbtRed) + (-1 * image[i + 1][j - 1].rgbtRed);
					gy = (-1 * image[i - 1][j - 1].rgbtRed) + (-2 * image[i - 1][j].rgbtRed) + (image[i + 1][j - 1].rgbtRed) + (2 * image[i + 1][j].rgbtRed);
					if (sqrt(gx * gx + gy * gy) > 255)
						new.rgbtRed = 255;
					else
						new.rgbtRed = sqrt(gx * gx + gy * gy);

					gx = (-1 * image[i - 1][j - 1].rgbtGreen) + (-2 * image[i][j - 1].rgbtGreen) + (-1 * image[i + 1][j - 1].rgbtGreen);
					gy = (-1 * image[i - 1][j - 1].rgbtGreen) + (-2 * image[i - 1][j].rgbtGreen) + (image[i + 1][j - 1].rgbtGreen) + (2 * image[i + 1][j].rgbtGreen);
					if (sqrt(gx * gx + gy * gy) > 255)
						new.rgbtGreen = 255;
					else
						new.rgbtGreen = sqrt(gx * gx + gy * gy);

					gx = (-1 * image[i - 1][j - 1].rgbtBlue) + (-2 * image[i][j - 1].rgbtBlue) + (-1 * image[i + 1][j - 1].rgbtBlue);
					gy = (-1 * image[i - 1][j - 1].rgbtBlue) + (-2 * image[i - 1][j].rgbtBlue) + (image[i + 1][j - 1].rgbtBlue) + (2 * image[i + 1][j].rgbtBlue);
					if (sqrt(gx * gx + gy * gy) > 255)
						new.rgbtBlue = 255;
					else
						new.rgbtBlue = sqrt(gx * gx + gy * gy);
				}
			}
			else 					// last row
			{
				if (j == 0)
				{
					gx = (image[i - 1][j + 1].rgbtRed) + (2 * image[i][j + 1].rgbtRed);
					gy = (-1 * image[i - 1][j + 1].rgbtRed) + (-2 * image[i - 1][j].rgbtRed);
					if (sqrt(gx * gx + gy * gy) > 255)
						new.rgbtRed = 255;
					else
						new.rgbtRed = sqrt(gx * gx + gy * gy);

					gx = (image[i - 1][j + 1].rgbtGreen) + (2 * image[i][j + 1].rgbtGreen);
					gy = (-1 * image[i - 1][j + 1].rgbtGreen) + (-2 * image[i - 1][j].rgbtGreen);
					if (sqrt(gx * gx + gy * gy) > 255)
						new.rgbtGreen = 255;
					else
						new.rgbtGreen = sqrt(gx * gx + gy * gy);

					gx = (image[i - 1][j + 1].rgbtBlue) + (2 * image[i][j + 1].rgbtBlue);
					gy = (-1 * image[i - 1][j + 1].rgbtBlue) + (-2 * image[i - 1][j].rgbtBlue);
					if (sqrt(gx * gx + gy * gy) > 255)
						new.rgbtBlue = 255;
					else
						new.rgbtBlue = sqrt(gx * gx + gy * gy);
				}
				else if (j < width - 1)
				{
					gx = (-1 * image[i - 1][j - 1].rgbtRed) + (image[i - 1][j + 1].rgbtRed) + (-2 * image[i][j - 1].rgbtRed) + (2 * image[i][j + 1].rgbtRed);
					gy = (-1 * image[i - 1][j - 1].rgbtRed) + (-2 * image[i - 1][j].rgbtRed) + (-1 * image[i - 1][j + 1].rgbtRed);
					if (sqrt(gx * gx + gy * gy) > 255)
						new.rgbtRed = 255;
					else
						new.rgbtRed = sqrt(gx * gx + gy * gy);

					gx = (-1 * image[i - 1][j - 1].rgbtGreen) + (image[i - 1][j + 1].rgbtGreen) + (-2 * image[i][j - 1].rgbtGreen) + (2 * image[i][j + 1].rgbtGreen);
					gy = (-1 * image[i - 1][j - 1].rgbtGreen) + (-2 * image[i - 1][j].rgbtGreen) + (-1 * image[i - 1][j + 1].rgbtGreen);
					if (sqrt(gx * gx + gy * gy) > 255)
						new.rgbtGreen = 255;
					else
						new.rgbtGreen = sqrt(gx * gx + gy * gy);

					gx = (-1 * image[i - 1][j - 1].rgbtBlue) + (image[i - 1][j + 1].rgbtBlue) + (-2 * image[i][j - 1].rgbtBlue) + (2 * image[i][j + 1].rgbtBlue);
					gy = (-1 * image[i - 1][j - 1].rgbtBlue) + (-2 * image[i - 1][j].rgbtBlue) + (-1 * image[i - 1][j + 1].rgbtBlue);
					if (sqrt(gx * gx + gy * gy) > 255)
						new.rgbtBlue = 255;
					else
						new.rgbtBlue = sqrt(gx * gx + gy * gy);
				}
				else
				{
					gx = (-1 * image[i - 1][j - 1].rgbtRed) + (-2 * image[i][j - 1].rgbtRed);
					gy = (-1 * image[i - 1][j - 1].rgbtRed) + (-2 * image[i - 1][j].rgbtRed);
					if (sqrt(gx * gx + gy * gy) > 255)
						new.rgbtRed = 255;
					else
						new.rgbtRed = sqrt(gx * gx + gy * gy);

					gx = (-1 * image[i - 1][j - 1].rgbtGreen) + (-2 * image[i][j - 1].rgbtGreen);
					gy = (-1 * image[i - 1][j - 1].rgbtGreen) + (-2 * image[i - 1][j].rgbtGreen);
					if (sqrt(gx * gx + gy * gy) > 255)
						new.rgbtGreen = 255;
					else
						new.rgbtGreen = sqrt(gx * gx + gy * gy);

					gx = (-1 * image[i - 1][j - 1].rgbtBlue) + (-2 * image[i][j - 1].rgbtBlue);
					gy = (-1 * image[i - 1][j - 1].rgbtBlue) + (-2 * image[i - 1][j].rgbtBlue);
					if (sqrt(gx * gx + gy * gy) > 255)
						new.rgbtBlue = 255;
					else
						new.rgbtBlue = sqrt(gx * gx + gy * gy);
				}
			}
			write(new_fd, &new, sizeof(RGBTRIPLE));
			j++;
		}
		k = 0;
		while (k < padding)
		{
			write(new_fd, 0, 1);
			k++;
		}
		i++;
	}
}

void	blur(int height, int width, int padding, int orig_fd, int new_fd)
{
	RGBTRIPLE	image[height][width];
	RGBTRIPLE	new;
	int			i;
	int			j;
	int			k;

	i = 0;
	while (i < height)
	{
		read(orig_fd, image[i], sizeof(RGBTRIPLE) * width);
		lseek(orig_fd, padding, SEEK_CUR);
		i++;
	}

	i = 0;
	while (i < height)
	{
		j = 0;
		while (j < width)
		{
			if (i == 0)				// first row
			{
				if (j == 0)
				{
					new.rgbtRed = (image[i][j].rgbtRed + image[i][j + 1].rgbtRed + image[i + 1][j].rgbtRed + image[i + 1][j + 1].rgbtRed) / 4;
					new.rgbtGreen = (image[i][j].rgbtGreen + image[i][j + 1].rgbtGreen + image[i + 1][j].rgbtGreen + image[i + 1][j + 1].rgbtGreen) / 4;
					new.rgbtBlue = (image[i][j].rgbtBlue + image[i][j + 1].rgbtBlue + image[i + 1][j].rgbtBlue + image[i + 1][j + 1].rgbtBlue) / 4;
				}
				else if (j < width - 1)
				{
					new.rgbtRed = (image[i][j - 1].rgbtRed + image[i][j].rgbtRed + image[i][j + 1].rgbtRed + image[i + 1][j - 1].rgbtRed + image[i + 1][j].rgbtRed + image[i + 1][j + 1].rgbtRed) / 6;
					new.rgbtGreen = (image[i][j - 1].rgbtGreen + image[i][j].rgbtGreen + image[i][j + 1].rgbtGreen + image[i + 1][j - 1].rgbtGreen + image[i + 1][j].rgbtGreen + image[i + 1][j + 1].rgbtGreen) / 6;
					new.rgbtBlue = (image[i][j - 1].rgbtBlue + image[i][j].rgbtBlue + image[i][j + 1].rgbtBlue + image[i + 1][j - 1].rgbtBlue + image[i + 1][j].rgbtBlue + image[i + 1][j + 1].rgbtBlue) / 6;
				}
				else
				{
					new.rgbtRed = (image[i][j - 1].rgbtRed + image[i][j].rgbtRed + image[i + 1][j - 1].rgbtRed + 	image[i + 1][j].rgbtRed) / 4;
					new.rgbtGreen = (image[i][j - 1].rgbtGreen + image[i][j].rgbtGreen + image[i + 1][j - 1].rgbtGreen + 	image[i + 1][j].rgbtGreen) / 4;
					new.rgbtBlue = (image[i][j - 1].rgbtBlue + image[i][j].rgbtBlue + image[i + 1][j - 1].rgbtBlue + 	image[i + 1][j].rgbtBlue) / 4;
				}
			}
			else if (i < height - 1)	// mid rows
			{
				if (j == 0)
				{
					new.rgbtRed = (image[i - 1][j].rgbtRed + image[i - 1][j + 1].rgbtRed + image[i][j].rgbtRed + image[i][j + 1].rgbtRed + image[i + 1][j].rgbtRed + image[i + 1][j + 1].rgbtRed) / 6;
					new.rgbtGreen = (image[i - 1][j].rgbtGreen + image[i - 1][j + 1].rgbtGreen + image[i][j].rgbtGreen + image[i][j + 1].rgbtGreen + image[i + 1][j].rgbtGreen + image[i + 1][j + 1].rgbtGreen) / 6;
					new.rgbtBlue = (image[i - 1][j].rgbtBlue + image[i - 1][j + 1].rgbtBlue + image[i][j].rgbtBlue + image[i][j + 1].rgbtBlue + image[i + 1][j].rgbtBlue + image[i + 1][j + 1].rgbtBlue) / 6;

				}
				else if (j < width - 1)
				{
					new.rgbtRed = (image[i - 1][j - 1].rgbtRed + image[i - 1][j].rgbtRed + image[i - 1][j + 1].rgbtRed + image[i][j - 1].rgbtRed + image[i][j].rgbtRed + image[i][j + 1].rgbtRed + image[i + 1][j - 1].rgbtRed + image[i + 1][j].rgbtRed + image[i + 1][j + 1].rgbtRed) / 9;
					new.rgbtGreen = (image[i - 1][j - 1].rgbtGreen + image[i - 1][j].rgbtGreen + image[i - 1][j + 1].rgbtGreen + image[i][j - 1].rgbtGreen + image[i][j].rgbtGreen + image[i][j + 1].rgbtGreen + image[i + 1][j - 1].rgbtGreen + image[i + 1][j].rgbtGreen + image[i + 1][j + 1].rgbtGreen) / 9;
					new.rgbtBlue = (image[i - 1][j - 1].rgbtBlue + image[i - 1][j].rgbtBlue + image[i - 1][j + 1].rgbtBlue + image[i][j - 1].rgbtBlue + image[i][j].rgbtBlue + image[i][j + 1].rgbtBlue + image[i + 1][j - 1].rgbtBlue + image[i + 1][j].rgbtBlue + image[i + 1][j + 1].rgbtBlue) / 9;
				}
				else
				{
					new.rgbtRed = (image[i - 1][j - 1].rgbtRed + image[i - 1][j].rgbtRed + image[i][j - 1].rgbtRed + image[i][j].rgbtRed + image[i + 1][j - 1].rgbtRed + image[i + 1][j].rgbtRed) / 6;
					new.rgbtGreen = (image[i - 1][j - 1].rgbtGreen + image[i - 1][j].rgbtGreen + image[i][j - 1].rgbtGreen + image[i][j].rgbtGreen + image[i + 1][j - 1].rgbtGreen + image[i + 1][j].rgbtGreen) / 6;
					new.rgbtBlue = (image[i - 1][j - 1].rgbtBlue + image[i - 1][j].rgbtBlue + image[i][j - 1].rgbtBlue + image[i][j].rgbtBlue + image[i + 1][j - 1].rgbtBlue + image[i + 1][j].rgbtBlue) / 6;
				}
			}
			else 					// last row
			{
				if (j == 0)
				{
					new.rgbtRed = (image[i - 1][j].rgbtRed + image[i - 1][j + 1].rgbtRed + image[i][j].rgbtRed + image[i][j + 1].rgbtRed) / 4;
					new.rgbtGreen = (image[i - 1][j].rgbtGreen + image[i - 1][j + 1].rgbtGreen + image[i][j].rgbtGreen + image[i][j + 1].rgbtGreen) / 4;
					new.rgbtBlue = (image[i - 1][j].rgbtBlue + image[i - 1][j + 1].rgbtBlue + image[i][j].rgbtBlue + image[i][j + 1].rgbtBlue) / 4;
				}
				else if (j < width - 1)
				{
					new.rgbtRed = (image[i - 1][j - 1].rgbtRed + image[i - 1][j].rgbtRed + image[i - 1][j + 1].rgbtRed + image[i][j - 1].rgbtRed + image[i][j].rgbtRed + image[i][j + 1].rgbtRed) / 6;
					new.rgbtGreen = (image[i - 1][j - 1].rgbtGreen + image[i - 1][j].rgbtGreen + image[i - 1][j + 1].rgbtGreen + image[i][j - 1].rgbtGreen + image[i][j].rgbtGreen + image[i][j + 1].rgbtGreen) / 6;
					new.rgbtBlue = (image[i - 1][j - 1].rgbtBlue + image[i - 1][j].rgbtBlue + image[i - 1][j + 1].rgbtBlue + image[i][j - 1].rgbtBlue + image[i][j].rgbtBlue + image[i][j + 1].rgbtBlue) / 6;
				}
				else
				{
					new.rgbtRed = (image[i - 1][j - 1].rgbtRed + image[i - 1][j].rgbtRed + image[i][j - 1].rgbtRed + image[i][j].rgbtRed) / 4;
					new.rgbtGreen = (image[i - 1][j - 1].rgbtGreen + image[i - 1][j].rgbtGreen + image[i][j - 1].rgbtGreen + image[i][j].rgbtGreen) / 4;
					new.rgbtBlue = (image[i - 1][j - 1].rgbtBlue + image[i - 1][j].rgbtBlue + image[i][j - 1].rgbtBlue + image[i][j].rgbtBlue) / 4;
				}
			}
			write(new_fd, &new, sizeof(RGBTRIPLE));
			j++;
		}
		k = 0;
		while (k < padding)
		{
			write(new_fd, 0, 1);
			k++;
		}
		i++;
	}
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
