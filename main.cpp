#include <SFML/Graphics.hpp>
#include <time.h>
#include <math.h>
#include<iostream>
#include<vector>
#include "Player.h"

using namespace sf;
using namespace std;

#define W 1200
#define H 700
#define TILE_ZE 32

bool collision;

string lvl;
vector<RectangleShape> holder =  vector<RectangleShape>();



void drawGrid(RenderTexture* g);
void checkCollide(RectangleShape* core, int posx, int posy);


int main()
{
	lvl += "##########################################";
	lvl += "...........................#..............";
	lvl += "...........................#..............";
	lvl += "..........................................";
	lvl += "..........................................";
	lvl += "...........................#..............";
	lvl += "...........................#..............";
	lvl += ".......................######.............";
	lvl += "..........#########################.......";
	lvl += "..........#######.......#############.....";
	lvl += "......###############..........####.......";
	lvl += "#.........###########.........#####.....##";
	lvl += "#.........###########........######.......";
	lvl += "#...........................#######.......";
	lvl += "##########################################";

	srand(time(0));

	RenderWindow window(VideoMode(W, H), "Nova0");
	window.setFramerateLimit(60);


	Sprite sprite;

	RenderTexture t;
	Texture p;
	t.create(W, H);
	t.setSmooth(true);
	sprite.setTexture(t.getTexture());

	
	p.loadFromFile("./pixer.jpg");
	

	Player pl(&p);
	RectangleShape* rec = pl.getCore();

	float dx=0.00f, dy=0.0f;


	float deltaTime = 0.0f;
	Clock clock;

	drawGrid(&t);


	while (window.isOpen())
	{
		deltaTime = clock.restart().asSeconds();

		if (deltaTime > 1.0f / 40.0f)
		{
			deltaTime = 1.0f / 40.0f;
		}
		Event e;
		while (window.pollEvent(e))
		{
			switch (e.type)
			{
			case Event::Closed:
				window.close();
				break;
			case Event::KeyPressed:
				switch (e.key.code)
				{
				case Keyboard::N:
					window.close();
					break;
				}
				break;
			}
		}

		

			
		try {
			


			int cor_x = (int)round((rec->getPosition().x) / TILE_ZE);
			int cor_y = (int)round(((rec->getPosition().y) / TILE_ZE));
			int cor_y1 = (int)(cor_y * 42);

			//1|2|3
			//4|#|5
			//6|7|8

			checkCollide(rec, cor_x, cor_y);

			checkCollide(rec, cor_x + 1, cor_y); //5
			checkCollide(rec, cor_x, cor_y + 1); //7
			checkCollide(rec, cor_x + 1, cor_y + 1); //8
			
			
			
			int x_offset = (rec->getPosition().x / TILE_ZE) == 0 ? 0 : 1;
			int y_offset = (rec->getPosition().y / TILE_ZE) == 0 ? 0 : 1;

			checkCollide(rec, cor_x - x_offset, cor_y); //4
			checkCollide(rec, cor_x, cor_y - y_offset); //2
			checkCollide(rec, cor_x - x_offset, cor_y - y_offset); //1

			checkCollide(rec, cor_x + x_offset, cor_y - y_offset); //3
			checkCollide(rec, cor_x - x_offset, cor_y + 1); //6

			


		}
		catch (exception) {
			throw;
		}
		
		

		dx = .0f;
		dy = .0f;

		pl.update(deltaTime);

		////// draw  ///////
		window.clear();

		window.draw(sprite);
		pl.Draw(window);
		window.display();
	}

	return 0;
}


void drawGrid(RenderTexture* g)
{
	
	for (int i = 0; i < 15; i++)
	{

		

		for (int j = 0; j < 43; j++)
		{
			RectangleShape l(Vector2f(TILE_ZE, TILE_ZE));
			l.setFillColor(Color::Red);

			if (lvl[j + (i*42)] == '#') 
			{
				

				l.setFillColor(Color::Black);
				
				
				
			}
			l.setPosition(j * TILE_ZE,  H - i * TILE_ZE - TILE_ZE);
			g->draw(l);
			
			l.setPosition(j * TILE_ZE, i * TILE_ZE);


			holder.push_back(l);
		}

	}

	
}




void checkCollide(RectangleShape* core, int posx, int posy)
{

	float push = 1.0f;

	float  cx = posx * TILE_ZE;
	float  cy = posy * TILE_ZE;
	float dx = core->getPosition().x - cx;
	float dy = core->getPosition().y - cy;

	float intersectX = abs(dx) - (TILE_ZE);
	float intersectY = abs(dy) - (TILE_ZE);


	if ((intersectX < 0.0f) && (intersectY < 0.0f) && (lvl[posx + posy*42]=='#'))
	{
		collision = true;

		if (intersectX > intersectY)
		{
			if (dx > 0.0f)
			{
				core->move(-1*(intersectX * push ), 0.0f);
			}
			else
			{
				core->move((intersectX * push ), 0.0f);
			}
		}
		else
		{
			if (dy > 0.0f)
			{
				core->move(0.0f, -1*intersectY * push);
			}
			else
			{
				core->move(0.0f, intersectY * push);
			}
		}


	}
}