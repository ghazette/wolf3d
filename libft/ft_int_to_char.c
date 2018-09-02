/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   ft_int_to_char.c                                 .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: ghazette <marvin@le-101.fr>                +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2017/11/23 14:05:22 by ghazette     #+#   ##    ##    #+#       */
/*   Updated: 2017/12/19 16:11:50 by ghazette    ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

/*
** converti un int en remplissant dst avec les bytes correspondant
**/

void    ft_int_to_char(int src, char dst[4])
{
    dst[0] = (src >> 24) & 0xFF;
    dst[1] = (src >> 16) & 0xFF;
    dst[2] = (src >> 8) & 0xFF;
    dst[3] = src & 0xFF;
}
