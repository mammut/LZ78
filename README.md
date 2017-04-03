# LZ78 Compression Tree for big alphabets

### Compilation
To compile simply run the following command:
```bash
make
```
this will create the `LZ78-parser` which has the following options:

```bash
$ ./LZ78-parser --help
Usage: LZ78-parser [OPTION...] INPUT_FILE
LZ78 parser to DFUDS, LOUDS & Cardinal LOUDS

  -c, --clouds               Cardinal LOUDS
  -d, --dfuds                DFUDS
  -l, --louds                LOUDS
  -o, --output=salida.       Output files name: name.ascii and name.letts
  -?, --help                 Give this help list
      --usage                Give a short usage message
  -V, --version              Print program version

Mandatory or optional arguments to long options are also mandatory or optional
for any corresponding short options.

Report bugs to <juan.escalona@alumnos.inf.utfsm.cl>.
```

### Input Format
The input file must have `uint32_t` i.e. 4 Bytes or 32 bits of the encoded text. The parser will detect the size of the document based on this information as well as the alphabet.

### Output Formats

There are 3 available output formats: DFUDS, LOUDS & Cardinal LOUDS
the output file name can be set with the `-o output_file_name` option.

#### DFUDS
To output the DFUDS encoding of the tree run the following command:
```bash
./LZ78-parser -d -o output_file_name input_file
```

this will generate the following files:
- output_file_name-DFUDS.letts
- output_file_name-DFUDS.ascii

the `.letts` file has the following format:
- **64 bits** total number of nodes
- *repeat* **32 bits** alphabet element in DFUDS order

the `.ascii` file has the following format:
- *repeat* **uint8_t**: char that is ether **(** or **)**
that follows the DFUDS representation of the tree


#### LOUDS
not important for now...

#### Cardinal Louds
To output the Cardinal LOUDS of the tree the following command:
```bash
./LZ78-parser -c -o output_file_name input_file
```

this will generate the following files:
- output_file_name-CLOUDS.ascii
- output_file_name-CLOUDS.letts

the `.letts` file has the following format:
- **64 bits** total number of nodes
- **64 bits** size of the alphabet
- *repeat* **32 bits** indices of the ones in the bitvector of the CLOUDS

the `.ascii` file has the following format:
- *repeat* **uint32_t**: element of the alphabet in the order of ids in the CLOUDS tree
