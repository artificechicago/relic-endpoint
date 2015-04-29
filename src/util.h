#ifndef __RELIC_UTIL_H__
#define __RELIC_UTIL_H__

#define _DECL_KEY_(name, val1, val2, val3, val4) static uint32_t name[] = \
  {val1, val2, val3, val4}

#ifdef __cplusplus
extern "C"{
#endif
int freeRam();
#ifdef __cplusplus
}
#endif //extern "C"
#endif //header guard
