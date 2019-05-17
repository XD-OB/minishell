/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_echo.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: obelouch <OB-96@hotmail.com>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/12 20:29:34 by obelouch          #+#    #+#             */
/*   Updated: 2019/05/17 02:28:15 by obelouch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void		init_echo(t_echo *echo)
{
	echo->cap_e = 0;
	echo->e = 0;
	echo->n = 0;
}

static int		echo_opts(char **tab, t_echo *echo, int i, int j)
{
	if (tab[i][j] == 'n')
		echo->n = 1;
	else if (tab[i][j] == 'e')
		echo->e = 1;
	else if (tab[i][j] == 'E')
		echo->cap_e = 1;
	else if (!ft_strcmp(&tab[i][j], "-help"))
	{
		ft_printf("usage: echo [-option] [string ...]\n");
		ft_printf("       echo [--help] [--version]\n");
		return (-10);
	}
	else if (!ft_strcmp(&tab[i][j], "-version"))
	{
		ft_printf("-obsh V1.0: all rights are reserved");
		ft_printf(" to obelouch 2019\n");
		return (-10);
	}
	else
		return (0);
	return (1);
}

static int		fill_echo(int size, char **tab, t_echo *echo)
{
	int			i;
	int			j;
	int			k;

	i = 0;
	init_echo(echo);
	while (++i < size && tab[i][0] == '-')
	{
		j = 0;
		while (tab[i][++j])
		{
			k = echo_opts(tab, echo, i, j);
			if (k == 0)
			{
				init_echo(echo);
				ft_putstr(tab[i]);
				(i < size - 1) ? ft_putchar(' ') : 0;
				return (i);
			}
			if (k == -10)
				return (-10);
		}
	}
	return (i - 1);
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
			(tab[i][j] == 34) ? d_quote++ : 0;
			(tab[i][j] == 39) ? s_quote++ : 0;
		}
		if (!(d_quote % 2) && !(s_quote % 2))
			return (1);
	}
	return (0);
}

int				ft_echo(int ac, char **av, char **envp, int *last)
{
	t_echo		echo;
	int			i;

	if ((i = fill_echo(ac, av, &echo)) == -1)
		return (0);
	while (++i < ac)
	{
		if (av[i][0] == '$')
			print_var(envp, &av[i][1], last);
		else if (av[i][0] == 34 || av[i][0] == 39)
		{
			if (!tab_well_quoted(&av[i]) && !quote_affiche(&av[i], echo))
				return ((*last = 1));
			else
				print_ee(av[i], echo);
		}
		else
			ft_print_sbslch(av[i]);
		(i < ac - 1) ? ft_putchar(' ') : 0;
	}
	(echo.n) ? ft_printf("%{YELLOW}%%%{eoc}") : 0;
	ft_putchar('\n');
	*last = 0;
	return (0);
}
