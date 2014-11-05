from RestrictedPython.Guards import safe_builtins
from RestrictedPython import compile_restricted
import sys
import traceback
import re
from importtools import joincontexts

def getexceptionmessage(exc):
    if exc == NameError:
        return 'name error message here'
    if exc == TypeError:
        return 'type error message here'
    else:
        return 'no match for error type found'

def exceptiondetails(code):
    returned_info = {}
    returned_info['exc_type'], returned_info['exc_obj'], tb = sys.exc_info()
    tb_string = traceback.format_exc()
    returned_info['lineno'] = -1
    returned_info['line'] = ''
    print('exec_type: '+str(returned_info['exc_type']))

    try:
        returned_info['lineno'] = int(re.findall("line [0-9]+", tb_string)[-1][5:]) #get the last line number mentioned in the traceback
        returned_info['line'] = code.splitlines()[returned_info['lineno']-1] #get the line where we
    except Exception as e:
        print("Unable to get a line number for the error")

    returned_info['message'] = getexceptionmessage(returned_info['exc_type'])
    return returned_info

def execute(code, context):
    print("Executing code")
    returned_errors = {}
    restricted_globals = dict(__builtins__ = safe_builtins)
    game_context = context
    execution_context = joincontexts(restricted_globals, game_context)
    try:
        compiled_code = compile_restricted(code, '<string>', 'exec')
        exec compiled_code in execution_context
        print('After execution, y is: '+execution_context['y'])
    except Exception as e:
        returned_errors = exceptiondetails(code)

    print('returning errors' + str(returned_errors))
    return returned_errors