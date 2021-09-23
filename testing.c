/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   testing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msantos- <msantos-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/23 20:33:53 by msantos-          #+#    #+#             */
/*   Updated: 2021/09/23 21:18:00 by msantos-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include <stdio.h>
# include <unistd.h>
# include <stdlib.h>
# include <stdio.h>
# include <string.h>
# include <strings.h>
# include <pthread.h>

int		main()
{
	int *ptr;
	int *ptr2;
	
	ptr = malloc(sizeof(int) * 3);
	ptr[0] = 1;
	ptr[1] = 2;
	ptr[3] = 3;
	ptr2 = &ptr[1];
	printf("%p %p", &ptr[1], ptr2);
	return(0);
}