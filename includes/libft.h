/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libft.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skattankakku <skattankakku@student.42.f    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/01 12:56:07 by rvuorenl          #+#    #+#             */
/*   Updated: 2023/04/05 15:13:52 by skattankakk      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LIBFT_H
# define LIBFT_H
# include <string.h>
# include <unistd.h>
# include <stdlib.h>
# include <fcntl.h>
# include <stdarg.h>

# define BUFF_SIZE 10000
# define SPECS "%dicoxXuUspnfFbBD"
# define RED "\033[0;31m"
# define GREEN "\033[0;32m"
# define YELLOW "\033[0;33m"
# define BLUE "\033[0;34m"
# define NOCO "\033[0m"

typedef struct s_list
{
	void			*content;
	size_t			content_size;
	struct s_list	*next;
}t_list;

typedef struct s_info
{
	uint16_t			flags;
	int					res;
	int					width;
	int					prec;
	int					arg_len;
	int					f_dec_len;
	long double			f_arg;
	char				hex;
	int					i;
	int					f_total;
	unsigned long long	cur_arg;
}t_info;

typedef enum e_spec
{
	H,
	HH,
	L,
	LL
}t_spec;

typedef enum e_flags
{
	SPACE = 1,
	PLUS = 2,
	MINUS = 4,
	ZERO = 8,
	HASH = 16,
	DOT = 32,
	LONG = 64,
	LLONG = 128,
	SHORT = 256,
	SSHORT = 512,
	NEGATIVE = 1024,
	FLONG = 2048
}t_flags;

typedef void				(*t_func_pointer) (t_info *, va_list);

void	ft_bubblesort_str(char **list);
void	ft_bubblesort_int(int *list, int size);
void	ft_free_strarray(char ***array);
void	ft_exit_error(char *msg, int ret);
char	*ft_strjoin_three(char *s1, char *s2, char *s3);
size_t	ft_strlen_match(char *str, char delimiter);
int		ft_strarray_size(char **arr);
char	**ft_dup_strarray(char **original);
char	**ft_create_strarray(int size);
int		ft_strcount(char *str, char target);
void	ft_copy_strarray(char **src, char **dst);
int		ft_iswhitespace(char c);
int		get_next_line(const int fd, char **line);
void	ft_putstr(char const *s);
void	ft_putchar(char c);
size_t	ft_strlen(const char *s);
int		ft_atoi(const char *str);
int		ft_toupper(int c);
int		ft_tolower(int c);
int		ft_isalpha(int c);
int		ft_isdigit(int c);
int		ft_strcmp(const char *s1, const char *s2);
int		ft_strncmp(const char *s1, const char *s2, size_t n);
int		ft_isalnum(int c);
int		ft_isascii(int c);
int		ft_isprint(int c);
char	*ft_strdup(const char *s1);
char	*ft_strcat(char *s1, const char *s2);
char	*ft_strncat(char *s1, const char *s2, size_t n);
char	*ft_strcpy(char *dst, const char *src);
char	*ft_strncpy(char *dst, const char *src, size_t len);
size_t	ft_strlcat(char *dst, const char *src, size_t dstsize);
char	*ft_strchr(const char *s, int c);
void	*ft_memset(void *b, int c, size_t len);
void	*ft_memcpy(void *dst, const void *src, size_t n);
void	*ft_memccpy(void *dst, const void *src, int c, size_t n);
void	ft_bzero(void *s, size_t n);
void	*ft_memmove(void *dst, const void *src, size_t len);
void	*ft_memchr(const void *s, int c, size_t n);
int		ft_memcmp(const void *s1, const void *s2, size_t n);
char	*ft_strrchr(const char *s, int c);
char	*ft_strstr(const char *haystack, const char *needle);
char	*ft_strnstr(const char *haystack, const char *needle, size_t len);
void	ft_putnbr(int n);
void	ft_strclr(char *s);
void	*ft_memalloc(size_t size);
char	*ft_strnew(size_t size);
int		ft_strequ(char const *s1, char const *s2);
char	*ft_itoa(int n);
void	ft_memdel(void **ap);
void	ft_strdel(char **as);
void	ft_striter(char *s, void (*f)(char *));
void	ft_striteri(char *s, void (*f)(unsigned int, char *));
char	*ft_strmap(char const *s, char (*f)(char));
char	*ft_strjoin(char const *s1, char const *s2);
char	*ft_strtrim(char const *s);
char	*ft_strmapi(char const *s, char (*f)(unsigned int, char));
int		ft_strnequ(char const *s1, char const *s2, size_t n);
char	*ft_strsub(char const *s, unsigned int start, size_t len);
void	ft_putendl(char const *s);
void	ft_putchar_fd(char c, int fd);
void	ft_putstr_fd(char const *s, int fd);
void	ft_putendl_fd(char const *s, int fd);
void	ft_putnbr_fd(int n, int fd);
char	**ft_strsplit(char const *s, char c);
t_list	*ft_lstnew(void const *content, size_t content_size);
void	ft_lstadd(t_list **alst, t_list *new);
void	ft_lstdelone(t_list **alst, void (*del)(void *, size_t));
void	ft_lstdel(t_list **alst, void (*del)(void *, size_t));
void	ft_lstiter(t_list *lst, void (*f)(t_list *elem));
t_list	*ft_lstmap(t_list *lst, t_list *(*f)(t_list *elem));
t_list	*ft_lstadd_end(t_list *head, t_list *new);

// ft_printf
int		ft_printf(const char *str, ...);
int		ft_atoi(const char *str);
int		ft_isdigit(int c);
size_t	ft_strlen(const char *s);
void	ft_putchar(char c);
void	print_zero_unsig(t_info *i);
char	*assign_str(t_info *i, va_list args);
void	print_zero_octal(t_info *i);
void	print_octal_numbers(t_info *i, unsigned long long a);
void	print_zero_octal_flags(t_info *i);
void	print_octal_non_minus(t_info *i);
void	print_octal_minus(t_info *i);
void	print_prefix_flag(t_info *i);
void	print_zero_number(t_info *i);
void	print_prec_flag(t_info *i);
void	print_width(t_info *i);
void	print_zero_hex(t_info *i);
void	count_hex(t_info *i, unsigned long long tmp);
void	print_hex(unsigned long long i, char letter);
void	print_hex_zero_width(t_info *i);
void	print_hex_width(t_info *i);
void	print_hex_minus(t_info *i);
void	print_hex_hash(t_info *i);
int		count_digits(unsigned long long num);
int		ft_putchar_multi(char c, int i);
void	ft_putnbr_l(unsigned long long n);
void	reset_info(t_info *info, int reset);
int		write_non_percent(const char *str, t_info *info);
int		check_flags(const char *str, t_info *info, va_list args, int i);
void	check_specifier(const char *str, t_info *info, va_list args);
void	float_calc_total(t_info *i);
void	print_float_flags(t_info *i);
void	print_float_zero_prec(t_info *i);
int		dot_zero_prec(t_info *info, const char *str, int i);
int		dot_flag(t_info *info, const char *str, int i, va_list args);
int		ast_precision_flag(t_info *i, va_list args);
int		dot_ast_flag(const char *str, t_info *info, va_list args);
void	special_flags(t_info *i);
void	check_len_flags(char c, t_info *info);
int		digit_minus_flag(const char *str, t_info *info);
void	plus_space_flag(const char *str, t_info *i);
void	assign_dic(t_info *i, va_list args);
void	assign_oux(t_info *i, va_list args);
int		check_rounding(long double frac, int prec);
void	print_unsigned_width(t_info *i);
void	print_zero_address(t_info *i);
void	assign_float_to_ints(long double frac, t_info *i, int prec);
void	assign_float(t_info *i, va_list args);
void	print_percent(t_info *i, va_list args);
void	print_number(t_info *i, va_list args);
void	print_char(t_info *info, va_list args);
void	print_octal(t_info *i, va_list args);
void	print_hex_flags(t_info *i, va_list args);
void	print_unsigned(t_info *i, va_list args);
void	print_unsigned_long(t_info *i, va_list args);
void	print_str(t_info *i, va_list args);
void	print_address(t_info *i, va_list args);
void	calc_printed(t_info *i, va_list args);
void	print_float(t_info *i, va_list args);
void	print_uppercase_number(t_info *i, va_list args);
void	print_binary(t_info *i, va_list args);
void	print_binary_value(t_info *i, unsigned long long num);

static const t_func_pointer	g_disp_table[17] = {
	print_percent,
	print_number,
	print_number,
	print_char,
	print_octal,
	print_hex_flags,
	print_hex_flags,
	print_unsigned,
	print_unsigned_long,
	print_str,
	print_address,
	calc_printed,
	print_float,
	print_float,
	print_binary,
	print_binary,
	print_uppercase_number
};

#endif

/* 	exit_codes
1	ft_itoa.c malloc
2	ft_itoa.c neg_itoa malloc
3	ft_itoa.c zero_itoa malloc
4	ft_lstnew.c malloc
5	ft_lstnew.c content malloc
6	ft_memalloc malloc
7	ft_memmove.c dst/src NULL input
8	ft_strrchr.c NULL input
9	ft_strequ.c s1/s2 NULL input
10	ft_strjoin_three.c s1/s2/s3 NULL input
11	ft_strjoin.c s1/s2 NULL input
12	ft_strjoin.c malloc
13	ft_strmap.c NULL input
14	ft_strmap.c malloc
15	ft_strmapi.c NULL input
16	ft_strmapi.c malloc
17	ft_strcmp.c s1/s2 NULL input
18	ft_strcpy.c dst/src NULL input
19	ft_strncmp.c s1/s2 NULL input
20	ft_strncpy.c dst/src NULL input
21	ft_strnew.c malloc
22	ft_strsplit.c NULL input
23	ft_strsplit.c char** malloc
24	ft_strsplit.c char* malloc
25	ft_strsub.c NULL input
26	ft_strsub.c malloc
27	ft_strtrim.c NULL input
28	ft_strtrim.c malloc
29	ft_atoi.c NULL input
30	ft_memccpy.c dst/src NULL input
31	ft_memchr.c NULL input
32	ft_memcmp.c s1/s2 NULL input
33	ft_memcpy.c dst/src NULL input
34	ft_memset.c	dst NULL
35	ft_strcat.c s1/s2 NULL input
36	ft_strchr.c NULL input
37	ft_strcount.c NULL input
38	ft_strlcat.c dst/src NULL input
39	ft_strlen_match.c NULL input
40	ft_strlen.c NULL input
41	ft_strncat.c s1/s2 NULL input
42	ft_strdup.c NULL input
43	ft_strdup.c malloc
44	ft_bzero.c NULL input
45	ft_strstr.c haystack/needle NULL input
46	ft_strnstr.c haystack/needle NULL input
47	ft_create_strarray malloc
*/
