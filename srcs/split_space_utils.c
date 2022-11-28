/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   split_space_utils.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dabey <dabey@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/18 22:01:32 by dabey             #+#    #+#             */
/*   Updated: 2022/11/26 17:29:44 by dabey            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	lenght_of_word(char *s, char sep)
{
	int		len_w;
	char	quote_tp;

	len_w = 0;
	while (*s && *s != sep)
		if (*s && (*s == '\"' || *s == '\''))
		{
			len_w++;
			quote_tp = *s;
			s++;
			while (*s && *s != quote_tp)
			{
				s++;
				len_w++;
			}
		s++;
		len_w++;
	}
	else if (*s && *s != sep)
	{
		while (*s && *s != '\'' && *s != '\"' && *s != ' ')
		{
			len_w++;
			s++;
		}
	}
	return (len_w);
}

int	ft_count_word(char *s, char sep)
{
	char	quote_tp;
	int		count_w;

	count_w = 0;
	while (*s)
	{
		if (*s && (*s == '\"' || *s == '\''))
		{
			quote_tp = *s;
			s++;
			while (*s && *s != quote_tp)
				s++;
		}
		if (*s == sep)
			++count_w;
		s++;
	}
	return (++count_w);
}

char	**ft_split_quote(char *buffer, char c)
{
	int		i;
	int		j;
	char	**tab;
	char	quote_tp; 
	int		count_w;

	i = 0;
	if (!buffer)
		return (0);
	count_w = ft_count_word(buffer, '|');
	tab = (char **)malloc((count_w + 1) * sizeof(char *));
	if (!(tab))
		return (0);
	while (i < count_w)
	{
		j = 0;
		while (*buffer == ' ' || *buffer == c)
			buffer++;
		tab[i] = (char *)malloc(sizeof(char) * (lenght_of_word(buffer, ' ') + 1));
		if (!tab[i])
			return (0);
		while (*buffer != c && *buffer != '\0')
		{
			while (*buffer && *buffer == ' ' && *(buffer - 1) == ' ')
			  buffer++;
			if (*buffer && (*buffer == '\"' || *buffer == '\''))
			{
				quote_tp = *buffer;
				tab[i][j++] = *buffer++;
				while (*buffer && *buffer != quote_tp)
					tab[i][j++] = *buffer++;//probleme d'invalid read
				tab[i][j++] = *buffer++;
			}
			while (*buffer && *buffer == ' ')
				buffer++;
		}
		tab[i++][j] = '\0';
	}
	tab[i] = 0;
	return (tab);
}



/*
int	lenght_of_word(char const *s, char sep)
{
	int		len_w;
	char	quote_tp;

	len_w = 0;
	// int i = 0;
	while (*s && *s != sep) // c = |
	{
		// while (*s && *s == ' ')
		// 	s++;
		if (*s && (*s == '\"' || *s == '\''))
		{
			len_w++;
			quote_tp = *s;
			s++;
			while (*s && *s != quote_tp)
			{
				s++;
				len_w++;
				// printf("i_quote = %d\n", ++i);
			}
			s++;
			len_w++;
		}
		else if (*s && *s != sep)
		{
			while (*s && *s != '\'' && *s != '\"' && *s != ' ')
			{
				len_w++;
				// printf("i_text = %d\n", ++i);
				s++;
			}
		}	
	}
	printf("@ len_word = %d et s = %s@\n", len_w, s);
	return (len_w);
}

int	ft_count_word(char const *s, char sep)
{
	int		quote_tp;
	int		count_w;

	quote_tp = 0;
	count_w = 0;
	while (*s)
	{
		if (*s && (*s == '\"' || *s == '\''))
		{
			quote_tp = *s;
			s++;
			while (*s && *s != quote_tp)
				s++;
			s++;
			printf("& buffer = %s &\n", s);
		}
		if (*s == sep)
			{++count_w;
			printf("$ simple_word = %d et s = %s $\n", count_w, s);}
		s++;
	}
	// printf("$ simple_word = %d et s = %s$\n", count_w + 1, s);
	return (++count_w);
}


char	**ft_split_space(char *s, char c)
{
	int		i;
	int		j;
	int		count_w;
	int		quote_tp;
	char	**tab;

	i = 0;
	if (!s)
		return (NULL);
	count_w = ft_count_w_simple(s, c);
	tab = (char **)malloc((count_w + 1) * sizeof(char *));
	if (!(tab))
		return (0);
	while (i < count_w)
	{
		j = 0;
		while (*s && *s == c)
			s++;
		tab[i] = (char *)malloc(sizeof(char) * (ft_len_w_simple(s, c) + 1));
		if (!tab[i])
			return (0);
		while (*s != c && *s != '\0')
		{
			if (*s && (*s == '\"' || *s == '\''))
			{
				quote_tp = *s;
				while (*s && *s != quote_tp)
					tab[i][j++] = *s++;
				s++;
			}
			if (*s && *s == ' ' && *(s - 1) == ' ')
			{
				s++;
				tab[i][j++] = *s++;
				while (*s && *s == ' ')
					s++;
			}
			else
				tab[i][j++] = *s++;
		}
		tab[i++][j] = '\0';
	}
	tab[i] = 0;
	return (tab);
}
*/