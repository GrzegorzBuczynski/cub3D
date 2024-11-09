/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_borders.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ssuchane <ssuchane@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/07 18:47:07 by ssuchane          #+#    #+#             */
/*   Updated: 2024/11/09 01:50:29 by ssuchane         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../cub3D.h"

int	getRowCount(char **map)
{
	int	rowCount;

	rowCount = 0;
	while (map[rowCount] != NULL)
	{
		rowCount++;
	}
	return (rowCount);
}

// Function to calculate the length of each row, ignoring trailing '\n'
int	getRowLength(char *row)
{
	int	len;

	len = strlen(row);
	if (len > 0 && row[len - 1] == '\n')
	{
		return (len - 1); // Ignore the trailing '\n'
	}
	return (len);
}

// Flood-fill function to mark all reachable cells from the border as visited
void	floodFill(char **map, bool **visited, int *y_sizes, int x, int y,
		char target)
{
	if (x < 0 || x >= getRowCount(map) || y < 0 || y >= y_sizes[x]
		|| map[x][y] != target || visited[x][y])
	{
		return ;
	}
	visited[x][y] = true; // Mark as visited
	// Recursively flood-fill in all directions
	floodFill(map, visited, y_sizes, x + 1, y, target);
	floodFill(map, visited, y_sizes, x - 1, y, target);
	floodFill(map, visited, y_sizes, x, y + 1, target);
	floodFill(map, visited, y_sizes, x, y - 1, target);
}

// Check if a region of '0's is completely enclosed by '1's
int	isEnclosedRegion(char **map, bool **visited, int *y_sizes, int x, int y)
{
	int	enclosed;

	if (x < 0 || x >= getRowCount(map) || y < 0 || y >= y_sizes[x])
	{
		return (0); // Out of bounds
	}
	if (map[x][y] == '1' || visited[x][y])
	{
		return (1); // Encountered a wall or already visited
	}
	visited[x][y] = true; // Mark as visited
	enclosed = 1;
	enclosed &= isEnclosedRegion(map, visited, y_sizes, x + 1, y);
	enclosed &= isEnclosedRegion(map, visited, y_sizes, x - 1, y);
	enclosed &= isEnclosedRegion(map, visited, y_sizes, x, y + 1);
	enclosed &= isEnclosedRegion(map, visited, y_sizes, x, y - 1);
	return (enclosed);
}

// Create a visited array
bool	**createVisitedArray(int x_size, int *y_sizes)
{
	bool	**visited;

	visited = malloc(x_size * sizeof(bool *));
	for (int i = 0; i < x_size; i++)
	{
		visited[i] = calloc(y_sizes[i], sizeof(bool)); // Allocate for each row
	}
	return (visited);
}

// Free the visited array
void	freeVisitedArray(bool **visited, int x_size)
{
	for (int i = 0; i < x_size; i++)
	{
		free(visited[i]);
	}
	free(visited);
}

// Main function to check if all regions of the map are enclosed by walls
int	check_borders(char **map)
{
	int x_size = getRowCount(map);

	// Calculate the y_sizes for each row, ignoring '\n' characters
	int *y_sizes = malloc(x_size * sizeof(int));
	if (!y_sizes)
	{
		return (0); // Memory allocation failed
	}
	for (int i = 0; i < x_size; i++)
	{
		y_sizes[i] = getRowLength(map[i]);
	}

	// Create a visited array
	bool **visited = createVisitedArray(x_size, y_sizes);
	if (!visited)
	{
		free(y_sizes);
		return (0); // Memory allocation failed
	}

	// Step 1: Mark all accessible exterior regions starting from boundary cells
	for (int i = 0; i < x_size; i++)
	{
		if (y_sizes[i] > 0 && map[i][0] == '0') // Left edge of each row
			floodFill(map, visited, y_sizes, i, 0, '0');
		if (y_sizes[i] > 1 && map[i][y_sizes[i] - 1] == '0')
			// Right edge of each row
			floodFill(map, visited, y_sizes, i, y_sizes[i] - 1, '0');
	}
	if (y_sizes[0] > 0)
	{ // Top edge row
		for (int j = 0; j < y_sizes[0]; j++)
		{
			if (map[0][j] == '0')
			{
				floodFill(map, visited, y_sizes, 0, j, '0');
			}
		}
	}
	if (x_size > 1 && y_sizes[x_size - 1] > 0)
	{ // Bottom edge row
		for (int j = 0; j < y_sizes[x_size - 1]; j++)
		{
			if (map[x_size - 1][j] == '0')
			{
				floodFill(map, visited, y_sizes, x_size - 1, j, '0');
			}
		}
	}

	// Step 2: Check for enclosed regions
	int enclosedRegions = 1; // Assume all regions are enclosed initially
	for (int i = 0; i < x_size; i++)
	{
		for (int j = 0; j < y_sizes[i]; j++)
		{
			if (map[i][j] == '0' && !visited[i][j])
			{
				// Found an unvisited '0', check if it's enclosed
				if (!isEnclosedRegion(map, visited, y_sizes, i, j))
				{
					enclosedRegions = 0; // Found an unbounded region
				}
			}
		}
	}

	// Clean up
	freeVisitedArray(visited, x_size);
	free(y_sizes);
	return (enclosedRegions);
}