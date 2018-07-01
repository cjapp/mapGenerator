/**
 * @file mapGenerator.h
 * @brief MapGenerator class header file for the map Generator project. Holds
 *        the tools specific to generating a map of double values.
 * @author Colby Japp
 * @version 1.0.0
 * @date 2018-07-01
 * @edited 2018-07-01
 */

#ifndef MAPGENERATOR_H
#define MAPGENERATOR_H 

#include "map.h"
#include "perlinNoise.h"

#define WIDTH 1024
#define HEIGHT 1024

class MapGenerator
{
  private:
    //variables
    unsigned int m_seed;
    unsigned int m_seedPer;

    unsigned int m_width;
    unsigned int m_height;

    Map<double> m_precip;
    Map<double> m_elevat;

    void _generateCircleGradient(Map<double>& circleGrad);

  public:
    MapGenerator();
    MapGenerator(unsigned int w, unsigned int h);
    ~MapGenerator();

    void generateElevation(double scale, int octave, double persistance);
    void generatePercipitation(double scale);

    double getPrecipitation(const int x, const int y) const{return m_precip[x][y];}
    double getElevation(const int x, const int y) const{return m_elevat[x][y];}

    //seed functions
    void setSeed(unsigned int s){m_seed = s;}
    unsigned int getSeed() const {return m_seed;}
    unsigned int height()  const {return m_height;}
    unsigned int width()   const {return m_width;}
    
};



#endif /* MAPGENERATOR_H */
