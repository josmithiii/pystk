"""
Test to verify that the package uses the modern importlib.resources.files approach.
"""

import synthesistoolkit as stk
import inspect
import os

def test_importlib_resources_usage():
    """Check that the __init__.py file uses importlib.resources.files instead of the deprecated path approach."""
    # Get the path to the __init__.py file
    init_file = inspect.getfile(stk)
    
    # Read the file
    with open(init_file, 'r') as f:
        init_content = f.read()
    
    # Assert that the file doesn't use the deprecated path approach
    assert "importlib.resources.path" not in init_content, "Still using deprecated importlib.resources.path!"
    
    # Assert that the file uses the modern files approach
    assert "importlib.resources.files" in init_content, "Not using modern importlib.resources.files approach!"

def test_rawwaves_path_access():
    """Test that the rawwaves path can be accessed properly."""
    # This would fail if the files approach wasn't working properly
    import importlib.resources
    rawwave_path = importlib.resources.files('synthesistoolkit').joinpath('rawwaves')
    
    # Check that the directory exists
    assert os.path.isdir(str(rawwave_path)), "Rawwaves directory not found!"
    
    # Check that at least one file exists in the directory
    assert any(os.path.isfile(os.path.join(str(rawwave_path), f)) for f in os.listdir(str(rawwave_path))), \
           "No files found in rawwaves directory!" 