#include "../includes/libft.h"

void	print_cipher(char *str, int key);
void	cipher_char(char orig, int key);

int main(int argc, char **argv)
{
	int		key;
	char	*plain;
	char	*cipher;

	if (argc != 2)
	{
		ft_printf("Usage: %s key\n", argv[0]);
		return (1);
	}

	key = ft_atoi(argv[1]);
	if (key < 1 || argc > 2)
	{
		ft_printf("Usage: %s key\n", argv[0]);
		return (1);
	}

	ft_printf("plaintext:  ");
	get_next_line(0, &plain);

	ft_printf("ciphertext: ");
	print_cipher(plain, key);
	return (0);
}

void	print_cipher(char *str, int key)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (ft_isalpha(str[i]))			// a-z or A-Z
			cipher_char(str[i], key);
		else
			ft_printf("%c", str[i]);
		i++;
	}
	ft_printf("\n");
}

void	cipher_char(char orig, int key)
{
	while (key > 0)
	{
		orig++;
		if (orig == 91 || orig == 123)	// from z/Z back to a/A
			orig -= 26;
		key--;
	}
	ft_printf("%c", orig);
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
