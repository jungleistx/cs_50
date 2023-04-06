#include "../includes/libft.h"

int		all_digits(char *str);
int		num_length(long num);
void	print_invalid(void);
int		checksum(long num, int length);
void	check_visa(long num, int length);
void	check_amex(long num, int length);
void	check_master_or_visa(long num, int length);
long	ft_atol(const char *str);

int	main(void)
{
	char	*input;
	long	num;
	int		length;

	while (1)
	{
		ft_printf("Number: ");
		get_next_line(0, &input);

		if (all_digits(input))
		{
			num = ft_atol(input);
			ft_strdel(&input);
			break ;
		}
		ft_strdel(&input);
	}

	length = num_length(num);

	// check the cardtype, based on length and cards first number
	if (length == 15)
		check_amex(num, length);
	else if (length == 13)
		check_visa(num, length);
	else if (length == 16)
		check_master_or_visa(num, length);
	else
		print_invalid();
	return (0);
}

void	check_master_or_visa(long num, int length)
{
	int		pos;
	long	copy;
	int		second;

	pos = 0;
	copy = num;
	while (pos < 14)
	{
		copy /= 10;
		pos++;
	}
	if (copy / 10 == 4)		// visas first number is 4
	{
		if (checksum(num, length))
			ft_printf("VISA\n");
	}
	else if (copy / 10 == 5)	// mastercards first number is 5
	{
		second = copy % 10;
		if (second >= 1 && second <= 5) // mastercards second number is from 1 to 5
		{
			if (checksum(num, length))
				ft_printf("MASTERCARD\n");
		}
		else
			print_invalid();
	}
	else
		print_invalid();
}

// sum of every other digit * 2. if result > 9, sum of those digits
int	sum_digits(long num)
{
	int result;
	int	total;

	result = (num % 10) * 2;
	if (result < 10)
		return (result);
	else
	{
		total = result % 10;
		result /= 10;
		total += result;
		return (total);
	}
}

// calculate the checksum for the cards numbers. algorhitm can be found in the task.
int	checksum(long num, int length)
{
	long 	num_copy;
	int		total;
	int		len_copy;

	total = 0;
	num_copy = num;

	len_copy = length - 1;
	while (len_copy > 0)
	{
		num_copy /= 10;
		total += sum_digits(num_copy);
		num_copy /= 10;
		len_copy -= 2;
	}

	len_copy = length;
	num_copy = num;
	while (len_copy > 0)
	{
		total += num_copy % 10;
		num_copy /= 10;
		num_copy /= 10;
		len_copy -= 2;
	}

	if (total % 10 != 0)
	{
		print_invalid();
		return (0);
	}
	return (1);
}

void	check_visa(long num, int length)
{
	int		pos;
	long	copy;

	pos = 0;
	copy = num;
	while (pos < 12)
	{
		copy /= 10;
		pos++;
	}
	if (copy == 4)		// visas first number is 4
	{
		if (checksum(num, length))
			ft_printf("VISA\n");
	}
	else
		print_invalid();
}

void	check_amex(long num, int length)
{
	int		pos;
	long	copy;

	copy = num;
	pos = 0;
	while (pos < 13)
	{
		copy /= 10;
		pos++;
	}
	if (copy % 10 == 7 || copy % 10 == 4)	// amex's second number is 4 or 7
	{
		copy /= 10;
		if (copy % 10 == 3)			// first number is 3
		{
			if (checksum(num, length))
				ft_printf("AMEX\n");
		}
		else
			print_invalid();
	}
	else
		print_invalid();
}

void	print_invalid(void)
{
	ft_printf("INVALID\n");
}

int	num_length(long num)
{
	int	result;

	result = 0;
	while (num != 0)
	{
		num /= 10;
		result++;
	}
	return (result);
}

// check if all characters are digits
int	all_digits(char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (str[i] < 48 || str[i] > 57)
			return (0);
		i++;
	}
	return (1);
}
