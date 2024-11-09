/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tests.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: llebugle <lucas.lebugle@student.s19.be>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/09 15:36:32 by llebugle          #+#    #+#             */
/*   Updated: 2024/11/09 17:53:07 by llebugle         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef TESTS_H
# define TESTS_H

#include "../so_long.h"
#include <assert.h>

void test_map_validation(void);
int	 validate_map_content(const char *map, t_data *data);
int	 read_map(char *filename, t_data *data);
void test_read_map(void);

#endif