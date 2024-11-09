/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test_reader.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: llebugle <lucas.lebugle@student.s19.be>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/09 17:47:22 by llebugle          #+#    #+#             */
/*   Updated: 2024/11/09 19:11:30 by llebugle         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "tests.h"
#include "../includes/so_long.h"

int mock_validate_map_content(const char *map, t_data *data) {
    if (strstr(map, "1111") != NULL) return 0; // Dummy check for valid content
    data->err_msg = "Invalid map content";
    return 0;
}

void test_read_map(void)
{
    printf("Testing read_map...\n");

    // Initialize t_data and its fields
    t_data data;
    data.max_row = 320; // Example max row size
    data.map = malloc(sizeof(t_map)); // Allocate map structure
    if (!data.map) {
        fprintf(stderr, "Failed to allocate data.map\n");
        return;
    }
    data.map->row = 0;
    data.err_msg = NULL;

    // Case 1: Valid map	
    const char *valid_map_content = "1111\n1P01\n1111\n";
    FILE *fp = fopen("valid_map.txt", "w");
    fputs(valid_map_content, fp);
    fclose(fp);

    assert(read_map("valid_map.txt", &data) == 0);
    assert(data.err_msg == NULL);
    printf("✓ Valid map test passed\n");

    // Case 2: Nonexistent file
    assert(read_map("nonexistent_map.txt", &data) == 1);
    assert(strcmp(data.err_msg, NO_MAP) == 0);
    printf("✓ Nonexistent file test passed\n");

    // Case 3: Map too big
    data.map->row = 0;
    data.max_row = TILE_SIZE * 2; // Set max row lower to trigger error
    const char *large_map_content = "1111\n1111\n1111\n1111\n";
    fp = fopen("large_map.txt", "w");
    fputs(large_map_content, fp);
    fclose(fp);

    assert(read_map("large_map.txt", &data) == 1);
    assert(strcmp(data.err_msg, MAP_TOO_BIG) == 0);
    printf("✓ Map too big test passed\n");

    // Case 4: Invalid map content
    data.max_row = 320;  // Reset max_row for valid size
    data.map->row = 0;
    const char *invalid_map_content = "1111\n1X01\n1111\n";
    fp = fopen("invalid_map.txt", "w");
    fputs(invalid_map_content, fp);
    fclose(fp);

    assert(read_map("invalid_map.txt", &data) == 1);
    printf("✓ Invalid map content test passed\n");

    // Clean up test files and allocated memory
    unlink("valid_map.txt");
    unlink("large_map.txt");
    unlink("invalid_map.txt");
    free(data.map);

    printf("All read_map tests passed! ✅\n\n");
}
