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

static int		print_squote(char *str, t_echo echo)
{
	int			i;
	int			len;

	if (!echo.e)
	{
		len = ft_strlen(str) - 2;
		write(1, &str[1], len);
		return (len - 2);
	}
	i = 0;
	len = 0;
	while (str[++i])
	{
		if (str[i] == 92)
		{
			i++;
			if (str[i] == 't')
				ft_putchar(9);
			else if (str[i] == 'a')
				ft_putchar(7);
			else if (str[i] == 'b')
				ft_putchar(8);
			else if (str[i] == 'n')
				ft_putchar(10);
			else if (str[i] == 'v')
				ft_putchar(11);
			else if (str[i] == 'f')
				ft_putchar(12);
			else if (str[i] == 'r')
				ft_putchar(13);
			else if (str[i] == 'e')
				ft_putchar(27);
			else if (str[i] == 92)
				ft_putchar(92);
			else
				ft_putchar(str[i]);
		}
		else
			ft_putchar(str[i]);
		len++;
	}
	return(len);
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
	print_squote(str, echo);
}

static int		tab_well_quoted(char **tab)
{
	int			i;
	int			j;
	int			s_quote;
	int			d_quote;

	i = 0;
	while (tab[i])
	{
		j = 0;
		while (tab[i][j])
		{
			if (tab[i][j] == 34)
				d_quote++;
			if (tab[i][j] == 39)
				s_quote++;
			j++;
		}
		i++;
	}
	if (!(d_quote % 2) && !(s_quote % 2))
		return (1);
	return (0);
}

static void	ft_print_e(char *str)
{
	int		i;

	i = -1;
	while (str[++i])
		if (str[i] != 92)
			ft_putchar(str[i]);
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
				quote_affiche(&tab[i], echo);
			if (print_squote(tab[i], echo) && tab[i + 1])
				ft_putchar(' ');
		}
		else if (tab[i][0] == '$')
		{
			if (print_var(envp, &tab[i][1], status) && tab[i + 1])
				ft_putchar(' ');
		}
		else
			ft_print_e(tab[i]);
		i++;
	}
	if (echo.n)
		ft_printf("%{YELLOW}%%%{eoc}");
	ft_putchar('\n');
	return (0);
}
