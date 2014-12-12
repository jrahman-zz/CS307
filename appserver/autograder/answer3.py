answer = 2550
student1 = evenNumber()

if (student1 is None):
    ret = (False,"You never returned your value!")
else:
    if isinstance(student1,int):
        if (student1 == answer):
            ret = (True, "")
                else:
                    if ((student1 - answer) >= .001):
                        ret = (False,"Your answer is too high!")
                        else:
                            ret = (False,"Your answer is too low!")
        else:
            ret = (False,"Your answer is not a interger!")