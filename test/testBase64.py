#!/usr/bin/python3.8

import json
import os
import shutil
import subprocess
import sys
import filecmp
from nose.tools import with_setup


# Constant definitions
testWorkspace = "testWorkspace/"
testCasesFolder = "testCases/"
jsonConfigName = "config.json"
exeSrcFolder = "../"
exeFile = "base64"


def copyFolder(src, dst):
    """Copy src folder content (incl. subdirs) to dst folder
    """

    # Create dst dir if doesn't exist
    if not os.path.exists(dst):
        os.makedirs(dst)

    # Copy each item contained within folder
    for item in os.listdir(src):
        # If item is a file, simply copy it
        if os.path.isfile(src + "/" + item):
            shutil.copyfile(src + "/" + item, dst + "/" + item)
        # if item is a subfolder, copy it calling recursively the copyFolder function
        elif os.path.isdir(src + "/" + item):
            copyFolder(src + "/" + item, dst + "/" + item)

def create_workspace():
    """Prepare test environement before test case.
    Create an empty folder in which test will be executed.
    """
    shutil.rmtree(testWorkspace, ignore_errors=True)
    os.makedirs(testWorkspace)


def remove_workspace():
    """Clean up after test execution.
    Remove folder dedicated to test execution.
    """
    shutil.rmtree(testWorkspace)
    pass



@with_setup(create_workspace, remove_workspace)
def check_base64_execution(folder, options, std_input, expectedConfig, error):
    """Test function that will be executed as many times as test cases

    Arguments are:
    - folder: folder containing everything required for test case (test description + files)
    - options: List of options to add to command line
    - std_input: Parameters defining if stdin shall be provided to tested program
    - expectedConfig: expected results (either in file or in json)
    - error: TODO
    All test cases will follow the scheme described by the test function below.
    """


    # prepare test environment
    copyFolder(testCasesFolder + folder, testWorkspace) # Copy test files
    shutil.copy(exeSrcFolder + exeFile, testWorkspace) # Copy executable

    rootDir = os.getcwd()
    os.chdir(testWorkspace)   # change current path to the folder where is located the executable

    # pre-process options before passing them to subprocess.run
    opts = []
    for opt in options:
        opts.extend(opt.split(' '))

    # Define arguments for calling executable (stdin wrapping)
    if std_input and "file" in std_input.keys():
        with open(std_input["file"], "r") as inFile:
            input_text = inFile.read()
        params = {"input": input_text}
    elif std_input and "value" in std_input.keys():
        params = {"input": std_input["value"]}
    else:
        params = {}

    # Call executable and check proper execution
    try:
        execTrace = subprocess.run(["./" + exeFile] + opts, **params, text=True, capture_output=True, check=True, timeout=1)
    except subprocess.CalledProcessError as e:
        self.assertTrue(False, "Program {} return error code {}".format(exeFile, e.returncode))

    os.chdir(rootDir)


    # Identify result file. If program is called with option -o, result file is the -o value.
    # Else, result file in stdout
    optionsO = [o for o in options if o.startswith("-o")]





    # Special case: expected is in file and application output is in file as well
    if ("file" in expectedConfig.keys()) and (optionsO):
        resultFile = testWorkspace + optionsO[0].split(" ")[-1]
        sameFiles = filecmp.cmp(resultFile, testWorkspace + expectedConfig["file"], shallow=False)
        assert sameFiles == True
    else:
        if optionsO:
            resultFile = testWorkspace + optionsO[0].split(" ")[-1]
            with open(resultFile, "r") as f:
                result = f.read()
        else:
            result = execTrace.stdout


        # Retrieve expected value
        if "file" in expectedConfig.keys():
            with open(testWorkspace + expectedConfig["file"], "r") as f:
                expected = f.read()
        elif "value" in expectedConfig.keys():
            expected = expectedConfig["value"] + "\n"

        # Check test result
        assert result == expected




def test_cases():
    """Parse all subfolders and execute test for each.

    Docstring automatically replaced at test execution
    """

    # Parse folder containing test cases
    for testCase in os.listdir(testCasesFolder):
        if os.path.isdir(testCasesFolder + testCase):


            # Load test config from json file
            with open(testCasesFolder + testCase + "/" + jsonConfigName) as jsonFile:
                config = json.load(jsonFile)

            if "error" not in config.keys():
                config["error"] = None
            if "results" not in config.keys():
                config["results"] = {}
            if "stdin" not in config.keys():
                config["stdin"] = None

            test_cases.__doc__ = """{} - {}""".format(testCase, config["purpose"])

            # # Create test case method corresponding to test and add it to unit test class
            # testFunc = make_function(testCase, config["options"], config["stdin"], config["expected"], config["error"])
            # testFunc.__doc__ = config["purpose"]    # Replace docstring from the template to a specific one issued from test context

            # Proceed to test
            yield check_base64_execution, testCase, config["options"], config["stdin"], config["expected"], config["error"]
