/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: obelouch <OB-96@hotmail.com>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/12 20:29:34 by obelouch          #+#    #+#             */
/*   Updated: 2019/05/12 23:36:32 by obelouch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtins.h"

void			print_ee(char *str, t_echo echo);
int				print_var(char **envp, char *var);
void			ft_print_sbslch(char *str);

static void		init_echo(t_echo *echo)
{
	echo->cap_e = 0;
	echo->e = 0;
	echo->n = 0;
}

/*
**	i:		0: i		1: j
*/

static int		fill_echo(int size, char **tab, t_echo *echo)
{
	int			i[2];

	i[0] = 0;
	init_echo(echo);
	while (++i[0] < size && tab[i[0]][0] == '-')
	{
		i[1] = 0;
		while (tab[i[0]][++i[1]])
		{
			if (tab[i[0]][i[1]] == 'n')
				echo->n = 1;
			else if (tab[i[0]][i[1]] == 'e')
				echo->e = 1;
			else if (tab[i[0]][i[1]] == 'E')
				echo->cap_e = 1;
			else
			{
				init_echo(echo);
				ft_putstr(tab[i[0]]);
				(i[0] < size - 1) ? ft_putchar(' ') : 0;
				return (i[0]);
			}
		}
	}
	return (i[0] - 1);
}

static void		quote_affiche(char **tab, t_echo echo)
{
	char		*str;
	char		*tmp;
	int			q;

	str = ft_strdup(tab[0]);
	q = (tab[0][0] == 34) ? 2 : 1;
	while (1)
	{
		ft_putstr((q == 2) ? "dquote> " : "quote> ");
		get_next_line(0, &tmp);
		ft_strcombin(&str, "\n");
		ft_strcombin(&str, tmp);
		if (ft_strchr(tmp, (q == 2) ? 34 : 39))
		{
			free(tmp);
			break ;
		}
		free(tmp);
	}
	print_ee(str, echo);
}

static int		tab_well_quoted(char **tab)
{
	int			d_quote;
	int			s_quote;
	int			i;
	int			j;

	i = -1;
	while (tab[++i])
	{
		j = -1;
		s_quote = 0;
		d_quote = 0;
		while (tab[i][++j])
		{
			if (tab[i][j] == 34)
				d_quote++;
			if (tab[i][j] == 39)
				s_quote++;
		}
		if (!(d_quote % 2) && !(s_quote % 2))
			return (1);
	}
	return (0);
}

int				main(int ac, char **av, char *envp[])
{
	t_echo		echo;
	int			i;

	i = fill_echo(ac, av, &echo);
	while (++i < ac)
	{
		if (av[i][0] == '$')
			print_var(envp, &av[i][1]);
		else if (av[i][0] == 34 || av[i][0] == 39)
		{
			if (!tab_well_quoted(&av[i]))
				quote_affiche(&av[i], echo);
			else
				print_ee(av[i], echo);
		}
		else
			ft_print_sbslch(av[i]);
		if (i < ac - 1)
			ft_putchar(' ');
	}
	if (echo.n)
		ft_printf("%{YELLOW}%%%{eoc}");
	ft_putchar('\n');
	return (0);
}
