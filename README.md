![](https://img.shields.io/badge/Code-C-informational?style=flat&logo=c&logoColor=white&color=brightgreen)
![](https://img.shields.io/badge/Code-C++-informational?style=flat&logo=cplusplus&logoColor=white&color=brightgreen)

# Sort Algorithm
Sorting is a fundamental concept in computer science and is widely used in tasks such as searching and data processing. This project implements and analyzes several sorting algorithms and evaluates their performance by testing different data sizes and orders, comparing running time and number of comparisons. 

1. [Introduction](#introduction)
2. [Installation](#installation)
3. [Execution](#execution)
4. [Troubleshoot](#troubleshoot)
5. [Contribution](#contribution)

## Introduction

## Installation

### Release

You can download our execution file in Github Release and run it by using [execution](#execution)

### Manual

## Execution
```
USAGE:
    Sort.exe -a Algorithm Input_file Output_parameter
    Sort.exe -a Algorithm Input_size Input_order Output_parameter
    Sort.exe -a Algorithm Input_size Output_parameter
    Sort.exe -c Algorithm_1 Algorithm_2 Input_file
    Sort.exe -c Algorithm_1 Algorithm_2 Input_size Input_order
    
OPTION:
    -mode               -a algorithm mode, -c comparison mode
    Algorithm           selection - sort, insertion - sort,...
    Input_file          path to user - provided data, with format :
                        1 st line: integer n (number of elements)
                        2 nd line: n integers, separated by a single space
    Input_size          generated data with specified size, Integer (<= 1,000,000)
    Input_order         generated data with order : -sorted, -nsorted, -rev, -rand
    Output_parameter    -time, -comp or -both
```

> [!IMPORTANT]
> Usage is for random pedestrian only. For lecturers and testers, please recompile the program, choose either the correct version or use the version provided by student according to the previously agreed convention.

## Troubleshoot

## Contribution
Pull requests are not welcome and abandoned by our mentor. For major changes, please open an issue first to discuss what you would like to change. However we won't accept that!

Please make sure to update tests as appropriate.