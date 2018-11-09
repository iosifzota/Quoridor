#include "Trench.h"



Trench::Trench()
{
}

void Trench::SetNorthOcupied(char n)
{
	NorthOcupied = n;
}

void Trench::SetSouthOcupied(char s)
{
	SouthOcupied = s;
}

void Trench::SetEastOcupied(char e)
{
	EastOcupied = e;
}

void Trench::SetWestOcupied(char w)
{
	WestOcupied = w;
}

char Trench::GetNorthOcupied() const
{
	return NorthOcupied;
}

char Trench::GetSouthOcupied() const
{
	return SouthOcupied;
}

char Trench::GetEastOcupied() const
{
	return EastOcupied;
}

char Trench::GetWestOcupied() const
{
	return WestOcupied;
}

