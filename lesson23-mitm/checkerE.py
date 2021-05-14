import subprocess, sys

def dist(x1, y1, x2, y2):
    return (x1-x2)**2 + (y1-y2)**2

_, f1, f2, gen, iters = sys.argv

for i in range(int(iters)):
    print('Test', i+1)
    test = subprocess.run(["python", gen], encoding="utf-8", capture_output=True).stdout
    #print(test)
    v1 = subprocess.run(["./%s" % f1], input=test, encoding="utf-8", capture_output=True).stdout
    v2 = subprocess.run(["./%s" % f2], input=test, encoding="utf-8", capture_output=True).stdout
    t1 = list(map(int, v1.split()))
    t2 = list(map(int, v2.split()))
    if dist(t1[0], t1[1], t1[2], t1[3]) != dist(t2[0], t2[1], t2[2], t2[3]):
        print("FAIL!\nInput:")
        print(test)
        print("Correct output:")
        print(v1)
        print("Wrong output:")
        print(v2)
        sys.exit()
print("No output differences found.")
