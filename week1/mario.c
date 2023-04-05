#include "../includes/libft.h"

int main(void)
{
	char	*input;
	int		height;
	int		level;
	int		tmp;

	height = 0;
	while (height < 1 || height > 8)
	{
		ft_printf("Height: ");
		get_next_line(0, &input);
		height = ft_atoi(input);
		ft_strdel(&input);
	}

	level = 1;
	while (level <= height)
	{
		tmp = height - level;
		while (tmp > 0)
		{
			ft_printf(" ");
			tmp--;
		}
		tmp = level;
		while (tmp > 0)
		{
			ft_printf("#");
			tmp--;
		}

		ft_printf("  ");

		tmp = level;
		while (tmp > 0)
		{
			ft_printf("#");
			tmp--;
		}
		ft_printf("\n");
		level++;
	}
	return (0);
}
