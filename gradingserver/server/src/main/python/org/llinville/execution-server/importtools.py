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
            exec('import ' + words[0]) in context
        elif len(words) >= 2:
            for word in words[1:]:
                exec('from ' + words[0] + ' import ' + word) in context
    return context

con = importfromfile('module_whitelist.txt')
print 'done'