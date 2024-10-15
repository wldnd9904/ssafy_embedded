arr = [3,3,2,6,2]
dat = [0 for _ in range(7)]
for i in arr:
    dat[i]+=1

for i in range(7):
    print(f"{i} : {dat[i]}개")