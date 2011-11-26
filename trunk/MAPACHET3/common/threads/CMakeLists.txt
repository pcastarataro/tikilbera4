FIND_LIBRARY(PTHREAD NAMES pthread)

include_directories(${PTHREAD_INCLUDE_DIRS})
ADD_LIBRARY(threads Lock Mutex Thread)
