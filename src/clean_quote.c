/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   clean_quote.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: obelouch <obelouch@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/17 22:29:55 by obelouch          #+#    #+#             */
/*   Updated: 2019/05/19 20:20:55 by obelouch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void		infinte_read(char **str, char q)
{
	char		*line;
	int			len;

	while (1)
	{
		(q == '"') ?
			ft_printf("%{CYAN}dquote%{YELLOW}> %{eoc}") :
			ft_printf("%{CYAN}quote%{YELLOW}> %{eoc}");
		if (get_next_line(0, &line) == -1)
			break ;
		if (ft_strchr(line, q))
		{
			len = ft_strlen(line) - 1;
			while (line[len] != q && len > 0)
				len--;
			line[len] = '\0';
			ft_strcombin(str, line);
			ft_strcombin(str, "\n");
			free(line);
			break ;
		}
		ft_strcombin(str, line);
		ft_strcombin(str, "\n");
		free(line);
	}
}

static void		from_secondchar(char **str)
{
	char		*tmp;

	tmp = *str;
	*str = ft_strdup(&(*str)[1]);
	free(tmp);
}

static void		qclean_tab(char **tab)
{
	char		*tmp;
	int			len;
	char		q;
	int			i;

	i = 0;
	while (tab[i])
	{
		q = -1;
		if (tab[i][0] == '"' || tab[i][0] == '\'')
		{
			q = tab[i][0];
			from_secondchar(&tab[i]);
			len = ft_strlen(tab[i]);
			if (tab[i][len - 1] != q)
				infinte_read(&tab[i], q);
			else
			{
				tmp = tab[i];
				tab[i] = ft_strndup(tab[i], len - 1);
				free(tmp);
			}
		}
		i++;
	}
}

static void		sqclean_tab(char **tab)
{
	char		*tmp;
	int			len;
	char		q;
	int			i;

	i = 0;
	while (tab[i])
	{
		q = -1;
		if (tab[i][0] == '"' || tab[i][0] == '\'')
		{
			q = tab[i][0];
			len = ft_strlen(tab[i]);
			if (tab[i][len - 1] != q)
				infinte_read(&tab[i], q);
			else
			{
				tmp = tab[i];
				tab[i] = ft_strdup(tab[i]);
				free(tmp);
			}
		}
		i++;
	}
}

char			**clean_cmds(char *cmd, int mode)
{
	char		**tab;
	int			i;

	if (well_quoted(cmd))
		tab = ft_split_quote(cmd);
	else
		tab = ft_split_invquote(cmd);
	if (!mode)
		sqclean_tab(tab);
	else
		qclean_tab(tab);
	i = -1;
	while (tab[++i])
		ft_trimstr(&tab[i]);
	return (tab);
}
