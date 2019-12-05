/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_isdigit.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acharlas <acharlas@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/07 15:58:09 by acharlas          #+#    #+#             */
/*   Updated: 2019/12/05 12:26:50 by acharlas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


int	ft_isdigit(int c)
{
	return (c >= '0' && c <= '9');
}