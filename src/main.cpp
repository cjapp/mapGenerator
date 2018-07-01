
#include "mapGenerator.h"
#include "ppm.h"
#include "perlinNoise.h"

#include<cmath>

#define WIDTH 1024
#define HEIGHT 1024

unsigned int gseed = 100000;

struct Color
{
  unsigned char r,g,b;
  Color(unsigned char pr,unsigned char pg, unsigned char pb):r(pr),g(pg),b(pb){}
  Color& operator=(const Color& c){ r = c.r; g = c.g; b = c.b; return *this;}
};

Color dtoColor(double val);

int main(int argc, char** argv)
{
  ppm image(WIDTH,HEIGHT);

  MapGenerator mg(WIDTH,HEIGHT);
  mg.setSeed(gseed);
  mg.setCenter(450,450);
  mg.setMaxDistance(WIDTH/1.5);

  mg.generateElevation(250,3,0.4);

  Map<double> map(WIDTH,HEIGHT);

  unsigned int kk = 0;
  for(int y = 0; y < HEIGHT; y++)
  {
    for(int x = 0; x < WIDTH; x++)
    {
      double n = mg.getElevation(x,y);
      n -= floor(n);
      n += 0.1;

      map[x][y] = n;

      Color col = dtoColor(n);

      image.r[kk] = col.r;
      image.g[kk] = col.g;
      image.b[kk] = col.b;

      kk++;
    }
  }

  image.write("test.ppm");
  return 0;
}


Color dtoColor(double val)
{
  Color ocean(56,56,250);
  Color beach(244,220,181);
  Color green(102,141,60);
  Color mountain(125,125,125);
  Color snow(244,244,244);

  if(val < 0.5)
    return ocean;
  else if(val < 0.55)
    return beach;
  else if(val < 0.72)
    return green;
  else if(val < 0.90)
    return mountain;
  else
    return snow;
}

