/**
 * @file map.h
 * @brief A simple map template class.
 * @author Colby Japp
 * @version 1.0.0
 * @date 2018-06-10
 * @edited 2018-06-10
 */

#ifndef MAP_H
#define MAP_H 

#define MAP_INITIALMAX 5

#include<stdexcept>
#include<iostream>

template<class T>
class Map
{
  private:
    unsigned int m_maxWidth, m_maxHeight; //variables of the data of map
    void _allocate();
    void _resize();
    void _deallocate();
  protected:
    T** m_data; 
    unsigned int m_width, m_height; //dimensional variables of the visible map


    unsigned int _getMaxHeight(){return m_maxHeight;}
    unsigned int _getMaxWidth(){return m_maxWidth;}

  public:

    class Column
    {
      private:
        T* _array;
        unsigned int _size;
      public:
        Column(T* array, unsigned int s);
        T& operator[](const unsigned int index);      //lhs index access operator
        T operator[](const unsigned int index) const; //rhs index access operator
    };

    Map();
    Map(unsigned int w, unsigned int h);
    Map(Map<T>& m);
    ~Map();

    bool setDimensions(const unsigned int w, const unsigned int h);

    Column operator[](const unsigned int index);      //lhs index access operator
    Column operator[](const unsigned int index) const;//rhs index access operator

    const unsigned int width(){return m_width;}
    const unsigned int height(){return m_height;};

};


/******************

  MAP CLASS FUNCTIONS

 *****************/

template<class T>
Map<T>::Map():
  m_maxWidth(MAP_INITIALMAX),
  m_maxHeight(MAP_INITIALMAX),
  m_data(nullptr),
  m_width(0),
  m_height(0)
{
  _allocate();
}


template<class T>
Map<T>::Map(unsigned int w, unsigned int h):
  m_maxWidth(MAP_INITIALMAX),
  m_maxHeight(MAP_INITIALMAX),
  m_data(nullptr),
  m_width(w),
  m_height(h)
{
  _allocate();
}


template<class T>
Map<T>::Map(Map<T>& map):
  m_maxWidth(map._getMaxHeight()),
  m_maxHeight(map._getMaxWidth()),
  m_data(nullptr),
  m_width(map.m_width),
  m_height(map.m_height)
{

  //change memory variables if they are unneccesarily large
  if(m_maxWidth > m_width*2)
    m_maxWidth = m_width*2;

  if(m_maxHeight > m_height*2)
    m_maxHeight = m_height*2;

  //copy the contents of m into this.m_data
  m_data = new T*[m_maxWidth];
  for(unsigned int x = 0; x < m_maxWidth; x++)
  {
    m_data[x] = new T[m_maxHeight];
    for(unsigned int y = 0; y < m_maxHeight; y++)
    {
      if( x < m_width && y < m_height)
        m_data[x][y] = map[x][y];
    }
  }
}


  template<class T>
Map<T>::~Map()
{
  if(m_data != nullptr)
    _deallocate();
}


  template<class T>
bool Map<T>::setDimensions(const unsigned int w, const unsigned int h)
{
  //Don't alter the dimensions if they are the same
  if(w == m_width && h == m_height)
    return false;

  m_width = w;
  m_height = h;

  //need to reallocate memory if size is larger than memory can accomodate
  if(m_width >= m_maxWidth || m_height >= m_maxHeight)
    _resize();

  return true;
}


template<class T>
/**
 * @brief Function that allocates the map's memory
 */
void Map<T>::_allocate()
{
  if(m_width*2 > MAP_INITIALMAX)
    m_maxWidth = m_width*2;

  if(m_height*2 > MAP_INITIALMAX)
    m_maxHeight = m_height*2;


  m_data = new T*[m_maxWidth];
  for(unsigned int x = 0; x < m_maxWidth; x++)
    m_data[x] = new T[m_maxHeight];
}

template<class T>
/**
 * @brief Function that resizes the map's memory should the size get larger
 */
void Map<T>::_resize()
{
  unsigned int newMaxWidth,newMaxHeight;

  newMaxWidth  = (m_maxWidth <= m_width)  ? m_width*2  : m_maxWidth;
  newMaxHeight = (m_maxHeight <= m_height)? m_height*2 : m_maxHeight;

  if(m_maxWidth < newMaxWidth)
  {
    T** tempData = m_data; 
    m_data = new T*[newMaxWidth];

    for(unsigned int x = 0; x < newMaxWidth; x++)
    {
      //if height changed, copy and delete old column
      if(m_maxHeight < newMaxHeight) 
      {
        m_data[x] = new T[newMaxHeight];

        if(x < m_maxWidth)
        {
          //copy contents of old column if possible
          for(unsigned int y = 0; y < m_maxHeight; y++)
          {
            m_data[x][y] = tempData[x][y];
          }
          delete [] tempData[x]; 
        }
      }
      else if(x < m_maxWidth)//if height is same and within old map
      {
        m_data[x] = tempData[x]; //reuse old columm
        tempData[x] = nullptr;
      }
      else
      {
        m_data[x] = new T[newMaxHeight];
      }
    }//end x loop

    delete [] tempData;
  }
  else// height is the only variable that changed
  {
    for(unsigned int x = 0; x < m_maxWidth; x++)
    {
      T* tempData = m_data[x];
      m_data[x] = new T[newMaxHeight];
      for(unsigned int y = 0; y < m_maxHeight; y++)
      {
        if(y < m_maxHeight)
          m_data[x][y] = tempData[y];
      }
      delete [] tempData;
    }
  }

  //apply the changes of max width and max height
  m_maxWidth = newMaxWidth;
  m_maxHeight = newMaxHeight;
}


template<class T>
/**
 * @brief Function that frees the map's memory
 */
void Map<T>::_deallocate()
{
  if(m_data == nullptr)
    return;

  for(unsigned int x = 0; x < m_maxWidth; x++)
    delete [] m_data[x];

  delete [] m_data;
}


template<class T>
/**
 * @brief Work around for double [] operator usage to access map elements
 *
 * @param index the x index(xth column) of the map
 *
 * @return the x column of the map
 */
typename Map<T>::Column Map<T>::operator[](const unsigned int index)
{
  try
  {
    if(index < m_width)
      return Column(m_data[index], m_height);
    else
      throw std::out_of_range(" Map::operator[] : Index is out of bounds");
  }
  catch(std::out_of_range e)
  {
    throw e;
  }
}


template<class T>
/**
 * @brief the const variation of the index operator 
 * 
 * @see Map<T>::operator[]
 *
 * @param index the x index(xth column) of the map
 *
 * @return the x column of the map
 */
typename Map<T>::Column Map<T>::operator[](const unsigned int index) const
{
  try
  {
    if(index < m_width)
      return Column(m_data[index], m_height);
    else
      throw std::out_of_range(" Map::operator[] : Index is out of bounds");
  }
  catch(std::out_of_range e)
  {
    throw e;
  }
}

/******************

  COLUMN NESTED/PROXY CLASS

 *****************/


template<class T>
Map<T>::Column::Column(T* array, unsigned int s):
  _array(array),
  _size(s)
{
}

  template<class T>
T& Map<T>::Column::operator[](const unsigned int index)
{
  if(index <= _size)
    return _array[index];
  else
    throw std::out_of_range("Column::operator[]() : Index out of bounds");
}

template<class T>
T Map<T>::Column::operator[](const unsigned int index) const
{
  if(index <= _size)
    return _array[index];
  else
    throw std::out_of_range("Column::operator[]() : Index out of bounds");
}


#endif /* MAP_H */
