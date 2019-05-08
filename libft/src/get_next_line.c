/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: obelouch <OB-96@hotmail.com>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/17 18:19:36 by obelouch          #+#    #+#             */
/*   Updated: 2019/05/03 02:45:18 by obelouch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_gnl		*node_search(t_gnl *list, int fd)
{
	t_gnl	*curr;

	curr = list;
	while (curr)
	{
		if (curr->fd == fd)
			return (curr);
		curr = curr->next;
	}
	return (NULL);
}

int			ft_linelen(char *str)
{
	int		len;

	len = 0;
	while (str[len] != '\0' && str[len] != '\n')
		len++;
	return (len);
}

int			prepare_next(t_gnl *node)
{
	char	*tmp;
	int		i;

	i = 0;
	if (!(node->content[ft_linelen(node->content)]))
		return (0);
	tmp = node->content;
	while (tmp[i] != '\n' && tmp[i])
		i++;
	node->content = ft_strdup(&tmp[++i]);
	free(tmp);
	return (1);
}

void		join_content(t_gnl **node, char *buff, int size)
{
	char	*tmp;

	buff[size] = '\0';
	tmp = (*node)->content;
	(*node)->content = ft_strnjoin(tmp, buff, size);
	free(tmp);
}

int			get_next_line(const int fd, char **line)
{
	char			buff[BUFF_SIZE + 1];
	static t_gnl	*list = NULL;
	t_gnl			*node;
	int				ret;

	if (fd < 0 || BUFF_SIZE < 1 || !line
			|| read(fd, buff, 0) < 0)
		return (-1);
	node = node_search(list, fd);
	if (!list || !node)
	{
		node = (t_gnl*)malloc(sizeof(t_gnl));
		node->content = ft_strnew(0);
		node->fd = fd;
		node->next = list;
		list = node;
	}
	while (!(ft_strchr(node->content, '\n'))
			&& (ret = read(fd, buff, BUFF_SIZE)) > 0)
		join_content(&node, buff, ret);
	*line = ft_strsub(node->content, 0,
			ft_linelen(node->content));
	return (prepare_next(node));
}
