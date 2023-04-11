#include "../includes/libft.h"

int	calculate_quarters(int cents);
int	calculate_dimes(int cents);
int	calculate_nickels(int cents);
int	calculate_pennies(int cents);

int main(void)
{
	char	*input;
	int		cash;
	int		quarter;
	int		dime;
	int		nickel;
	int		penny;

	cash = 0;
	while (cash == 0)	// loop until valid input
	{
		ft_printf("Change owed: ");
		get_next_line(0, &input);
		cash = ft_atoi(input);
		ft_strdel(&input);
	}

	quarter = 0;
	dime = 0;
	nickel = 0;
	penny = 0;

	quarter = calculate_quarters(cash);
	cash = cash - (quarter * 25);
	dime = calculate_dimes(cash);
	cash = cash - (dime * 10);
	nickel = calculate_nickels(cash);
	cash = cash - (nickel * 5);
	penny = calculate_pennies(cash);
	cash = cash - (penny * 1);

	ft_printf("%d\n", quarter + dime + nickel + penny);
	return (0);
}

int	calculate_quarters(int cents)
{
	int total;

	total = 0;
	while (cents >= 25)
	{
		total++;
		cents -= 25;
	}
	return (total);
}

int	calculate_dimes(int cents)
{
	int total;

	total = 0;
	while (cents >= 10)
	{
		total++;
		cents -= 10;
	}
	return (total);
}

int	calculate_nickels(int cents)
{
	int total;

	total = 0;
	while (cents >= 5)
	{
		total++;
		cents -= 5;
	}
	return (total);
}

int	calculate_pennies(int cents)
{
	int total;

	total = 0;
	while (cents >= 1)
	{
		total++;
		cents -= 1;
	}
	return (total);
}
