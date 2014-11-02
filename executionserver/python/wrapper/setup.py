#!/bin/env python

# Run 'python setup.py build' to build the module

from distutils.core import setup, Extension
import os.path
import sys

# https://wiki.python.org/moin/boost.python/BuildingExtensions

include_dirs = ["/usr/include/boost/", "../include"]
libraries = ['boost_python']
library_dirs = [' /usr/lib/x86_64-linux-gnu/']

module = Extension('gamelib',
			sources=['interface.cpp'],
			define_macros = [('DEBUG', '1')],
			include_dirs = include_dirs,
			libraries = libraries,
			library_dirs = library_dirs,
			extra_compile_args=['-std=c++11'],
			extra_link_args=['libgame.a'])

setup(name='Gamelib',
	version = '0.1',
	author = 'Jason P. Rahman',
	author_email = 'rahmanj@purdue.edu',
	description = 'Python wrapper for game library',
	ext_modules = [module])
