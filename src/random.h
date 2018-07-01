/**
* @file random.h
* @brief Random class declaration file
* @author Colby Japp
* @version 1.0.0
* @date 2018-06-09
* @edited 2018-06-09
*/
#ifndef RANDOM_H
#define RANDOM_H 

#include<cstdint> //uint32_t

#define RANDOM_SEED_TYPE unsigned int

/**
* @brief Random singleton that generates random numbers and 
*        knows whether it is currently seeded and returns 
*        the seed it is using.
*/
class Random
{
  private:
    static bool m_seeded;
    static RANDOM_SEED_TYPE m_seed;
    static uint32_t m_state;

  public:
    Random();
    ~Random();

    static int random();
    static int range(int min, int max);
    static void seedRandom(RANDOM_SEED_TYPE s);

    static RANDOM_SEED_TYPE getSeed(){return m_seed;}

};



#endif /* RANDOM_H */
