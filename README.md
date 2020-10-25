# HuffmanCode
A simple implementation of HuffmanCode

## How to build
```
git clone https://github.com/bogdasar1985/HuffmanCode.git

cd HuffmanCode/src

mkdir build

cd build

cmake ..

make -j4
```

## How to use
```
./coder <decompressed-file> <compressed-file>

./decoder <compressed-file> <decompressed-file>
```

## Example
```
./coder sample.txt out.txt

./decoder out.txt res.txt

diff sample.txt res.txt   # Should be same
```
