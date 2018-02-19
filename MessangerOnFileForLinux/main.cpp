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
  return fibonacci(5);
}
