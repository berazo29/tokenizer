# Tokenizer
Simple string tokenizer


## Installation:

`Note: python 3 and cmake is required`

1. Clone the repo
```git
git clone https://github.com/berazo29/tokenizer.git
```
2. Go inside the project
```sh
cd tokenizer
```
3. Build the project with the python script
```py
python build.py
```

## Usage

Inside the folder `build` there is the executable `Tokenizer`, 
you can pass any string as argument.

*Example:*
```
./Tokenizer 123+++=+
```
*Output:*
```
Number 1
Number 2
Number 3
increment: "++"
plus equals: "+="
addition: "+"
```

<!-- LICENSE -->
## License

Distributed under the MIT License. See `LICENSE.txt` for more information.

<p align="right">(<a href="#top">back to top</a>)</p>


