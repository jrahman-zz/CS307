answer1 = 23328
answer2 = 0
answer3 = 27216
ret = ""

correctness = True

student1 = sqYardTosqInch(18)
student2 = sqYardTosqInch(0)
student3 = sqYardTosqInch(21)

if (student1 is None) or (student2 is None) or (student3 is None):
	ret = (False,"You never returned your value!")
else: 
	if (isinstance(student1,int)) & isinstance(student1,int) & isinstance(student1,int):
		if (abs(answer1 - student1) <= .00001 ) and (abs(answer2 - student2) <= .00001 ) and (abs(answer3 - student3) <= .00001 ):
			ret = (True,"")
		else:
			if ((student1 - answer1) >= .001) or ((student3 - answer3) >= .001):
				ret = (False,"Your answer is too high!")
			else:
				ret = (False,"Your answer is too low!")

	else:
		ret = (False,"Your answer is not a interger(No decimals)!")

