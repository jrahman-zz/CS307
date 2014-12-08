answer1 = 509.4	
answer2 = 0
answer3 = 594.3

correctness = True
try:
 	student1 = ozToGrams(18)
 	student2 = ozToGrams(0)
 	student3 = ozToGrams(21)
except NameError:
  	ret = (False,"Store your variable in \"student\"")
if correctness:
	if((answer1 == student1) && (answer2 == student2) && (answer3 == student3))
		ret = (True, "")
else:
	if((answer1 < student1) && (answer2 < student2) && (answer3 < student3))
		ret = (False,"Your answer is too high!")
	elif((answer1 > student1) && (answer2 > student2) && (answer3 > student3))
		ret = (False,"Your answer is too low!")

