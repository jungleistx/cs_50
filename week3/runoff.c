#include "../includes/libft.h"
#define MAX 9

typedef struct candidate
{
	char	*name;
	int		votes;
	int		eliminated;
}			candidate;

int		check_winner(int major_votes, int tot_candidates, candidate *candidates);
void	vote(int **ballot, int voters, int tot_candidates, candidate *candidates);
void	free_ballots(int **ballot, int voters);
void	init_ballots(int **ballot, int voters);
void	init_candidates(char **argv, candidate *candidates, int tot_candidates);
int		get_voters(void);
void	set_total_candidates(int *tot_candidates, int argc);
void	count_first_votes(int **ballot, int voters, candidate *candidates);
void	remove_last_candidate(candidate *candidates, int tot_candidates, int **ballot, int voters);
void	check_droput_tie(candidate *candidates, int min, int tot_candidates);

int main(int argc, char **argv)
{
	int 		voters;
	int 		major_votes;
	int			i;
	int			j;
	int			tot_candidates;
	int			**ballot;
	candidate	candidates[MAX];

	if (argc < 2)
	{
		ft_printf("Usage: %s [candidates...]\n", argv[0]);
		return (1);
	}
	set_total_candidates(&tot_candidates, argc);
	get_voters();
	init_ballots(ballot, voters);
	init_candidates(argv, candidates, tot_candidates);

	major_votes = (voters / 2) + 1;		// votes needed for win

	vote(ballot, voters, tot_candidates, candidates);
	count_first_votes(ballot, voters, candidates);

	while (!(check_winner(major_votes, tot_candidates, candidates)))
	{
		remove_last_candidate(candidates, tot_candidates, ballot);

		// check_only_candidate
	}

	free_ballots(ballot, voters);
	free_candidates(candidates, tot_candidates);
	return (0);
}

//	*	*	*	*	*	*	*	*	*	*	*	*	*	*	*	*	*	*	*	*	*	*	*	*
//	*	*	*	*	*	*	*	*	*	*	*	*	*	*	*	*	*	*	*	*	*	*	*	*

/*
	functions:
		delete_last_candidate()
*/

//	*	*	*	*	*	*	*	*	*	*	*	*	*	*	*	*	*	*	*	*	*	*	*	*
//	*	*	*	*	*	*	*	*	*	*	*	*	*	*	*	*	*	*	*	*	*	*	*	*

void	count_first_votes(int **ballot, int voters, candidate *candidates)
{
	int	i;
	int	pos;

	i = 0;
	while (i < voters)
	{
		if (ballot[i][0] != -1)
		{
			pos = ballot[i][0];			// voters first choice
			candidates[pos].votes++;
		}
		i++;
	}
}

void	vote(int **ballot, int voters, int tot_candidates, candidate *candidates)
{
	int		i;
	int		j;
	int		k;
	char	*input;

	i = 0;
	while (i < voters)
	{
		// all voters have 3 votes
		j = 0;
		while (j < 3)
		{
			ft_printf("Rank %d: ", j + 1);
			get_next_line(0, &input);
			if (input)
			{
				k = 0;
				while (k < tot_candidates)
				{
					if (ft_strequ(input, candidates[k].name))
					{
						ballot[i][j] = k;	// ballot[0][0] = 3 	==	 first voters first vote is candidate[3]
						break ;
					}
					k++;
				}
				ft_strdel(&input);
			}
			j++;
		}
		ft_printf("\n");
		i++;
	}
}

void	set_total_candidates(int *tot_candidates, int argc)
{
	*tot_candidates = argc - 1;
	if (*tot_candidates > MAX)
	{
		ft_printf("Too many candidates, max is %d\n", MAX);
		exit(1);
	}
}

int	get_voters(void)
{
	char	*input;
	int		voters;

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
	return (voters);
}

void	free_candidates(candidate *candidates, int tot_candidates)
{
	int	i;

	i = 0;
	while (i < tot_candidates)
	{
		ft_strdel(&(candidates[i].name));
		i++;
	}
}

// copy candidate names, set votes to 0
void	init_candidates(char **argv, candidate *candidates, int tot_candidates)
{
	int	i;

	i = 0;
	while (i < tot_candidates)
	{
		candidates[i].name = ft_strdup(argv[i + 1]);
		candidates[i].votes = 0;
		candidates[i].eliminated = 0;
		i++;
	}
}

void	check_droput_tie(candidate *candidates, int min, int tot_candidates)
{
	int	i;
	int	dropouts;
	int	survivors;

	i = 0;
	dropouts = 0;
	survivors = 0;
	while (i < tot_candidates)
	{
		if (candidates[i].votes == min)		// count dropouts
			dropouts++;
		if (candidates[i].eliminated == 0)	// count candidates left
			survivors++;
		i++;
	}
	if ((survivors - dropouts) < 1)		// all remaining candidates would be removed, tie
	{
		ft_printf("\n");
		i = 0;
		while (i < tot_candidates)
		{
			if (candidates[i].eliminated == 0)
				ft_printf("%s\n", candidates[i].name);
			i++;
		}
		exit(0);			// tie
	}
}

// cast votes for remaining candidates if there is a highest preference for the removed candidate
void	cast_removed_votes(candidate *candidates, int pos, int tot_candidates, int min, int **ballot, int voters)
{
	int	i;
	int	j;
	int	cur_pos;

	i = 0;
	while (i < voters)
	{
		j = 0;
		while (j < 3)	// look for votes for the removed candidates[pos] as first/first remaining vote
		{
			cur_pos = ballot[i][j];
			if (cur_pos != pos && candidates[cur_pos].eliminated == 0)		// voter has other preference
				break ;
			else if (cur_pos == pos)
			{
				j++;
				while (j < 3)
				{
					cur_pos = ballot[i][j];
					// next remaining candidate who is not being removed
					if ((candidates[cur_pos].eliminated == 0) && (candidates[cur_pos].votes > min))
					{
						candidates[cur_pos].votes++;
						break ;
					}
					j++;
				}
			}
			j++;
		}
		i++;
	}
}

void	remove_last_candidate(candidate *candidates, int tot_candidates, int **ballot, int voters)
{
	int	i;
	int	min;
	int	eliminated;

	i = 0;
	min = tot_candidates;
	while (i < tot_candidates)		// find the least amount of votes from remaining candidates
	{
		if (min > candidates[i].votes && candidates[i].eliminated == 0)
			min = candidates[i].votes;
		i++;
	}
	check_droput_tie(candidates, min, tot_candidates);
	i = 0;
	while (i < tot_candidates)
	{
		if (candidates[i].votes == min)
		{
			candidates[i].eliminated = 1;
			cast_removed_votes(candidates, i, tot_candidates, min, ballot, voters);
		}
		i++;
	}
}


int	check_winner(int major_votes, int tot_candidates, candidate *candidates)
{
	int i;

	i = 0;
	while (i < tot_candidates)
	{
		if (candidates[i].votes >= major_votes)
		{
			ft_printf("\n%s\n", candidates[i].name);
			return (1);
		}
		i++;
	}
	return (0);
}

void	free_ballots(int **ballot, int voters)
{
	int	i;

	i = 0;
	while (i < voters)
	{
		free(ballot[i]);
		i++;
	}
	free(ballot);
}

/*
	every voters preferred candidate's index saved in order:
	ballot[0][0] = 2		==		first voters first choice is candidate[2].name
	ballot[0][1] = 3		==		first voters second choice is candidate[3].name
*/
void	init_ballots(int **ballot, int voters)
{
	int	i;
	int	j;

	ballot = (int **) malloc(sizeof(int *) * voters);
	if (!ballot)
	{
		ft_printf("Error in init_ballots int** malloc!\n");
		exit(2);
	}

	i = 0;
	while (i < voters)
	{
		ballot[i] = (int *) malloc(sizeof(int) * 3);
		if (!ballot[i])
		{
			ft_printf("Error in init_ballots int* malloc!\n");
			exit(3);
		}
		j = 0;
		while (j < 3)
		{
			ballot[i][j] = -1;		// initialize to -1, 0 is a position
			j++;
		}
		i++;
	}
}
