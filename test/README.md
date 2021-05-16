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
* expected: Filename of expected results. Program's output is compared to this file to define if test is conform.

### Example 1

```
{
    "purpose": "Test of base64 encoding from file and to stdout",
    "stdin" : {
        "value": "test"
    },
    "options": [
        "-e",
        "-i in.txt"
        ],
    "expected": "expected.txt"
}
```
