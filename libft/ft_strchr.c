/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nayache <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/07 14:32:23 by nayache           #+#    #+#             */
/*   Updated: 2021/03/01 10:14:09 by nayache          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strchr(const char *s, int c)
{
	int		i;
	char	d;

	d = (char)c;
	i = 0;
	while (s[i] != '\0')
	{
		if (s[i] == d)
			return ((char *)(&s[i]));
		i++;
	}
	if (s[i] == d)
		return ((char *)(&s[i]));
	return (NULL);
}
