/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test_main.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: llebugle <lucas.lebugle@student.s19.be>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/09 15:38:18 by llebugle          #+#    #+#             */
/*   Updated: 2024/11/09 17:52:31 by llebugle         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include "tests.h"

int main(void)
{
    printf("\nRunning so_long tests...\n\n");
    
    // Run test suites
    test_map_validation();
    test_read_map();
    
    printf("\nAll tests passed! ✅\n");
    return 0;
}