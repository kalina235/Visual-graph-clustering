#include<bits/stdc++.h>
#include"MCSP.h"
#include<stdio.h>

using namespace std;

void MCSP::GenerateLaplacian() 
{
	auto deg  = VectorXd(m_matSize);
	for(int i = 0; i < m_matSize;i++)
	{
		for(int j = 0; j < m_matSize; j++)
			{
				if(m_classes(i,j) > 0.0000001 && i != j) 
				{
					deg(i) += m_classes(i,j);//1
					deg(j) += m_classes(i,j);//1
				}
			}
	}
	m_laplacian=MatrixXd(m_matSize,m_matSize);
	for(int i = 0; i < m_matSize;i++)
	{
		for(int j = 0; j < m_matSize; j++)
			{
				if(m_classes(i,j) > 0.0000001 && i != j) 
				{
					m_laplacian(i,j) = -2.0/sqrt(deg(i)*deg(j));//1
				}
				if(i == j)
				{
					m_laplacian(i,j) = 1.0;
				}
			}
	}
}
void MCSP::FindCoordinates()
{
	SelfAdjointEigenSolver<MatrixXd> eigenvaluesGen(m_laplacian);
	cout << eigenvaluesGen.eigenvalues();
	VectorXd eigenvalues = eigenvaluesGen.eigenvalues();
	auto min1 = make_pair(HUGE_VAL, 0);
	auto min2 = make_pair(HUGE_VAL, 0);
	
	for(auto index = 0; index < eigenvalues.size(); index++)
	{
		if(eigenvalues(index) <= 0.0000001)
		{ 
			continue;
		}
		if(eigenvalues(index) <= min1.first) 
		{
			min2 = min1;
			min1 = make_pair(eigenvalues(index), index);
			continue;
		}
		if(eigenvalues(index) <= min2.first) 
		{
			min2 = make_pair(eigenvalues(index), index);
		}
	}
	
	auto xCoordinates = eigenvaluesGen.eigenvectors().col(1);
	auto yCoordinates = eigenvaluesGen.eigenvectors().col(2);
	auto zCoordinates = eigenvaluesGen.eigenvectors().col(3);
	for(auto index = 0; index < xCoordinates.size(); index++)
	{
		m_finalCoordinates.push_back(make_pair(xCoordinates(index),make_pair( yCoordinates(index),zCoordinates(index))));
	}
}

void MCSP::PrintCoordinates(std::string fileName)
{
	freopen(fileName.c_str(), "w", stdout);
	printf("{%lf,%lf,%lf}", m_finalCoordinates[0].first, m_finalCoordinates[0].second.first,  m_finalCoordinates[0].second.second);
	for(auto index = 1; index < m_matSize; index++)
	{
		printf(",{%lf,%lf,%lf}", m_finalCoordinates[index].first, m_finalCoordinates[index].second.first, m_finalCoordinates[index].second.second);
	}
	fclose(stdout);
}

void MCSP::PrintAdjacency( std::string fileName )
{
	freopen(fileName.c_str(),"w",stdout);
	for(int i=0;i<m_matSize;i++)
	{
		printf("{");
		printf("%lf", m_classes(i,0));
		for(int j=1;j<m_matSize;j++)
		{
			printf(",%lf", m_classes(i,j));
		}
		printf("}\n");
		if(i!=m_matSize-1) 
		{
			printf(",");
		}
	}
		
}

MCSP::MCSP(std::string fileName, int matSize):
	m_matSize(matSize),
	m_classes(MatrixXd(matSize,matSize))	
{
	freopen(fileName.c_str(), "r", stdin);
	
	for(auto i = 0; i < m_matSize; i++)
	{
		for(auto j = 0; j < m_matSize; j++)
		{
			double x;
			scanf("%lf", &x);
			m_classes(i,j) = x;
		}
	}
	fclose(stdin);
	GenerateLaplacian();
	FindCoordinates();
}
