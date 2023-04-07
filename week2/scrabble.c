#include "../includes/libft.h"

int	count_total(char *str, int *letters);

int main(void)
{
	int		letters[] = {1, 3, 3, 2, 1, 4, 2, 4, 1, 8, 5, 1, 3, 1, 1, 3, 10, 1, 1, 1, 1, 4, 4, 8, 4, 10};
	char	*player1;
	char	*player2;
	int		total1;
	int		total2;

	ft_printf("Player 1: ");
	get_next_line(0, &player1);
	ft_printf("Player 2: ");
	get_next_line(0, &player2);

	total1 = count_total(player1, letters);
	total2 = count_total(player2, letters);

	if (total1 > total2)
		ft_printf("Player 1 wins!\n");
	else if (total1 < total2)
		ft_printf("Player 2 wins!\n");
	else
		ft_printf("Tie!\n");

	ft_strdel(&player1);
	ft_strdel(&player2);
	return (0);
}

int	count_total(char *str, int *letters)
{
	int	i;
	int	total;

	total = 0;
	i = 0;
	while (str[i])
	{
		if (str[i] >= 97 && str[i] <= 122)	// a-z
		{
			total += letters[str[i] - 97];	// - 'a'
		}
		else if (str[i] >= 65 && str[i] <= 90) // A-Z
		{
			total += letters[str[i] - 65];	//	- 'A'
		}
		i++;
	}
	return (total);
}
