#include "../includes/libft.h"
#define MAX 9

typedef struct candidate
{
	char	*name;
	int		votes;
}			candidate;

void	print_winner(candidate *candidates, int tot_candidates);
void	vote(int voters, int tot_candidates, candidate *candidates);

int main(int argc, char **argv)
{
	candidate	candidates[MAX];
	int			i;
	int			voters;
	char		*input;

	if (argc < 2)
	{
		ft_printf("Usage: %s [candidate names...]\n", argv[0]);
		return (1);
	}

	// copy candidate names
	i = 0;
	while (i < argc - 1)
	{
		candidates[i].name = ft_strdup(argv[i + 1]);
		candidates[i].votes = 0;
		i++;
	}

	// get amount of voters
	voters = 0;
	while (voters < 1)
	{
		ft_printf("Enter number of voters: ");
		get_next_line(0, &input);
		if (input)
		{
			voters = ft_atoi(input);
			ft_strdel(&input);
		}
	}

	vote(voters, argc - 1,  candidates);
	print_winner(candidates, argc - 1);

	// free candidate names
	i = 0;
	while (i < argc - 1)
	{
		ft_strdel(&(candidates[i].name));
		i++;
	}
	return (0);
}

void print_winner(candidate *candidates, int tot_candidates)
{
	int	i;
	int	max;

	max = 0;
	i = 0;
	while (i < tot_candidates)
	{
		if (max < (candidates[i]).votes)
			max = (candidates[i]).votes;
		i++;
	}
	ft_printf("\nWinners:\n");
	i = 0;
	while (i < tot_candidates)
	{
		if ((candidates[i]).votes == max)
			ft_printf("%s\n", (candidates[i]).name);
		i++;
	}
}

void vote(int voters, int tot_candidates, candidate *candidates)
{
	int		i;
	char	*ballot;
	int		found;
	int		j;

	i = 0;
	while (i < voters)
	{
		ft_printf("Vote: ");
		get_next_line(0, &ballot);
		found = 0;
		if (ballot)
		{
			j = 0;
			while (j < tot_candidates)
			{
				if (ft_strequ(ballot, (candidates[j]).name))
				{
					found = 1;
					(candidates[j]).votes++;
					break ;
				}
				j++;
			}
			ft_strdel(&ballot);
			if (!found)
				ft_printf("Invalid vote.\n");
		}
		else
			ft_printf("Invalid vote.\n");
		i++;
	}
}
