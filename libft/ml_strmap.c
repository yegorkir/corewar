/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ml_strmap.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ylila <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/07 17:19:49 by ylila             #+#    #+#             */
/*   Updated: 2019/08/10 19:41:04 by mdeanne          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ml_strmap(const char *s, char (*f)(char), u_int32_t lst_num)
{
	char	*new_str;
	char	*ptr2new;

	if (!s || !f || !(new_str = ml_strnew(ft_strlen(s), lst_num)))
		return (NULL);
	ptr2new = new_str;
	while (*s)
		*ptr2new++ = (*f)(*s++);
	return (new_str);
}
