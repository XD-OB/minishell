/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_echo.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: obelouch <OB-96@hotmail.com>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/16 01:56:20 by obelouch          #+#    #+#             */
/*   Updated: 2019/05/16 07:26:47 by obelouch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void			ft_print_sbslch(char *str)
{
	int			i;

	i = 0;
	while (str[i])
	{
		if (str[i] != 92)
			ft_putchar(str[i]);
		i++;
	}
}

int				print_var(char **envp, char *var, int *last)
{
	int			i;
	int			len;

	i = -1;
	if (!ft_strcmp(var, "$"))
	{
		ft_putnbr(getpid());
		return (1);
	}
	else if (!ft_strcmp(var, "?"))
	{
		ft_putnbr(*last);
		return (1);
	}
	len = ft_strlen(var);
	while (envp[++i])
	{
		if (!ft_strncmp(envp[i], var, len) &&
				envp[i][len] == '=')
		{
			ft_putstr(&envp[i][len + 1]);
			return (1);
		}
	}
	return (0);
}

void			print_ee(char *str, t_echo echo)
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

int				quote_affiche(char **tab, t_echo echo)
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
	ft_putchar('\n');
	return (0);
}
