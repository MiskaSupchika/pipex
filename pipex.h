/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rburner <rburner@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/13 02:48:45 by rburner           #+#    #+#             */
/*   Updated: 2022/01/26 07:27:25 by rburner          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_H
# define PIPEX_H

# include <stdio.h>
# include <unistd.h>
# include <stdlib.h>
# include <fcntl.h>
# include <string.h>
# include "./libft/libft.h"

int		child_process(char **p, char **envp, char **av, int *fd);
int		parent_process(char **p, char **av, int *fd, char **envp);
char	*ft_search(char **p, char *cmd);
void	err(char *s);
void	free_array(char **arr);
#endif