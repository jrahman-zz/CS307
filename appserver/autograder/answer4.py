answer1 = 10000
student1 = oddNumbers()


if (student1 is None):
	ret = (False,"You never returned your value!")
	print "no ret value"
else:
	if isinstance(student1,int): 
		if (student1 == answer1):
			ret = (True, "")
			print "correct"
		else:
			if ((student1 - answer1) >= .001):
				ret = (False,"Your answer is too high!")
				print "high"
			else:
				ret = (False,"Your answer is too low!")
				print "low"
	else:
		ret = (False,"Your answer is not a interger!")
		print "not int"

