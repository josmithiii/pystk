import os
import importlib
from ._pystk_impl import *

with importlib.resources.path('pystk', 'rawwaves') as fspath:
    set_rawwave_path(str(fspath))
