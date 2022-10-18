/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dabey <dabey@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/06 17:05:27 by dabey             #+#    #+#             */
/*   Updated: 2022/10/18 19:39:41 by dabey            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	main(void)
{
	int			j;
	int			i;
	t_list		*list;

	i = 0;
	j = 0;
	list = NULL;
	list = ft_init(list);
	write(1, "$> ", 3);
	while (getline(&list->buffer, &list->buf_size, stdin) > 0) // supprimer le strncmp 
	{
		// using_history();
		// add_history(buffer);
		list->cmd = ft_split(list->buffer, '|');
		j = 0;
		while (list->cmd[j] != 0)
		{
			printf("cmd = %s\n",list->cmd[j]);
			j++;
		}
		j = 0;
		write(1, "$> ", 3);
	}
	//if (strcmp(cmd[i], "exit") == 0)
	//	exit(0);
	return (0);
}
