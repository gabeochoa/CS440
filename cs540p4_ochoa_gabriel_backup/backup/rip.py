f = open('Array.hpp','a')
alpha = 'ABCDEFGHIJKLMNOPQRSTUVWXYZ'

def sss(length, apple = ""):
	strs = ""
	for i in range(0, length):
		strs += apple + (alpha[i])
		if(i != length-1):
			strs += (', ')
	return strs

def create(length):
	output = ""

	output += ('template <class T,')
	output += sss(length, "size_t ")
	output += ('>\n')
	output += ('struct Array< T, ')
	output += sss(length)
	output += ('>')
	output += (' : public BaseArray<T, ')
	output += sss(length)
	output += ('>\n{};\n\n')
	return output

strings = []
for count in range(0, 26):
	strings.append(create(count))

for line in range(len(strings)):
	f.write(strings[len(strings) - line -1])
