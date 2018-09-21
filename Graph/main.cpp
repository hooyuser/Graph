#include<iostream>

#include"Graphmatrix.h"

using namespace std;

int main()
{
	GraphMatrix<char,int> Network;
	Network.insert('S');
	cout << Network.vertex(0);

	return 0;
}