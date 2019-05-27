## Interval Map

```interval_map<K, V>``` is a data structure that efficiently associates intervals of keys of type K with values of type V. It is implemented on top of [```std::map```](https://en.cppreference.com/w/cpp/container/map).

The ```assign``` member function is implemented as follows:

Each key-value-pair (K, V) in the ```std::map``` means that the value V is associated with the interval from K (including) to the next key (excluding) in the ```std::map```.

### Example
The std::map (0,'A'), (3,'B'), (5,'A') represents the mapping:

* 0 -> 'A'
* 1 -> 'A'
* 2 -> 'A'
* 3 -> 'B'
* 4 -> 'B'
* 5 -> 'A'
* 6 -> 'A'
* 7 -> 'A'
* ... all the way to numeric_limits<int>::max()

The representation in the ```std::map``` must be canonical, that is, consecutive map entries must not have the same value: ..., (0,'A'), (3,'A'), ... is not allowed. Initially, the whole range of K is associated with a given initial value, passed to the constructor of the ```interval_map<K, V>``` data structure.

### Key Type K

* besides being copyable and assignable, is less-than comparable via operator<
* is bounded below, with the lowest value being std::numeric_limits<K>::lowest()
* does not implement any other operations, in particular no equality comparison or arithmetic operators

### Value Type V

* besides being copyable and assignable, is equality-comparable via operator==
* does not implement any other operations
