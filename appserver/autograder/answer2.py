def sell(price)
if(price >= 23 AND price <= 80):
	student = “SOLD”
else
	student = “NOT SOLD”

def main():
	try:
  		student
	except NameError:
  		correctness = false
  		ret = (correctness,"Store your variable in \"student\"")
	else:
		sell(23)
