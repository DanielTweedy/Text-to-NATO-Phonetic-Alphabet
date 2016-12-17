# StringToNPAlpha
## Description
Program takes input text and ouputs it with the indivdual alphanumeric characters as their [NATO Phonetic Alphabet characters](https://en.wikipedia.org/wiki/NATO_phonetic_alphabet) followed by a period.
## Usage
### Input
`cat example.txt`
```
This is a message to all people,
"Hello".
That is all.
```
### Outputs
`./stringToNPAlpha < example.txt`
```
tango.hotel.india.sierra. india.sierra. alpha. mike.echo.sierra.sierra.alpha.golf.echo. papa.echo.oscar.papa.lima.echo.,
"hotel.echo.lima.lima.oscar.".
tango.hotel.alpha.tango. india.sierra. alpha.lima.lima..
```
## Required Software and non-standard Libraries
- Git
- GCC
- Make
- GNU C Library

## How to Build
1. Pull the project from GitHub
```git clone 'https://github.com/MelBrooksKA/Text-to-NATO-Phonetic-Alphabet'```
2. Compile the code with `gcc` or `make`
```
gcc -Wall -c StringToNPAlpha.c
gcc -Wall StringToNPAlpha.o -o StringToNPAlpha
```
or
```
make StringToNPAlpha
```

