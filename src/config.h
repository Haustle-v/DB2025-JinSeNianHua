#pragma once

// #define ENABLE_DEBUG_PRINT  // 注释掉即可关闭调试输出

#ifdef ENABLE_DEBUG_PRINT
  #define DEBUG_PRINT(x) std::cout << x << std::endl
#else
  #define DEBUG_PRINT(x) do {} while(0)
#endif

#ifdef ENABLE_DEBUG_PRINT
  #define DEBUG_PRINT_BLOCK(code) do { code } while(0)     // 控制客户端的输出
#else
  #define DEBUG_PRINT_BLOCK(code) do {} while(0)
#endif
