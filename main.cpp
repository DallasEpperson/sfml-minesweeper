#include <SFML/Graphics.hpp>
#include <time.h>

const int tilesVert=12, tilesHoriz=12;
int tile[tilesVert][tilesHoriz];
bool knownTile[tilesVert][tilesHoriz];

void floodUncover(int x, int y){
    if(knownTile[x][y]) return;
    knownTile[x][y]=true;
    if(tile[x][y]!=0)return;
    if(y-1 >= 0) floodUncover(x, y-1);
    if(y+1 < tilesVert) floodUncover(x, y+1);
    if(x-1 >= 0){
        if(y-1>=0) floodUncover(x-1,y-1);
        floodUncover(x-1,y);
        if(y+1 < tilesVert) floodUncover(x-1,y+1);
    }
    if(x+1 < tilesHoriz){
        if(y-1>=0) floodUncover(x+1,y-1);
        floodUncover(x+1,y);
        if(y+1 < tilesVert) floodUncover(x+1,y+1);
    }
}

int main(){
    int tileWidth=32;
    int windowPaddingLeft=8, windowPaddingRight=8, windowPaddingTop=8, windowPaddingBottom=8;
    int bombChanceDivisor=5;

    srand(time(NULL));

    sf::RenderWindow window(sf::VideoMode(
        (tileWidth*tilesHoriz) + windowPaddingLeft + windowPaddingRight, 
        (tileWidth*tilesVert) + windowPaddingTop + windowPaddingBottom), 
        "Minesweeper");
    
    sf::Texture texture;
    texture.loadFromFile("./sprites.png");
    sf::Sprite sprites(texture);
    
    for (int y = 0; y < tilesVert; y++) {
        for (int x = 0; x < tilesHoriz; x++) {
            knownTile[x][y] = false;
            tile[x][y]=0;
            if (rand()%bombChanceDivisor==0)
                tile[x][y]=9;
        }
    }

    for (int y = 0; y < tilesVert; y++) {
        for (int x = 0; x < tilesHoriz; x++) {
            int neighbors=0;
            if(tile[x][y]==9) continue;
            if((y+1)<tilesVert && tile[x][y+1]==9) neighbors++;
            if((y-1)>=0 && tile[x][y-1]==9) neighbors++;
            if(x+1 < tilesHoriz){
                if(tile[x+1][y]==9) neighbors++;
                if((y+1)<tilesVert && tile[x+1][y+1]==9) neighbors++;
                if((y-1)>=0 && tile[x+1][y-1]==9) neighbors++;
            }
            if(x-1 >= 0){
                if(tile[x-1][y]==9) neighbors++;
                if((y+1)<tilesHoriz && tile[x-1][y+1]==9) neighbors++;
                if((y-1)>=0 && tile[x-1][y-1]==9) neighbors++;
            }
            tile[x][y]=neighbors;
        }
    }

    while(window.isOpen()){
        sf::Event event;
        while(window.pollEvent(event)){
            if (event.type == sf::Event::Closed)
                window.close();
            
            if(event.type == sf::Event::MouseButtonPressed){
                sf::Vector2i mousePos = sf::Mouse::getPosition(window);
                if((mousePos.x - windowPaddingLeft >= 0) 
                    && (mousePos.x - windowPaddingLeft < tileWidth*tilesHoriz) 
                    && (mousePos.y - windowPaddingTop >= 0)
                    && (mousePos.y - windowPaddingTop < tileWidth*tilesVert))
                {
                    int mouseTileX = (mousePos.x - windowPaddingLeft)/tileWidth;
                    int mouseTileY = (mousePos.y - windowPaddingTop)/tileWidth;
                    if((sf::Mouse::Button)event.key.code == sf::Mouse::Left) floodUncover(mouseTileX, mouseTileY);
                    //todo if tile[mtx][mty] is bomb, game over
                    //todo if tile[mtx][mty] is 0, fill/flood algo
                }
            }
            //todo get mouse button press
            //  right mb == flag thing
        }
        window.clear(sf::Color::White);
        
        for (int y = 0; y < tilesVert; y++) {
            for (int x = 0; x < tilesHoriz; x++) {
                sprites.setTextureRect(sf::IntRect(0,0,tileWidth,tileWidth));
                if(knownTile[x][y])
                    sprites.setTextureRect(sf::IntRect((tile[x][y]+2)*tileWidth,0,tileWidth,tileWidth));
                sprites.setPosition(windowPaddingLeft + x*tileWidth, y*tileWidth + windowPaddingTop);
                window.draw(sprites);
            }
        }
        window.display();
    }

    //todo restart if explodey boi

    //todo Yay if all tiles uncovered

    return 0;
}

//todo create a map for bomb values -> sprite position