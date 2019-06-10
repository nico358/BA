import pytest
import mock as mocker
import os

@pytest.fixture(params=['nodict', 'dict'])#(scope="module")
def generate_initial_transform_parameters(request):
    test_input = {
        'name': 'John Q. Public',
        'street': '123 Main St.',
        'city': 'Anytown',
        'state': 'FL',
        'zip': 99999,
    }
    expected_output = {
        'name': 'John Q. Public',
        'street': '123 Main St.',
        'city': 'Anytown',
        'state': 'FL',
        'zip': 99999,
    }

    if request.param == 'dict':
        test_input['relastionships'] = {
            'siblings': ['Michael R. Public', 'Suzy Q. Public'],
            'parents': ['John Q. Public Sr.', 'Mary S. Public'],
        }
        expected_output['siblings'] = ['Michael R. Public', 'Suzy Q. Public']
        expected_output['parents'] = ['John Q. Public Sr.', 'Mary S. Public']

    #mocker.patch.object(os, 'system')
    #mocker.system.return_value("ls /usr")

    return test_input, expected_output