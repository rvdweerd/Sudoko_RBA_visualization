#include "Field.h"
#include <iostream>
#include "Point.h"
#include "Windows.h"
#include "SpriteCodex.h"

Field::Field(char* pArr)
{
	for (int i = 0; i < 9 * 9; i++, pArr++)
	{
		fieldArray[i] = *pArr;
		fieldArrayStart[i] = *pArr;
		AssignCell(i, fieldArray[i]);
	}
}

void Field::PrintConsole() const
{
	std::cout<<"  -------------------------" << std::endl;
	for (int Y = 0; Y < 9; Y++)
	{
			std::cout << " |";
		for (int X = 0; X < 3; X++)
		{
			for (int i = 0; i < 3; i++)
			{
				std::cout << " "<<fieldArray[(3 * X + i) + Y * 9] << "";
			}
			std::cout << " | ";	
		}
		std::cout << std::endl;
		if ( (Y+1)%3 == 0)
		{
			std::cout <<  "  -------------------------" << std::endl;
		}
	} 
}

void Field::PrintGfx(Vei2 tLeft, Graphics& gfx, Color c_letter, Color c_TileBackground)
{
	for (int Y = 0; Y < 9; Y++)
	{
		for (int X = 0; X < 3; X++)
		{
			for (int i = 0; i < 3; i++)
			{
				//switch (fieldArray[(3 * X + i) + Y * 9])
				//{
				//SpriteCodex::DrawTileNumber(tLeft + Vei2((3 * X + i) * 16, Y * 16), '0', gfx, c_letter, c_TileBackground);
				Vei2 tLeft_tile(tLeft + Vei2((3 * X + i) * 16 + X*10, Y * 16 + (Y/3)*10 ) );
				

				if (fieldArray[(3 * X + i) + Y * 9] != '.')
				{
					gfx.DrawRect(tLeft_tile.x, tLeft_tile.y, tLeft_tile.x + 16, tLeft_tile.y + 16, Colors::LightGray);
				}

				
				SpriteCodex::DrawTileNumber(tLeft_tile, fieldArray[(3 * X + i) + Y * 9],gfx,c_letter,c_TileBackground);

				if (fieldArrayStart[(3 * X + i) + Y * 9] != '.')
				{
					gfx.DrawRect(tLeft_tile.x, tLeft_tile.y, tLeft_tile.x + 16, tLeft_tile.y + 16, Colors::Blue);
				}


				SpriteCodex::DrawTileNumber(tLeft_tile, fieldArrayStart[(3 * X + i) + Y * 9], gfx, Colors::Green, c_TileBackground);



				/*case '1':
					SpriteCodex::DrawTile1(tLeft + Vei2((3*X+i) * 16, Y * 16), gfx);
					break;
				case '2':
					SpriteCodex::DrawTile2(tLeft + Vei2((3*X+i) * 16, Y * 16), gfx);
					break;
				case '3':
					SpriteCodex::DrawTile3(tLeft + Vei2((3*X+i) * 16, Y * 16), gfx);
					break;
				case '4':
					SpriteCodex::DrawTile4(tLeft + Vei2((3*X+i) * 16, Y * 16), gfx);
					break;
				case '5':
					SpriteCodex::DrawTile5(tLeft + Vei2((3*X+i) * 16, Y * 16), gfx);
					break;
				case '6':
					SpriteCodex::DrawTile6(tLeft + Vei2((3*X+i) * 16, Y * 16), gfx);
					break;
				case '7':
					SpriteCodex::DrawTile7(tLeft + Vei2((3*X+i) * 16, Y * 16), gfx);
					break;
				case '8':
					SpriteCodex::DrawTile8(tLeft + Vei2((3*X+i) * 16, Y * 16), gfx);
					break;
				case '9':
					SpriteCodex::DrawTile9(tLeft + Vei2((3*X+i) * 16, Y * 16), gfx);
					break;
					
				}*/
			}
		}
		if ((Y + 1) % 3 == 0)
		{
		}
	}
}

void Field::AssignCell(int i, char ch)
{
	fieldArray[i] = ch;
	
	rowSubfields[i/9].subfieldArray[i%9] = ch;
	colSubfields[i%9].subfieldArray[i/9] = ch;

	Point fieldCell(i % 9, i / 9);
	Point block(fieldCell.x / 3, fieldCell.y / 3);
	Point blockCell(fieldCell.x - block.x * 3, fieldCell.y - block.y * 3);
	blockSubfields[block.x + block.y * 3].subfieldArray[blockCell.x + blockCell.y * 3] = ch;
}

int Field::GetAvailableChars(int i, char* pArr)
{
	int row = i / 9;
	int col = i % 9;
	int block = col/3 + int(row/3)*3;
	int count = 0;
	char* pIt = pArr;

	for (char ch = '1'; ch <= '9'; ch++)
	{
		if ( !colSubfields[col].Contains(ch) && !rowSubfields[row].Contains(ch) && !blockSubfields[block].Contains(ch) )
		{
			*pIt = ch;
			pIt++;
			count++;
		}
	}
	return count;
}

bool Field::SolutionExists(Graphics& gfx)
{
	for (int i = 0; i < 9 * 9; i++)
	{
		if (fieldArray[i] == '.')
		{
			char AvailableChars[9] = { 0 };
			int n = GetAvailableChars(i, AvailableChars);
			for (int k=0; k<n; k++)
			{
				AssignCell(i, AvailableChars[k]);
				
				Sleep(20);
				gfx.BeginFrame();
				PrintGfx(Vei2(100,100), gfx, Colors::Red, Colors::Gray);
				gfx.EndFrame();

				if (SolutionExists(gfx))
				{
					return true;
				}
			}
			AssignCell(i,'.');
			return false;
		}
	}
}

void Field::SubField::Print()
{
	char* p1 = subfieldArray; char* p2 = p1 + 9;
	for (; p1 < p2; p1++)
	{
		std::cout << *p1 << ",";
	}
	std::cout << std::endl;
}
