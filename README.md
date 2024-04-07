# quadratic_equation module

### Description

The quadratic_equation module in the C language contains 
an implementation of the solve_equation function. 

The arguments of the function are 3 real numbers $a$, $b$, $c$. 
The function solves the quadratic equation $ax^2 + bx + c = 0$. 

As a result, the function returns msg_id (the values are described 
in the quadratic_equation.h file).

### Bilding

To build a static library, run the following commands:

1) Clone the repository:
```bash
git clone https://github.com/arseny114/quadratic_equation.git
```
2) Create a build:
```bash
mkdir build
```
3) Go to build:
```bash
cd build
```
4) Run the build:
```bash
cmake ..
make
```

### Tests

To run the tests, you need to use the commands from build:
```bash
make check
```
or:
```bash
make test
```
or:
```bash
ctest
```
