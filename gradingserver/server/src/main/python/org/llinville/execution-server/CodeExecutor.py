from RestrictedPython.Guards import safe_builtins
from RestrictedPython import compile_restricted
import sys
import linecache


def exceptiondetails():
    exc_type, exc_obj, tb = sys.exc_info()
    f = tb.tb_frame
    lineno = tb.tb_lineno
    filename = f.f_code.co_filename
    linecache.checkcache(filename)
    line = linecache.getline(filename, lineno, f.f_globals)
    return exc_type, lineno, line.strip(), exc_obj


def execute(code):
    returned_errors = []
    restricted_globals = dict(__builtins__ = safe_builtins)
    game_context = dict({'y':2}) #TODO: Add game context variables here
    execution_context = dict(list(restricted_globals.items()) + list(game_context.items()))

    compiled_code = compile_restricted(code, '<string>', 'exec')
    try:
        exec compiled_code in execution_context
        print(execution_context['y'])
    except ImportError:
        return exceptiondetails()
    return False
print(execute("import sys"))