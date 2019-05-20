/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   star.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: obelouch <OB-96@hotmail.com>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/19 20:27:55 by obelouch          #+#    #+#             */
/*   Updated: 2019/05/20 07:24:26 by obelouch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static char			**ft_star(char *path)
{
	struct dirent	*dir;
	DIR				*flux_dir;
	char			**tab;

	tab = (char**)malloc(sizeof(char*) * 1);
	tab[0] = NULL;
	if (!(flux_dir = opendir(path)))
		return (NULL);
	while ((dir = readdir(flux_dir)))
	{
		if (ft_strcmp(dir->d_name, ".") && ft_strcmp(dir->d_name, ".."))
			add_2_tab(&tab, dir->d_name);
	}
	closedir(flux_dir);
	return (tab);
}

static int			star_ret(char ***tab, char **str)
{
	free(*str);
	*str = join_from_tab(*tab, 0, " ");
	ft_trimstr(str);
	free_tabstr(tab);
	return (0);
}

int					ft_wildcard(char **str, char *path)
{
	char				**tab;
	char				*b_star;
	char				*a_star;
	int					i;

	if (!(tab = ft_star(path)))
		return (0);
	if (is_allstar(*str))
		return (star_ret(&tab, str));
	b_star = ((*str)[0] != '*') ? first_w(*str) : NULL;
	a_star = ((*str)[ft_strlen(*str) - 1] != '*') ? last_w(*str) : NULL;
	i = -1;
	while (tab[++i])
		if ((b_star && !is_fine_b(tab[i], b_star)) ||
				(a_star && !is_fine_a(tab[i], a_star)))
		{
			free(tab[i]);
			tab[i] = ft_strnew(0);
		}
	if (manage_mid(str, &b_star, &a_star))
		new_verify(&tab, *str);
	join_tab_snull(&tab, str);
	return (0);
}

void				wildcard(t_minishell *ms)
{
	char			*pwd;
	char			**tab;
	int				i;

	if (!ft_strchr(ms->cmd, '*'))
		return ;
	if (!ft_strchr(ms->cmd, '"') && !ft_strchr(ms->cmd, '\''))
	{
		tab = ft_strsplit(ms->cmd, ' ');
		pwd = ft_strnew(100);
		pwd = getcwd(pwd, 100);
		i = -1;
		while (tab[++i])
			if (ft_strchr(tab[i], '*'))
				ft_wildcard(&tab[i], pwd);
		ms->cmd = join_from_tab(tab, 0, " ");
		ms->cmd_freable = 1;
		free(pwd);
		free_tabstr(&tab);
	}
}
