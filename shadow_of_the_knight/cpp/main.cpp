#include <iostream>
#include <string>
#include <vector>
#include <algorithm>

using std::cerr;

using namespace std;

int init_map(std::vector<std::vector<int>> *to_init, int rows, int cols)
{
  if (rows <= 0 || cols <= 0)
  {
    std::cout << "Error with vector dimensions" << std::endl;
    return (1);
  }
  if (!to_init)
  {
    std::cout << "Error, vector's pointer is NULL" << std::endl;
    return (1);
  }
  for (int i = 0; i < cols ; i++)
  {
    std::vector<int> line;
    for (int y = 0; y < rows; y++)
      line.push_back(0);
    (*to_init).push_back(line);
  }
  return (0);
}


void print_2dvector(std::vector<std::vector<int>> *vec)
{
  for (int i = 0; i < (*vec).size(); i++)
  {
    for (int y = 0; y < (*vec)[i].size(); y++)
      std::cerr << (*vec)[i][y] << " ";
    std::cerr << "\n";
  }
}

std::vector<int> return_middle_cell_coordinates(std::vector<int> start, std::vector<int>end)
{
  int middle_y = (end.at(1) + start.at(1)) / 2;
  int middle_x = (end.at(0) + start.at(0)) / 2;
  return {middle_x, middle_y};
}

void discriminate_down(std::vector<std::vector<int>> *vec, int ypos)
{
  for (int i = ypos; i < (*vec).size(); i++)
    for (int j = 0; j < (*vec)[i].size(); j++)
      (*vec)[i][j]++;
}

void discriminate_up(std::vector<std::vector<int>> *vec, int ypos)
{
  for (int i = ypos; i >= 0; i--)
    for (int j = 0; j < (*vec)[i].size(); j++)
      (*vec)[i][j]++;
}

void discriminate_left(std::vector<std::vector<int>> *vec, int xpos)
{
  for (int i = 0; i < (*vec).size(); i++)
    for (int j = xpos; j >= 0; j--)
      (*vec)[i][j]++;
}
void discriminate_right(std::vector<std::vector<int>> *vec, int xpos)
{
  for (int i = 0; i < (*vec).size(); i++)
    for (int j = xpos; j < (*vec)[i].size(); j++)
      (*vec)[i][j]++;
}

void discriminate_cells(std::vector<std::vector<int>> *vec, std::string input, int xpos, int ypos)
{
  if (input.length() <= 0 || input.length() > 2)
  {
    cerr << "Bad string input" << std::endl;
    return ;
  }
  if (!vec)
  {
    cerr << "Vector's pointer is null" << std::endl;
    return ;
  }
  if (input.find("U", 0) != std::string::npos)
    discriminate_down(vec, ypos);
  if (input.find("D", 0) != std::string::npos)
    discriminate_up(vec, ypos);
  if (input.find("R", 0) != std::string::npos)
    discriminate_left(vec, xpos);
  if (input.find("L", 0) != std::string::npos)
    discriminate_right(vec, xpos);
}

std::vector<int> find_first_valid_cell(std::vector<std::vector<int>> *vec)
{
  for (int i = 0; i < (*vec).size(); i++)
    for (int y = 0; y < (*vec)[i].size(); y++)
      if ((*vec)[i][y] == 0)
	return {y,i};
  return {0,0};
}

std::vector<int> find_last_valid_cell(std::vector<std::vector<int>> *vec)
{
  for (int i = (*vec).size() - 1; i >= 0; i--)
    for (int y = (*vec)[i].size() - 1; y >= 0; y--)
      if ((*vec)[i][y] == 0)
	return {y,i};
  return {0,0};
}

/**
 * Auto-generated code below aims at helping you parse
 * the standard input according to the problem statement.
 **/

int main()
{
    int w; // width of the building.
    int h; // height of the building.
    cin >> w >> h; cin.ignore();
    int n; // maximum number of turns before game over.
    cin >> n; cin.ignore();
    int x0;
    int y0;
    cin >> x0 >> y0; cin.ignore();
    vector<vector <int>> building;


    init_map(&building, w, h);
    // game loop
    while (1) {
        string bomb_dir; // the direction of the bombs from batman's current location (U, UR, R, DR, D, DL, L or UL)
        std::vector<int> middle_cell{0,0};
        cin >> bomb_dir; cin.ignore();
        // Write an action using cout. DON'T FORGET THE "<< endl"
        // To debug: cerr << "Debug messages..." << endl;
        discriminate_cells(&building, bomb_dir, x0, y0);
        //print_2dvector(&building);
        middle_cell = return_middle_cell_coordinates(find_first_valid_cell(&building), find_last_valid_cell(&building));

        // the location of the next window Batman should jump to.
        cout << middle_cell[0] << " " << middle_cell[1] << endl;
        x0 = middle_cell[0];
        y0 = middle_cell[1];
    }
}
