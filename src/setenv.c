/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   setenv.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: obelouch <OB-96@hotmail.com>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/10 18:53:23 by obelouch          #+#    #+#             */
/*   Updated: 2019/05/10 19:07:58 by obelouch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	set_var_value(char *cmd, char **var, char **val)
{
	char	**tab;

	tab = ft_strsplit(cmd, ' ');
	tmp = tab[0];
	tab++;
	free(tmp);
	if (len_tab(tab) > 2 || len_tab(tab) <= 0)
			return (0);
	if (len_tab(tab) == 1)
	{
		if (!ft_strchr(tab[0], "="))
			return (0);
	}
	return (1);
}

void		ft_setenv(char **envp, char *cmd)
{
	char	*new;
	char	*var;
	char	*value;
	int		len_var;
	int		i;

	i = 0;
	new = NULL;
	if (!set_var_value(cmd, &var, &value))
			return (1);
	len_var = ft_strlen(var);
	while (envp[i])
	{
		if (!ft_strncmp(envp[i], var, len_var))
		{
			new = ft_strjoin(var, "=");
			ft_strcombin(&new, value);
			ft_strclr(envp[i]);
			ft_strcpy(envp[i], new);
			break ;
		}
		i++;
	}
	if (!new)
	{
		new = ft_strjoin(var, "=");
		ft_strcombin(&new, value);
		ft_strclr(envp[i]);
		ft_strcpy(envp[i], new);
	}
	free(value);
	free(new);
	free(var);
}
