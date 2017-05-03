# intervals

Small header only library for interval set and map.

## Required

Compiler with C++11.


# Usage

There are some thing in the library:

 * interval
 * set of intervals
 * map of intervals

### interval

Different type cvan be used as domain type for intervals

```cpp
intervals::interval<double> double_ival;
intervals::interval<std::string> string_ival;
intervals::interval<my_class, my_less> my_class_ival;

```

### set






