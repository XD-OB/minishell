/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_echo.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: obelouch <OB-96@hotmail.com>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/12 23:07:37 by obelouch          #+#    #+#             */
/*   Updated: 2019/05/12 23:36:44 by obelouch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtins.h"

void		ft_print_sbslch(char *str)
{
	int		i;

	i = -1;
	while (str[++i])
		if (str[i] != 92)
			ft_putchar(str[i]);
}

int			print_var(char **envp, char *var)
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

void		print_ee(char *str, t_echo echo)
{
	int		i;
	int		len;

	i = (str[0] == 39 || str[0] == 34) ? 1 : 0;
	len = ft_strlen(str) - i;
	while (i < len)
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
		i++;
	}
}
