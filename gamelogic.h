#pragma once
#include <exception>
#include <stdlib.h>
#include <time.h>
#include <vector>

using namespace System;
using namespace System::ComponentModel;
using namespace System::Collections;
using namespace System::Windows::Forms;
using namespace System::Data;
using namespace System::Drawing;


ref class Position {
private:
	int x;
	int y;
public:
	//
	Position() { x = 1; y = 1; }
	Position(int x, int y)
	{
		if (x >= 0 && x <= 2)
			this->x = x;
		else 
			throw gcnew Exception("Значення позиції повинно бути 1 <= x <= 2");
		
		if (y >= 0 && y <= 12)
			this->y = y;
		else 
			throw gcnew Exception("Значення позиції повинно бути 1 <= y <= 12");
	}
	Position(const Position^ pos)
	{
		this->x = pos->x;
		this->y = pos->y;
	}

	Position^ operator=(const Position^ pos)
	{
		this->x = pos->x;
		this->y = pos->y;
		return this;
	}
	bool operator==(const Position^ pos)
	{
		if (this->x == pos->x && this->y == pos->y)
			return true;
		else return false;
	}
	Position^ operator+(int plus)
	{
		int tmpY = 0;
		int tmpX = x;
		if (x == 2)
		{
			tmpY = y + plus;
			if (tmpY > 12)
			{
				tmpY = 12 - (tmpY - 13);
				tmpX = x - 1;
			}
		}
		else {
			tmpY = y - plus;
			if (tmpY < 1)
			{
				tmpY = 1 + (tmpY * (-1));
				tmpX = x + 1;
			}
		}
		return gcnew Position(tmpX, tmpY);
	}
	//
	int getX()
	{
		return this->x;
	}
	void setX(int x)
	{
		if (x >= 1 && x <= 2)
			this->x = x;
		else
			throw gcnew Exception("Значення позиції повинно бути 1 <= x <= 2");

	}
	int getY()
	{
		return this->y;
	}
	void setY(int y)
	{
		if (y >= 1 && y <= 12)
			this->y = y;
		else
			throw gcnew Exception("Значення позиції повинно бути 1 <= y <= 12");
	}
};

ref class Checker {
private:
	bool active; 
	Position^ pos;
public:
	//
	Checker(Position ^ pos)
	{
		this->active = true;
		this->pos = pos;
	}
	~Checker(){
		delete pos;
	}
	//
	bool getActive()
	{
		return active;
	}
	void setActive(bool active)
	{
		this->active = active;
	}

	Position^ getPos()
	{
		return pos;
	}
	void setPos(Position^ pos)
	{
		this->pos = pos;
	}
	//
	bool canExit(bool color)
	{
		if (color)
		{
			if (pos->getX() == 1 && pos->getY() <= 6)
				return true;
		}
		else
		{
			if (pos->getX() == 2 && pos->getY() >= 7)
				return true;
		}
		return false;
	}
	bool ifCanMove(int size, bool color)
	{
		if (color && (this->pos->getY()-size) < 1 && this->pos->getX() == 1)
			return false;
		else if (!color && (this->pos->getY()+size) > 12 && this->pos->getX() == 2)
			return false;
		else return true;
	}
	void move(int size)
	{
		this->setPos(this->getPos() + size);
	}
};

ref class Cube {
private:
	int value;
	bool active;
	bool doubleMove;
public:
	//
	Cube()
	{
		value = 1;
		active = false;
		doubleMove = false;
	}
	//
	int getValue() {
		return this->value;
	}
	void setValue(int value) {
		if (value >= 1 && value <= 6)
			this->value = value;
		else
			throw gcnew Exception("Значення грального куба повинно бути 1 <= x <= 6");
	}
	bool getActive() {
		return this->active;
	}
	void setActive(bool active) {
		this->active = active;
	}
	bool getDoubleMove() {
		return this->doubleMove;
	}
	void setDoubleMove(bool doubleMove) {
		this->doubleMove = doubleMove;
	}
	//
	void generate()
	{
		this->value = rand() % 6 + 1;
		this->active = active;
	}

	void use()
	{
		if (active)
		{
			if (this->doubleMove)
				this->doubleMove = false;

			else
				this->active = false;
		}
	}

	//draw
	void drawCubes(Graphics^ g, int x, int y) {
		Image^ img;
		if (this->active)
		{
			switch (this->value)
			{
			case 1:
				img = Image::FromFile("1.png");
				break;
			case 2:
				img = Image::FromFile("2.png");
				break;
			case 3:
				img = Image::FromFile("3.png");
				break;
			case 4:
				img = Image::FromFile("4.png");
				break;
			case 5:
				img = Image::FromFile("5.png");
				break;
			case 6:
				img = Image::FromFile("6.png");
				break;
			}
			g->DrawImage(img, x, y, 50, 50);
		}
		else {
			switch (this->value)
			{
			case 1:
				img = Image::FromFile("1un.png");
				break;
			case 2:
				img = Image::FromFile("2un.png");
				break;
			case 3:
				img = Image::FromFile("3un.png");
				break;
			case 4:
				img = Image::FromFile("4un.png");
				break;
			case 5:
				img = Image::FromFile("5un.png");
				break;
			case 6:
				img = Image::FromFile("6un.png");
				break;
			}
			g->DrawImage(img, x, y, 50, 50);
		}
	}
};

ref class Player {
private:
	bool color; //1-white 0-black
	bool active;
	array<Checker^>^ checkers;
public:
	//
	Player(bool color)
	{
		this->color = color;
		this->active = false;

		checkers = gcnew array<Checker^>(15);
		if (color)
		{
			for (int i = 0; i < 15; i++)
				checkers[i] = gcnew Checker(gcnew Position(2, 1));
		}
		else
		{
			for (int i = 0; i < 15; i++)
				checkers[i] = gcnew Checker(gcnew Position(1, 12));
		}

	}
	~Player()
	{
		for (int i = 0; i < 15; i++)
		{
			delete checkers[i];
		}
		delete[] checkers;
	}
	//
	bool getColor()
	{
		return this->color;
	}
	void setColor(bool color)
	{
		this->color = color;
	}
	bool getActive()
	{
		return this->active;
	}
	void setActive(bool active)
	{
		this->active = active;
	}
	array<Checker^>^ getCheckers()
	{
		return checkers;
	}
	//
	void printHowManyActive(Graphics^ g, int x, int y, String^ text, Font^ f, SolidBrush^ b)
	{
		int couter;
		for (int i = 0; i < 15; i++)
		{
			if (checkers[i]->getActive())
			{
				couter++;
			}
		}
		g->DrawString(text + couter, f, b, x, y);

	}
	
};

ref class Board {
private:
	Player^ player1;
	Player^ player2;
	array<Cube^>^ cubes;
	bool selected;
	Position^ posSel;

	PictureBox^ board;
	PictureBox^ info;
	PictureBox^ exitZone0;
	PictureBox^ exitZone1;
public:
	Board(PictureBox^ board, PictureBox^ info, PictureBox^ exitZone0, PictureBox^ exitZone1) {
		player1 = gcnew Player(1);
		player2 = gcnew Player(0);

		cubes = gcnew array<Cube^> (2);
		for (int i = 0; i < 2; i++)
		{
			cubes[i] = gcnew Cube();
		}

		selected = false;

		player1->setActive(true);

		this->board = board;
		this->info = info;
		this->exitZone0 = exitZone0;
		this->exitZone1 = exitZone1;

		drawBoard(this->board);
		drawInfo(this->info);

		generateCubes();
	}
	~Board() {
		delete player1;
		delete player2;
		for (int i = 0; i < 2; i++)
		{
			delete cubes[i];
		}
		delete[] cubes;
		delete posSel;
		delete board;
		delete info;
		delete exitZone0;
		delete exitZone1;
	}
	//program logic function
	void generateCubes()
	{
		
		for (int j = 0; j < 2; j++)
		{
			cubes[j]->generate();
			cubes[j]->setActive(true);

			if(j == 1)
			{
				if (cubes[j]->getValue() == cubes[j - 1]->getValue())
				{
					cubes[j]->setDoubleMove(true);
					cubes[j - 1]->setDoubleMove(true);
				}
			}
		}
		drawInfo(this->info);

		checkIfNextMove();
		
	}
	int checkIfNextMove()
	{
		int checker = 0;
		int checker3 = 0;
		if (player1->getActive())
		{
			for (int i = 0; i < 15; i++)
			{
				if (!player1->getCheckers()[i]->getActive())
				{
					checker3++;
				}
			}
			if (checker3 == 15)
			{
				drawWin(this->info, player2->getColor());
				return 0;
			}

			if (cubes[0]->getActive() || cubes[1]->getActive())
			{
				int checker2 = 0;
				for (int i = 0; i < 15; i++)
				{
					if (player1->getCheckers()[i]->canExit(player1->getColor()))
					{
						checker2++;
					}
				}
				if (checker2 >= 15 - checker3)
					return 0;
			}
			for (int i = 0; i < 15; i++)
			{
				if (player1->getCheckers()[i]->getActive())
				{
					array<Position^>^ arr = findPositions(player1->getCheckers()[i]->getPos());
					if (arr == nullptr)
						checker++;
				}
				else 
					checker++;
			}
			if (checker == 15)
			{
				this->player1->setActive(false);
				this->player2->setActive(true);

				generateCubes();
			}
		}
		else if (player2->getActive())
		{
			for (int i = 0; i < 15; i++)
			{
				if (!player2->getCheckers()[i]->getActive())
				{
					checker3++;
				}
			}
			if (checker3 == 15)
			{
				drawWin(this->info, player2->getColor());
				return 0;
			}

			if (cubes[0]->getActive() || cubes[1]->getActive())
			{
				int checker2 = 0;
				for (int i = 0; i < 15; i++)
				{
					if (player2->getCheckers()[i]->canExit(player2->getColor()))
					{
						checker2++;
					}
				}
				if (checker2 >= 15 - checker3)
					return 0;
			}
			for (int i = 0; i < 15; i++)
			{
				if (player2->getCheckers()[i]->getActive())
				{
					array<Position^>^ arr = findPositions(player2->getCheckers()[i]->getPos());
					if (arr == nullptr)
						checker++;
				}
				else 
					checker++;
			}
			if (checker == 15)
			{
				this->player1->setActive(true);
				this->player2->setActive(false);

				generateCubes();
			}
		}
	}
	//board click function
	void boardClick(int x, int y)
	{
		y = (y / 300) + 1;
		x = (x / 50) + 1;

		if (!selected)
		{
			
			posSel = gcnew Position(y, x);

			if (player1->getActive())
			{
				for (int i = 0; i < 15; i++)
				{
					if (player1->getCheckers()[i]->getActive())
					{
						if (player1->getCheckers()[i]->getPos() == posSel)
						{
							drawPossibleBoard(this->board, findPositions(posSel));
							selected = true;
						}
					}
				}
			}
			if (player2->getActive())
			{
				for (int i = 0; i < 15; i++)
				{
					if (player2->getCheckers()[i]->getActive())
					{
						if (player2->getCheckers()[i]->getPos() == posSel)
						{
							drawPossibleBoard(this->board, findPositions(posSel));
							selected = true;
						}
					}
				}
			}
		}
		else if (selected)
		{
			selected = false;

			Position^ tmpPos = gcnew Position(y, x);
			array<Position^>^ arr = findPositions(posSel);

			if (arr != nullptr)
			{
				bool make = false;
				for (int m = 0; m < arr->Length; m++)
				{
					if (arr[m] == tmpPos)
					{
						for (int n = 0; n < 15; n++)
						{
							if (player1->getActive())
							{
								if (player1->getCheckers()[n]->getPos() == posSel)
								{
									player1->getCheckers()[n]->setPos(tmpPos);
									for (int i = 0; i < 2; i++)
									{
										if (cubes[i]->getActive())
										{
											if (posSel + cubes[i]->getValue() == tmpPos)
											{
												cubes[i]->use();
												break;
											}
										}
									}
									make = true;
									break;
								}
							}
							else if (player2->getActive())
							{
								if (player2->getCheckers()[n]->getPos() == posSel)
								{
									player2->getCheckers()[n]->setPos(tmpPos);
									int sum = 0;
									for (int i = 0; i < 2; i++)
									{
										if (cubes[i]->getActive())
										{
											if (posSel + cubes[i]->getValue() == tmpPos)
											{
												cubes[i]->use();
												break;
											}
										}
									}
									make = true;
									break;
								}
							}
							if (make)
								break;
						}
					}
				}
				drawBoard(this->board);
				drawInfo(this->info);
				checkIfNextMove();
			}


		}
		
	}
	
	array<Position^>^ findPositions(Position^ pos)
	{
		int cube1 = 0, cube2 = 0;
		int counter = 0;
		if (cubes[0]->getActive())
			cube1 = cubes[0]->getValue();
		if (cubes[1]->getActive())
			cube2 = cubes[1]->getValue();

		

		if (player1->getActive())
		{
			for (int i = 0; i < 15; i++)
			{
				if (player1->getCheckers()[i]->getPos() == pos)
				{
					if (cube1 != 0 && player1->getCheckers()[i]->ifCanMove(cube1, this->player1->getColor()))
					{
						bool check = true;
						for (int j = 0; j < 15; j++)
						{
							if (player2->getCheckers()[j]->getPos() == (pos + cube1))
							{
								check = !check;
								cube1 = 0;
								break;
							}
						}
						if (check)
						{
							counter++;
							break;
						}
					}
				}
			}
			for (int i = 0; i < 15; i++)
			{
				if (player1->getCheckers()[i]->getPos() == pos)
				{
					if (cube2 != 0 && player1->getCheckers()[i]->ifCanMove(cube2, this->player1->getColor()))
					{
						bool check = true;
						for (int j = 0; j < 15; j++)
						{
							if (player2->getCheckers()[j]->getPos() == (pos + cube2))
							{
								check = !check;
								cube2 = 0;
								break;
							}
						}
						if (check)
						{
							counter++;
							break;
						}
					}
				}
			}
		}
		else
		{

			for (int i = 0; i < 15; i++)
			{
				if (player2->getCheckers()[i]->getPos() == pos)
				{
					if (cube1 != 0 && player2->getCheckers()[i]->ifCanMove(cube1, this->player2->getColor()))
					{
						bool check = true;
						for (int j = 0; j < 15; j++)
						{
							if (player1->getCheckers()[j]->getPos() == (pos + cube1))
							{
								check = !check;
								cube1 = 0;
								break;
							}
						}
						if (check)
						{
							counter++;
							break;
						}
					}
				}
			}
			for (int i = 0; i < 15; i++)
			{
				if (player2->getCheckers()[i]->getPos() == pos)
				{
					if (cube2 != 0 && player2->getCheckers()[i]->ifCanMove(cube2, this->player2->getColor()))
					{
						bool check = true;
						for (int j = 0; j < 15; j++)
						{
							if (player1->getCheckers()[j]->getPos() == (pos + cube2))
							{
								check = !check;
								cube2 = 0;
								break;
							}
						}
						if (check)
						{
							counter++;
							break;
						}
					}
				}
			}
		}

		if(counter == 0)
			return nullptr;
		else
		{
			array<Position^>^ arr = gcnew array<Position^>(counter);
			for (int i = 0; i < arr->Length; i++)
			{
				if (cube1 > 0)
				{
					arr[i] = pos + cube1;
					cube1 = 0;
				}
				else if (cube2 > 0)
				{
					arr[i] = pos + cube2;
					cube2 = 0;
				}
			}
			
			return arr;
			
		}

		
	}
	int clickExitZone(bool color)
	{
		bool used = false;
		if (color && this->player1->getActive() && selected)
		{
			bool prev = false;
			for (int i = 0; i < 15; i++)
			{
				if (!this->player1->getCheckers()[i]->canExit(this->player1->getColor()) && this->player1->getCheckers()[i]->getActive())
					return 0;
				if (this->player1->getCheckers()[i]->getPos()->getY() > posSel->getY() && this->player1->getCheckers()[i]->getActive())
					prev = true;
			}

			if (!prev)
			{
				for (int n = 0; n < 15; n++)
				{
					used = false;
					if (player1->getCheckers()[n]->getPos() == posSel)
					{
						for (int j = 0; j < 2; j++)
						{
							if (posSel->getY() - cubes[j]->getValue() <= 0 && cubes[j]->getActive())
							{
								player1->getCheckers()[n]->setActive(false);
								player1->getCheckers()[n]->setPos(gcnew Position(0, 0));
								cubes[j]->use();
								used = true;
								break;
							}
						}
					}
					if (used)
						break;
				}
			}
			else
			{
				for (int n = 0; n < 15; n++)
				{
					used = false;
					if (player1->getCheckers()[n]->getPos() == posSel)
					{
						for (int j = 0; j < 2; j++)
						{
							if (posSel->getY() - cubes[j]->getValue() == 0 && cubes[j]->getActive())
							{
								player1->getCheckers()[n]->setActive(false);
								player1->getCheckers()[n]->setPos(gcnew Position(0, 0));
								cubes[j]->use();
								used = true;
								break;
							}
						}
					}
					if (used)
						break;
				}
			}
		}
		if (!color && this->player2->getActive() && selected)
		{
			bool prev = false;
			for (int i = 0; i < 15; i++)
			{
				if (!this->player2->getCheckers()[i]->canExit(this->player2->getColor()) && this->player2->getCheckers()[i]->getActive())
					return 0;
				if (this->player2->getCheckers()[i]->getPos()->getY() < posSel->getY() && this->player2->getCheckers()[i]->getActive())
					prev = true;
			}

			
			if (!prev)
			{
				for (int n = 0; n < 15; n++)
				{
					used = false;
					if (player2->getCheckers()[n]->getPos() == posSel)
					{
						for (int j = 0; j < 2; j++)
						{
							if (posSel->getY() + cubes[j]->getValue() >= 13 && cubes[j]->getActive())
							{
								player2->getCheckers()[n]->setActive(false);
								player2->getCheckers()[n]->setPos(gcnew Position(0, 0));
								cubes[j]->use();
								used = true;
								break;
							}
						}
					}
					if (used)
						break;
				}
			}
			else
			{
				for (int n = 0; n < 15; n++)
				{
					used = false;
					if (player2->getCheckers()[n]->getPos() == posSel)
					{
						for (int j = 0; j < 2; j++)
						{
							if (posSel->getY() + cubes[j]->getValue() == 13 && cubes[j]->getActive())
							{
								player2->getCheckers()[n]->setActive(false);
								player2->getCheckers()[n]->setPos(gcnew Position(0, 0));
								cubes[j]->use();
								used = true;
								break;
							}
						}
					}
					if (used)
						break;
				}
			}
		}
		drawBoard(this->board);
		drawInfo(this->info);
		checkIfNextMove();
	}
	// draw functions
	void drawExitZones()
	{
		Bitmap^ bmp = gcnew Bitmap(this->exitZone0->Width, exitZone0->Height);
		Graphics^ g = Graphics::FromImage(bmp);
		Image^ img;

		img = Image::FromFile("background2.png");
		g->DrawImage(img, 0, 0, this->exitZone0->Width, this->exitZone0->Height);

		for (int i = 0; i < 15; i++)
		{
			if (!player2->getCheckers()[i]->getActive())
			{
				img = Image::FromFile("checker0.png");
				g->DrawImage(img, 15, (i * 20), 30, 30);
			}
		}
		this->exitZone0->Image = bmp;


		bmp = gcnew Bitmap(this->exitZone1->Width, exitZone1->Height);
		g = Graphics::FromImage(bmp);
		img;

		img = Image::FromFile("background2.png");
		g->DrawImage(img, 0, 0, this->exitZone1->Width, this->exitZone1->Height);

		for (int i = 0; i < 15; i++)
		{
			if (!player1->getCheckers()[i]->getActive())
			{
				img = Image::FromFile("checker1.png");
				g->DrawImage(img, 15, (i * 20), 30, 30);
			}
		}
		this->exitZone1->Image = bmp;
	}
	void drawBoard(PictureBox^ p)
	{
		Bitmap^ bmp = gcnew Bitmap(p->Width, p->Height);
		Graphics^ g = Graphics::FromImage(bmp);
		Image^ img; 
		bool color = false;
		bool drawColor = false;
		int counter = 0;
		int xtmp, ytmp;



		img = Image::FromFile("background.png");
		g->DrawImage(img,0,0, p->Width, p->Height);



		for (int i = 0; i < 2; i++)
		{
			color = !color;
			for (int j = 0; j < 12; j++)
			{
				if (color)
					img = Image::FromFile("BoardTitle1.png");
				else
					img = Image::FromFile("BoardTitle0.png");

				if (i == 0)
				{
					img->RotateFlip(RotateFlipType::Rotate180FlipNone);
				}
				g->DrawImage(img, j*50, i*300, 50, 150);
				color = !color;
			}
		}

		for (int i = 0; i < 2; i++)
		{
			for (int j = 0; j < 12; j++)
			{
				counter = 0;
				for (int n = 0; n < 15; n++)
				{
					xtmp = player1->getCheckers()[n]->getPos()->getX();
					ytmp = player1->getCheckers()[n]->getPos()->getY();
					if (xtmp == i + 1 && ytmp == j + 1)
					{
						if (player1->getCheckers()[n]->getActive())
						{
							drawColor = player1->getColor();
							counter++;
						}
					}
					xtmp = player2->getCheckers()[n]->getPos()->getX();
					ytmp = player2->getCheckers()[n]->getPos()->getY();
					if (xtmp == i + 1 && ytmp == j + 1)
					{
						if (player2->getCheckers()[n]->getActive())
						{
							drawColor = player2->getColor();
							counter++;
						}
					}
				}
				for (int n = 0; n < counter; n++)
				{
					if (i == 0)
					{
						if (drawColor)
							img = Image::FromFile("checker1.png");
						else
							img = Image::FromFile("checker0.png");
						g->DrawImage(img, (j * 50) + 10, (i * 300) + (n * 12), 30, 30);
					}
					else {
						if (drawColor)
							img = Image::FromFile("checker1.png");
						else
							img = Image::FromFile("checker0.png");
						g->DrawImage(img, (j * 50) + 10, (i * 300) - (n * 12) + 110, 30, 30);
					}
				}
			}
		}
		drawExitZones();
		p->Image = bmp;
	}
	void drawPossibleBoard(PictureBox^ p, array<Position^>^ arr)
	{
		Bitmap^ bmp = gcnew Bitmap(p->Width, p->Height);
		Graphics^ g = Graphics::FromImage(bmp);
		Image^ img;
		bool color = false;
		bool drawColor = false;
		int counter = 0;
		int xtmp, ytmp;


		img = Image::FromFile("background.png");
		g->DrawImage(img, 0, 0, p->Width, p->Height);



		for (int i = 0; i < 2; i++)
		{
			color = !color;
			for (int j = 0; j < 12; j++)
			{
				bool skipDraw = false;
				if (arr != nullptr)
				{
					for (int m = 0; m < arr->Length; m++)
					{
						if (Position(i + 1, j + 1) == arr[m])
						{

							if (color)
								img = Image::FromFile("BoardTitle11.png");
							else
								img = Image::FromFile("BoardTitle01.png");

							if (i == 0)
							{
								img->RotateFlip(RotateFlipType::Rotate180FlipNone);
							}
							g->DrawImage(img, j * 50, i * 300, 50, 150);
							skipDraw = true;
						}
					}
				}
				if (!skipDraw)
				{
					if (color)
						img = Image::FromFile("BoardTitle1.png");
					else
						img = Image::FromFile("BoardTitle0.png");

					if (i == 0)
					{
						img->RotateFlip(RotateFlipType::Rotate180FlipNone);
					}
					g->DrawImage(img, j * 50, i * 300, 50, 150);
				}
				color = !color;

			}
		}

		for (int i = 0; i < 2; i++)
		{
			for (int j = 0; j < 12; j++)
			{
				counter = 0;
				for (int n = 0; n < 15; n++)
				{
					xtmp = player1->getCheckers()[n]->getPos()->getX();
					ytmp = player1->getCheckers()[n]->getPos()->getY();
					if (xtmp == i + 1 && ytmp == j + 1)
					{
						if (player1->getCheckers()[n]->getActive())
						{
							drawColor = player1->getColor();
							counter++;
						}
					}
					xtmp = player2->getCheckers()[n]->getPos()->getX();
					ytmp = player2->getCheckers()[n]->getPos()->getY();
					if (xtmp == i + 1 && ytmp == j + 1)
					{
						if (player2->getCheckers()[n]->getActive())
						{
							drawColor = player2->getColor();
							counter++;
						}
					}
				}
				for (int n = 0; n < counter; n++)
				{
					if (i == 0)
					{
						if (drawColor)
							img = Image::FromFile("checker1.png");
						else
							img = Image::FromFile("checker0.png");
						g->DrawImage(img, (j * 50) + 10, (i * 300) + (n * 12), 30, 30);
					}
					else {
						if (drawColor)
							img = Image::FromFile("checker1.png");
						else
							img = Image::FromFile("checker0.png");
						g->DrawImage(img, (j * 50) + 10, (i * 300) - (n * 12) + 110, 30, 30);
					}
				}
			}
		}
		//
		
		drawExitZones();
		p->Image = bmp;
	}
	void drawInfo(PictureBox^ p)
	{
		Font ^drawFont = gcnew Font("Arial", 16);
		SolidBrush^ drawBrush = gcnew SolidBrush(Color::Black);
		Bitmap^ bmp = gcnew Bitmap(p->Width, p->Height);
		Graphics^ g = Graphics::FromImage(bmp);
		Image^ img;

		img = Image::FromFile("background.png");
		g->DrawImage(img, 0, 0, p->Width, p->Height);
		int currentHeight = 0;
		img = Image::FromFile("background2.png");
		g->DrawImage(img, 0, currentHeight, p->Width, 150);
		currentHeight += 150;

		for (int i = 0; i < 2; i++)
		{
			cubes[i]->drawCubes(g, p->Width/3 + (i * 50), currentHeight / 3);
		}

		Pen^ pen = gcnew Pen(Color::Black);
		pen->Width = 2;
		g->DrawLine(pen, 0, 0, 2, 1000);

		currentHeight += 20;
		if(player1->getActive())
			g->DrawString("Ход игрока: 1", drawFont, drawBrush, 20, currentHeight);
		if (player2->getActive())
			g->DrawString("Ход игрока: 2", drawFont, drawBrush, 20, currentHeight);

		
		currentHeight += 60;
		player1->printHowManyActive(g, 20, currentHeight, "Игроку 1 осталось\n вывести: ", drawFont, drawBrush);
		currentHeight += 60;
		player2->printHowManyActive(g, 20, currentHeight, "Игроку 2 осталось\n вывести: ", drawFont, drawBrush);
		
		

		p->Image = bmp;
	}
	void drawWin(PictureBox^ p, bool player)
	{
		Font^ drawFont = gcnew Font("Arial", 16);
		SolidBrush^ drawBrush = gcnew SolidBrush(Color::Black);
		Bitmap^ bmp = gcnew Bitmap(p->Width, p->Height);
		Graphics^ g = Graphics::FromImage(bmp);
		Image^ img;

		img = Image::FromFile("background.png");
		g->DrawImage(img, 0, 0, p->Width, p->Height);
		int currentHeight = 0;
		img = Image::FromFile("background2.png");
		g->DrawImage(img, 0, currentHeight, p->Width, 150);
		currentHeight += 150;

		for (int i = 0; i < 2; i++)
		{
			cubes[i]->drawCubes(g, p->Width / 3 + (i * 50), currentHeight / 3);
		}

		Pen^ pen = gcnew Pen(Color::Black);
		pen->Width = 2;
		g->DrawLine(pen, 0, 0, 2, 1000);

		currentHeight += 20;
		if (player1->getActive())
			g->DrawString("Ход игрока: 1", drawFont, drawBrush, 20, currentHeight);
		if (player2->getActive())
			g->DrawString("Ход игрока: 2", drawFont, drawBrush, 20, currentHeight);


		currentHeight += 60;
		player1->printHowManyActive(g, 20, currentHeight, "Игроку 1 осталось\n вывести: ", drawFont, drawBrush);
		currentHeight += 60;
		player2->printHowManyActive(g, 20, currentHeight, "Игроку 2 осталось\n вывести: ", drawFont, drawBrush);
		currentHeight += 60;
		if (player)
		{
			g->DrawString("Выиграл игрок 1", drawFont, drawBrush, 20, currentHeight);
		}
		else if (!player)
		{
			g->DrawString("Выиграл игрок 2", drawFont, drawBrush, 20, currentHeight);
		}



		p->Image = bmp;
	}
};


