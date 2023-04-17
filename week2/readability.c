#include "../includes/libft.h"
#include <math.h>

int main(void)
{
	int		letters;
	int		words;
	int		sentences;
	int		i;
	int		j;
	char	*input;

	ft_printf("Text: ");
	get_next_line(0, &input);
	if (!input)
		exit(1);

	letters = 0;
	words = 01;
	sentences = 0;
	i = 0;
	j = 0;
	while (input[i])
	{
		if (ft_isalpha(input[i]))		// a-z or A-Z
			letters++;

		if (input[i] == '.' || input[i] == '?' || input[i] == '!')
			sentences++;

		if (ft_iswhitespace(input[i]))
			words++;

		i++;
	}
	ft_strdel(&input);
	ft_printf("\n");

	float	L;
	float	S;
	double	index;

	L = 100.0 / words * letters;
	S = 100.0 / words * sentences;

	index = 0.0588 * L - 0.296 * S - 15.8;

	if (index >= 16)
		ft_printf("Grade 16+\n");
	else if (index < 1)
		ft_printf("Before grade 1\n");
	else
		ft_printf("Grade %.0lf\n", round(index));	// rounded to nearest whole num
}
