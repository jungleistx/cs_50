#include "../includes/libft.h"

int main(void)
{
	char	*input;
	int		start_pop;
	int		end_pop;
	int		years;
	int		loss;
	int		growth;

	years = 0;
	start_pop = 0;
	while (start_pop < 9)
	{
		ft_printf("Enter starting population: ");
		get_next_line(0, &input);
		start_pop = ft_atoi(input);
		ft_strdel(&input);
	}

	end_pop = 0;
	while (end_pop < start_pop)
	{
		ft_printf("Enter ending population: ");
		get_next_line(0, &input);
		end_pop = ft_atoi(input);
		ft_strdel(&input);
	}

	while (start_pop < end_pop)
	{
		growth = start_pop / 3;
		loss = start_pop / 4;
		start_pop = start_pop + growth - loss;
		years++;
	}

	ft_printf("Years: %d\n", years);
	return (0);
}
