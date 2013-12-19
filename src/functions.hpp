#pragma once
#ifndef __NVCC__
#include <armadillo>
#include <algorithm>
#endif


struct Squared_Error {
  template<typename U>
  #ifdef __NVCC__
  __device__
  #endif
  static inline U error(U target, U result) {
    return 1/2.0f * (target - result) * (target - result);
  }
  template<typename U, typename J>
  #ifdef __NVCC__
  __device__ static inline U error_dir(U target, J result) {
    return (target - result);
  }
  #else
  static inline auto error_dir(U target, J result) -> decltype(target-result) {
    return (target - result);
  }
  #endif
};

#ifndef __NVCC__
using arma::exp;
#endif
struct Logistic {
  template<typename U>
  #ifdef __NVCC__
  __device__
  #endif
  static inline U activation(U k) {
    return 1 / (1 + exp(-k));
  }

  template<typename U>
  #ifdef __NVCC__
  __device__ static inline U activation_dir(U k) {
    return k * (1 - k);
  }
  #else
  static inline U activation_dir(U k) {
    return k % (1 - k);
  }
  #endif
};
