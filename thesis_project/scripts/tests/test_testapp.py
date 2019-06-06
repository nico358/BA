import pytest

import os, sys
currDir = os.path.dirname(os.path.realpath(__file__))
print(os.path.realpath(__file__))
rootDir = os.path.abspath(os.path.join(currDir, '..'))
print(os.path.join(currDir, '..'))
if rootDir not in sys.path: # add parent dir to paths
    sys.path.append(rootDir)
print(sys.path)

import testapp as app

def test_initial_transform(generate_initial_transform_parameters):
    test_input = generate_initial_transform_parameters[0]
    expected_output = generate_initial_transform_parameters[1]
    assert app.initial_transform(test_input) == expected_output
