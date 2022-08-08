/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   process.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rburner <rburner@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/21 00:31:42 by rburner           #+#    #+#             */
/*   Updated: 2022/01/26 10:42:14 by rburner          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	free_array(char **arr)
{
	int	i;

	i = 0;
	while (arr[i])
	{
		free(arr[i]);
		i++;
	}
	free(arr);
}

int	child_process(char **p, char **envp, char **av, int *fd)
{
	char	**fl;
	char	*cmd;
	int		k;

	k = 0;
	fl = ft_split(av[2], ' ');
	while (fl[k])
		k++;
	fl[k] = av[1];
	cmd = ft_search(p, fl[0]);
	if (!cmd)
		err("command doesn't exist\n");
	if (dup2(fd[1], 1) < 0)
		err(":p\n");
	exit(execve(cmd, fl, envp));
}

int	parent_process(char **p, char **av, int *fd, char **envp)
{
	int		fout;
	char	**fl2;
	char	*cmd1;
	int		k;

	k = 0;
	fl2 = ft_split(av[3], ' ');
	cmd1 = ft_search(p, fl2[0]);
	if (!cmd1)
		err("command doesn't exist\n");
	fout = open(av[4], O_CREAT | O_RDWR | O_TRUNC, 0777);
	close(fd[1]);
	if (dup2(fd[0], 0) < 0)
		err(":p\n");
	if (dup2(fout, 1) < 0)
		err(":p\n");
	exit(execve(cmd1, fl2, envp));
}
