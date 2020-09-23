#include <SFML/Graphics.hpp>
#include <math.h>

using namespace sf;
using namespace std;



RenderWindow WindoW(VideoMode(1100, 800), "Game", Style::Default, ContextSettings(0, 0, 5, 1, 1, 0, false));
Event Ev;
Mouse Mice;
RectangleShape *WallList;
int KolWalls, MaxWalls = 1000;
int WallSize = 20;
float R = 400, Rr = R * 10;
bool RightPressed = false, IsLight = false, LeftPressed = false;

void Draw();
bool IsAlreadyBuilt(int x, int y);
void ClickEventManage(); 
void DeleteAndMove(int x, int y);
void DrawShadows();

int main()
{

	WindoW.setMouseCursorVisible(true);
	WallList = new RectangleShape[MaxWalls];
	while (WindoW.isOpen())
	{
		Draw();
		ClickEventManage();


		while (WindoW.pollEvent(Ev))
		{
			if (Ev.type == Event::Closed) WindoW.close();
		}
	}


	return 0;
}

void Draw()
{
	WindoW.clear(Color::Black);

	string s = "" + KolWalls;

	WindoW.setTitle(s);

	if (IsLight) {
		for (int i = R; i >= R / 2; i -= 4)
		{
			CircleShape Mse;
			Mse.setRadius(i);
			Mse.setFillColor(Color(255 * (i - R), 255 * (i - R), 255 * (i - R)));
			Mse.setPosition(Mice.getPosition(WindoW).x - i, Mice.getPosition(WindoW).y - i);

			WindoW.draw(Mse);

		}
	}

	if (IsLight) DrawShadows();

	for (int i = 0; i < KolWalls; i++)
	{
		WindoW.draw(WallList[i]);
	}

	WindoW.display();
}
void ClickEventManage()
{
	if (Mice.isButtonPressed(Mouse::Button::Right))
	{
		if (!RightPressed)
		{
			if (IsLight)
			{
				WindoW.setMouseCursorVisible(true);
				IsLight = false;
			}
			else
			{
				//WindoW.setMouseCursorVisible(false);
				IsLight = true;
			}
			RightPressed = true;
		}
	}
	else RightPressed = false;

	if (Mice.isButtonPressed(Mouse::Button::Left))
	{
		if (!LeftPressed && !IsLight) {
			LeftPressed = true;
			if (IsAlreadyBuilt(Mice.getPosition(WindoW).x - Mice.getPosition(WindoW).x % WallSize, Mice.getPosition(WindoW).y - Mice.getPosition(WindoW).y % WallSize))
			{
				DeleteAndMove(Mice.getPosition(WindoW).x - Mice.getPosition(WindoW).x % WallSize, Mice.getPosition(WindoW).y - Mice.getPosition(WindoW).y % WallSize);
			}
			else if (KolWalls < MaxWalls)
			{
				WallList[KolWalls] = RectangleShape(Vector2f(WallSize, WallSize));
				WallList[KolWalls].setFillColor(Color(101, 21, 107));
				WallList[KolWalls].setPosition(Mice.getPosition(WindoW).x - Mice.getPosition(WindoW).x % WallSize, Mice.getPosition(WindoW).y - Mice.getPosition(WindoW).y % WallSize);
				KolWalls++;
			}
		}
	}
	else LeftPressed = false;
}

bool IsAlreadyBuilt(int x, int y)
{
	bool Is = false;
	for (int i = 0; i < KolWalls; i++)
	{
		if (WallList[i].getPosition().x == x & WallList[i].getPosition().y == y)
		{
			Is = true;
			break;
		}
	}
	return Is;
}

void DeleteAndMove(int x, int y)
{
	for (int i = 0; i < KolWalls; i++)
	{
		if (WallList[i].getPosition().x == x & WallList[i].getPosition().y == y)
		{
			for (int j = i + 1; j < KolWalls; j++)
			{
				WallList[j - 1] = WallList[j];
			}
			KolWalls--;
			break;
		}
	}
}

void DrawShadows()
{
	for (int i = 0; i < KolWalls; i++)
	{
		//if ()
	}
	for (int i = 0; i < KolWalls; i++)
	{
		Vector2f P1, P2, P3, P4;
		Vector2i MP;
		MP = Mice.getPosition(WindoW);
		P1 = WallList[i].getPosition();
		P2 = WallList[i].getPosition(); P2.x += WallList[i].getSize().x;
		P3 = WallList[i].getPosition(); P3.y += WallList[i].getSize().y;
		P4 = WallList[i].getPosition(); P4.x = P2.x; P4.y = P3.y;

		ConvexShape Con;
		Con.setFillColor(Color::Black);
		if (MP.y >= P4.y && MP.x >= P4.x && (P4.x - MP.x) * (P4.x - MP.x) + (MP.y - P4.y) * (MP.y - P4.y) < R * R)
		{
			Vector2f Temp1;
			Temp1.x = MP.x - (Rr * (MP.x - P3.x)) / (sqrtf((MP.y - P3.y) * (MP.y - P3.y) + (MP.x - P3.x) * (MP.x - P3.x)));
			if (Temp1.x > P3.x) Temp1.x = P3.x;
			Temp1.y = MP.y - (Rr * (MP.y - P3.y)) / (sqrtf((MP.y - P3.y) * (MP.y - P3.y) + (MP.x - P3.x) * (MP.x - P3.x)));
			if (Temp1.y > P3.y) Temp1.y = P3.y;
			Vector2f Temp2;
			Temp2.x = MP.x - (Rr * (MP.x - P2.x)) / (sqrtf((MP.y - P2.y) * (MP.y - P2.y) + (MP.x - P2.x) * (MP.x - P2.x)));
			if (Temp2.x > P2.x) Temp2.x = P2.x;
			Temp2.y = MP.y - (Rr * (MP.y - P2.y)) / (sqrtf((MP.y - P2.y) * (MP.y - P2.y) + (MP.x - P2.x) * (MP.x - P2.x)));
			if (Temp2.y > P2.y) Temp2.y = P2.y;
			///
			Con.setPointCount(3);
			Con.setPoint(0, P3);
			Con.setPoint(1, P1);
			Con.setPoint(2, Temp1);
			WindoW.draw(Con);

			Con.setPoint(0, P1);
			Con.setPoint(1, Temp2);
			Con.setPoint(2, Temp1);
			WindoW.draw(Con);

			Con.setPoint(0, P2);
			Con.setPoint(1, P1);
			Con.setPoint(2, Temp2);
			WindoW.draw(Con);
			///
		}
		else if (MP.y >= P3.y && MP.x <= P3.x && (P3.x - MP.x) * (P3.x - MP.x) + (MP.y - P3.y) * (MP.y - P3.y) < R * R)
		{
			Vector2f Temp1;
			Temp1.x = MP.x - (Rr * (MP.x - P1.x)) / (sqrtf((MP.y - P1.y) * (MP.y - P1.y) + (MP.x - P1.x) * (MP.x - P1.x)));
			if (Temp1.x < P1.x) Temp1.x = P1.x;
			Temp1.y = MP.y - (Rr * (MP.y - P1.y)) / (sqrtf((MP.y - P1.y) * (MP.y - P1.y) + (MP.x - P1.x) * (MP.x - P1.x)));
			if (Temp1.y > P1.y) Temp1.y = P1.y;
			Vector2f Temp2;
			Temp2.x = MP.x - (Rr * (MP.x - P4.x)) / (sqrtf((MP.y - P4.y) * (MP.y - P4.y) + (MP.x - P4.x) * (MP.x - P4.x)));
			if (Temp2.x < P4.x) Temp2.x = P4.x;
			Temp2.y = MP.y - (Rr * (MP.y - P4.y)) / (sqrtf((MP.y - P4.y) * (MP.y - P4.y) + (MP.x - P4.x) * (MP.x - P4.x)));
			if (Temp2.y > P4.y) Temp2.y = P4.y;

			Con.setPointCount(3);
			Con.setPoint(0, P1);
			Con.setPoint(1, Temp1);
			Con.setPoint(2, P2);
			WindoW.draw(Con);

			Con.setPoint(0, P2);
			Con.setPoint(1, Temp2);
			Con.setPoint(2, Temp1);
			WindoW.draw(Con);

			Con.setPoint(0, P2);
			Con.setPoint(1, P4);
			Con.setPoint(2, Temp2);
			WindoW.draw(Con);
		}
		else if (MP.y <= P2.y && MP.x >= P2.x && (P2.x - MP.x) * (P2.x - MP.x) + (MP.y - P2.y) * (MP.y - P2.y) < R * R)
		{
			Vector2f Temp1;
			Temp1.x = MP.x - (Rr * (MP.x - P1.x)) / (sqrtf((MP.y - P1.y) * (MP.y - P1.y) + (MP.x - P1.x) * (MP.x - P1.x)));
			if (Temp1.x > P1.x) Temp1.x = P1.x;
			Temp1.y = MP.y - (Rr * (MP.y - P1.y)) / (sqrtf((MP.y - P1.y) * (MP.y - P1.y) + (MP.x - P1.x) * (MP.x - P1.x)));
			if (Temp1.y < P1.y) Temp1.y = P1.y;
			Vector2f Temp2;
			Temp2.x = MP.x - (Rr * (MP.x - P4.x)) / (sqrtf((MP.y - P4.y) * (MP.y - P4.y) + (MP.x - P4.x) * (MP.x - P4.x)));
			if (Temp2.x > P4.x) Temp2.x = P4.x;
			Temp2.y = MP.y - (Rr * (MP.y - P4.y)) / (sqrtf((MP.y - P4.y) * (MP.y - P4.y) + (MP.x - P4.x) * (MP.x - P4.x)));
			if (Temp2.y < P4.y) Temp2.y = P4.y;

			Con.setPointCount(3);
			Con.setPoint(0, P1);
			Con.setPoint(1, Temp1);
			Con.setPoint(2, P3);
			WindoW.draw(Con);

			Con.setPoint(0, P3);
			Con.setPoint(1, Temp2);
			Con.setPoint(2, Temp1);
			WindoW.draw(Con);

			Con.setPoint(0, P3);
			Con.setPoint(1, P4);
			Con.setPoint(2, Temp2);
			WindoW.draw(Con);
		}
		else if (MP.y <= P1.y && MP.x <= P1.x && (P1.x - MP.x) * (P1.x - MP.x) + (MP.y - P1.y) * (MP.y - P1.y) < R * R)
		{
			Vector2f Temp1;
			Temp1.x = MP.x - (Rr * (MP.x - P3.x)) / (sqrtf((MP.y - P3.y) * (MP.y - P3.y) + (MP.x - P3.x) * (MP.x - P3.x)));
			if (Temp1.x < P3.x) Temp1.x = P3.x;
			Temp1.y = MP.y - (Rr * (MP.y - P3.y)) / (sqrtf((MP.y - P3.y) * (MP.y - P3.y) + (MP.x - P3.x) * (MP.x - P3.x)));
			if (Temp1.y < P3.y) Temp1.y = P3.y;
			Vector2f Temp2;
			Temp2.x = MP.x - (Rr * (MP.x - P2.x)) / (sqrtf((MP.y - P2.y) * (MP.y - P2.y) + (MP.x - P2.x) * (MP.x - P2.x)));
			if (Temp2.x < P2.x) Temp2.x = P2.x;
			Temp2.y = MP.y - (Rr * (MP.y - P2.y)) / (sqrtf((MP.y - P2.y) * (MP.y - P2.y) + (MP.x - P2.x) * (MP.x - P2.x)));
			if (Temp2.y < P2.y) Temp2.y = P2.y;

			Con.setPointCount(3);
			Con.setPoint(0, P3);
			Con.setPoint(1, Temp1);
			Con.setPoint(2, P4);
			WindoW.draw(Con);

			Con.setPoint(0, P4);
			Con.setPoint(1, Temp2);
			Con.setPoint(2, Temp1);
			WindoW.draw(Con);

			Con.setPoint(0, P2);
			Con.setPoint(1, P4);
			Con.setPoint(2, Temp2);
			WindoW.draw(Con);
		}
		else if (MP.x <= P2.x && MP.x >= P1.x && MP.y < P1.y && (P1.x - MP.x) * (P1.x - MP.x) + (MP.y - P1.y) * (MP.y - P1.y) < R * R)
		{
			Vector2f Temp1;
			Temp1.x = MP.x - (Rr * (MP.x - P1.x)) / (sqrtf((MP.y - P1.y) * (MP.y - P1.y) + (MP.x - P1.x) * (MP.x - P1.x)));
			Temp1.y = MP.y - (Rr * (MP.y - P1.y)) / (sqrtf((MP.y - P1.y) * (MP.y - P1.y) + (MP.x - P1.x) * (MP.x - P1.x)));
			Vector2f Temp2;
			Temp2.x = MP.x - (Rr * (MP.x - P2.x)) / (sqrtf((MP.y - P2.y) * (MP.y - P2.y) + (MP.x - P2.x) * (MP.x - P2.x)));
			Temp2.y = MP.y - (Rr * (MP.y - P2.y)) / (sqrtf((MP.y - P2.y) * (MP.y - P2.y) + (MP.x - P2.x) * (MP.x - P2.x)));
			
			Con.setPointCount(3);
			Con.setPoint(0, P1);
			Con.setPoint(1, Temp1);
			Con.setPoint(2, P3);
			WindoW.draw(Con);

			Con.setPoint(0, P3);
			Con.setPoint(1, P4);
			Con.setPoint(2, Vector2f(MP.x, MP.y + R));
			WindoW.draw(Con);

			Con.setPoint(0, P3);
			Con.setPoint(1, Temp1);
			Con.setPoint(2, Vector2f(MP.x, MP.y + R));
			WindoW.draw(Con);

			Con.setPoint(0, Temp2);
			Con.setPoint(1, P4);
			Con.setPoint(2, Vector2f(MP.x, MP.y + R));
			WindoW.draw(Con);

			Con.setPoint(0, P2);
			Con.setPoint(1, P4);
			Con.setPoint(2, Temp2);
			WindoW.draw(Con);
		}
		else if (MP.x <= P2.x && MP.x >= P1.x && MP.y > P3.y && (P3.x - MP.x) * (P3.x - MP.x) + (MP.y - P3.y) * (MP.y - P3.y) < R * R)
		{
			Vector2f Temp1;
			Temp1.x = MP.x - (Rr * (MP.x - P3.x)) / (sqrtf((MP.y - P3.y) * (MP.y - P3.y) + (MP.x - P3.x) * (MP.x - P3.x)));
			Temp1.y = MP.y - (Rr * (MP.y - P3.y)) / (sqrtf((MP.y - P3.y) * (MP.y - P3.y) + (MP.x - P3.x) * (MP.x - P3.x)));
			Vector2f Temp2;
			Temp2.x = MP.x - (Rr * (MP.x - P4.x)) / (sqrtf((MP.y - P4.y) * (MP.y - P4.y) + (MP.x - P4.x) * (MP.x - P4.x)));
			Temp2.y = MP.y - (Rr * (MP.y - P4.y)) / (sqrtf((MP.y - P4.y) * (MP.y - P4.y) + (MP.x - P4.x) * (MP.x - P4.x)));

			Con.setPointCount(3);
			Con.setPoint(0, P1);
			Con.setPoint(1, Temp1);
			Con.setPoint(2, P3);
			WindoW.draw(Con);

			Con.setPoint(0, P1);
			Con.setPoint(1, P2);
			Con.setPoint(2, Vector2f(MP.x, MP.y - R));
			WindoW.draw(Con);

			Con.setPoint(0, P1);
			Con.setPoint(1, Temp1);
			Con.setPoint(2, Vector2f(MP.x, MP.y - R));
			WindoW.draw(Con);

			Con.setPoint(0, Temp2);
			Con.setPoint(1, P2);
			Con.setPoint(2, Vector2f(MP.x, MP.y - R));
			WindoW.draw(Con);

			Con.setPoint(0, P2);
			Con.setPoint(1, P4);
			Con.setPoint(2, Temp2);
			WindoW.draw(Con);
		}
		else if (MP.y <= P3.y && MP.y >= P1.y && MP.x > P2.x && (P2.x - MP.x) * (P2.x - MP.x) + (MP.y - P2.y) * (MP.y - P2.y) < R * R)
		{
			Vector2f Temp1;
			Temp1.x = MP.x - (Rr * (MP.x - P2.x)) / (sqrtf((MP.y - P2.y) * (MP.y - P2.y) + (MP.x - P2.x) * (MP.x - P2.x)));
			Temp1.y = MP.y - (Rr * (MP.y - P2.y)) / (sqrtf((MP.y - P2.y) * (MP.y - P2.y) + (MP.x - P2.x) * (MP.x - P2.x)));
			Vector2f Temp2;
			Temp2.x = MP.x - (Rr * (MP.x - P4.x)) / (sqrtf((MP.y - P4.y) * (MP.y - P4.y) + (MP.x - P4.x) * (MP.x - P4.x)));
			Temp2.y = MP.y - (Rr * (MP.y - P4.y)) / (sqrtf((MP.y - P4.y) * (MP.y - P4.y) + (MP.x - P4.x) * (MP.x - P4.x)));

			Con.setPointCount(3);
			Con.setPoint(0, P1);
			Con.setPoint(1, Temp1);
			Con.setPoint(2, P2);
			WindoW.draw(Con);

			Con.setPoint(0, P1);
			Con.setPoint(1, P3);
			Con.setPoint(2, Vector2f(MP.x - R, MP.y));
			WindoW.draw(Con);

			Con.setPoint(0, P1);
			Con.setPoint(1, Temp1);
			Con.setPoint(2, Vector2f(MP.x - R, MP.y));
			WindoW.draw(Con);

			Con.setPoint(0, Temp2);
			Con.setPoint(1, P3);
			Con.setPoint(2, Vector2f(MP.x - R, MP.y));
			WindoW.draw(Con);

			Con.setPoint(0, P3);
			Con.setPoint(1, P4);
			Con.setPoint(2, Temp2);
			WindoW.draw(Con);
		}
		else if (MP.y <= P3.y && MP.y >= P1.y && MP.x < P3.x && (P1.x - MP.x) * (P1.x - MP.x) + (MP.y - P1.y) * (MP.y - P1.y) < R * R)
		{
			Vector2f Temp1;
			Temp1.x = MP.x - (Rr * (MP.x - P3.x)) / (sqrtf((MP.y - P3.y) * (MP.y - P3.y) + (MP.x - P3.x) * (MP.x - P3.x)));
			Temp1.y = MP.y - (Rr * (MP.y - P3.y)) / (sqrtf((MP.y - P3.y) * (MP.y - P3.y) + (MP.x - P3.x) * (MP.x - P3.x)));
			Vector2f Temp2;
			Temp2.x = MP.x - (Rr * (MP.x - P1.x)) / (sqrtf((MP.y - P1.y) * (MP.y - P1.y) + (MP.x - P1.x) * (MP.x - P1.x)));
			Temp2.y = MP.y - (Rr * (MP.y - P1.y)) / (sqrtf((MP.y - P1.y) * (MP.y - P1.y) + (MP.x - P1.x) * (MP.x - P1.x)));

			Con.setPointCount(3);
			Con.setPoint(0, P1);
			Con.setPoint(1, Temp2);
			Con.setPoint(2, P2);
			WindoW.draw(Con);

			Con.setPoint(0, P2);
			Con.setPoint(1, P4);
			Con.setPoint(2, Vector2f(MP.x + R, MP.y));
			WindoW.draw(Con);

			Con.setPoint(0, P2);
			Con.setPoint(1, Temp2);
			Con.setPoint(2, Vector2f(MP.x + R, MP.y));
			WindoW.draw(Con);

			Con.setPoint(0, Temp1);
			Con.setPoint(1, P4);
			Con.setPoint(2, Vector2f(MP.x + R, MP.y));
			WindoW.draw(Con);

			Con.setPoint(0, P3);
			Con.setPoint(1, P4);
			Con.setPoint(2, Temp1);
			WindoW.draw(Con);	
		}
	}
}

