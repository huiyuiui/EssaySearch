# EssaySearch

### NTHU 110 10 EECS204001 Data Structures Final Project

### Introduction

There are many search engines nowadays, like Google, Yahoo, Baidu... etc. In this final project, I built up a simple essay search engine by using Suffix Tree that can output the file name given a query word.

### Usage
```
g++ -std=c++17 -o essay-search.exe ./*.cpp -lstdc++fs
```
- Command above intruction to compile. Then a executable file named ```essay-search.exe``` should be created

```
./essay-search.exe data queray.txt output.txt
```
- ```[./executable_file_name] [data_folder_name] [query_file_name] [output_file_name]```
- Command above intruction to exectue. Then ```output_file_name``` should be created

### More detail
please refer to [Spec](./FinalProjectSpec.pdf).