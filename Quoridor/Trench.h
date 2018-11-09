#pragma once
class Trench
{
public:
	Trench();
	void SetNorthOcupied(char n);
	void SetSouthOcupied(char s);
	void SetEastOcupied(char e);
	void SetWestOcupied(char w);

	char GetNorthOcupied() const;
	char GetSouthOcupied() const;
	char GetEastOcupied() const;
	char GetWestOcupied() const;

private:
	char NorthOcupied:1;
	char SouthOcupied:1;
	char EastOcupied:1;
	char WestOcupied:1;
};

