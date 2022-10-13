/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dabey <dabey@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/06 17:05:27 by dabey             #+#    #+#             */
/*   Updated: 2022/10/13 19:34:55 by dabey            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	main(void)
{
	int			j;
	int			i;
	char		*buffer;
	static char	**cmd;
	size_t		buf_size;

	i = 0;
	j = 0;
	cmd = NULL;
	buffer = NULL;
	buf_size = 2048;
	buffer = (char *)malloc(sizeof(char) * buf_size);
	if (!buffer)
	{
		perror("Malloc failure");
		return (EXIT_FAILURE);
	}
	write(1, "$> ", 3);
	while (getline(&buffer, &buf_size, stdin) > 0) // supprimer le strncmp 
	{
		// buffer = ft_one_spcae(buffer);
		// if (ft_strcmp(buffer, "exit") == 0)
		// {
		// 	printf("Bye \n");
		// 	free(buffer);
		// 	while (cmd[j] != 0)
		// 	{
		// 		free(cmd[j]);
		// 		j++;
		// 	}
		// 	printf("Exit\n");
		// 	return (0);
		// }
		cmd = ft_split(buffer, '|');
		j = 0;
		while (cmd[j] != 0)
		{
			printf("cmd = %s\n",cmd[j]);
			j++;
		}
		j = 0;
		write(1, "$> ", 3);
	}
	//if (strcmp(cmd[i], "exit") == 0)
	//	exit(0);
	return (0);
}
