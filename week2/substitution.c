#include "../includes/libft.h"

void	print_cipher(char *str, char *key);
int		find_pos(char c);

int main(int argc, char **argv)
{
	char	*input;

	if (argc != 2)
	{
		ft_printf("Usage: %s key\n", argv[0]);
		return (1);
	}
	else if (ft_strlen(argv[1]) != 26)
	{
		ft_printf("Key must contain 26 characters.\n");
		return (1);
	}

	ft_printf("plaintext:  ");
	get_next_line(0, &input);

	ft_printf("ciphertext: ");
	print_cipher(input, argv[1]);

	ft_strdel(&input);
}

void	print_cipher(char *str, char *key)
{
	int		i;
	char	new;
	int		pos;

	i = 0;
	while (str[i])
	{
		if (ft_isalpha(str[i]))	// a-z or A-Z
		{
			pos = find_pos(str[i]);
			new = key[pos];
			if (str[i] >= 65 && str[i] <= 90)		// A-Z
				ft_printf("%c", ft_toupper(new));
			else
				ft_printf("%c", ft_tolower(new)); 	// a-z
		}
		else
			ft_printf("%c", str[i]);
		i++;
	}
	ft_printf("\n");
}

int	find_pos(char c)	// index in letters, a = 0...
{
	if (c >= 65 && c <= 90)
		return (c - 'A');
	else
		return (c - 'a');
}
