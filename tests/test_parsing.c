/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test_parsing.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: llebugle <lucas.lebugle@student.s19.be>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/09 15:37:10 by llebugle          #+#    #+#             */
/*   Updated: 2024/11/09 17:44:50 by llebugle         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <assert.h>
#include "../so_long.h" // Include your main header
#include "tests.h"

void data_init(t_data *data)
{
	data->max_col = 0;
	data->max_row = 0;
	data->err_msg = NULL;
	data->map = malloc(sizeof(t_map));
	if (!data->map)
		display_err_and_exit(MALLOC_ERROR_MSG, data);
}

void test_map_validation(void)
{
	t_data data;
	data_init(&data);

    printf("Testing map validation...\n");
    
	int result = validate_map_content("1111\n1P01\n1111", &data);
	if (result != 0) {
    	printf("❌ Basic valid map test failed. Expected 1, but got %d\n", result);
    	if (data.err_msg) {
        	printf("Error message: %s\n", data.err_msg);
    	}
	}
    // Valid cases
    assert(validate_map_content("1111\n1P01\n1111", &data) == 0);
    printf("✓ Basic valid map test passed\n");
    
    assert(validate_map_content("11111\n1P001\n11111", &data) == 0);
    printf("✓ Larger valid map test passed\n");

    // Invalid cases
    assert(validate_map_content("1111\n\n1111", &data) == 1);
    printf("✓ Empty line test passed\n");

    assert(validate_map_content("1111\n1X01\n1111", &data) == 1);
    printf("✓ Invalid character test passed\n");
    
    assert(validate_map_content("1111\n1P01\n1111\n", &data) == 0);
    printf("✓ Trailing newline test passed\n");
    
    assert(validate_map_content("", &data) == 1);
    printf("✓ Empty map test passed\n");
    
    printf("\nAll map validation tests passed! ✅\n\n");
	free(data.map);
}