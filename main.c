/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rburner <rburner@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/17 11:12:05 by rburner           #+#    #+#             */
/*   Updated: 2022/01/26 10:41:01 by rburner          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	err(char *s)
{
	ft_putstr_fd(s, 2);
	exit (1);
}

char	*ft_search(char **p, char *cmd)
{
	char	*a;
	char	*b;
	int		i;

	i = -1;
	while (p[++i])
	{
		a = ft_strjoin(p[i], "/");
		if (!a)
			return (NULL);
		b = ft_strjoin(a, cmd);
		if (!b)
		{
			free (a);
			return (NULL);
		}
		free(a);
		if (access(b, 0) == 0)
			break ;
		free (b);
		b = NULL;
	}
	return (b);
}

char	**ft_path(char **envp)
{
	int		i;
	char	**c;

	i = 0;
	c = NULL;
	while (envp[i] && strncmp(envp[i], "PATH=", 5))
		i++;
	if (envp[i])
		c = ft_split(envp[i] + 5, ':');
	else
		err("PATH is unseted\n");
	return (c);
}

int	pipex(char **av, char **envp)
{
	int		pid[2];
	char	**p;
	int		fd[2];

	if (pipe(fd) == -1)
		err("pipe error\n");
	p = ft_path(envp);
	if (p == NULL)
		err("Error path not found\n");
	pid[0] = fork();
	if (pid[0] < 0)
		return (1);
	if (pid[0] == 0)
		child_process(p, envp, av, fd);
	pid[1] = fork();
	if (pid[1] < 0)
		return (1);
	if (pid[1] == 0)
		parent_process(p, av, fd, envp);
	close(fd[0]);
	free_array(p);
	return (1);
}

int	main(int ac, char **av, char **envp)
{
	int	fd;

	if (ac == 5)
	{
		fd = open(av[1], O_RDONLY);
		if (fd < 0)
		{
			write(2, "file not found!\n", 17);
			return (1);
		}
		close(fd);
		pipex(av, envp);
	}
	else if (ac > 5)
		write (2, "many arguments", 15);
	else
		write (2, "few arguments", 14);
	return (0);
}
