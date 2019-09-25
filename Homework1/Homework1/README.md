Homework 1
----------

## Solution Results:
![Solution Result](https://github.com/jingyangcarl/Resources/blob/master/CSCI561/Assignment1/output.png)

## Solution Introduction:
This solution is used to implement BFS (Breadth First Search), UCS (Uninform Cost Search), and ASS (A* Search).
* BFS is implemented with a normal queue, where deeper nodes will be expanded after all the shallower nodes are expanded.
* UCS is implemented with a priority queue, where nodes with smaller cost (distance accumulated from landing location in this case) will be expanded first.
* A* is implemented with a priority queue, where nodes with smaller sum of current cost (distance accumulated from landing location in this case) and predicted cost (distance from the current locaiton to distinations) will be expanded first.

## Solution Environment:
Visual Studio 2019

## Solution Documentation:


## Solution Hierarchy:
```
Homework1
©¦  Homework1.sln
©¦
©À©¤Debug
©¦      Homework1.exe
©¦      Homework1.ilk
©¦      Homework1.pdb
©¦
©¸©¤Homework1
    ©¦  ASSProcessor.cpp
    ©¦  ASSProcessor.h
    ©¦  BFSProcessor.cpp
    ©¦  BFSProcessor.h
    ©¦  Homework1.vcxproj
    ©¦  Homework1.vcxproj.filters
    ©¦  Homework1.vcxproj.user
    ©¦  input.txt
    ©¦  Input1.txt
    ©¦  Input2.txt
    ©¦  Input3.txt
    ©¦  InputGenerator.cpp
    ©¦  InputGenerator.h
    ©¦  main.cpp
    ©¦  output.txt
    ©¦  README.md
    ©¦  SearchProcessor.h
    ©¦  UCSProcessor.cpp
    ©¦  UCSProcessor.h
    ©¦  Utility.cpp
    ©¦  Utility.h
    ©¦
    ©¸©¤Debug
        ©¦  ASSProcessor.obj
        ©¦  BFSProcessor.obj
        ©¦  Homework1.log
        ©¦  InputGenerator.obj
        ©¦  main.obj
        ©¦  UCSProcessor.obj
        ©¦  Utility.obj
        ©¦  vc142.idb
        ©¦  vc142.pdb
        ©¦
        ©¸©¤Homework1.tlog
                CL.command.1.tlog
                CL.read.1.tlog
                CL.write.1.tlog
                Homework1.lastbuildstate
                link.command.1.tlog
                link.read.1.tlog
                link.write.1.tlog
```