#include <SFML/Graphics.hpp>
#include <time.h>
using namespace sf;

int minesweeper()
{
    enum MyEnum : int {
        MINE = 9,
        FLAG = 11
    };

    srand(time(0));
    int countMines(int, int, int grid[12][12], int);
    RenderWindow app(VideoMode(400, 400), "Minesweeper!");
    const int tileSize=32;
    const int gridSize = 12;
    int grid[gridSize][gridSize];
    int shownGrid[gridSize][gridSize]; //for showing
    int mineChance = 5;//1 in 5
    Texture texture;
    texture.loadFromFile("images/minesweeper/tiles.jpg");
    Sprite sprite(texture);

    for (int row=1; row <=10; row++)
     for (int column =1; column <=10;column++)
      {
        shownGrid[row][column]=10;
        if (rand()%mineChance==0)  grid[row][column]=9;
        else grid[row][column]=0;
      }

    for (int row=1;row<=10;row++)
     for (int column=1;column<=10;column++)//repeats for each tile
      {
         if (countMines(row, column, grid, MINE) == -1)continue;
        grid[row][column] = countMines(row, column, grid, MINE);
      }

    while (app.isOpen())
    {
        Vector2i pos = Mouse::getPosition(app);
        int x = pos.x/tileSize;
        int y = pos.y/tileSize;

        Event event;
        while (app.pollEvent(event))
        {
            if (event.type == Event::Closed)
                app.close();

            if (event.type == Event::MouseButtonPressed)
              if (event.key.code == Mouse::Left) shownGrid[x][y]=grid[x][y];//reveal grid
              else if (event.key.code == Mouse::Right) shownGrid[x][y]=FLAG;//place flag
        }

        app.clear(Color::White);

        for (int row=1; row <=10; row++)
         for (int column =1; column <=10;column++)//drawing
          {
           if (shownGrid[x][y]== MINE)
               shownGrid[row][column]=grid[row][column];//if mine is found show mine
           sprite.setTextureRect(IntRect(shownGrid[row][column]*tileSize,0,tileSize,tileSize));
           sprite.setPosition(row * tileSize, column * tileSize);
           app.draw(sprite);
          }

        app.display();
    }

    return 0;
}


int countMines(int t_row,int t_column,int t_grid[12][12], int t_mine)
{
    int mineCounter = 0;
    if (t_grid[t_row][t_column] == t_mine) return -1; //if tile is a mine return -1
    if (t_grid[t_row + 1][t_column] == t_mine) mineCounter++;//checks all tiles (3x3 area) for nearby mines, 9 = mine if found increase mine counter for number displayed
    if (t_grid[t_row][t_column - 1] == t_mine) mineCounter++;
    if (t_grid[t_row - 1][t_column] == t_mine) mineCounter++;
    if (t_grid[t_row + 1][t_column + 1] == t_mine) mineCounter++;
    if (t_grid[t_row - 1][t_column - 1] == t_mine) mineCounter++;
    if (t_grid[t_row - 1][t_column + 1] == t_mine) mineCounter++;
    if (t_grid[t_row + 1][t_column - 1] == t_mine) mineCounter++;
    t_grid[t_row][t_column] = mineCounter;
    return mineCounter;
}