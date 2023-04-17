#include "../includes/libft.h"
#define MAX 9

typedef struct candidate
{
	char	*name;
	int		votes[3];
}			candidate;

void	vote(int voters, int tot_candidates, candidate *candidates);
int		check_winner(int major_votes, int tot_candidates, candidate *candidates);

int main(int argc, char **argv)
{
	int 		voters;
	char 		*input;
	int 		major_votes;
	int			i;
	int			j;
	int			tot_candidates;
	candidate	candidates[MAX];

	if (argc < 2)
	{
		ft_printf("Usage: %s [candidates...]\n", argv[0]);
		return (1);
	}

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

	tot_candidates = argc - 1;
	if (tot_candidates > MAX)
	{
		ft_printf("Too many candidates, max is %d\n", MAX);
		exit(1);
	}

	// copy candidate names, set votes to 0
	i = 0;
	while (i < tot_candidates)
	{
		j = 0;
		candidates[i].name = ft_strdup(argv[i + 1]);
		while (j < 3)
		{
			(candidates[i]).votes[j] = 0;
			j++;
		}
		i++;
	}

	// count majority (instant win)
	major_votes = (voters / 2) + 1;

	vote(voters, tot_candidates, candidates);

	// while (!(check_winner(major_votes, tot_candidates, candidates)))
	// {
	// }
	check_winner(major_votes, tot_candidates, candidates);

	return (0);
}

void	vote(int voters, int tot_candidates, candidate *candidates)
{
	int		i;
	int		j;
	int		k;
	char	*ballot;

	i = 0;
	while (i < voters)
	{
		// all vote 3 times
		j = 0;
		while (j < 3)
		{
			ft_printf("Rank %d: ", j + 1);
			get_next_line(0, &ballot);
			if (ballot)
			{
				k = 0;
				while (k < tot_candidates)
				{
					if (ft_strequ(candidates[k].name, ballot))
					{
						// add vote to candidates jth-preference index
						(candidates[k]).votes[j]++;
						break ;
					}
					k++;
				}
				ft_strdel(&ballot);
			}
			j++;
		}
		ft_printf("\n");
		i++;
	}
}

int	check_winner(int major_votes, int tot_candidates, candidate *candidates)
{
	int i;

	i = 0;
	while (i < tot_candidates)
	{
		if (candidates[i].votes[0] >= major_votes)
		{
			ft_printf("%s\n", candidates[i].name);
			return (1);
		}
		i++;
	}
	return (0);
}

/*
	functions:
		check_all_tied()
		delete_last_candidate()
*/
