/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: obelouch <OB-96@hotmail.com>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/09 16:30:41 by obelouch          #+#    #+#             */
/*   Updated: 2019/05/10 00:56:11 by obelouch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void		init_echo(t_echo *echo)
{
	echo->cap_e = 0;
	echo->e = 0;
	echo->n = 0;
}

/*
**	i:		0: i		1: j
*/

static int		fill_echo(char **tab, t_echo *echo)
{
	int			i[2];

	i[0] = 0;
	init_echo(echo);
	while (tab[++i[0]] && tab[i[0]][0] == '-')
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
				(tab[i[0] + 1]) ? ft_putchar(' ') : 0;
				return (i[0] + 1);
			}
		}
	}
	return (i[0]);
}

static int		print_var(char *envp[], char *var, int status)
{
	int		i;
	int		len;

	i = 0;
	len = ft_strlen(var);
	if (!(ft_strcmp(var, "?")))
		ft_putstr(ft_itoa(status));
	while (envp[i])
	{
		if (!ft_strncmp(envp[i], var, len) &&
			envp[i][len] == '=')
		{
			ft_putstr(&envp[i][len + 1]);
			return (1);
		}
		i++;
	}
	return (0);
}

static int		print_squote(char *str)
{
	int			len;

	len = ft_strlen(str) - 2;
	write(1, &str[1], len);
	return (len - 2);
}

static void		quote_affiche(char **tab, int cap_e)
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
	print_squote(str);
}

static int		tab_well_quoted(char **tab)
{
	int			i;
	int			j;
	int			s_quote;
	int			d_quote;

	i = -1;
	while (tab[++i])
	{
		j = -1;
		while (tab[i][++j])
		{
			if (tab[i][j] == 34)
				d_quote++;
			if (tab[i][j] == 39)
				s_quote++;
		}
	}
	if (!(d_quote % 2) && !(s_quote % 2))
		return (1);
	return (0);
}

static void	print_not_print(char c)
{
	if (c == 7)
		ft_putstr("\a");
	else if (c == 8)
		ft_putstr("\b");
	else if (c == 9)
		ft_putstr("\t");
	else if (c == 10)
		ft_putstr("\n");
	else if (c == 11)
		ft_putstr("\v");
	else if (c == 12)
		ft_putstr("\f");
	else if (c == 13)
		ft_putstr("\r");
	else if (c == 27)
		ft_putstr("\e");
	else if (c == 92)
		ft_putstr("\\");
	else
		ft_putchar(c);
}

static void	ft_print_e(char *str, int cap_e)
{
	int		i;

	if (cap_e == 1)
	{
		i = 0;
		while (str[i])
				print_not_print(str[i++]);
	}
	else
		ft_putstr(str);
}

int			ft_echo(char **tab, char *envp[], int status)
{
	t_echo		echo;
	int			i;

	i = fill_echo(tab, &echo);
	while (tab[i])
	{
		if (tab[i][0] == 34 || tab[i][0] == 39)
		{
			if (!tab_well_quoted(&tab[i]))
				quote_affiche(&tab[i], (echo.cap_e && !echo.e));
			else if (print_squote(tab[i]) && tab[i + 1])
				ft_putchar(' ');
		}
		else if (tab[i][0] == '$')
		{
			if (print_var(envp, &tab[i][1], status) && tab[i + 1])
				ft_putchar(' ');
		}
		else
			ft_print_e(tab[i], (echo.cap_e && !echo.e));
		i++;
	}
	if (echo.n)
		ft_printf("%{YELLOW}%%%{eoc}");
	ft_putchar('\n');
	return (0);
}
