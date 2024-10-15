a = dict()
a["KFC"] = 10
a["MC"] = 20
a["MOMS"] = 30

key = input()

if(key in a):
    print(a[key])
else:
    print(1000)