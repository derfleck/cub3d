/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstlast.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mleitner <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/08 11:38:08 by mleitner          #+#    #+#             */
/*   Updated: 2022/10/10 14:07:31 by mleitner         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_list	*ft_lstlast(t_list *lst)
{
	t_list	*lst2;

	if (!lst)
		return ((t_list *)lst);
	lst2 = (t_list *)lst;
	while (lst2->next)
	{
		lst2 = lst2->next;
	}
	return (lst2);
}
