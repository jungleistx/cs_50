#include "../includes/libft.h"
#define MAX 9

typedef struct candidate
{
	char	*name;
	int		votes;
	int		eliminated;
}			candidate;

// void	vote(int voters, int tot_candidates, candidate *candidates);
// int		check_winner(int major_votes, int tot_candidates, candidate *candidates);

void	free_ballots(int **ballot, int voters);
void	init_ballots(int **ballot, int voters, int tot_candidates);

int main(int argc, char **argv)
{
	int 		voters;
	char 		*input;
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

	tot_candidates = argc - 1;
	if (tot_candidates > MAX)
	{
		ft_printf("Too many candidates, max is %d\n", MAX);
		exit(1);
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

	init_ballots(ballot, voters, tot_candidates);


	// copy candidate names, set votes to 0
	i = 0;
	while (i < tot_candidates)
	{
		candidates[i].name = ft_strdup(argv[i + 1]);
		candidates[i].votes = 0;
		candidates[i].eliminated = 0;
		i++;
	}

	// count majority (instant win)
	major_votes = (voters / 2) + 1;

	// vote(voters, tot_candidates, candidates);

	// while (!(check_winner(major_votes, tot_candidates, candidates)))
	// {
	// 	delete_last_candidate(candidates, tot_candidates);
	// }

	free_ballots(&ballot);
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
	every voters preferred candidate's index saved in order
	ballot[0][0] = 2		==		first voters first choice is candidate[2].name
	ballot[0][1] = 3		==		first voters second choice is candidate[3].name
*/
void	init_ballots(int **ballot, int voters, int tot_candidates)
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
		ballot[i] = (int *) malloc(sizeof(int) * tot_candidates);
		if (!ballot[i])
		{
			ft_printf("Error in init_ballots int* malloc!\n");
			exit(3);
		}
		j = 0;
		while (j < tot_candidates)
		{
			ballot[i][j] = -1;
			j++;
		}
		i++;
	}
}

// int	check_tied_votes(int min, int pos, int tot_candidates, candidate *candidates)
// {
// 	int	i;
// 	int	last;

// 	i = 0;
// 	last = 0;
// 	while (i < tot_candidates)
// 	{
// 		if (candidates[i].votes[0] == min)
// 			last++;
// 		i++;
// 	}

// }

// void	delete_last_candidate(candidate *candidates, int tot_candidates)
// {
// 	int	i;
// 	int	j;
// 	int	min;

// 	i = 0;
// 	j = 0;
// 	min = tot_candidates;
// 	while (i < tot_candidates)
// 	{
// 		if (min > candidates[i].votes[j])
// 			min = candidates[i].votes[j];
// 		i++;
// 	}
// 	i = 0;
// 	while (i < tot_candidates)
// 	{
// 		if (candidates[i])
// 		i++;
// 	}


// }

// void	vote(int voters, int tot_candidates, candidate *candidates)
// {
// 	int		i;
// 	int		j;
// 	int		k;
// 	char	*input;

// 	i = 0;
// 	while (i < voters)
// 	{
// 		// all vote 3 times
// 		j = 0;
// 		while (j < 3)
// 		{
// 			ft_printf("Rank %d: ", j + 1);
// 			get_next_line(0, &input);
// 			if (input)
// 			{
// 				k = 0;
// 				while (k < tot_candidates)
// 				{
// 					if (ft_strequ(candidates[k].name, input))
// 					{
// 						// add vote to candidates jth-preference index
// 						(candidates[k]).votes[j]++;
// 						break ;
// 					}
// 					k++;
// 				}
// 				ft_strdel(&input);
// 			}
// 			j++;
// 		}
// 		ft_printf("\n");
// 		i++;
// 	}
// }

// int	check_winner(int major_votes, int tot_candidates, candidate *candidates)
// {
// 	int i;

// 	i = 0;
// 	while (i < tot_candidates)
// 	{
// 		if (candidates[i].votes[0] >= major_votes)
// 		{
// 			ft_printf("%s\n", candidates[i].name);
// 			return (1);
// 		}
// 		i++;
// 	}
// 	return (0);
// }
