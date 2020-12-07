#include"MCSP.h"
#include<bits/stdc++.h>
int main()
{
	MCSP Representation("matrix.txt", 81);
	Representation.PrintAdjacency("adj.txt");
	Representation.PrintCoordinates("coordinates.txt");
}
