import re

with open('Contents.md','r+',encoding='UTF-8') as f:
    d = f.read()
    pattern = 'https://github.com/grandyang/LeetCode-All-In-One/issues'
    repl = 'leetcode_solutions'
    # print('src:',d)
    # failed...
    # re.sub(pattern,repl,d)
    # succeed...
    d = d.replace(pattern,repl)
    # print('changed',d)
    f.seek(0,0)
    f.truncate()
    f.write(d)
    # print(re.search(pattern,d),re.search(repl,d))
    if not re.search(pattern,d) and re.search(repl,d):
        print('succeed.')
    else:
        print('failed.')
