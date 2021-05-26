# Python test framework
Here is a framework designed to simply write new test cases without specific coding knowledge.

## Principle
Folder `testCases` contains all test cases. There is one subfolder per case.
Each subfolder contains all files required for test execution and one description file (`config.json`)
to describe test input and expected results.


## Creating a new test
1. Create new subfolder for the test case
1. Add all files required for test such as input file, expected results file
1. Create file `config.json` to describe test procedure

## JSON config file description
JSON file contains following fields:
* purpose: String that describes test intent
* stdin (optional): provides data to be passed to stdin if test case uses stdin (no option -i). This field has to contain one and only one of following fields:
  * value: String to pass to stdin
  * file: filename which content will be passed to stdin (file has to be present in test case folder)
* options: Array of all options to add to program call
* expected: expected result. This field has to contain one and only one of following key
  * file: expected value is stored in indicated file
  * value: expected value is directly indicated here


### Example 1
* value `string to encode` is given to program through stdin
* only one option is set: `-e`
* expected result is stored in file `expected.txt`
```
{
    "purpose": "Test of base64 encoding from stdin and to file",
    "stdin" : {
        "value": "string to encode"
        },
    "options": [
        "-e"
        ],
    "expected": {
        "file": "expected.txt"
        }
}
```

### Example 2
* stdin is not used
* 3 options are set: `-e`, `-i in.txt` and `-o out.txt`
* expected result is `c3RyaW5nIHRvIGVuY29kZQo=`
```
{
    "purpose": "Test of base64 encoding from file and to file",
    "options": [
        "-e",
        "-i in.txt",
        "-o out.txt"
        ],
    "expected": {
        "value": "c3RyaW5nIHRvIGVuY29kZQo="
        }
}
```
