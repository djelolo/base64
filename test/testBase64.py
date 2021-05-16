#!/usr/bin/python3.8

import json
import os
import shutil
import subprocess
import sys
import unittest


# Constant definitions
testWorkspace = "testWorkspace/"
testCasesFolder = "testCases/"
jsonConfigName = "config.json"
exeSrcFolder = "../"
exeFile = "base64"
stdoutFile = "result.txt"


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



class TestBase64(unittest.TestCase):
    """Minimal class fot unittest.

    Only contains setUp and tearDown methods.
    Test cases methods will be dynamically added at runtime.
    """

    def setUp(self):
        """Prepare test environement before test case.

        Create an empty folder in which test will be executed.
        """

        shutil.rmtree(testWorkspace, ignore_errors=True)
        os.makedirs(testWorkspace)


    def tearDown(self):
        """Clean up after test execution.

        Remove folder dedicated to test execution.
        """
        #shutil.rmtree(testWorkspace)
        pass



def make_test_function(folder, options, std_input, expectedFile, error):
    """Create a test case method.

    The created method will have to be added to the unit test class.
    Arguments are:
    - folder: folder containing everything required for test case (test description + files)
    - options: List of options to add to command line
    - std_input: Parameters defining if stdin shall be provided to tested program
    - expectedFile: File containing expected result
    - error: TODO
    All test cases will follow the scheme described by the test function below.
    """

    def test(self):
        """Test base common to each test case

        Principles of the test case are:
        - Copy test files into the folder dedicated to test execution
        - Run program with desired options
        - Analyse output file to compare with expected results
        """

        returnCode = 0


        # prepare test environment
        copyFolder(testCasesFolder + folder, testWorkspace) # Copy test files
        shutil.copy(exeSrcFolder + exeFile, testWorkspace) # Copy executable

        # Execute program
        #=================
        # Standard output is redirected to a file
        rootDir = os.getcwd()
        os.chdir(testWorkspace)   # change current path to the folder where is located the executable
        with open(rootDir + "/" + testWorkspace + stdoutFile, "w") as outfile:
            opts = []
            for opt in options:
                opts.extend(opt.split(' '))

            try:
                if std_input and "file" in std_input.keys():
                    with open(std_input["file"], "r") as inFile:
                        execTrace = subprocess.run(["./" + exeFile] + opts, stdin=inFile, stdout=outfile, stderr=outfile, check=True)  # Run exe with options
                elif std_input and "value" in std_input.keys():
                    execTrace = subprocess.run(["./" + exeFile] + opts, input=std_input["value"], stdout=outfile, stderr=outfile, check=True, text=True)  # Run exe with options
                else:
                    execTrace = subprocess.run(["./" + exeFile] + opts, stdout=outfile, stderr=outfile, check=True)  # Run exe with options
            except subprocess.CalledProcessError as e:
                self.assertTrue(False, "Program {} return error code {}".format(exeFile, e.returncode))

        os.chdir(rootDir)


        # Identify result file. If program is called with option -o, result file is the -o value.
        # Else, result file if the standard output file
        optionsO = [o for o in options if o.startswith("-o")]
        if optionsO:
            resultFile = testWorkspace + optionsO[0].split(" ")[-1]
        else:
            resultFile = testWorkspace + stdoutFile

        with open(resultFile, "r") as f:
            result = f.read()


        with open(testWorkspace + expectedFile, "r") as f:
            expected = f.read()


        self.assertEqual(expected, result, "Incorrect base64 conversion")


        # # Check error returned by prog
        # #=============================
        # if error:
        #     self.assertEqual(error["code"], returnCode, "Wrong error code returned. Expected: {} - obtained: {}".format(error["code"], returnCode))
        #     if "message" in error.keys():
        #         self.assertTrue(findMessage(testWorkspace + exePath + "Erreur.log", error["message"]), "Error message not found")
        # else:
        #     self.assertEqual(0, returnCode, "Unexpected error code returned : {}".format(returnCode))
        #


    return test



if __name__ == '__main__':

    # Parse each subdir (i.e. each test case)
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



            # Create test case method corresponding to test and add it to unit test class
            testFunc = make_test_function(testCase, config["options"], config["stdin"], config["expected"], config["error"])
            testFunc.__doc__ = config["purpose"]    # Replace docstring from the template to a specific one issued from test context
            setattr(TestBase64, 'test_{0}'.format(testCase), testFunc)



    # Run unit tests
    unittest.main(verbosity=1)
