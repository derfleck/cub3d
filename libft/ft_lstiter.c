/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstiter.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mleitner <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/08 13:50:00 by mleitner          #+#    #+#             */
/*   Updated: 2022/10/10 14:07:07 by mleitner         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_lstiter(t_list *lst, void (*f)(void *))
{
	t_list	*lst2;

	if (!lst || !f)
		return ;
	lst2 = (t_list *)lst;
	while (lst2)
	{
		(*f)(lst2->content);
		lst2 = lst2->next;
	}
}
