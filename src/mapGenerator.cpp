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
  m_xCenter(256),
  m_yCenter(256),
  m_maxDist(256),
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
  m_xCenter(w/2),
  m_yCenter(h/2),
  m_maxDist(w/2),
  m_precip(m_width,m_height),
  m_elevat(m_width,m_height)
{

}

MapGenerator::~MapGenerator()
{

}


/**
 * @brief function that populates the elevation map with noise values
 *
 * @param scale the scale of the perlin noise function
 * @param octave the octave count of the perlin noise function
 * @param persistance the persistance value of the perlin noise function
 */
void MapGenerator::generateElevation(double scale, int octave, double persistance)
{
  //seed perlin noise object
  PerlinNoise pn(m_seed);

  std::cout << "Center: " << m_xCenter << "," << m_yCenter << std::endl;
  std::cout << "MaxDistance: " << m_maxDist << std::endl;

  for(unsigned int i = 0; i < m_width; i++)
  {
    for(unsigned int j = 0; j < m_height; j++)
    {
      double n = pn.opNoise2(double(i)/scale,double(j)/scale, octave, persistance);
      n *= _calculateCircleValue(i,j);

      m_elevat[i][j] = n;
    }
  }
}


/**
 * @brief function that populates the percipitation map with noise values
 *
 * @param scale the scale of the perlin noise function
 */
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


double MapGenerator::_calculateCircleValue(unsigned int x, unsigned int y)
{
  unsigned int distx = std::abs(x - m_xCenter);
  unsigned int disty = std::abs(y - m_yCenter);
  double dist = std::sqrt(double(distx*distx) + double(disty*disty));

  if(dist > m_maxDist)
    return 0.0;
  else
    return std::abs(m_maxDist*m_maxDist - dist*dist)/(m_maxDist*m_maxDist); 
}

