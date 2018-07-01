/**
 * @file random.cpp
 * @brief Random class definitions file
 * @author Colby Japp
 * @version 1.0.0
 * @date 2018-06-09
 * @edited 2018-06-09
 */

#include "random.h"//Random, RANDOM_SEED_TYPE

#include<cstdlib> //srand(),rand()
#include<ctime>  //time()
#include<iostream>//cerr(),endl

bool Random::m_seeded = false;
RANDOM_SEED_TYPE Random::m_seed = 0;
uint32_t Random::m_state = 0;

Random::Random()
{

}


Random::~Random()
{

}


/**
 * @brief Function that returns a random number. Current 
 *        implementation uses rand() from cstdlib.
 *
 * @return a random number generated by the Random class
 */
int Random::random()
{
  if(!m_seeded)
  {
    std::cerr << "Random::Random() WARN: Random hasnt been seeded, seeding with current time." << std::endl;

    try
    {
      seedRandom(time(NULL));
    }
    catch(std::exception e)
    {
      throw e;
    }
  }

  static uint32_t x = m_state + 92192019;
  static uint32_t y = 12345678;
  static uint32_t z = 521288629;
  static uint32_t w = m_state;
  uint32_t t;

  t = x ^ (x << 11);   
  x = y; y = z; z = w;   
  return w = w ^ (w >> 19) ^ (t ^ (t >> 8));

  //return rand();
}


/**
 * @brief function that returns a pseudo-random number that exists 
 *        between the range provided
 *
 * @param min the minimum value of the range
 * @param max the maximim value of the range
 *
 * @return  a pseudo-random number between the min and max of the range
 */
int Random::range(int min, int max){

  if(min == max)
    return min;

  if(min > max)
    throw std::runtime_error("Provided minimum is larger than maximum for range");


  try
  {
    return int((unsigned int)random() % (max - min + 1) + min);
  }
  catch(std::exception e)
  {
    throw e;
  }

}


/**
 * @brief Function that seeds the random number generator class 
 *
 * @param s the seed to seed it the generator with
 * @throw will throw an exception at runtime if the 
 *        random class is already seeded
 */
void Random::seedRandom(RANDOM_SEED_TYPE s)
{
  if(m_seeded)
  {
    throw std::runtime_error("Random class has already been seeded");
  }

  m_seeded = true;
  m_seed = s;
  m_state = s;
  //srand(s);
}
