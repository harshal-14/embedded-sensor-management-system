#include <iostream>
#include <vector>
#include <utility>
#include <queue>
#include <limits>
#include <set>

/*Given a grid with obstacle ('#'), road (' '), and interested points ('P'). Find a spot to set a camp that have shortest total distance to all 'P'.*/

int shortest_distance(std::vector<std::vector<char>> grid) {
    int rows = grid.size();
    if (rows == 0) return -1;
    int cols = grid[0].size();
    if (cols == 0) return -1;

    const char OBSTACLE = '#';
    const char ROAD = ' ';
    const char INTEREST_POINT = 'P';

    std::vector<std::pair<int, int>> directions = {{1,0}, {-1,0}, {0,1}, {0,-1}}; // down, up, right, left

    // Collect all interest points
    std::vector<std::pair<int, int>> interest_points; // store the coords of interest points
    for (int row = 0; row < rows; row++) {
        for (int col = 0; col < cols; col++) {
            if (grid[row][col] == INTEREST_POINT) { // if the cell is an interest point, add the coords to the interest_points vector
                interest_points.push_back({row, col});
            }
        }
    }

    if (interest_points.empty()) return -1; // if there are no interest points, return -1

    // For each cell, calculate total distance to all interest points
    int min_total_dist = std::numeric_limits<int>::max();
    // start the bfs algo here
    for (int row = 0; row < rows; row++) {
        for (int col = 0; col < cols; col++) {
            // Can only place camp on ROAD, you can't place at interest point or obstacle
            if (grid[row][col] != ROAD) continue;

            int total_dist = 0;
            bool reachable = true; // also define a boolean variable to check if the cell is reachable from all the interest points

            // BFS from this cell to each interest point
            for (const auto& [p_row, p_col] : interest_points) { 
                // BFS to find distance from (row, col) to (p_row, p_col)
                std::queue<std::tuple<int, int, int>> q; // row, col, distance // is this a queue? yes, it is a queue that stores the cells to be visited
                std::set<std::pair<int, int>> visited; // is this a hashset? yes, it is a hashset that stores the visited cells

                q.push({row, col, 0});
                visited.insert({row, col});

                int dist_to_point = -1; // dist_to_point is the distance from the current cell to the interest point

                while (!q.empty()) {
                    auto [curr_row, curr_col, curr_dist] = q.front(); // get the front element of the queue and remove it from the queue
                    q.pop();

                    // Found the interest point
                    if (curr_row == p_row && curr_col == p_col) {
                        dist_to_point = curr_dist;
                        break;
                    }

                    // Explore all 4 directions
                    for (const auto& [row_inc, col_inc] : directions) {
                        int new_row = curr_row + row_inc;
                        int new_col = curr_col + col_inc;

                        // Check boundaries and if not visited
                        if (new_row >= 0 && new_row < rows &&
                            new_col >= 0 && new_col < cols &&
                            grid[new_row][new_col] != OBSTACLE &&
                            visited.find({new_row, new_col}) == visited.end()) {

                            visited.insert({new_row, new_col});
                            q.push({new_row, new_col, curr_dist + 1});
                        }
                    }
                }

                // If we couldn't reach this interest point, this cell is not viable
                if (dist_to_point == -1) {
                    reachable = false;
                    break;
                }

                total_dist += dist_to_point;
            }

            // Update minimum if this cell can reach all points
            if (reachable) {
                min_total_dist = std::min(min_total_dist, total_dist);
            }
        }
    }

    return (min_total_dist != std::numeric_limits<int>::max()) ? min_total_dist : -1;
}

int main() {
    std::vector<std::vector<char>> grid = {
        {'#', '#', '#', '#', '#'},
        {'#', ' ', ' ', ' ', '#'},
        {'#', ' ', 'P', ' ', '#'},
        {'#', ' ', ' ', ' ', '#'},
        {'#', '#', '#', '#', '#'}
    };
    int result = shortest_distance(grid);
    printf("Shortest distance: %d\n", result);
    return 0;
}