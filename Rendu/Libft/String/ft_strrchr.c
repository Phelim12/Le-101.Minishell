/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   ft_strrchr.c                                     .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: clcreuso <clcreuso@student.le-101.fr>      +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2017/11/24 22:08:13 by clcreuso     #+#   ##    ##    #+#       */
/*   Updated: 2017/11/24 22:08:13 by clcreuso    ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strrchr(const char *s, int c)
{
	int a;

	a = 0;
	while (s[a] != '\0')
		a++;
	if (c == '\0')
		return ((char *)s + a);
	while (a >= 0)
	{
		if (s[a] == (unsigned char)c)
			return ((char *)s + a);
		else
			a--;
	}
	return (NULL);
}
