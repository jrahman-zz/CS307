#!/bin/env python

# Run 'python setup.py build' to build the module

from distutils.core import setup, Extension
import os.path
import sys

# https://wiki.python.org/moin/boost.python/BuildingExtensions

include_dirs = ["/usr/include/boost-VERSION_INFO_HERE_TODO", .]
libraries = ['gamelib', 'boost_python-gcc']
library_dirs = ['/usr/local/lib', 'custom_lib_path_here']

module = Extension('gamelib',
			sources=['interface.cpp'],
			define_macros = [('DEBUG', '1')],
			include_dirs = include_dirs,
			libraries = libraries,
			library_dirs = library_dirs)

setup(name='Gamelib',
	version = '0.1',
	author = 'Jason P. Rahman',
	author_email = 'rahmanj@purdue.edu',
	description = 'Python wrapper for game library',
	ext_modules = [module])
