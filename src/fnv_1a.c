#include "include/fnv_1a.h"

//hashing algorithm: FNV-1a
//from: https://en.wikipedia.org/wiki/Fowler–Noll–Vo_hash_function
unsigned long fnv_1a(char *str) {
  unsigned long offset = 14695981039346656037;
  unsigned long prime = 1099511628211;

  unsigned long hash = offset;

  for (int i = 0; i < strlen(str); i++) {
    hash = hash ^ str[i];
    hash = hash * prime;
  }
  
  return hash;
}
