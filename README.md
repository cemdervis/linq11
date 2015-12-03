# linq11 - LINQ for C++11

linq11 is a header-only LINQ library for C++11 with minimal dependencies.
It neatly integrates into the STL and takes advantage of C++11 features, mainly the range-based for loop.

Example usage:

```cpp
#include <iostream>
#include <string>
#include <vector>
#include "linq.h"

struct Person
{
    std::string Name;
    int Age;
};

int main()
{
    std::vector<Person> people = {
        {"P1", 20},
        {"P2", 21},
        {"P3", 22}
    };

    auto query = linq::from(&people)
        .where([](const Person& p) { return p.Age > 20; });

    for (const auto& p : query)
    {
        std::cout << p.Name << ", " << p.Age << std::endl;
    }

    return 0;
}
```

```
Output:
P2, 21
P3, 22
```

linq11...
- resolves all type related functionality at compile-time; no virtual dispatch is used
- uses lazy evaluation, so your queries still work even after you modify the container it's based on
- is extremely efficient in the way it works with your data; it avoids making copies and passes by reference wherever it can
- does not maintain a flat list of operators in your query, but rather generates a linked-list at compile time
- does not use exceptions
- does not use boost or any other library
- works with everything that behaves like an STL container. So vector, maps, strings, ...
- tries to notify the user of errors at compile-time whenever it can (static_assert)
- is licensed under the MIT license
- uses the beloved dot operator!

Please take a look at the [Wiki](https://github.com/cemdervis/linq11/wiki) for the list of supported operators and their usage.
