


with open("deck.macro.hpp", "r") as ins:
    array = []
    for line in ins:
        array.append(line)

with open("Deque.hpp", "w") as outs:
    for i in array:
        if(i[0] == '#'):
            outs.write(i)
            continue
        i = i.rstrip()
        while(len(i) < 85):
            i += " "
        i += " \\\n"
        outs.write(i)