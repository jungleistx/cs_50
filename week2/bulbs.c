#include "../includes/libft.h"

void	convert_to_binary(int num, int *byte);
void 	print_binary_num(int *byte);

int main(void)
{
	int		value;
	char	*input;
	size_t	len;
	int		i;

	ft_printf("Message: ");
	get_next_line(0, &input);
	len = ft_strlen(input);
	int		byte[len][8];

	i = 0;
	while (input[i])
	{
		convert_to_binary(input[i], byte[i]);
		print_binary_num(byte[i]);
		i++;
	}
	ft_strdel(&input);
}

void	convert_to_binary(int num, int *byte)
{
	int	i;

	i = 7;
	while (i >= 0)
	{
		if (num % 2 == 1)
			byte[i] = 1;
		else
			byte[i] = 0;
		num /= 2;
		i--;
	}
}

void 	print_binary_num(int *byte)
{
	int	i;

	i = 0;
	while (i < 8)
	{
		ft_printf("%d", byte[i]);
		i++;
	}
	ft_printf("\n");
}
