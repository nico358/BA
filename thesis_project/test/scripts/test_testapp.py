from setpath import setpath
setpath()

import pytest
import scripts.testapp as app

def test_initial_transform(generate_initial_transform_parameters):
    test_input = generate_initial_transform_parameters[0]
    expected_output = generate_initial_transform_parameters[1]
    assert app.initial_transform(test_input) == expected_output
    #assert app.assert_called_once_with('ls /usr')
