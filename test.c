/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aben-ham <aben-ham@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/21 10:40:11 by aben-ham          #+#    #+#             */
/*   Updated: 2022/05/21 10:41:11 by aben-ham         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include <stdio.h>

int	main()
{
	double	a;

	a = 1.0 / 0.0;
	printf("%f\n", a);
	return (0);
}
