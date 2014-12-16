student1 = purchases(0,0,0)
student2 = purchases(1,2,3)
student3 = purchases(1000,56,300)
student4 = purchases(1001,56,300)


if (student1 is None) or (student2 is None) or (student3 is None) or (student4 is None):
	ret = (False,"You never returned your value!")
	print "No return value"
else:
	if isinstance(student1,str) and isinstance(student2,str) and isinstance(student3,str) and isinstance(student4,str): 
		if (student1 == "I need more money!") and (student2 == "I need more money!") and (student3 == "YAY! I CAN BUY IT!") and (student4 == "YAY! I CAN BUY IT!"):
			ret = (True, "")
			print "Right"
		elif (not (student1 == "I need more money!" or student1 == "YAY! I CAN BUY IT!") and not (student2 == "I need more money!" or student2 == "YAY! I CAN BUY IT!") and not (student3 == "I need more money!" or student3 == "YAY! I CAN BUY IT!") and not (student4 == "I need more money!" or student4 == "YAY! I CAN BUY IT!")):
			ret = (False, "You have to have the exact saying!")
			print "Print the right statement"
		else:
			ret = (False, "Your answer is incorrect. One of our test cases are not passing")
			print "Your answer is incorrect. One of our test cases are not passing"
	else:
		ret = (False, "You did not return a string")
		print "Not return string"


