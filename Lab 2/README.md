## Problem statement

Implement a desk calculator using operator precedence parsing.

## How to run

```
$ g++ main.cpp
$ ./a.out
$ 6+(5*3-(10/5))
> 19
```

## Notes
- Negative values are not handled. i.e. `5-9` is good but `-4` is not.
- Supported operations __addition__, __substraction__, __multiply__, __divide__.
- Brackets __`()`__ are supported.