#include "../../includes/libft.h"

void	print_green(char c, int pos, int **hits);
void	print_yellow(char c, int pos, int **yellow);
void	print_red(char c, int *misses);
void	print_result(char *word, int guesses, int found);
void	print_invalid_word(char *str);
void	print_guess_instruction(int len);
void	print_helpers(char **helper, int lines, int len);
void	print_suggestions(char *filename, int len, int **hits, int **yel, int *miss, char **helper);

void	welcome_msg(int len);
void	init_helper(int *misses, int **hits, char **helper, int **yellow, int len);
void	init_filename(char *filename, int len);
void	helper_prompt(char **answer, int *suggestions);

void	enter_guess(int guess, int len, char *filename, char **input);
int		validate_input(char *input);
int		char_found(char c, char *str);
int		word_found(char *str, char *filename);
int		check_red_help(char *buf, int *misses);
int		check_yellow_help(char *buf, int **yellow, int len);
int		check_green_help(char *buf, int **hits, int len);

void	free_helpers(int **hits, int **yellow, int len);
void	free_suggestions(char **helper);

int main(int argc, char **argv)
{
	char	word[10];		// answer
	int		word_length;	// answer & guess -length
	int		guesses;		// 0-5
	int		found;			// guess == answer
	int		i;
	int		j;
	char	*input;			// entered guess
	int		misses[26];		// 0/1 for every letter, indicates missed (red) letters
	int		help_counter;
	int		total_possib;	// total possibilities of answers
	char 	*helper[5];		// suggestions based on previous guesses
	int		suggestions;
	char	*suggestion_prompt;
	char	filename[34];		// wordlist filename

	if (argc == 3)	// randomly generated answer & word_length sent from wordle.sh
	{
		word_length = ft_atoi(argv[2]);
		ft_strncpy(word, argv[1], word_length);
		word[word_length] = '\0';
	}
	else
	{
		ft_printf("ERROR in wordle main.c\n");
		return (1);
	}

	int		*hits[word_length];			// for every position, every letter possibility
	int		*yellow[word_length];		// letters that are in answer but in wrong position

	welcome_msg(word_length);
	helper_prompt(&suggestion_prompt, &suggestions);	// activate suggestions
	init_helper(misses, hits, helper, yellow, word_length);		// allocate arrays & init to 0
	init_filename(filename, word_length);			// read different wordlists based on wordlength

	guesses = 0;
	found = 0;
	while (guesses < 6)
	{
		enter_guess(guesses, word_length, filename, &input);

		i = 0;
		while (i < word_length)			// print matched letters and update the g/y/r arrays
		{
			if (input[i] == word[i])
				print_green(input[i], i, hits);
			else if (char_found(input[i], word))
				print_yellow(input[i], i, yellow);	// V2 NOTE: yellows might be false-positive
			else
				print_red(input[i], misses);
			i++;
		}
		ft_printf("\n");

		guesses++;
		if (ft_strequ(input, word))
			found = 1;
		ft_strdel(&input);

		if (found)
			break ;
		else if (guesses < 6 && suggestions) 		// suggestions turned on
			print_suggestions(filename, word_length, hits, yellow, misses, helper);
	}
	print_result(word, guesses, found);
	free_helpers(hits, yellow, word_length);
	return (0);
}

// 	*	*	*	*	*	*	*	*	*	*	*	*	*	*	*	*	*	*	*	*
// 	*	*	*	*	*	*	*	*	*	*	*	*	*	*	*	*	*	*	*	*
// 	*	*	*	*	*	*	*	*	*	*	*	*	*	*	*	*	*	*	*	*
// 	*	*	*	*	*	*	*	*	*	*	*	*	*	*	*	*	*	*	*	*
// 	*	*	*	*	*	*	*	*	*	*	*	*	*	*	*	*	*	*	*	*

void	enter_guess(int guess, int len, char *filename, char **input)
{
	while (1)	// loop until valid guess given
	{
		ft_printf("Enter %d. guess: ", guess + 1);
		get_next_line(0, input);
		if (*input)
		{
			if (ft_strlen(*input) == len && validate_input(*input))	// all lowercase correct length input
			{
				if (word_found(*input, filename))		// input found in wordlist
					return ;
				else
					print_invalid_word(*input);
			}
			else
				print_guess_instruction(len);
			ft_strdel(input);
		}
	}
}

void	print_suggestions(char *filename, int len, int **hits, int **yel, int *miss, char **helper)
{
	int		fd_helper;		// open for reading words for helper
	int		suggestions;
	int		total_possib;	// all possible answers
	int		read_amount;	// linelength in file
	char	buf[9];			// buffer for reading single line from file

	fd_helper = open(filename, O_RDONLY);
	if (fd_helper == -1)
	{
		ft_printf("ERROR opening %s in print_suggestions\n", filename);
		exit(4);
	}
	if (len == 5)						// not sure why it reads differently with len 5
		read_amount = len + 2;			// maybe newline in different position in files?
	else
		read_amount = len + 1;

	suggestions = 0;
	total_possib = 0;

	while (read(fd_helper, &buf, read_amount) > 0)	// read wordlist line-by-line, skip newlines
	{
		buf[len] = '\0';
		if (check_green_help(buf, hits, len))		// 'greens' match the word
		{
			if (check_red_help(buf, miss))			// no 'reds' in the word
			{
				if (check_yellow_help(buf, yel, len))	// word contains all 'yellows'
				{
					if (suggestions < 5)				// add to suggestions
					{
						helper[suggestions] = ft_strdup(buf);
						suggestions++;
					}
					total_possib++;		// even if suggestions == 5, count all the possible answers
				}
			}
		}
	}
	close(fd_helper);
	print_helpers(helper, total_possib, len);
	free_suggestions(helper);
}

void	print_result(char *word, int guesses, int found)
{
	if (found)
	{
		ft_printf(GREEN"\n\nWINNER");
		if (guesses < 6)
		{
			if (guesses == 1)
				ft_printf(" on your first try, amazing! Have you considered doing lottery?\n\n"NOCO);
			else
				ft_printf(", with "YELLOW"%d"GREEN" guess(es) to spare!\nNice!\n\n"NOCO, 6 - guesses);
		}
		else
			ft_printf(" on your last try, congrats!\n\n"NOCO);
	}
	else
		ft_printf(RED"\nWOOPS, out of guesses."NOCO" Word was \'"GREEN"%s"NOCO"\'.\n\n", word);
}

void	helper_prompt(char **answer, int *suggestions)
{
	ft_printf(YELLOW"Activate suggestions? (y/n) "NOCO);
	get_next_line(0, answer);

	*suggestions = 0;
	if (answer && *answer)
	{
		if (ft_strequ(*answer, "y") || ft_strequ(*answer, "Y"))
			*suggestions = 1;
		ft_strdel(answer);
	}
}

void	init_filename(char *filename, int len)
{
	if (len == 4)
		ft_strcpy(filename, "week2/wordle/wordlists/eng_4.txt");
	else if (len == 5)
		ft_strcpy(filename, "week2/wordle/wordlists/eng_5.txt");
	else if (len == 6)
		ft_strcpy(filename, "week2/wordle/wordlists/eng_6.txt");
	else if (len == 7)
		ft_strcpy(filename, "week2/wordle/wordlists/eng_7.txt");
	else if (len == 8)
		ft_strcpy(filename, "week2/wordle/wordlists/eng_8.txt");
}

void free_suggestions(char **helper)
{
	int i;

	i = 0;
	while (i < 5)
	{
		if (helper[i] && *helper[i])
		{
			free(helper[i]);
			helper[i] = NULL;
		}
		i++;
	}
}

void print_helpers(char **helper, int lines, int len)
{
	int i;

	ft_printf(YELLOW"\t\tSUGGESTIONS: (%d possibilities, ", lines);
	if (lines)												// if 0, division will go crazy
		ft_printf("%.2f%% chance\n"NOCO, 100.0 / lines);
	else
		ft_printf("but should be atleast 1...  :|\n"NOCO);

	i = 0;
	while (i < 5)
	{
		if (helper[i] && *(helper[i]))
		{
			if (ft_strlen(helper[i]) > 0)
			{
				ft_printf("\t\t%d: ", i + 1);
				ft_printf("%s\n", helper[i]);
			}
		}
		i++;
	}
}

void free_helpers(int **hits, int **yellow, int len)
{
	int i;

	i = 0;
	while (i < len)
	{
		free(hits[i]);
		free(yellow[i]);
		i++;
	}
}

int check_red_help(char *buf, int *misses)
{
	int i;

	i = 0;
	while (buf[i])
	{
		if (misses[buf[i] - 97] == 1)		// buf[i] - 'a' = pos in letters; a = 0...
			return (0);						// letter is found in red array
		i++;
	}
	return (1);
}

int check_yellow_help(char *buf, int **yellow, int len)
{
	int i;
	int j;
	int k;
	int found;

	i = 0;
	while (i < len)
	{
		j = 0;
		while (j < 26)
		{
			if (yellow[i][j] == 1)		// yellow found, check if found in word
			{
				if (buf[i] == j + 'a')		// yellow is match (green)
					return (0);
				k = 0;
				found = 0;
				while (k < 5)
				{
					if (buf[k] == j + 'a')
					{
						found++;
						break ;
					}
					k++;
				}
				if (!found)
					return (0);
			}
			j++;
		}
		i++;
	}
	return (1);
}

int check_green_help(char *buf, int **hits, int len)
{
	int i;
	int j;

	i = 0;
	while (i < len)		// loop through every pos of word
	{
		j = 0;
		while (j < 26)		// loop through every letter of pos [i]
		{
			if (hits[i][j] == 1)	// if match found in pos[i] and with letter j (j[0] == 'a', ...)
			{
				if (buf[i] != j + 'a')
					return (0);		// green in [i] not a match with this word
				if (i < len - 1)			// match found, move on to next pos
				{
					i++;
					j = -1;
				}
				else 				// last pos, return success on every hit found in this word
					return (1);
			}
			j++;
		}
		i++;
	}
	return (1);
}

int	word_found(char *str, char *filename)
{
	int		wordlist_fd;
	char	buf[10001];
	int		ret;

	wordlist_fd = open(filename, O_RDONLY);
	if (wordlist_fd == -1)
	{
		ft_printf("ERROR opening wordlist in word_found...\n");
		exit(3);
	}

	ret = read(wordlist_fd, &buf, 10000);
	while (ret > 0)
	{
		buf[ret] = '\0';
		if (ft_strstr(buf, str))	// search for the guess in the wordlist
		{
			close(wordlist_fd);
			return (1);
		}
		ret = read(wordlist_fd, &buf, 10000);
	}
	close(wordlist_fd);
	return (0);				// guess not found in the wordlist
}

int	validate_input(char *input)
{
	int	i;

	i = 0;
	while (input[i])
	{
		if (!ft_isalpha(input[i]) || (input[i] >= 65 && input[i] <= 90))	// not lowercase letter
			return (0);
		i++;
	}
	return (1);
}

void	welcome_msg(int len)
{
	ft_printf("WELCOME TO WORDLE!\n\nYou have 6 tries to guess %d letters-long ", len);
	ft_printf("word. \n\nLetters in correct positions are shown in %sgreen", GREEN);
	ft_printf("%s, \nletters correct but in wrong positions are shown in ", NOCO);
	ft_printf("%syellow", YELLOW);
	ft_printf("%s, \nand letters completely wrong are shown in ", NOCO);
	ft_printf("%sred", RED);
	ft_printf(NOCO".\n\nEnter the guesses in lowercase (a-z).");
	ft_printf("\nGood luck!\n\n");
}

int	char_found(char c, char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (str[i] == c)
			return (1);
		i++;
	}
	return (0);
}

void	print_green(char c, int pos, int **hits)
{
	ft_printf(GREEN"%c "NOCO, c);

	if (hits[pos][c - 'a'] == 0)			// turn on 'green' for that positions letter
		hits[pos][c - 'a'] = 1;
}

void	print_yellow(char c, int pos, int **yellow)
{
	ft_printf(YELLOW"%c "NOCO, c);

	if (yellow[pos][c - 'a'] == 0)		// turn on 'yellow' for that positions letter
		yellow[pos][c - 'a'] = 1;
}

void	print_red(char c, int *misses)
{
	ft_printf(RED"%c "NOCO, c);

	if (misses[c - 'a'] == 0)		//	turn on the miss in position assigned to char (a == 0, ...)
		misses[c - 'a'] = 1;
}

void print_invalid_word(char *str)
{
	ft_printf(RED"\'%s\' not found in the wordlist!\n"NOCO, str);
}

void print_guess_instruction(int len)
{
	ft_printf(RED"Word must be %d-letters and only contain a-z!\n"NOCO, len);
}

void init_helper(int *misses, int **hits, char **helper, int **yellow, int len)
{
	int i;

	//	init 'reds' all to 0
	i = 0;
	while (i < 26)
	{
		misses[i] = 0;
		i++;
	}

	//	init 'greens' & 'yellows' all to 0
	int j;
	i = 0;
	while (i < len)
	{
		hits[i] = malloc(sizeof(int) * 26);
		if (!hits[i])
		{
			ft_printf("ERROR in malloc hits\n");
			exit(6);
		}
		yellow[i] = malloc(sizeof(int) * 26);
		if (!yellow[i])
		{
			ft_printf("ERROR in malloc yellow\n");
			exit(7);
		}
		j = 0;
		while (j < 26)
		{
			hits[i][j] = 0;
			yellow[i][j] = 0;
			j++;
		}
		i++;
	}

	//	helper matches
	i = -1;
	while (++i < 5)
		helper[i] = NULL;
}

    //    0 nul    1 soh    2 stx    3 etx    4 eot    5 enq    6 ack    7 bel
    //    8 bs     9 ht    10 nl    11 vt    12 np    13 cr    14 so    15 si
    //   16 dle   17 dc1   18 dc2   19 dc3   20 dc4   21 nak   22 syn   23 etb
    //   24 can   25 em    26 sub   27 esc   28 fs    29 gs    30 rs    31 us
    //   32 sp    33  !    34  "    35  #    36  $    37  %    38  &    39  '
    //   40  (    41  )    42  *    43  +    44  ,    45  -    46  .    47  /
    //   48  0    49  1    50  2    51  3    52  4    53  5    54  6    55  7
    //   56  8    57  9    58  :    59  ;    60  <    61  =    62  >    63  ?
    //   64  @    65  A    66  B    67  C    68  D    69  E    70  F    71  G
    //   72  H    73  I    74  J    75  K    76  L    77  M    78  N    79  O
    //   80  P    81  Q    82  R    83  S    84  T    85  U    86  V    87  W
    //   88  X    89  Y    90  Z    91  [    92  \    93  ]    94  ^    95  _
    //   96  `    97  a    98  b    99  c   100  d   101  e   102  f   103  g
    //  104  h   105  i   106  j   107  k   108  l   109  m   110  n   111  o
    //  112  p   113  q   114  r   115  s   116  t   117  u   118  v   119  w
    //  120  x   121  y   122  z   123  {   124  |   125  }   126  ~   127 del
