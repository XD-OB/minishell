/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   setenv.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: obelouch <OB-96@hotmail.com>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/10 18:53:23 by obelouch          #+#    #+#             */
/*   Updated: 2019/05/12 23:55:58 by obelouch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtins.h"

static int	error_len(char **envp, int len_t)
{
	if (len_t > 3)
		return (1);
	if (len_t == 1)
	{
		show_env(envp);
		return (1);
	}
	return (0);
}

static int	set_var_value(char **av, char **envp, char **var, char **val)
{
	char	**tmp;
	int		len_t;

	len_t = len_tab(av);
	if (error_len(envp, len_t))
		return (0);
	if (len_t == 2)
	{
		if (ft_strchr(av[1], '='))
		{
			tmp = ft_strsplit(av[1], '=');
			affect_chars(var, val, tmp[0], tmp[1]);
			free_tabstr(&tmp);
		}
		else
			affect_chars(var, val, av[1], "");
	}
	else
		affect_chars(var, val, av[1], av[2]);
	return (1);
}

static void	add_var_env(char **envp, char **new, char *var, char *value)
{
	if (!*new)
	{
		*new = ft_strjoin(var, "=");
		ft_strcombin(new, value);
		envp[0] = ft_strdup(*new);
		envp[1] = NULL;
	}
}

int			main(int ac, char **av, char **envp)
{
	char	*new;
	char	*var;
	char	*value;
	int		len_var;
	int		i;

	i = -1;
	if (!set_var_value(av, envp, &var, &value))
			return (1);
	len_var = ft_strlen(var);
	while (envp[++i])
	{
		if (!ft_strncmp(envp[i], var, len_var))
		{
			new = ft_strjoin(var, "=");
			ft_strcombin(&new, value);
			ft_strclr(envp[i]);
			ft_strcpy(envp[i], new);
			break ;
		}
	}
	add_var_env(&envp[i], &new, var, value);
	ft_putendl(envp[i]);
	triple_free(&new, &var, &value);
	return (0);
}
