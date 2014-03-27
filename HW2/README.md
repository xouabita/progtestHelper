Tax Register 1 & 2
===============

Instructions
----------------

Just go into the assignement you want to do and put your code in taxregister.cpp
To test just run rake test.
Before to submit to progtest, erase that :

```cpp
#ifndef NO_MAIN
// main function
#endif
```

```bash
cd taxregister1/src # put your code here
cd ..
rake test
```

To have a more precise test results :

```bash
./build/test.out -s
```
Documentation for Catch : [http://kiq.li/S9][1]

If you want to add some test, just go into ./test/test.cpp

[1]: http://kiq.li/S9
