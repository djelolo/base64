# Base64
Tool for encoding to of decoding from base64.
Can read from stdin or from file. Can produce output to stdout or directly to file.

## Build instruction
Simply run the make command.
```
make
```

Remove object files
```
make clean
```

## Usage
* Encode to base64 (from stdin, to stdout)
```
echo "string to encode" | ./base64 -e
```

* Decode from base64 (from stdin, to stdout)
```
echo "string to decode" | ./base64 -d
```

* Encode/Decode from file (to stdout)
```
./base64 -e -i <file>   # Encode
./base64 -d -i <file>   # Decode
```

* Encode/Decode to file (from stdin)
```
echo "string to encode" | ./base64 -e -o <file>   # Encode
echo "string to decode" | ./base64 -d -o <file>   # Decode
```

* Encode/Decode from file and to file
```
./base64 -e -i <input_file> -o <output_file>   # Encode
./base64 -d -i <input_file> -o <output_file>   # Decode
```

* Show help
```
./base64 -?
./base64 --help
```
