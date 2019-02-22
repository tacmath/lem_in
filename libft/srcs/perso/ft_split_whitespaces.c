/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   ft_split_whitespaces.c                           .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: lperron <marvin@le-101.fr>                 +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2018/08/08 14:43:42 by lperron      #+#   ##    ##    #+#       */
/*   Updated: 2018/10/05 11:17:29 by lperron     ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include <stdlib.h>

static void		compute_words(char *str, int *nb_words)
{
	int i;

	i = -1;
	*nb_words = 0;
	while (str[++i] != '\0')
	{
		if (str[i] != 9 && str[i] != ' ' && str[i] != '\n' && *nb_words == 0)
			*nb_words = 1;
		if (str[i] != 9 && str[i] != ' ' && str[i] != '\n')
			;
		else
		{
			while (str[++i] == 9 || str[i] == ' ' || str[i] == '\n')
				;
			if (str[i] == '\0')
				return ;
			else
			{
				*nb_words = *nb_words + 1;
				i--;
			}
		}
	}
	return ;
}

static int		compute_size(char *s, int word, int i, int size)
{
	int nb_words;

	nb_words = -1;
	while ((s[++i] == 9 || s[i] == ' ' || s[i] == '\n') && s[i] != '\0')
		;
	i--;
	while (s[++i] != '\0')
	{
		if (s[i] != 9 && s[i] != ' ' && s[i] != '\n' && nb_words != word)
			size++;
		else
		{
			if (nb_words == word - 1)
				return (size);
			while ((s[++i] == 9 || s[i] == ' ' || s[i] == '\n') && s[i] != '\0')
				;
			nb_words++;
			i--;
			size = 0;
		}
	}
	return (size);
}

static void		parser(char **tab, char *str, int i, int j)
{
	str--;
	while ((*(++str) == 9 || *str == ' ' || *str == '\n') && *str != '\0')
		;
	str--;
	while (*(++str) != '\0')
	{
		if (*str != 9 && *str != ' ' && *str != '\n')
			tab[i][++j] = *str;
		else
		{
			while (*(++str) == 9 || *str == ' ' || *str == '\n')
				;
			tab[i][++j] = '\0';
			if (*str != '\0')
			{
				--str;
				++i;
				j = -1;
			}
			else
				return ;
		}
	}
	return ;
}

char			**ft_split_whitespaces(char *str)
{
	int		nb_words;
	char	**res;
	int		i;

	if (!str)
		return (0);
	i = 0;
	compute_words(str, &nb_words);
	res = 0;
	res = malloc(sizeof(*res) * (nb_words + 1));
	if (!res)
		return (0);
	while (i < nb_words)
	{
		res[i] = 0;
		res[i] = malloc(sizeof(*res[i]) * compute_size(str, i, -1, 0));
		if (!res[i])
			return (0);
		i++;
	}
	res[nb_words] = 0;
	parser(res, str, 0, -1);
	return (res);
}
