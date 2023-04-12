#include "../../../includes/libft.h"

int ft_strlen_fin(char *str);
int validate_chars(char *str);

int main(void)
{
	int		wordlist_fd;
	int		filtered_fd;
	char	*line;

	wordlist_fd = open("week2/wordle/wordlists/english.txt", O_RDONLY);
	if (wordlist_fd == -1)
	{
		ft_printf("ERROR reading wordlist\n");
		return (1);
	}

	filtered_fd = open("week2/wordle/wordlists/eng_4.txt", O_RDWR | O_CREAT | O_TRUNC, 0644);
	if (filtered_fd == -1)
	{
		ft_printf("ERROR opening filtered_wordlist\n");
		return (2);
	}

	while (get_next_line(wordlist_fd, &line) > 0)
	{
		int len;
		len = ft_strlen_fin(line);
		if (len == 4)
		{
			if (validate_chars(line))
			{
				write(filtered_fd, line, ft_strlen(line));		// finnish language prevents using 'len' here; ä/ö are 2-characters long, so the output would be false.
				write(filtered_fd, "\n", 1);
			}
		}
		free(line);
		line = NULL;
	}
	if (line)
	{
		free(line);
		line = NULL;
	}
	close(filtered_fd);
	close(wordlist_fd);
}

int ft_strlen_fin(char *str)
{
	int i;
	int len;

	if (!str)
		return (0);
	i = 0;
	len = 0;
	while (str[i])
	{
		if (str[i] == -61 && str[i + 1])				// first value of (ä/ö)
		{
			if (str[i + 1] == -74 || str[i + 1] == -92)		// second value of (ä/ö)
				i++;
		}
		len++;
		i++;
	}
	return (len);
}

int validate_chars(char *str)
{
	int i;

	i = 0;
	while (str[i])
	{
		if (!ft_isalpha(str[i]))
		{
			if (str[i] != -61)		// first value of (ä/ö)
				return (0);
			i++;
		}
		i++;
	}
	return (1);
}
