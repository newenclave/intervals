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

Different type can be used as domain type for intervals

```cpp
intervals::interval<double> double_ival;
intervals::interval<std::string> string_ival;
intervals::interval<my_class, my_less> my_class_ival;

```

```cpp
usage ival_type = intervals::interval<double>;
ival_type double_ival = ival_type::left_open(-0.1, 10.1);

/// double_ival == "(-0.1, 10.1]"

```
#### producers

```cpp
ival_type::open(a, b)           -> (a, b)
ival_type::closed(a, b)         -> [a, b]

ival_type::degenerate(a)        -> ival_type::closed(a, a)
                                -> [a, a]

ival_type::left_open(a, b)      -> (a, b]
ival_type::left_open(a)         -> (a, +inf)

ival_type::left_closed(a, b)    -> [a, b)
ival_type::left_closed(a)       -> [a, +inf)

ival_type::right_open(a, b)     -> [a, b)
ival_type::right_open(a)        -> (-inf, b)

ival_type::right_closed(a, b)   -> (a, b]
ival_type::right_closed(a)      -> (-inf, b]

//// infinities
ival_type::infinite( )          -> (-inf, +inf)
ival_type::minus_infinite( )    -> (-inf, -inf) or (-inf)
ival_type::plus_infinite( )     -> (+inf, +inf) or (+inf)

```

### set

Represents set of disjoint intervals. Interval can be added to the set, can be cut off or merged.
```cpp
usage ival_type = intervals::interval<double>;
intervals::set<double> double_ival_set;

/// example
double_ival_set.insert(ival_type::open(0, 10));
double_ival_set.insert(ival_type::closed(10, 20));
double_ival_set.insert(ival_type::left_opened(20));

/// double_ival_set == "(0, 10) [10, 20] (20, +inf)"

```

#### insert
Insterts nrew interval to the set.
It doesn't merge the values if new interval intersect with them.

```cpp
usage ival_type = intervals::interval<double>;
intervals::set<double> dis;

dis.insert(ival_type::infinite( )); /// {(-inf, +inf)}
dis.insert(ival_type::left_closed( 0, 10)); /// {(-inf, 0) [0, 10) [10, +inf)}
                                                           ^
                   inserted value splits other interval____|

/// empty interval can be inserted
dis.insert(ival_type::left_open( -1, -1 )); /// {(-inf, -1](-1, -1](-1, 0) [0, 10) [10, +inf)}
                                                           ^      ^
                                         empty interval____|______|


```





