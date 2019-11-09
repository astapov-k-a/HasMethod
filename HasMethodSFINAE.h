/// @author Astapov K.A. +7(931)-29-17-0-16
/// @date 08/11/2019
/// @HasMethod.h - how to detect if a class contains given method

#ifndef    HAS_METHOD_SFINAE_PROTECT_SIGNATURE_FB7F2CF5D94EF
#define    HAS_METHOD_SFINAE_PROTECT_SIGNATURE_FB7F2CF5D94EF
#include <cstdio>


struct A {
  const char * SomeFun(int i) { return "aa"; }
  void AaBbCcDd() {}
};

struct B {};

/// @brief создаёт структурку ClassName с помощью которого можно определить наличие метода FunName в заданном классе (класс задаётся как параметр шаблона)
/// @details пример: 
///           HAS_METHOD_DEFINTION( HasPrintMethod, Print )
///           struct S { void Print() {} };
///           void main () {
///             bool exist = HasPrintMethod<S>::value;
///           }
/// @warning не работает, если в методе есть 2 перегрузки метода, наличие которого мы проверяем
#define HAS_METHOD_DEFINITION( ClassName, FunName ) \
template <typename T> struct ClassName { \
 private: \
  struct HasMethodHelperFalse { \
    static constexpr const bool value = 0; \
  };\
\
  template <class T2, decltype(&T2::FunName) U = &T2:: FunName > struct HasMethodHelperTrue { \
    static constexpr const bool value = 1; \
  }; \
\
  HasMethodHelperFalse static constexpr detect(...) { return HasMethodHelperFalse(); } \
\
  template <typename T2> HasMethodHelperTrue<T2> static constexpr detect( T2 * ) { return HasMethodHelperTrue<T2>();  } \
\
 public: \
  static constexpr const bool value = decltype(     detect(   static_cast<T*>( nullptr )   )     ):: value;\
};

HAS_METHOD_DEFINITION( HasMethod, AaBbCcDd )
HAS_METHOD_DEFINITION( HasMethod2, SomeFun )


int main() {
    printf("\n%u %u %u", HasMethod <A>::value, HasMethod <B>::value, HasMethod <int>::value );
    printf("\n%u %u %u", HasMethod2<A>::value, HasMethod2<B>::value, HasMethod2<int>::value );
    return 0;    
}


// пример, как то же сделать без макросов для одного метода. example: same, but without macro
// замените AaBbCcDd на нужную функцию. replace AaBbCcDd to given method name
#   if 0 
template <typename T> struct HasMethod {
 private:
  struct HasMethodHelperFalse {
    static constexpr const bool value = 0;
  };

  template <class T2, decltype(&T2::AaBbCcDd) U = &T2::AaBbCcDd > struct HasMethodHelperTrue {
    static constexpr const bool value = 1;
  };

  HasMethodHelperFalse static constexpr detect(...) { return HasMethodHelperFalse(); }

  template <typename T2> HasMethodHelperTrue<T2> static constexpr detect( T2 * ) { return HasMethodHelperTrue<T2>();  }

 public:
  static constexpr const bool value = decltype(     detect(   static_cast<T*>( nullptr )   )     ):: value;
};
#   endif

#endif  // HAS_METHOD_SFINAE_PROTECT_SIGNATURE_FB7F2CF5D94EF
