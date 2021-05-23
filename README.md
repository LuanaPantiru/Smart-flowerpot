## Getting Started

---
Git clone this project in your machine.

### **Prerequisites**

This project was developed on windows using WSL for Ubuntu 20.04 LTS and tested on windows using WSL for Ubuntu 20.04 LTS.

### **1. Setup Windows environment**


#### **1.1. Setup WSL**

You can run this program in windows if you use WSL. Check this to set up your environment.
https://www.jetbrains.com/help/clion/how-to-use-wsl-development-environment-in-product.html#wsl-general


#### **1.2. Install mosquitto broker**

1.2.1 On windows

Also on machine should run **mosquitto broker** (https://mosquitto.org/download/).
On WSL mosquitto broker is not supported so consider a windows version if you use WSL.

Mosquitto broker can be started with `mosquitto` command ran from the installer root folder.

You can test the mosquitto connection and emulate requests with Mqtt-Client-Explorer (http://mqtt-explorer.com/)


1.2.2 On ubuntu

```
$ sudo apt-add-repository ppa:mosquitto-dev/mosquitto-ppa
$ sudo apt-get update
$ sudo apt install mosquitto
$ sudo service mosquitto start
```

### **2. Setup host machine (dependencies instalation)**

2.1. Update packages

```
$ sudo apt-get update
```

2.2. You will need to have a C++ compiler for C++17 standard (Pistache library will use that standard).

```
$ sudo apt-get install g++
```

2.3. Install Pistache library (check this for updated instructions http://pistache.io/docs/ or follow the next instructions).You will need to install the Pistache library. On Ubuntu, you can install a pre-built binary as described here.

```
$ git clone https://github.com/pistacheio/pistache.git
$ cd pistache
$ sudo apt install meson
$ sudo meson setup build
$ sudo meson install -C build
$ cd ..
```

2.4. Install nlohmann-json libray (check this for updated instructions https://github.com/nlohmann/json or follow the next instruction)

```
$ sudo apt-get install nlohmann-json3-dev
```

2.5. Install Paho library (check this for updated instructions https://github.com/eclipse/paho.mqtt.cpp or follow the next instructions)

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

$ cmake -Bbuild -H. -DPAHO_ENABLE_TESTING=OFF -DPAHO_BUILD_STATIC=ON -DPAHO_WITH_SSL=ON -DPAHO_HIGH_PERFORMANCE=ON
$ sudo cmake --build build/ --target install
$ sudo ldconfig
$ cd ..
```

Building the Paho C++ library

```
$ git clone https://github.com/eclipse/paho.mqtt.cpp
$ cd paho.mqtt.cpp

$ cmake -Bbuild -H. -DPAHO_BUILD_STATIC=ON -DPAHO_BUILD_DOCUMENTATION=TRUE -DPAHO_BUILD_SAMPLES=TRUE
$ sudo cmake --build build/ --target install
$ sudo ldconfig
$ cd ..
```

### **3. Building**
3.1.

In order to build this project, you must clone the repository into your machine.
**If you already have the project cloned, skip to 3.2.**

- Chose a location where you want to clone the project.
- Type `git clone https://github.com/LuanaPantiru/Smart-flowerpot.git` into the console.
- A directory named `Smart-flowerpot` should appear.

3.2.
- Navigate two levels into the project directory, using `cd Smart-flowerpot/project`

[comment]: <> (- Switch to the develop branch of this project &#40;this our current &#41;)
- Build the project by using the `make` command. A building process should start. If everything is alright, you will see this message:
>Compile finished.
- An executable file `smartpot.out` should be generated in your current directory. You can check this with the `ls` command.


### **4. Running**
- Make sure you are in the right directory `Smart-flowerpot/project`
- Run the project by typing `./smartpot.out`
- You're all set!



### **5. Stop the program**
To stop the program use **http://localhost:9080/api/close** endpoint or use the standard killing commands like `CTRL+C`.

Obs:  **http://localhost:9080/** is default setting. If you change this, change route in **api/close** endpoint also.