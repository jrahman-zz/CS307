student1 = sell(1)
student2 = sell(23)
student3 = sell(50)
student4 = sell(80)
student5 = sell(82)

if (student1 is None) or (student2 is None) or (student3 is None) or (student4 is None) or (student5 is None):
	ret = (False,"You never returned your value!")
else:
	if isinstance(student1,str) and isinstance(student2,str) and isinstance(student3,str) and isinstance(student4,str) and isinstance(student5,str): 
		if (student1 == "NOT SOLD") and (student2 == "SOLD") and (student3 == "SOLD") and (student4 == "SOLD") and (student5 == "NOT SOLD"):
			ret = (True, "")
		elif (not (student1 == "NOT SOLD" or student1 == "SOLD") and not (student2 == "NOT SOLD" or student2 == "SOLD") and not (student3 == "NOT SOLD" or student3 == "SOLD") and not (student4 == "NOT SOLD" or student4 == "SOLD") and not (student5 == "NOT SOLD" or student5 == "SOLD")):
			ret = (False, "")
		else:
			ret = (False, "Your conditional is incorrect")
	else:
		ret = (False, "You did not return a string")





