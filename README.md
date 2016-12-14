# linq11 - LINQ for C++11

http://cemdervis.github.io/linq11/

linq11 is a header-only LINQ library for C++11 with minimal dependencies.
It neatly integrates into the STL and takes advantage of C++11 features, mainly the range-based for loop and lambda functions.

_Example_:
```cpp
#include <iostream>
#include <string>
#include <vector>
#include "linq.h"

using namespace std;

struct Person
{
    string Name;
    int Age;
};

int main()
{
    vector<Person> people = {
        { "P1", 20 },
        { "P2", 21 },
        { "P3", 22 }
    };

    auto query = linq::from(&people)
        .where([](const Person& p) { return p.Age > 20; });

    for (const auto& p : query)
    {
        cout << p.Name << ", " << p.Age << endl;
    }

    return 0;
}
```

_Output_:
```
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


# Supported LINQ Operators

- [Aggregate Operators](https://github.com/cemdervis/linq11/wiki/Aggregate-Operators)
  - _[Aggregate](https://github.com/cemdervis/linq11/wiki/Aggregate-Operators#aggregate)_
  - _[Average](https://github.com/cemdervis/linq11/wiki/Aggregate-Operators#average)_
  - _[Count](https://github.com/cemdervis/linq11/wiki/Aggregate-Operators#count)_
  - _[Max](https://github.com/cemdervis/linq11/wiki/Aggregate-Operators#max)_, _[Min](https://github.com/cemdervis/linq11/wiki/Aggregate-Operators#min)_
  - _[Sum](https://github.com/cemdervis/linq11/wiki/Aggregate-Operators#sum)_

- [Concatenation Operators](https://github.com/cemdervis/linq11/wiki/Concatenation-Operators)
  - _[Append](https://github.com/cemdervis/linq11/wiki/Concatenation-Operators#append)_

- [Element Operators](https://github.com/cemdervis/linq11/wiki/Element-Operators)
  - _[Element At](https://github.com/cemdervis/linq11/wiki/Element-Operators#element-at)_
  - _[First](https://github.com/cemdervis/linq11/wiki/Element-Operators#first)_, _[Last](https://github.com/cemdervis/linq11/wiki/Element-Operators#last)_

- [Filter Operators](https://github.com/cemdervis/linq11/wiki/Filter-Operators)
  - _[Where](https://github.com/cemdervis/linq11/wiki/Filter-Operators#where)_

- [Generation Operators](https://github.com/cemdervis/linq11/wiki/Generation-Operators)
  - _[From To](https://github.com/cemdervis/linq11/wiki/Generation-Operators#from-to)_
  - _[Repeat](https://github.com/cemdervis/linq11/wiki/Generation-Operators#repeat)_
  - _[Generate](https://github.com/cemdervis/linq11/wiki/Generation-Operators#generate)_

- [Join Operators](https://github.com/cemdervis/linq11/wiki/Join-Operators)
  - _[Join](https://github.com/cemdervis/linq11/wiki/Join-Operators)_

- [Partition Operators](https://github.com/cemdervis/linq11/wiki/Partition-Operators)
  - _[Skip](https://github.com/cemdervis/linq11/wiki/Partition-Operators#skip)_, _[Skip While](https://github.com/cemdervis/linq11/wiki/Partition-Operators#skip-while)_
  - _[Take](https://github.com/cemdervis/linq11/wiki/Partition-Operators#take)_, _[Take While](https://github.com/cemdervis/linq11/wiki/Partition-Operators#take-while)_

- [Projection Operators](https://github.com/cemdervis/linq11/wiki/Projection-Operators)
  - _[Select](https://github.com/cemdervis/linq11/wiki/Projection-Operators#select)_
  - _[Select Many](https://github.com/cemdervis/linq11/wiki/Projection-Operators#select-many)_

- [Quantifier Operators](https://github.com/cemdervis/linq11/wiki/Quantifier-Operators)
  - _[All](https://github.com/cemdervis/linq11/wiki/Quantifier-Operators#all)_
  - _[Any](https://github.com/cemdervis/linq11/wiki/Quantifier-Operators#any)_

- [Set Operators](https://github.com/cemdervis/linq11/wiki/Set-Operators)
  - _[Distinct](https://github.com/cemdervis/linq11/wiki/Set-Operators#distinct)_

- [Sorting Operators](https://github.com/cemdervis/linq11/wiki/Sorting-Operators)
  - _[Order By](https://github.com/cemdervis/linq11/wiki/Sorting-Operators#order-by)_
  - _[Then By](https://github.com/cemdervis/linq11/wiki/Sorting-Operators#then-by)_
  - _[Reverse](https://github.com/cemdervis/linq11/wiki/Sorting-Operators#reverse)_


