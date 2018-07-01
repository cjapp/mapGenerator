
set(SRC_SOURCE_FILES
  map.h
  mapGenerator.cpp
  mapGenerator.h
  ppm.cpp
  ppm.h
  perlinNoise.cpp
  perlinNoise.h
  random.cpp
  random.h
  )

add_library(src ${SRC_SOURCE_FILES})
