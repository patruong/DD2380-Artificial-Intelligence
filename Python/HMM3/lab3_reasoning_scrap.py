from lab3_func import *

#FOR KATTIS
#import sys
#file = sys.stdin

file = open("hmm3_01.in")

#########  MAIN  ##########
# Append the raw data to list
raw_list = []
for i,l in enumerate(file):
    raw_list.append(l)

# Remove \n from end of elements and convert lines to lists
for i in range(len(raw_list)):
    raw_list[i] = raw_list[i][:-1].split()

# Converting two first elements (dimensions) to int
# and the rest to floats.
for i in range(len(raw_list)):
    for j in range(len(raw_list[i])):
        if j == 0 or j == 1:
            raw_list[i][j] = int(raw_list[i][j])
        else:
            raw_list[i][j] = float(raw_list[i][j])

A = getMat(raw_list, 0)
B = getMat(raw_list, 1)
pi = getMat(raw_list, 2)
O = [int(i) for i in getVect(raw_list, 3)]

res = EvalProb(A,B,pi,O)
print(res)

## Lesson 2 Testdata
At, Bt, Pt, Ot = Lesson2Data()


t1 = elemWise(Pt[0], transpose(getCol(Bt, Ot[0]))[0], giveMatrixForm = True)


theMat = [[0.05*0.6*0.6, 0, 0 , 0.05*0.2*0.6], [0.05*0.1*0.1, 0, 0, 0],
          [0, 0, 0, 0], [0, 0, 0, 0]]

theMat2 = [[0.05*0.6, 0, 0 , 0.05*0.2], [0.05*0.1, 0, 0, 0],
          [0.05*0.1, 0, 0, 0.05*0.1], [0.05*0.2, 0, 0, 0.05*0.7]]

#theMat2
print(elemWise(t1[0], transpose(getCol(At,0))[0]))
print(elemWise(t1[0], transpose(getCol(At,1))[0]))
print(elemWise(t1[0], transpose(getCol(At,2))[0]))
print(elemWise(t1[0], transpose(getCol(At,3))[0]))

print("")

#theMat
print([i*getCol(Bt,0)[0][0] for i in elemWise(t1[0],
                                              transpose(getCol(At,0))[0])])
print([i*getCol(Bt,0)[1][0] for i in elemWise(t1[0],
                                              transpose(getCol(At,1))[0])])
print([i*getCol(Bt,0)[2][0] for i in elemWise(t1[0],
                                              transpose(getCol(At,2))[0])])
print([i*getCol(Bt,0)[3][0] for i in elemWise(t1[0],
                                              transpose(getCol(At,3))[0])])

#theAnsw


print(max([i*getCol(Bt,0)[0][0] for i in elemWise(t1[0],
                                              transpose(getCol(At,0))[0])]))
print(max([i*getCol(Bt,0)[1][0] for i in elemWise(t1[0],
                                              transpose(getCol(At,1))[0])]))
print(max([i*getCol(Bt,0)[2][0] for i in elemWise(t1[0],
                                              transpose(getCol(At,2))[0])]))
print(max([i*getCol(Bt,0)[3][0] for i in elemWise(t1[0],
                                              transpose(getCol(At,3))[0])]))




