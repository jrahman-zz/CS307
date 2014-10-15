import re
class CodeValidator:
    whitelist = False #should imported methods be allowed by whitelist or forbidden by blacklist

    def __init__(self):
        with open("modules.txt") as f:
            modulenames = f.readlines()

    def checkimports(self, codetext):
        imported = []
        for statement in re.findall("import (\w+(,\s*)?)+")