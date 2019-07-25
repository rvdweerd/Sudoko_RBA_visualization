#pragma once
#include "Graphics.h"
#include "Vei2.h"

class Field
{
public:
	class SubField {
	public:
		bool Contains(char ch)
		{
			for (int i = 0; i < 9; i++)
			{
				if (subfieldArray[i] == ch)
				{
					return true;
				}
			}
			return false;
		}
		int Count(char ch)
		{
			int count = 0;
			for (int i = 0; i < 9; i++)
			{
				if (subfieldArray[i] == ch)
				{
					count++;
				}
			}
			return count;
		}
		void Print();
		char subfieldArray[9];
	};

public:
	Field() = default;
	Field(char* pArr);
	void PrintConsole() const;
	void PrintGfx(Vei2 tLeft, Graphics& gfx);
	void AssignCell(int i, char ch);
	int GetAvailableChars(int i, char* pArr);
	bool Field::IsViable();
	bool SolutionExists(Graphics& gfx);

private:
	char fieldArray[9 * 9] = { 0 };
	char fieldArrayStart[9 * 9] = { 0 };
	SubField colSubfields[9] = { 0 };
	SubField rowSubfields[9] = { 0 };
	SubField blockSubfields[9]={ 0 };
	int iProblematic[9 * 9] = { -1 };
	int nProblematic = 0;
};