arr = ["MC","BTS","BTS","MC","BTS"]

dt = dict()
for item in arr:
    if(item in dt):
        dt[item] += 1
    else:
        dt[item] = 1

for key in dt.keys():
    print(f"{key}: {dt[key]}개")