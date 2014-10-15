from RestrictedPython.Guards import safe_builtins
from RestrictedPython import compile_restricted



def execute(code):
    restricted_globals = dict(__builtins__ = safe_builtins)
    game_context = dict({'y':2}) #TODO: Add game context variables here
    execution_context = dict(list(restricted_globals.items()) + list(game_context.items()))

    compiled_code = compile_restricted(code, '<string>', 'exec')
    try:
        exec(compiled_code) in execution_context
    except ValueError:
        pass
    return True