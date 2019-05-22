/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: obelouch <obelouch@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/12 20:29:34 by obelouch          #+#    #+#             */
/*   Updated: 2019/05/22 22:42:04 by obelouch         ###   ########.fr       */
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

static int		fill_echo(int len_t, char **tab, t_echo *echo)
{
	int			i;
	int			j;
	int			k;

	i = 0;
	init_echo(echo);
	while (++i < len_t && tab[i][0] == '-')
	{
		j = 0;
		while (tab[i][++j])
		{
			k = echo_opts(tab, echo, i, j);
			if (k == 0)
			{
				init_echo(echo);
				ft_putstr(tab[i]);
				(i < len_t - 1) ? ft_putchar(' ') : 0;
				return (i);
			}
			if (k == -10)
				return (-10);
		}
	}
	return (i - 1);
}

static void		print_ee(char *str, t_echo echo)
{
	int			i;
	char		q;
	int			len;

	q = str[0];
	i = (q == 39 || q == 34) ? 0 : -1;
	len = ft_strlen(str) - i;
	while (str[++i] && str[i] != q)
	{
		if ((!echo.cap_e || echo.e) && str[i] == 92
				&& ft_strchr("tabnvfre\\", str[++i]))
		{
			(str[i] == 't') ? ft_putchar(9) : 0;
			(str[i] == 'a') ? ft_putchar(7) : 0;
			(str[i] == 'b') ? ft_putchar(8) : 0;
			(str[i] == 'n') ? ft_putchar(10) : 0;
			(str[i] == 'v') ? ft_putchar(11) : 0;
			(str[i] == 'f') ? ft_putchar(12) : 0;
			(str[i] == 'r') ? ft_putchar(13) : 0;
			(str[i] == 'e') ? ft_putchar(27) : 0;
			(str[i] == 92) ? ft_putchar(92) : 0;
		}
		else
			ft_putchar(str[i]);
	}
}

int				ft_echo(t_minishell *ms)
{
	t_echo		echo;
	int			len_t;
	int			i;

	echo.tab = clean_cmds(ms->cmd, 0);
	len_t = len_tab(echo.tab);
	if ((i = fill_echo(len_t, echo.tab, &echo)) == -1)
	{
		free_tabstr(&echo.tab);
		return (0);
	}
	while (++i < len_t)
	{
		(echo.tab[i][0] == 34 || echo.tab[i][0] == 39) ?
			print_ee(echo.tab[i], echo) :
			print_sbslch(echo.tab[i]);
		(i < len_t - 1) ? ft_putchar(' ') : 0;
	}
	(echo.n) ? ft_printf("%{YELLOW}%%%{eoc}\n") : ft_putchar('\n');
	free_tabstr(&echo.tab);
	return (0);
}
