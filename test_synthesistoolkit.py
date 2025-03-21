# test_synthesistoolkit.py

# # Old deprecated way:
# from importlib.resources import path
# with path('package_name', 'resource_name') as resource_path:
#     # Use resource_path

# # New way:
# from importlib.resources import files
# resource_path = files('package_name').joinpath('resource_name')
# # Use resource_path

import warnings
import synthesistoolkit as stk
import inspect
import importlib
import os

# Print the location of the synthesistoolkit package
print(f"synthesistoolkit location: {inspect.getfile(stk)}")

# Check importlib.resources
print("\nSearching for deprecated importlib.resources.path usage...")
import importlib.resources
print(f"importlib.resources.__file__: {importlib.resources.__file__}")

# Read the init file to check for importlib resources usage
init_file = inspect.getfile(stk)
with open(init_file, 'r') as f:
    init_content = f.read()
    if "importlib.resources.path" in init_content:
        print("WARNING: Still using deprecated importlib.resources.path!")
    elif "importlib.resources.files" in init_content:
        print("SUCCESS: Using modern importlib.resources.files approach!")
    else:
        print("No importlib.resources usage found in __init__.py")

# Capture warnings
with warnings.catch_warnings(record=True) as w:
    warnings.simplefilter("always")
    try:
        # Test using some STK classes directly from the main namespace
        # Check if we have expected classes
        if hasattr(stk, 'Clarinet'):
            print("Found Clarinet class")
        if hasattr(stk, 'set_sample_rate'):
            print("Found set_sample_rate function")
        
        # Try to initialize sample rate as mentioned in README
        stk.set_sample_rate(44100)
        print("Successfully set sample rate")
        
        # Try to create an instrument if available
        if hasattr(stk, 'Clarinet'):
            clarinet = stk.Clarinet()
            print("Successfully created Clarinet instance")
    except Exception as e:
        print(f"Error during STK usage: {e}")
    
    # Print all warnings
    for warning in w:
        print(f"\nWarning: {warning.message}")
        print(f"Category: {warning.category}")
        print(f"Filename: {warning.filename}")
        print(f"Line number: {warning.lineno}")
