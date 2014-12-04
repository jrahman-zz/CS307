from RestrictedPython.Guards import safe_builtins
from RestrictedPython import compile_restricted
import sys
import traceback
import re
from executiontools import joincontexts, run_with_limited_time, run_in_context, findimports

timeout_interval = 5 #timeout in seconds

def getexceptionmessage(exc):
    if exc == NameError:
        return '''You tried to use a variable that you haven't defined yet. Check your spelling.'''
    if exc == TypeError:
        return 'You are using the wrong type of variable here. Check if it is a string, number, or list and how you are using it.'
    if exc == ImportError:
        return 'You tried to import something which either does not exist or is not allowed.'
    if exc == KeyError:
        return 'You tried to access a dictionary entry which does not exist.'
    if exc == IndexError:
        return 'You tried to access a part of an array which was outside its bounds. Check that the array and index are what you expected them to be.'
    if exc == MemoryError:
        return 'The system has run out of memory. Check that you are not using any extremely large arrays.'
    if exc == OverflowError:
        return 'The number you are using is too large for the system to use in calculations.'
    if exc == SyntaxError:
        return 'There is a typo in your code. Check the spelling and order of the words in this line.'
    if exc == IndentationError:
        return 'This line is not indented the right amount. Check the number of leading spaces.'
    if exc == SystemError:
        return 'There was an error in our system. We are not sure the cause, but it was not your fault.'
    if exc == TabError:
        return 'You are using both tabs and spaces to indent your code. Please use only one.'
    if exc == ZeroDivisionError:
        return 'You tried to divide by zero. Check that your denominator is the value you expected it to be.'
    else:
        return 'An error occurred, but we are not sure what went wrong'

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

def gettimeouterror():
    returned_info = {}
    returned_info['exc_type'] = 'TimeoutError'
    returned_info['exc_obj'] = None
    returned_info['lineno'] = -1
    returned_info['line'] = ''
    returned_info['message'] = "Your code took too long to run. Check for loops that will never finish or calculations that are extremely large"
    return returned_info

def getimporterror(lineno, line):
    returned_info = {}
    returned_info['exc_type'] = 'ImportError'
    returned_info['exc_obj'] = None
    returned_info['lineno'] = lineno
    returned_info['line'] = line
    returned_info['message'] = "You tried to import a module, but importing is not allowed."
    return returned_info

def execute(code, context, engine):
    print("Executing code")
    returned_errors = {}
    restricted_globals = dict(__builtins__ = safe_builtins)
    execution_context = joincontexts(restricted_globals, context)

    imports = findimports(code)
    if imports is not None:
        return (execution_context, getimporterror(imports['lineno'], imports['line']))

    engine.startSubmission()
    try:

        # Compile restricted is completely broken when interacting with libgame
        #compiled_code = compile_restricted(code, '<string>', 'exec')
        compiled_code = code

        # importresults = findimports(code)
        # if importresults is not None:
        #     return (execution_context, getimporterror(importresults[0], importresults[1]))
        if not run_with_limited_time(run_in_context, (compiled_code, execution_context), {}, timeout_interval):
            return_errors = gettimeouterror()

    except Exception as e:
        returned_errors = exceptiondetails(code)

    engine.endSubmission()
    print('returning errors' + str(returned_errors))
    return (execution_context, returned_errors)
