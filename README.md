# Huffman Code
A simple implementation of Huffman Code.

## Installation
```bash
git clone https://github.com/bogdasar1985/HuffmanCode

cd HuffmanCode/src

mkdir build

cd build

cmake ..

make -j4
```

## How to use
Go to folder with executables (should be `/src`).

```bash
./coder <input-file> <output_file>

./decoder <input-file> <output-file>
```

Example:

```bash
./coder sample.txt compress.txt

./decoder compress.txt result.txt

diff sample.txt result.txt  #Should be the same
```