#include "minishell.h"

static void	div_path(char *cmd, char **dir, char **file)
{
	int	i;

	i = ft_strlen(cmd);
	while (--i >= 0)
		if (cmd[i] == '/')
			break ;
	if (i > 0)
	{
		*dir = ft_strndup(cmd, i);
		*file = ft_strdup(&cmd[i + 1]);
	}
	else
		*file = ft_strdup(cmd);
}

static char	**tab_dirs(char *path)
{
	char	**dirs;
	char	*tmp;
	int	i;

	i = 0;
	dirs = ft_strsplit(path, '/');
	while (dirs[++i])
	{
		ft_strcombin(&dirs[i - 1], "/");
		tmp = dirs[i];
		dirs[i] = ft_strjoin(dirs[i - 1], dirs[i]);
		free(tmp);
	}
	return (dirs);
}

static int	check_file(char *cmd, char *dir_exec, char *file)
{
	struct dirent	*dir;
	struct stat	status;
	DIR		*flux_dir;

	if (!(flux_dir = opendir(dir_exec)))
		return (-2);
	while ((dir = readdir(flux_dir)))
	{
		if (!ft_strcmp(dir->d_name, file))
		{
			stat(cmd, &status);
			if (!(S_IXUSR & status.st_mode))
				return (-2);
			return (0);
		}
	}
	return (-1);
}

static int	fine_file(char *cmd, char *path_dir, char *file)
{
	struct dirent	*dir;
	struct stat	status;
	char		**dirs;
	DIR		*flux_dir;
	int		i;

	i = -1;
	dirs = tab_dirs(path_dir);
	while (dirs[++i + 1])
	{
		if (!(flux_dir = opendir(dirs[i])))
			return (-2);
		while ((dir = readdir(flux_dir)))
		{
			if (!ft_strcmp(dir->d_name, dirs[i + 1])
				&& dir->d_type == DT_DIR)
				break ;
		}
		stat(cmd, &status);
		if (!(S_IXUSR & status.st_mode))
			return (-2);
		if (!dir)
			return (-1);
	}
	return (check_file(cmd, dirs[i], file));
}

int	cmd_user(char ***tab, char *envp[])
{
	char	*dir;
	char	*file;
	int	ret;

	if (ft_strchr((*tab)[0], '/'))
	{
		div_path((*tab)[0], &dir, &file);
		ret = fine_file((*tab)[0], dir, file);
		if (ret == -1)
			ft_printf("%s: file not found\n", (*tab)[0]);
		else if (ret == -2)
			ft_printf("%s: Permission denied\n", (*tab)[0]);
		else
			execve((*tab)[0], *tab, envp);
		free(dir);
		free(file);
		free_tabstr(*tab);
		return (1);
	}
	return (0);
}
