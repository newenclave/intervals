# intervals

Small header only library for interval set and map.

## Required

Compiler with C++11.


# Usage

There are some things in the library:

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

ival_type::degenerate(a)        -> [a, a]
ival_type::closed(a, a)         -> [a, a]

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

ival_type::intersection( [a, b) [c, d) ) -> [a, d)

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

Insterts new interval to the set.
It doesn't merge the other intervals if new interval intersects with them.

```cpp
usage ival_type = intervals::interval<double>;
intervals::set<double> dis;

dis.insert(ival_type::infinite( )); /// {(-inf, +inf)}
dis.insert(ival_type::left_closed( 0, 10)); /// {(-inf, 0) [0, 10) [10, +inf)}
//                                                         ^
//                 inserted value splits other interval____|

/// empty interval can be inserted (see "known issue" above)
dis.insert(ival_type::left_open( -1, -1 )); /// {(-inf, -1](-1, -1](-1, 0) [0, 10) [10, +inf)}
//                                                         ^      ^
//                                       empty interval____|______|

```

##### known issue
    There is no way to insert empty interval with both open side (a, a)
    Because it is impossible to know which endpoint must be closed.
    So this type of intervals just cut off right part from interval that intersects with

```cpp
usage ival_type = intervals::interval<double>;
intervals::set<double> dis;

dis.insert(ival_type::infinite( )); /// {(-inf, +inf)}

/// warning!
dis.insert(ival_type::open( 0, 0)); /// The result is: {(-inf, 0] (0, 0)}

```

#### merge
Insterts new interval to the set and merges all the others that it intersects.

```cpp
usage ival_type = intervals::interval<double>;
intervals::set<double> dis;

dis.merge(left_closed( 0, 10 ) ); /// {[0, 10)}
dis.merge(left_closed( 10, 20 ) ); /// {[0, 10),[10, 20)}
//                                         ^        ^
//                                         |        |
// merge value                             [ 5, 15  )

dis.merge(left_closed( 5, 15 ) ); /// {[0, 20)}

```

#### cut
Cuts interval of values from the set.


```cpp
usage ival_type = intervals::interval<double>;
intervals::set<double> dis;

dis.insert(ival_type::infinite( )); /// {(-inf, +inf)}

dis.cut(ival_type::left_closed( 0, 10)); /// {(-inf, 0) [10, +inf)}

dis.cut(ival_type::degenerate(-1)); /// {(-inf, -1)(-1, 0)[10, +inf)}

/// cut empty interval; ie split the other into 2 parts
dis.cut(ival_type::right_open(100)); /// {(-inf, -1)(-1, 0)[10, 100) [100, +inf)}
//                                                                  ^
//                                              [100, 100) here ____|

```

#### find

##### find by domain type

```cpp
usage ival_type = intervals::interval<double>;
intervals::set<double> dis;

dis.insert(ival_type::infinite( )); /// {(-inf, +inf)}
auto f = dis.find( 100.999 );
/// here is f is iterator than points to the unique set's element "(-inf, +inf)"

dis.cut(ival_type::closed( -100, 100 )); /// {(-inf, -100) (100 +inf)}
auto f = dis.find( 100.999 );
auto s = dis.find( 0 );

/// f points to (100 +inf)
/// s is dis.end( )

```

##### find by interval
Seaching by interval is a little bit tricky. ```dis.insert(some_interval)```
returns iterator that points to element that equal to "some_interval" or contains it.

```cpp
usage ival_type = intervals::interval<double>;
intervals::set<double> dis;

dis.insert(ival_type::left_closed(  0, 10));
dis.insert(ival_type::left_closed( 10, 20));
dis.insert(ival_type::left_closed( 20, 30));
dis.insert(ival_type::left_closed( 30, 40));
/// dis = {[0, 10)[10, 20)[20, 30)[30, 40)  }

auto f = dis.find( ival_type::left_closed( 20, 30) ) // ok. points to [20, 30)
auto s = dis.find( ival_type::open( 20, 30) )        // ok. points to [20, 30)
auto t = dis.find( ival_type::open( 32, 35) )        // ok. points to [30, 40)
auto e = dis.find( ival_type::open( 10, 35) )        // == end( )

```

### map

The map is very similar to the set but has mapped value and operator []

#### some examples

```cpp
usage ival_type = intervals::interval<double>;
intervals::map<double, std::string> dim; // maps interval<double> -> string

dim[ival_type::infinite( )] = "infinite";
/// dim { (-inf, +inf) -> "infinite" }



```
