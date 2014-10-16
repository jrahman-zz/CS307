from RestrictedPython.Guards import safe_builtins
from RestrictedPython import compile_restricted
import sys
import traceback
import re


def exceptiondetails(code):
    exc_type, exc_obj, tb = sys.exc_info()
    tb_string = traceback.format_exc()
    lineno = int(re.findall("line [0-9]+", tb_string)[-1][5:]) #get the last line number mentioned in the traceback
    line = code.splitlines()[lineno-1] #get the line where we
    return exc_type, exc_obj, lineno, line


def execute(code):
    returned_errors = []
    restricted_globals = dict(__builtins__ = safe_builtins)
    game_context = dict({'y':2}) #TODO: Add game context variables here
    execution_context = dict(list(restricted_globals.items()) + list(game_context.items()))
    try:
        compiled_code = compile_restricted(code, '<string>', 'exec')
        exec compiled_code in execution_context
        print(execution_context['y'])
    except Exception as e:
        print exceptiondetails(code)

        return False
    return True