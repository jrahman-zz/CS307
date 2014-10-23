#!/bin/env python

# Run 'python setup.py build' to build the module

from distutils.core import setup, Extension

module = Extension('gamelib',
			sources=['interface.cpp'],
			define_macros = [('DEBUG', '1')],
			include_dirs = [],
			libraries = ['gamelib'],
			library_dirs = ['custom_library_path'])

setup(name='Gamelib',
	version = '0.1',
	author = 'Jason P. Rahman',
	author_email = 'rahmanj@purdue.edu',
	description = 'Python wrapper for game library',
	ext_modules = [module])
