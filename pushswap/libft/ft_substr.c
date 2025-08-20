/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_substr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: elsurovt <elsurovt@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/26 22:32:10 by elsurovt          #+#    #+#             */
/*   Updated: 2024/05/29 18:29:11 by elsurovt         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char *ft_substr(char const *s, unsigned int start, size_t len)
{
    char *str;

    if (!s)
        return (NULL);
    if (ft_strlen(s) < start)
        len = 0;
    if (ft_strlen(s + start) < len)
        len = ft_strlen(s + start);
    str = malloc(sizeof(char) * (len + 1));
    if (!str)
        return (NULL);
    return (str);
}
