# Smart-flowerpot


## Getting Started
---
Git clone this project in your machine.

### **Prerequisites**

This project was developed on Ubuntu 18 and tested on Ubuntu 18 and 20.

**Step by step instalation**

You will need to have a C++ compiler for C++17 standard (Pistache library will use that standard).

1. Install Pistache library (check this for updated instructions http://pistache.io/docs/ or follow the next instructions)

    ```
    $ git clone https://github.com/pistacheio/pistache.git
    $ cd pistache
    $ meson setup build
    $ meson install -C build
    ```
2. Install nlohmann-json libray (check this for updated instructions https://github.com/nlohmann/json or follow the next instruction)

    ```
    $ sudo apt-get install nlohmann-json3-dev
    ```
3. Install Paho library (check this for updated instructions https://github.com/eclipse/paho.mqtt.cpp or follow the next instructions)

    Prerequisites

    ```
    $ sudo apt-get install build-essential gcc make cmake cmake-gui cmake-curses-gui

    $ sudo apt-get install libssl-dev 

    $ sudo apt-get install doxygen graphviz
    ```

    Building the Paho C library

    Before building the C++ library, first, build and install the Paho C library, if not already present. Note, this version of the C++ library requires Paho C v1.3.8 or greater.

    ```
    $ git clone https://github.com/eclipse/paho.mqtt.c.git
    $ cd paho.mqtt.c
    $ git checkout v1.3.8

    $ cmake -Bbuild -H. -DPAHO_ENABLE_TESTING=OFF -DPAHO_BUILD_STATIC=ON \
    -DPAHO_WITH_SSL=ON -DPAHO_HIGH_PERFORMANCE=ON
    $ sudo cmake --build build/ --target install
    $ sudo ldconfig
    ```

    Building the Paho C++ library

    ```
    $ git clone https://github.com/eclipse/paho.mqtt.cpp
    $ cd paho.mqtt.cpp

    $ cmake -Bbuild -H. -DPAHO_BUILD_STATIC=ON \
        -DPAHO_BUILD_DOCUMENTATION=TRUE -DPAHO_BUILD_SAMPLES=TRUE
    $ sudo cmake --build build/ --target install
    $ sudo ldconfig
    ```

You will need to install the Pistache library. On Ubuntu, you can install a pre-built binary as described here.

### **Building**
TODO


### **Running**
TODO