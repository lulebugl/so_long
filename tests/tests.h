/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tests.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: llebugle <lucas.lebugle@student.s19.be>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/09 15:36:32 by llebugle          #+#    #+#             */
/*   Updated: 2024/11/09 18:42:29 by llebugle         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef TESTS_H
# define TESTS_H

#include <assert.h>
#include "../srcs/so_long.h"


void test_map_validation(void);
int	 validate_map_content(const char *map, t_data *data);
int	 read_map(char *filename, t_data *data);
void test_read_map(void);

#endif