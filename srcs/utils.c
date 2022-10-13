/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dabey <dabey@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/13 15:37:17 by dabey             #+#    #+#             */
/*   Updated: 2022/10/13 19:20:55 by dabey            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

// char	*t_one_spcae(char *buffer)
// {
// 	int		i;
// 	char	c;

// 	c = ' ';
// 	i = 0;
// 	if (!buffer)
// 		return (0);
// 	while (buffer[i] && buffer[i] != c)
// 		i++;
// 	while
	
// }

int	ft_strcmp(char *s1, char *s2)
{
	size_t i;

	i = 0;
	while ((s1[i] || s2[i]))
	{
		if (s1[i] != s2[i])
			return ((unsigned char)s1[i] - (unsigned char)s2[i]);
		i++;
		// printf("passe dans cmp\n");
	}
	printf("cmp==0\n");
	return (0);
}

static size_t	ft_len_w(char const *s, char c)
{
	size_t	len_w;

	len_w = 0;
	while (*s != c && *s != '\0')
	{
		len_w++;
		s++;
	}
	return (len_w);
}

static size_t	ft_count_w(char const *s, char c)
{
	size_t	count_w;

	count_w = 0;
	while (*s)
	{
		while (*s == c)
			s++;
		if (*s != '\0')
			count_w++;
		while (*s != c && *s != '\0')
			s++;
	}
	return (count_w);
}

char	**ft_split(char *s, char c)
{
	size_t	i;
	size_t	j;
	size_t	count_w;
	char	**tab;

	i = 0;
	if (!s)
		return (NULL);
	count_w = ft_count_w(s, c);
	tab = (char **)malloc((count_w + 1) * sizeof(char *));
	if (!(tab))
		return (0);
	while (i < count_w)
	{
		j = 0;
		while (*s == ' ' || *s == c)
			s++;
		tab[i] = (char *)malloc(sizeof(char) * (ft_len_w(s, c) + 1));
		if (!tab[i])
			return (0);
		while (*s != c && *s != '\0')
		{
			while (*s && *s == ' ' && *(s - 1) == ' ')
			{
				s++;
				// printf("s - 1 = |%c|\t", *(s - 1));
			}
			tab[i][j++] = *s++;
			while (*s && *s == ' ' && *(s - 1) == ' ')
				s++;
		}
		tab[i++][j] = '\0';
	}
	tab[i] = 0;
	return (tab);
}
