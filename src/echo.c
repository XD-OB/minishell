/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: obelouch <OB-96@hotmail.com>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/09 16:30:41 by obelouch          #+#    #+#             */
/*   Updated: 2019/05/09 17:10:28 by obelouch         ###   ########.fr       */
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

static int		print_var(char *envp[], char *var)
{
	int		i;
	int		len;

	i = 0;
	len = ft_strlen(var);
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

int			ft_echo(char **tab, char *envp[])
{
	t_echo		echo;
	int			i;

	i = fill_echo(tab, &echo);
	while (tab[i])
	{
		if (tab[i][0] == '$')
		{
			if (print_var(envp, &tab[i][1]) && tab[i + 1])
				ft_putchar(' ');
		}
		else
		{
			ft_putstr(tab[i]);
			if (tab[i + 1])
				ft_putchar(' ');
		}
		i++;
	}
	if (echo.n)
		ft_printf("%{YELLOW}%%%{eoc}");
	ft_putchar('\n');
	return (0);
}
