/*
*
* \brief MCSP project created at Canada/USA Mathcamp 2018
* 
* \file: MCSP.cpp
* \date: 07.2018
* \author: Kalina Jasinska
* \contact: 532anilak@gmail.com
* 
*/
#include"eigen/Eigen/Eigenvalues"
#include<algorithm>
#include<vector>

using namespace Eigen;

class MCSP
{
	
public:
	void PrintCoordinates( std::string fileName );
	void PrintAdjacency( std::string fileName );
	MCSP(std::string fileName, int matSize);
	
private:
	int m_matSize;
	MatrixXd m_classes;
	MatrixXd m_laplacian;
	std::vector< std::pair<double,double > > m_finalCoordinates;
	
	void GenerateLaplacian();
	void FindCoordinates();
};
