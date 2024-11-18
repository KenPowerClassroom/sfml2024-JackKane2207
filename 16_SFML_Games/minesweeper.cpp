#include <SFML/Graphics.hpp>
#include <time.h>
using namespace sf;

int minesweeper()
{
    int mine = 9;
    srand(time(0));

    RenderWindow app(VideoMode(400, 400), "Minesweeper!");

    int tileSize=32;
    int grid[12][12];
    int shownGrid[12][12]; //for showing
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
        int mineCounter=0;
        if (grid[row][column]==mine) continue; //if tile is a mine continue
        if (grid[row+1][column]== mine) mineCounter++;//checks all tiles for nearby mines, 9 = mine if found increase mine counter for number displayed
        if (grid[row][column-1]== mine) mineCounter++;
        if (grid[row -1][column]== mine) mineCounter++;
        if (grid[row][column -1]== mine) mineCounter++;
        if (grid[row +1][column +1]== mine) mineCounter++;
        if (grid[row -1][column -1]== mine) mineCounter++;
        if (grid[row -1][column +1]== mine) mineCounter++;
        if (grid[row +1][column -1]== mine) mineCounter++;
        grid[row][column] = mineCounter;
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
              if (event.key.code == Mouse::Left) shownGrid[x][y]=grid[x][y];
              else if (event.key.code == Mouse::Right) shownGrid[x][y]=11;
        }

        app.clear(Color::White);

        for (int row=1; row <=10; row++)
         for (int column =1; column <=10;column++)
          {
           if (shownGrid[x][y]== mine)
               shownGrid[row][column]=grid[row][column];//if mine is found show mine
           sprite.setTextureRect(IntRect(shownGrid[row][column]*tileSize,0,tileSize,tileSize));
           sprite.setPosition(row * tileSize, column * tileSize);
           app.draw(sprite);
          }

        app.display();
    }

    return 0;
}
