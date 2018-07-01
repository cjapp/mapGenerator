#ifndef PERLIN_NOISE_H
#define PERLIN_NOISE_H 

#include<vector>

class PerlinNoise
{
  private:
    std::vector<int> p;

    double fade(double t);
    double lerp(double t,double a, double b);
    double grad(int hash, double x, double y, double z);

    double grad2(int hash, double x, double y);

  public:
    PerlinNoise();
    PerlinNoise(unsigned int seed);
    ~PerlinNoise();

    double pNoise3(double x, double y, double z);
    double opNoise3(double x, double y, double z, int octave, double persistance);

    double pNoise2(double x, double y);
    double opNoise2(double x, double y, int octave, double persistence);

};

#endif /* PERLIN_NOISE_H */
