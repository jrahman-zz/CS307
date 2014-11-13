#!/bin/bash
if ! type "pip" > /dev/null; then
  wget http://bootstrap.pypa.io/get-pip.py
  python get-pip.py
  pip install flask
  pip install RestrictedPython
fi
