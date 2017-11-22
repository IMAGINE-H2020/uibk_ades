ADES C++ implementation
----

Depends on :
 - mlpack [http://www.mlpack.org/]
 - libgp [https://github.com/mblum/libgp]
 - boost serialization [http://www.boost.org/]

## Quick-start

This library implements in C++ the ADES model and related tools. Documentation can be generated by enabling the option via passing when invoking cmake
```
-DBUILD_DOC=ON
```

## Building

This library relies on CMake for build ; thus, building only requires the usual following commands (in the library folder):

```
mkdir build && cd build

cmake ..

make (-j4)

sudo make install
```

Files will be installed in ```/usr/lib``` and ```/usr/include```, and are assumed to be there when searched by the ROS node (see below). Consider updating these path if you follow a different organisation.

## Usage

Some examples can be found in the examples folder and can be compiled by calling
```
make populating_ades
make populating_db
make save_load_ades
```
and subsequently run by changing to ```build/src/examples``` and executing any of the resulting binaries.

Observe that for this you first have to successfully install the library. They demonstrate basic usage of the library. A ROS wrapper is temporary available [here](https://github.com/r1d1/iis_libades_ros) for easy integration with robot software. It provides some services to interact with the ADES database and ADES data structures. The intented use of this library is through the node, but if you develop a different interface, we'll be happy to know about.

**IMPORTANT NOTE**: as the library is under active development, saved ADES are usually not compatible with newer versions of the library (i.e. do not use the last version of the library if you want to keep use of an older version of the ADES). A fix will be issued as soon as possible.
