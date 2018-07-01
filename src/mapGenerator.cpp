/**
 * @file mapGenerator.cpp
 * @brief MapGenerator class definition file for the map generator 
 *        project. Functions provided assist in populating maps filled 
 *        with double values.
 * @author Colby Japp
 * @version 1.0.0
 * @date 2018-07-01
 * @edited 2018-07-01
 */

#include "mapGenerator.h"
#include<ctime>
#include<cmath>

#include<iostream>


MapGenerator::MapGenerator():
  m_seed(0),
  m_seedPer(90),
  m_width(512),
  m_height(512),
  m_precip(m_width,m_height),
  m_elevat(m_width,m_height)
{
  std::cout << "Percipitate dim: (" << m_precip.width()<< "," << m_precip.height() << ")."<< std::endl;
  std::cout << "Elevate dim: (" << m_elevat.width()<< "," << m_elevat.height() << ")."<< std::endl;
}


MapGenerator::MapGenerator(unsigned int w, unsigned int h):
  m_seed(0),
  m_seedPer(90),
  m_width(w),
  m_height(h),
  m_precip(m_width,m_height),
  m_elevat(m_width,m_height)
{

}

MapGenerator::~MapGenerator()
{

}


void MapGenerator::generateElevation(double scale, int octave, double persistance)
{
  //seed perlin noise object
  PerlinNoise pn(m_seed);

  Map<double> circleGrad(m_width,m_height);
  _generateCircleGradient(circleGrad);

  for(unsigned int i = 0; i < m_width; i++)
  {
    for(unsigned int j = 0; j < m_height; j++)
    {
      double n = pn.opNoise2(double(i)/scale,double(j)/scale, octave, persistance);
      n *= circleGrad[i][j];
      n += 0.1;

      m_elevat[i][j] = n;
    }
  }
}


void MapGenerator::generatePercipitation(double scale)
{
  //seed perlin noise object
  PerlinNoise pn(m_seed + m_seedPer);

  for(unsigned int i = 0; i < m_width; i++)
  {
    for(unsigned int j = 0; j < m_height; j++)
    {
      m_precip[i][j] = pn.pNoise2(double(i)/scale,double(j)/scale);
    }
  }
}


void MapGenerator::_generateCircleGradient(Map<double>& gradient)
{
  double xCenter = m_width/2.0;
  double yCenter = m_height/2.0;
  double maxDist = std::sqrt((xCenter*xCenter) + (yCenter*yCenter)); //<-maxValue
  
  for(unsigned int x = 0; x < m_width; x++)
  {
    for(unsigned int y = 0; y < m_height; y++)
    {
      double distx = std::abs(x - xCenter);
      double disty = std::abs(y - yCenter);
      double dist = std::sqrt((distx*distx) + (disty*disty));
     
     double root = (maxDist*maxDist - dist*dist)/(maxDist*maxDist); 
     gradient[x][y] = root;
    }
  }
}
