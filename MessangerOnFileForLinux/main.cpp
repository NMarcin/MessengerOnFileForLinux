#include <iostream>



constexpr unsigned fibonacci(const unsigned x)
{
    return x <= 1
            ?
            1
              :
            fibonacci(x - 1) + fibonacci(x - 2);
}

int main() {
  if (int a = 6; a < 7)
      return 0;
  return fibonacci(5);
}

