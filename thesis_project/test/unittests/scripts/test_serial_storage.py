"""TODO."""
from setpath import setpath
setpath()

import pytest
import mock
import os
from scripts.serial_storage import SerialStorage

class TestSerialStorage:
    """TODO."""

    def test_writeToTextFile(instance):
        """TODO."""
        writer = SerialStorage()
        with pytest.raises(TypeError):
            writer.writeToTextFile()
        with pytest.raises(TypeError):
            writer.writeToTextFile(0)
        writer.writeToTextFile("")

    @mock.patch('os.path.join')
    def test_appendPathToWriteIn(instance, os_path_join):
        ss = SerialStorage()
        with pytest.raises(TypeError):
            ss.appendPathToWriteIn()
        ss.appendPathToWriteIn("/testpath")
        os_path_join.assert_called_once_with('C:\\Users\\Nicolas Frick', '/testpath')

if __name__ == "__main__":
    pass
        
