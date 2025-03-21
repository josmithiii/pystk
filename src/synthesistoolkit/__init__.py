import os
import importlib
import importlib.resources
from ._pystk_impl import *

# Replace deprecated path usage with newer files approach
rawwave_path = importlib.resources.files('synthesistoolkit').joinpath('rawwaves')
set_rawwave_path(str(rawwave_path))
