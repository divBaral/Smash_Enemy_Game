#include "Levels.h"

using namespace levelZone;

//**********************************************LEVEL ONE ZONE****************************************************

level1::level1(  sf::RenderWindow *window )
:
wMap(  )

{
    assignScreen(window); //this method is in initiator.h
    levelcount = 1;
    //is weapon ready to launch?
    hasEnded = false;
    readyToLaunch = true;

    pButtonMade = false;
    nextButtonMade = false;
}

level1::~level1()
{
    playerData.updateUserData(player_name, levelcount, score);
}


void level1::loadElements()
{

    float tile2x = winX - 128;
    float tile2y = winY - 128 -128;

    //first element
    Vector2d elem1size( 15, 60); //pixels
    Vector2d elem1pos(tile2x, tile2y - elem1size.y);
    woodElements.push_back( new Element( elem1pos, elem1size, m_world ));
    woodElements[FIRST]->load( "assets/elements/elementWood019.png", elem1size );

    //2ND right element

    float shiftxfromfirst = 100;
    Vector2d elem2size( 15, 60); //pixels
    Vector2d elem2pos(tile2x + shiftxfromfirst, tile2y - elem1size.y );
    woodElements.push_back( new Element( elem2pos, elem2size, m_world) );
    woodElements[SECOND]->load( "assets/elements/elementWood019.png", elem2size );

    //third upper element standing,
    Vector2d elem3size(120, 15);
    Vector2d elem3pos(elem1pos.x, tile2y - elem1size.y -  elem3size.y);
    woodElements.push_back( new Element( elem3pos, elem3size, m_world) );
    woodElements[THIRD]->load( "assets/elements/elementWood015.png", elem3size );
    //fourth left element
    Vector2d elem4size( 15, 60); //pixels
    Vector2d elem4pos(tile2x, tile2y - 2* elem1size.y - elem3size.y  );
    woodElements.push_back( new Element( elem4pos, elem4size, m_world ));
    woodElements[FOURTH]->load( "assets/elements/elementWood019.png", elem1size );

    //fifth right element

    shiftxfromfirst = 100;
    Vector2d elem5size( 15, 60); //pixels
    Vector2d elem5pos(tile2x + shiftxfromfirst, tile2y - 2* elem1size.y - elem3size.y );
    woodElements.push_back( new Element( elem5pos, elem5size, m_world) );
    woodElements[FIFTH]->load( "assets/elements/elementWood019.png", elem2size );

    //6th element upper to above
    Vector2d elem6size(120, 15);
    Vector2d elem6pos(elem1pos.x,  tile2y - 2* elem1size.y -  2*elem6size.y );
    woodElements.push_back( new Element( elem6pos, elem6size, m_world) );
    woodElements[SIXTH]->load( "assets/elements/elementWood015.png", elem3size );
    
}

void level1::loadAliens()
{
    //relative to some elements
    //here tile2 is right tile
    float tile2x = winX - 128;
    float tile2y = winY - 128 -128;

    //first element 
    Vector2d elem1size( 15, 60); //pixels
    Vector2d elem1pos(tile2x, tile2y - elem1size.y );
    Vector2d elem2size( 120, 15);
    //alien1
    float alien1radius = 20.f;
    float shiftxfrom1element = 70.f;
    Vector2d alien1pos(elem1pos.x + shiftxfrom1element , tile2y - alien1radius  );
    
    aliens.push_back( new Alien( alien1pos, alien1radius, m_world) );
    aliens[FIRST]->load( "assets/aliens/alienYellow_round.png" );

    //2nd alien
    float alien2radius = 20.f;
    Vector2d alien2pos(elem1pos.x + shiftxfrom1element , tile2y - elem1size.y - elem2size.y - alien1radius  );
    
    aliens.push_back( new Alien( alien2pos, alien2radius, m_world) );
    aliens[SECOND]->load( "assets/aliens/alienYellow_round.png" );

    //3rd alien
    float alien3radius = 20.f;
    Vector2d alien3pos(elem1pos.x + shiftxfrom1element , tile2y - 2*elem1size.y - 2* elem2size.y -alien2radius  );
    
    aliens.push_back( new Alien( alien3pos, alien3radius, m_world) );
    aliens[THIRD]->load( "assets/aliens/alienYellow_round.png" );


    aliencount = aliens.size(); 
}

void level1::loadTiles()
{
    //at left corner
    tiles.push_back( new StaticBox( Vector2d(0, winY-128), Vector2d(200, 128), m_world ) );// (world, positon, size)
    tiles[FIRST]->load( "assets/tiles/Tile1.png" );
    //stretching sprite
    sf::IntRect rect = tiles[FIRST]->getSprite()->getTextureRect();
    float X = 200.f/rect.width;
    float Y = 128.f/rect.height;
    tiles[FIRST]->getSprite()->setScale(X, Y);

    //at right corner
    tiles.push_back (new StaticBox( Vector2d((winX-128), (winY-128-128)), Vector2d(128, 256), m_world ) );
    tiles[SECOND]->load( "assets/tiles/Tilelzero.png" );

}

//**********************************************LEVEL TWO ZONE****************************************************


level2::level2(  sf::RenderWindow *window )
:
wMap( )

{
    assignScreen(window); //this method is in initiator.h
    hasEnded = false;
    levelcount = 2;
    //is weapon ready to launch?
    readyToLaunch = true;

    pButtonMade = false;
    nextButtonMade = false;
}

level2::~level2()
{
    playerData.updateUserData(player_name, levelcount, score);
}

void level2::loadElements()
{
    //right tile
    float tile2x = winX - 128;
    float tile2y = winY - 128;


    //first element
    Vector2d elemsize( 15, 60 ); //pixels
    float shiftx = 14;

    Vector2d elempos(tile2x + shiftx, tile2y - elemsize.y);

    woodElements.push_back( new Element( elempos, elemsize, m_world ));
    woodElements[FIRST]->load( "assets/elements/elementWood019.png", elemsize );

    //middle elements
    Vector2d upperTilePos(600, 200);

    elemsize.set(15, 80);
    shiftx = 140 + 20;
    elempos.set(upperTilePos.x+shiftx, upperTilePos.y - elemsize.y);
    woodElements.push_back(new Element( elempos, elemsize, m_world) );
    woodElements[SECOND]->load("assets/elements/elementWood019.png", elemsize);

    elemsize.set(15, 80);
    shiftx = 140+120;
    elempos.set(upperTilePos.x+shiftx, upperTilePos.y - elemsize.y);
    woodElements.push_back(new Element( elempos, elemsize, m_world) );
    woodElements[THIRD]->load("assets/elements/elementWood019.png", elemsize);

    elemsize.set(110, 15);
    shiftx = 140 + 20;
    elempos.set( upperTilePos.x+shiftx, upperTilePos.y - elemsize.y - 80 );//verical element size
    woodElements.push_back( new Element( elempos, elemsize, m_world) );
    woodElements[FOURTH]->load( "assets/elements/elementWood015.png", elemsize );

}

void level2::loadAliens()
{
    //relative to some element
    float tile2x = winX - 128;
    float tile2y = winY - 128;

    //first element 
    Vector2d elem1size( 15, 60); //pixels
    Vector2d elem1pos(tile2x, tile2y - elem1size.y );
    Vector2d elem2size( 120, 15);


    //aliens
    float alien1radius = 20.f;
    float shiftxfrom1element = 70.f;
    Vector2d alien1pos(elem1pos.x + shiftxfrom1element , tile2y - alien1radius  );
    
    aliens.push_back( new Alien( alien1pos, alien1radius, m_world) );
    aliens[FIRST]->load( "assets/aliens/alienYellow_round.png" );

    Vector2d upperTilePos(600, 200);
    float alien2radius = alien1radius;
    float shiftxfromelement = 140.f;
    Vector2d alien2pos(upperTilePos.x + shiftxfromelement+alien2radius+50 , upperTilePos.y - alien2radius  );//elementwidth = 15
    
    aliens.push_back( new Alien( alien2pos, alien2radius, m_world) );
    aliens[SECOND]->load( "assets/aliens/alienGreen_round.png" );

    float alien3radius = alien1radius;
    shiftxfromelement = 70.f;
    Vector2d alien3pos(elem1pos.x + shiftxfromelement, tile2y - ( 2 * alien3radius )  );//elementwidth = 15
    
    aliens.push_back( new Alien( alien3pos, alien3radius, m_world) );
    aliens[THIRD]->load( "assets/aliens/alienBlue_round.png" );

    aliencount = aliens.size(); 
}

void level2::loadTiles()
{
    //LOADING TILES : push, load, [stretch] 

    Vector2d size, pos;

    //at left corner
    pos.set(0, winY-128);
    size.set(200, 128);
    tiles.push_back( new StaticBox( pos, size, m_world ) );
    tiles[FIRST]->load( "assets/tiles/Tile1.png" );// (world, positon, size)
    //stretching sprite
    sf::IntRect rect = tiles[FIRST]->getSprite()->getTextureRect();
    float X = 200.f/rect.width;
    float Y = 128.f/rect.height;
    tiles[FIRST]->getSprite()->setScale(X, Y);

    //at right corner
    pos.set(winX-128, winY-128);
    size.set(128, 128);
    tiles.push_back ( new StaticBox( pos, size, m_world ) );
    tiles[SECOND]->load( "assets/tiles/Tile1L.png" );


    //long middle tile,
    size.set(250, 60);
    pos.set(750, 200);//to resize you have to resize in 3 places
    tiles.push_back (new StaticBox( pos, size, m_world ) );
    tiles[THIRD]->load( "assets/tiles/Tilelone.png" );
    rect = tiles[THIRD]->getSprite()->getTextureRect();
    X = 250.f/rect.width;
    Y = 60.f/rect.height;
    tiles[THIRD]->getSprite()->setScale(X, Y);
}



//**********************************************LEVEL THREE ZONE****************************************************


level3::level3(  sf::RenderWindow *window )
:
wMap( )

{
    assignScreen(window); //this method is in initiator.h
    hasEnded = false;
    levelcount = 3;
    //is weapon ready to launch?
    readyToLaunch = true;

    pButtonMade = false;
    nextButtonMade = false;
}

level3::~level3()
{
    playerData.updateUserData(player_name, levelcount, score);
}

void level3::loadElements()
{
    //right tile
    float tile2x = winX - 128;
    float tile2y = winY - 128;


    //first element
    Vector2d elemsize( 15, 60 ); //pixels
    float shiftx = 14;

    Vector2d elempos(tile2x + shiftx, tile2y - elemsize.y);

    woodElements.push_back( new Element( elempos, elemsize, m_world ));
    woodElements[FIRST]->load( "assets/elements/elementWood019.png", elemsize );

    //middle elements
    Vector2d upperTilePos(600, 200);

    elemsize.set(15, 80);
    shiftx = 140 + 20;
    elempos.set(upperTilePos.x+shiftx, upperTilePos.y - elemsize.y);
    woodElements.push_back(new Element( elempos, elemsize, m_world) );
    woodElements[SECOND]->load("assets/elements/elementWood019.png", elemsize);

    elemsize.set(15, 80);
    shiftx = 140+120;
    elempos.set(upperTilePos.x+shiftx, upperTilePos.y - elemsize.y);
    woodElements.push_back(new Element( elempos, elemsize, m_world) );
    woodElements[THIRD]->load("assets/elements/elementWood019.png", elemsize);

    elemsize.set(110, 15);
    shiftx = 140 + 20;
    elempos.set( upperTilePos.x+shiftx, upperTilePos.y - elemsize.y - 80 );//verical element size
    woodElements.push_back( new Element( elempos, elemsize, m_world) );
    woodElements[FOURTH]->load( "assets/elements/elementWood015.png", elemsize );

}

void level3::loadAliens()
{
    //relative to some element
    float tile2x = winX - 128;
    float tile2y = winY - 128;

    //first element 
    Vector2d elem1size( 15, 60); //pixels
    Vector2d elem1pos(tile2x, tile2y - elem1size.y );
    Vector2d elem2size( 120, 15);


    //aliens
    float alien1radius = 10.f;
    float shiftxfrom1element = 70.f;
    Vector2d alien1pos(elem1pos.x + shiftxfrom1element , tile2y - alien1radius  );
    
    aliens.push_back( new Alien( alien1pos, alien1radius, m_world) );
    aliens[FIRST]->load( "assets/aliens/alienYellow_round_small.png" );

    Vector2d upperTilePos(600, 200);
    float alien2radius = alien1radius;
    float shiftxfromelement = 140.f;
    Vector2d alien2pos(upperTilePos.x + shiftxfromelement + alien2radius + 50 , upperTilePos.y - alien2radius  );
    
    aliens.push_back( new Alien( alien2pos, alien2radius, m_world) );
    aliens[SECOND]->load( "assets/aliens/alienGreen_round_small.png" );

    float alien3radius = alien1radius;
    shiftxfromelement = 70.f;
    Vector2d alien3pos(elem1pos.x + shiftxfromelement, tile2y - ( 2 * alien3radius )  );//elementwidth = 15
    
    aliens.push_back( new Alien( alien3pos, alien3radius, m_world) );
    aliens[THIRD]->load( "assets/aliens/alienBlue_round_small.png" );

    float alien4radius = 20.f;
    shiftxfromelement = 140.f;
    Vector2d alien4pos(upperTilePos.x + shiftxfromelement + alien4radius + 50 , upperTilePos.y - alien4radius - 80  );//elementheight = 80
    
    aliens.push_back( new Alien( alien4pos, alien4radius, m_world) );
    aliens[FOURTH]->load( "assets/aliens/alienPink_round.png" );

    aliencount = aliens.size(); 

}

//Tiles are similar to that of level one 
void level3::loadTiles()
{
    //LOADING TILES : push, load, [stretch] 

    Vector2d size, pos;

    //at left corner
    pos.set(0, winY-128);
    size.set(200, 128);
    tiles.push_back( new StaticBox( pos, size, m_world ) );
    tiles[FIRST]->load( "assets/tiles/Tile1.png" );// (world, positon, size)
    //stretching sprite
    sf::IntRect rect = tiles[FIRST]->getSprite()->getTextureRect();
    float X = 200.f/rect.width;
    float Y = 128.f/rect.height;
    tiles[FIRST]->getSprite()->setScale(X, Y);

    //at right corner
    pos.set(winX-128, winY-128);
    size.set(128, 128);
    tiles.push_back ( new StaticBox( pos, size, m_world ) );
    tiles[SECOND]->load( "assets/tiles/Tile1L.png" );


    //long middle tile,
    size.set(250, 60);
    pos.set(750, 200);//to resize you have to resize in 3 places
    tiles.push_back (new StaticBox( pos, size, m_world ) );
    tiles[THIRD]->load( "assets/tiles/Tilelone.png" );
    rect = tiles[THIRD]->getSprite()->getTextureRect();
    X = 250.f/rect.width;
    Y = 60.f/rect.height;
    tiles[THIRD]->getSprite()->setScale(X, Y);
}



//**********************************************LEVEL FOUR ZONE****************************************************
level4::level4(  sf::RenderWindow *window )
:
wMap( )

{
    assignScreen(window); //this method is in initiator.h
    hasEnded = false;
    levelcount = 4;
    //is weapon ready to launch?
    readyToLaunch = true;

    pButtonMade = false;
    nextButtonMade = false;
}

level4::~level4()
{
    playerData.updateUserData(player_name, levelcount, score);
}

void level4::loadElements()
{
    //right tile  position 
    const Vector2d right(winX-128*2, winY- 128*2+120);


    //first element
    Vector2d elemsize( 25, 120 ); //pixels
    float shiftx = 25;
    //elemwood 019, 015 glass 
    Vector2d elempos(right.x + shiftx, right.y - elemsize.y);

    woodElements.push_back( new Element(elempos, elemsize, m_world));
    woodElements[FIRST]->load("assets/elements/elementWood019.png", elemsize);

    shiftx = 150;
    elempos.set(elempos.x + shiftx, elempos.y);
    woodElements.push_back( new Element(elempos, elemsize, m_world) );
    woodElements[SECOND]->load("assets/elements/elementWood019.png", elemsize);

    
    elemsize.set(120+50, 25);//horizontal
    elempos.set(elempos.x-shiftx, elempos.y-elemsize.y);
    woodElements.push_back( new Element(elempos, elemsize, m_world) );
    woodElements[THIRD]->load("assets/elements/elementWood015.png", elemsize);

    elemsize.set(25, 100);
    elempos.set(elempos.x , elempos.y - elemsize.y);
    woodElements.push_back( new Element(elempos, elemsize, m_world));
    woodElements[FOURTH]->load("assets/elements/elementGlass026.png", elemsize);

    shiftx = 150;
    elempos.set(elempos.x + shiftx, elempos.y);
    woodElements.push_back( new Element(elempos, elemsize, m_world) );
    woodElements[FIFTH]->load("assets/elements/elementGlass026.png", elemsize);

    
    elemsize.set(120+50, 25);//horizontal
    elempos.set(elempos.x-shiftx, elempos.y-elemsize.y);
    woodElements.push_back( new Element(elempos, elemsize, m_world) );
    woodElements[SIXTH]->load("assets/elements/elementGlass017.png", elemsize);

    shiftx = 75;
    elemsize.set(25, 50);
    elempos.set(shiftx + elempos.x , elempos.y -elemsize.y);
    woodElements.push_back( new Element(elempos, elemsize, m_world) );
    woodElements[SEVENTH]->load("assets/elements/elementWood016.png", elemsize);

}

void level4::loadAliens()
{
    
    const Vector2d right(winX-128*2, winY- 128*2+120);
    //aliens

    float alienradius = 20.f;
    float shiftx = 100.f;
    Vector2d alienpos(right.x + shiftx , right.y  - alienradius  );//140 right glass height
    aliens.push_back( new Alien( alienpos, alienradius, m_world) );
    aliens[FIRST]->load( "assets/aliens/alienYellow_round.png" );

    shiftx = alienradius + 5;
    alienpos.set(alienpos.x + shiftx, alienpos.y);
    aliens.push_back( new Alien( alienpos, alienradius, m_world) );
    aliens[SECOND]->load( "assets/aliens/alienBlue_round.png" );

    shiftx = 100.f;
    alienpos.set(right.x+shiftx, alienpos.y-120-25);
    aliens.push_back( new Alien( alienpos, alienradius, m_world) );
    aliens[THIRD]->load( "assets/aliens/alienYellow_round.png" );

    shiftx = alienradius + 5;
    alienpos.set(alienpos.x + shiftx, alienpos.y);
    aliens.push_back( new Alien( alienpos, alienradius, m_world) );
    aliens[FOURTH]->load("assets/aliens/alienBlue_round.png");

    aliencount = aliens.size();
 
}

void level4::loadTiles()
{
    //LOADING TILES : push, load, [stretch] 

    Vector2d size, pos;

    //at left corner
    pos.set(0, winY-128);
    size.set(200, 128);
    tiles.push_back( new StaticBox( pos, size, m_world ) );
    tiles[FIRST]->load( "assets/tiles/Tile1.png" );// (world, positon, size)
    //stretching sprite
    sf::IntRect rect = tiles[FIRST]->getSprite()->getTextureRect();
    float X = 200.f/rect.width;
    float Y = 128.f/rect.height;
    tiles[FIRST]->getSprite()->setScale(X, Y);


    //tile 
    size.set(128, 128);
    int offset = 120;
    pos.set(winX-128, winY- 128*2+offset);
    tiles.push_back(new StaticBox( pos, size, m_world));
    tiles[SECOND]->load("assets/tiles/2.png");

    pos.set(pos.x, pos.y+128);
    tiles.push_back(new StaticBox( pos, size, m_world));
    tiles[THIRD]->load("assets/tiles/5.png");

    pos.set(pos.x-128, pos.y-128);

    tiles.push_back(new StaticBox( pos, size, m_world));
    tiles[FOURTH]->load("assets/tiles/1.png");

    pos.set(pos.x, pos.y+128);
    tiles.push_back(new StaticBox( pos, size, m_world));
    tiles[FIFTH]->load("assets/tiles/8.png");

}



//**********************************************LEVEL FIVE ZONE****************************************************
level5::level5(  sf::RenderWindow *window )
:
wMap( )

{
    assignScreen(window); //this method is in initiator.h
    hasEnded = false;
    levelcount = 5;
    //is weapon ready to launch?
    readyToLaunch = true;

    pButtonMade = false;
    nextButtonMade = false;
}

level5::~level5()
{
    playerData.updateUserData(player_name, levelcount, score);
}

void level5::loadElements()
{
    //right tile  position 
    Vector2d right(750, 400);


    //first element
    Vector2d elemsize( 20, 140 ); //pixels
    float shiftx = 50;
    //elemwood 019, 015
    Vector2d elempos(right.x + shiftx, right.y - elemsize.y);

    woodElements.push_back(new Element( elempos, elemsize, m_world) );
    woodElements[FIRST]->load("assets/elements/elementWood019.png", elemsize);
    //attached to first


    elempos.set(elempos.x - elemsize.x, elempos.y);
    //elemsize.set(elemsize.x, elemsize.y + 15);//15 is horizontal offset
    woodElements.push_back(new Element( elempos, elemsize, m_world) );
    woodElements[SECOND]->load("assets/elements/elementGlass019.png", elemsize);

    elempos.set(right.x + shiftx + elemsize.x + 40, right.y - elemsize.y ); //40 gap
    woodElements.push_back(new Element( elempos, elemsize, m_world) );
    woodElements[THIRD]->load("assets/elements/elementWood019.png", elemsize);
    
    elempos.set(elempos.x + elemsize.x, elempos.y);
    woodElements.push_back(new Element( elempos, elemsize, m_world) );
    woodElements[FOURTH]->load("assets/elements/elementGlass021.png", elemsize);

    //lon

    elemsize.set(2*elemsize.x + 40, 15);//40 is gaps
    elempos.set(right.x+shiftx, right.y-elemsize.y-140);//140 above first
    woodElements.push_back( new Element(elempos, elemsize, m_world));
    woodElements[FIFTH]->load("assets/elements/elementWood012.png", elemsize);

    elemsize.set(elemsize.x+2*20, elemsize.y);//20 is long element width
    elempos.set(elempos.x-20, elempos.y - elemsize.y);//20 is same as above
    woodElements.push_back( new Element(elempos, elemsize, m_world));
    woodElements[SIXTH]->load("assets/elements/elementGlass014.png", elemsize);

}

void level5::loadAliens()
{
    
    //right tile  position 
    Vector2d right(750, 400);
    //aliens

    Vector2d side(20, 140);

    float alienradius = 20.f;
    float shiftx = 50.f;
    Vector2d alienpos(right.x + shiftx + side.x + alienradius, right.y  - alienradius  );//140 right glass height
    
    aliens.push_back( new Alien( alienpos, alienradius, m_world) );
    aliens[FIRST]->load( "assets/aliens/alienYellow_round.png" );

    //second up
    alienpos.set(alienpos.x , alienpos.y - alienradius );//140 right glass height
    aliens.push_back( new Alien( alienpos, alienradius, m_world) );
    aliens[SECOND]->load( "assets/aliens/alienGreen_round.png" );

    alienpos.set(alienpos.x , alienpos.y - alienradius );//140 right glass height
    aliens.push_back( new Alien( alienpos, alienradius, m_world) );
    aliens[THIRD]->load( "assets/aliens/alienBlue_round.png" );

    aliencount = aliens.size();
 
}

void level5::loadTiles()
{
    //LOADING TILES : push, load, [stretch] 

    Vector2d size, pos;

    //at left corner
    pos.set(0, winY-128);
    size.set(200, 128);
    tiles.push_back( new StaticBox( pos, size, m_world ) );
    tiles[FIRST]->load( "assets/tiles/Tile1.png" );// (world, positon, size)
    //stretching sprite
    sf::IntRect rect = tiles[FIRST]->getSprite()->getTextureRect();
    float X = 200.f/rect.width;
    float Y = 128.f/rect.height;
    tiles[FIRST]->getSprite()->setScale(X, Y);



    size.set(252, 20);
    pos.set(750, 400);//to resize you have to resize in 3 places
    tiles.push_back (new StaticBox( pos, size, m_world ) );
    tiles[SECOND]->load( "assets/tiles/13.png" );
    rect = tiles[SECOND]->getSprite()->getTextureRect();
    X = 252.f/rect.width;
    Y = 40.f/rect.height;//more
    tiles[SECOND]->getSprite()->setScale(X, Y);
}


//**********************************************LEVEL SIX ZONE****************************************************
level6::level6(  sf::RenderWindow *window )
:
wMap( )

{
    assignScreen(window); //this method is in initiator.h
    hasEnded = false;
    levelcount = 6;
    //is weapon ready to launch?
    readyToLaunch = true;

    pButtonMade = false;
    nextButtonMade = false;
}

level6::~level6()
{
    playerData.updateUserData(player_name, levelcount, score);
}

void level6::loadElements()
{
    //right tile  position 
    Vector2d right(750, 300);
    //middle left tile position
    Vector2d midleft(250 , 200);


    //first element
    Vector2d elemsize( 140, 140 ); //pixels
    float shiftx = 25;
    //elemwood 019, 015
    Vector2d elempos(right.x + shiftx, right.y - elemsize.y);

    woodElements.push_back(new Element( elempos, elemsize, m_world) );
    woodElements[FIRST]->load("assets/elements/elementGlass035.png", elemsize);

    //lon

    elemsize.set(30, 60);

    elempos.set(midleft.x+shiftx, midleft.y-elemsize.y);
    woodElements.push_back( new Element(elempos, elemsize, m_world));
    woodElements[SECOND]->load("assets/elements/elementGlass018.png", elemsize);

    elemsize.set(30, 60);
    elempos.set(right.x+shiftx, right.y-elemsize.y-140);//140 above first
    woodElements.push_back( new Element(elempos, elemsize, m_world));
    woodElements[THIRD]->load("assets/elements/elementGlass018.png", elemsize);

}

void level6::loadAliens()
{
    
    //right tile  position 
    Vector2d right(750, 300);
    //middle left tile position
    Vector2d midleft(250 , 200);
    //aliens

    float alienradius = 10.f;
    float shiftx = 70.f;
    Vector2d alienpos(right.x + shiftx , right.y -140 - alienradius  );//140 right glass height
    aliens.push_back( new Alien( alienpos, alienradius, m_world) );
    aliens[FIRST]->load( "assets/aliens/alienYellow_round_small.png" );

    //second side to first
    alienpos.set(right.x + 2*shiftx , right.y -140 - alienradius  );//140 right glass height
    aliens.push_back( new Alien( alienpos, alienradius, m_world) );
    aliens[SECOND]->load( "assets/aliens/alienGreen_round_small.png" );

    alienpos.set(midleft.x+3*shiftx, midleft.y);
    alienradius = 20.f;
    aliens.push_back( new Alien(alienpos, alienradius, m_world));
    aliens[THIRD]->load("assets/aliens/alienPink_round.png");



    aliencount = aliens.size();
 
}

void level6::loadTiles()
{
    //LOADING TILES : push, load, [stretch] 

    Vector2d size, pos;

    //at left corner
    pos.set(0, winY-128);
    size.set(200, 128);
    tiles.push_back( new StaticBox( pos, size, m_world ) );
    tiles[FIRST]->load( "assets/tiles/Tile1.png" );// (world, positon, size)
    //stretching sprite
    sf::IntRect rect = tiles[FIRST]->getSprite()->getTextureRect();
    float X = 200.f/rect.width;
    float Y = 128.f/rect.height;
    tiles[FIRST]->getSprite()->setScale(X, Y);


    //long middle tile,
    size.set(252, 52);
    pos.set(250, 200);//to resize you have to resize in 3 places
    tiles.push_back (new StaticBox( pos, size, m_world ) );
    tiles[SECOND]->load( "assets/tiles/longTileT2.png" );
    rect = tiles[SECOND]->getSprite()->getTextureRect();
    X = 250.f/rect.width;
    Y = 60.f/rect.height;
    tiles[SECOND]->getSprite()->setScale(X, Y);


    size.set(252, 20);
    pos.set(750, 300);//to resize you have to resize in 3 places
    tiles.push_back (new StaticBox( pos, size, m_world ) );
    tiles[THIRD]->load( "assets/tiles/13.png" );
    rect = tiles[THIRD]->getSprite()->getTextureRect();
    X = 252.f/rect.width;
    Y = 40.f/rect.height;//more
    tiles[THIRD]->getSprite()->setScale(X, Y);
}