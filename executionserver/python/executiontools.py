from multiprocessing import Process
import re

#returns a context containing the modules listed in a file
def importfromfile(filename):
    context = dict()
    file = open(filename)
    lines = file.readlines()
    for line in lines:
        if line[0] is '#': #line is a comment
            continue
        words = line.split()
        if len(words) is 1:
            try:
                exec('import ' + words[0]) in context
            except ImportError as e:
                print(e)
        elif len(words) >= 2:
            for word in words[1:]:
                try:
                    exec('from ' + words[0] + ' import ' + word) in context
                except ImportError as e:
                    print(e)

    return context

#join two contexts together
def joincontexts(context1, context2):
    return dict(list(context1.items()) + list(context2.items()))

def findimports(code):
    codelines = code.split('\n')
    for lineno, line in enumerate(codelines):
        if re.match('import', line) is not None:
            return (lineno, line)
    return None

def run_in_context(code, context):
    exec code in context

def run_with_limited_time(func, args, kwargs, time):
    """Runs a function with time limit

    :param func: The function to run
    :param args: The functions args, given as tuple
    :param kwargs: The functions keywords, given as dict
    :param time: The time limit in seconds
    :return: True if the function ended successfully. False if it was terminated.
    """
    p = Process(target=func, args=args, kwargs=kwargs)
    p.start()
    p.join(time)
    if p.is_alive():
        p.terminate()
        return False

    return True