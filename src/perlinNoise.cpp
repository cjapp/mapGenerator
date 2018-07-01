#include "perlinNoise.h"
#include <cmath>
#include <random>
#include <algorithm>
#include <numeric>

PerlinNoise::PerlinNoise()
{
  p = {
    151,160,137,91,90,15,131,13,201,95,96,53,194,233,7,225,140,36,103,30,69,142,
    8,99,37,240,21,10,23,190, 6,148,247,120,234,75,0,26,197,62,94,252,219,203,117,
    35,11,32,57,177,33,88,237,149,56,87,174,20,125,136,171,168, 68,175,74,165,71,
    134,139,48,27,166,77,146,158,231,83,111,229,122,60,211,133,230,220,105,92,41,
    55,46,245,40,244,102,143,54, 65,25,63,161,1,216,80,73,209,76,132,187,208, 89,
    18,169,200,196,135,130,116,188,159,86,164,100,109,198,173,186, 3,64,52,217,226,
    250,124,123,5,202,38,147,118,126,255,82,85,212,207,206,59,227,47,16,58,17,182,
    189,28,42,223,183,170,213,119,248,152, 2,44,154,163, 70,221,153,101,155,167, 
    43,172,9,129,22,39,253, 19,98,108,110,79,113,224,232,178,185, 112,104,218,246,
    97,228,251,34,242,193,238,210,144,12,191,179,162,241, 81,51,145,235,249,14,239,
    107,49,192,214, 31,181,199,106,157,184, 84,204,176,115,121,50,45,127, 4,150,254,
    138,236,205,93,222,114,67,29,24,72,243,141,128,195,78,66,215,61,156,180 };

  // Duplicate the permutation vector
  p.insert(p.end(), p.begin(), p.end());
}


PerlinNoise::PerlinNoise(unsigned int seed)
{
  p.resize(256);

  std::iota(p.begin(), p.end(), 0);

  std::default_random_engine engine(seed);

  std::shuffle(p.begin(), p.end(), engine);

  p.insert(p.end(),p.begin(),p.end());
}

PerlinNoise::~PerlinNoise()
{

}


double PerlinNoise::pNoise3(double x, double y, double z) {
  //Find the unit cube that contains the point
  int X = int (floor(x)) & 255;
  int Y = int (floor(y)) & 255;
  int Z = int (floor(z)) & 255;

  // Find relative x, y,z of point in cube
  x -= floor(x);
  y -= floor(y);
  z -= floor(z);

  // Compute fade curves for each of x, y, z
  double u = fade(x);
  double v = fade(y);
  double w = fade(z);

  // Hash coordinates of the 8 cube corners
  int AAA = p[p[p[  X]+   Y]+   Z];
  int ABA = p[p[p[  X]+ Y+1]+   Z];
  int AAB = p[p[p[  X]+   Y]+ Z+1];
  int ABB = p[p[p[  X]+ Y+1]+ Z+1];

  int BAA = p[p[p[X+1]+   Y]+   Z];
  int BBA = p[p[p[X+1]+ Y+1]+   Z];
  int BAB = p[p[p[X+1]+   Y]+ Z+1];
  int BBB = p[p[p[X+1]+ Y+1]+ Z+1]; 

  // Add blended results from 8 corners of cube
  double x1,x2,y1,y2;
  x1 = lerp(grad(AAA,x,y,z),   grad(BAA,x-1,y,z),   u);
  x2 = lerp(grad(ABA,x,y-1,z), grad(BBA,x-1,y-1,z), u);
  y1 = lerp(x1,x2,v);

  x1 = lerp(grad(AAB,x,y,z-1),   grad(BAB,x-1,y,z-1),   u);
  x2 = lerp(grad(ABB,x,y-1,z-1), grad(BBB,x-1,y-1,z-1), u);
  y2 = lerp(x1,x2,v);

  return (lerp(y1,y2,w)+1.0)/2.0;
}


double PerlinNoise::opNoise3(double x, double y, double z, int octaves, double persistance)
{
  double total = 0.0;
  double frequency = 2.0;
  double amplitude = 1.0;
  double maxValue = 0.0;

  for(int i = 0; i< octaves; i++)
  {
    total += pNoise3(x*frequency, y*frequency, z*frequency) * amplitude;

    maxValue  += amplitude;
    amplitude = amplitude * persistance;
    frequency = frequency * 2;
  }

  return total/maxValue;
}

double PerlinNoise::pNoise2(double x, double y)
{
  //Find the unit cube that contains the point
  int X = int (floor(x)) & 255;
  int Y = int (floor(y)) & 255;

  // Find relative x, y,z of point in cube
  x -= floor(x);
  y -= floor(y);

  // Compute fade curves for each of x, y, z
  double u = fade(x);
  double v = fade(y);

  // Hash coordinates of the 8 cube corners
  int AAA = p[p[p[  X]+   Y]];
  int ABA = p[p[p[  X]+ Y+1]];

  int BAA = p[p[p[X+1]+   Y]];
  int BBA = p[p[p[X+1]+ Y+1]];

  // Add blended results from 8 corners of cube
  double x1,x2;
  x1 = lerp(grad2(AAA,x,y),   grad2(BAA,x-1,y),   u);
  x2 = lerp(grad2(ABA,x,y-1), grad2(BBA,x-1,y-1), u);

  return (lerp(x1,x2,v)+1.0)/2.0;
}

double PerlinNoise::opNoise2(double x, double y, int octaves, double persistence)
{
  double total = 0.0;
  double frequency = 2.0;
  double amplitude = 1.0;
  double maxValue = 0.0;

  for(int i = 0; i< octaves; i++)
  {
    total += pNoise2(x*frequency, y*frequency) * amplitude;

    maxValue  += amplitude;
    amplitude = amplitude * persistence;
    frequency = frequency * 2;
  }

  return total/maxValue;
}


/**
 * @brief the fade function of the perlin noise algorithm, 
 *        used to ease into gradient calculations for smoother 
 *        transitions
 *
 * @param t the value to smooth
 *
 * @return a smoother transition value converted from the original value
 */
double PerlinNoise::fade(double t)
{
  return t * t * t * (t *(t * 6 - 15) + 10);
}


/**
 * @brief the interpolation function of the perlin noise function
 *
 * @param a the starting value
 * @param b the ending value
 * @param t the transitioning value
 *
 * @return  the interpolated value given the previous parameters
 */
double PerlinNoise::lerp(double a, double b, double t)
{
  return a + t * (b-a);
}


/**
 * @brief function that returns a gradient curve value for 
 *        the noise using the following params
 *
 * @param hash the hash value from a permutation vector
 * @param x the x coordinate on the unit cube
 * @param y the y coordinate of the unit cube
 * @param z the z coordinate of the unit cube
 *
 * @return 
 */
double PerlinNoise::grad(int hash, double x, double y, double z)
{
  int h = hash & 15;

  // Convert lower 4 bits of hash into 12 gradient directions
  double u = (h < 8)? x : y,
         v = (h < 4)? y : ((h == 12 || h == 14 )? x : z);

  return (((h&1) == 0)? u:-u) + (((h&2) == 0)? v:-v);
}


/**
 * @brief function that returns a 2D gradient curve value for the 
 *        noise using x and y
 *
 * @param hash the hash value from a permutation vector
 * @param x the x coordinate of the unit cube
 * @param y the y coordniate of the unit cube
 *
 * @return a gradient curve value given a hash, x and y
 */
double PerlinNoise::grad2(int hash, double x, double y)
{
  int h = hash & 15;

  return ((h&1)? x:-x) + ((h&2)? y:-y);
}


