
import sys

if len(sys.argv) == 2:
    
    f = open(sys.argv[1], "r")
    result = None
    shape = list()
    for line in f.readlines():
        line = line.strip()

        if len(line) > 0:
            if result is None:
                result = line
            else:
                shape.append(line)
                if len(shape) == 5:

                    all = "".join(shape)
                    values = [1 if c == "#" else 0 for c in all]

                    print "{result};{rest}".format(result=result, rest=";".join([str(value) for value in values]))

                    result = None
                    shape = list()




else:
    print "Usage {script} <filename>".format(script=sys.argv[0])

