#ifndef FMAP_H_
#define FMAP_H_

#include <stdlib.h>
#include <string.h>

#include <limits>
#include <algorithm>

template <typename T, typename U>
class FMap {
 public:
  FMap() : min_(0), max_(0), buffer_(NULL) {}
  FMap(T min, T max) : min_(min), max_(max) {
    buffer_ = reinterpret_cast<U *>(malloc(sizeof(U) * (max_ - min_)));
    std::fill_n(buffer_, max_ - min_, std::numeric_limits<U>::max());
  }

  U &operator[](T loc) {
    if (loc < min_) {
      T new_min = loc;
      U *new_buf = reinterpret_cast<U *>(malloc(sizeof(U) * (max_ - new_min)));
      memcpy(&new_buf[min_ - new_min], buffer_, (max_ - min_) * sizeof(U));
      std::fill_n(new_buf, min_ - new_min, std::numeric_limits<U>::max());
      free(buffer_);
      min_ = new_min;
      buffer_ = new_buf;
    }
    if (loc >= max_) {
      T new_max = loc + 1;
      U *new_buf = reinterpret_cast<U *>(malloc(sizeof(U) * (new_max - min_)));
      memcpy(new_buf, buffer_, (max_ - min_) * sizeof(U));
      std::fill_n(&new_buf[max_ - min_], new_max - max_,
                  std::numeric_limits<U>::max());
      free(buffer_);
      max_ = new_max;
      buffer_ = new_buf;
    }
    return buffer_[loc - min_];
  }

 private:
  T min_, max_;
  U *buffer_;
};

#endif
