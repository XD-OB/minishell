/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   clean_quote.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: obelouch <OB-96@hotmail.com>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/17 22:29:55 by obelouch          #+#    #+#             */
/*   Updated: 2019/05/18 23:42:43 by obelouch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int			fail_qtest(char *cmd)
{
	int		i;

	i = 0;
	while (cmd[i] && cmd[i + 1])
	{
		if ((cmd[i] == 34 || cmd[i] == 39) && cmd[i + 1] == '-')
			return (1);
		i++;
	}
	return (0);
}

void		infinte_read(char **str, char q)
{
	char	*line;
	int		len;

	while (1)
	{
		if (q == '"')
			ft_printf("%{CYAN}dquote%{YELLOW}> %{eoc}");
		else
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
			free(line);
			break ;
		}
		ft_strcombin(str, line);
		free(line);
	}
}

static void	from_secondchar(char **str)
{
	char		*tmp;

	tmp = *str;
	*str = ft_strdup(&(*str)[1]);
	free(tmp);
}

void		qclean_tab(char **tab)
{
	char			*tmp;
	int				len;
	char			q;
	int				i;

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

char		**clean_cmds(char *cmd)
{
	char	**tab;

	if (well_quoted(cmd))
		tab = ft_split_quote(cmd);
	else
		tab = ft_split_invquote(cmd);
	qclean_tab(tab);
	return (tab);
}
