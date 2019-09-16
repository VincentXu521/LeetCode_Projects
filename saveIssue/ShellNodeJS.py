import sys
import os

start = int(sys.argv[1])
count = 0

for i in range(start,start + 60):
    f = os.popen("node saveIssue.js " + str(i),"r")
    d = f.read()
    # attention: use strip(),cause the output string may have '\n',you cannot see it; 
    if d.strip() == 'undefined':
        count = count + 1
        print(i,':','failed.')
    else:
        print(i,':','succeed.')
    f.close()
	
print('All 60 issues done...\nFailed:',count)
