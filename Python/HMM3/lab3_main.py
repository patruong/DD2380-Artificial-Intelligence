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

## Lesson 2 Testdata
At, Bt, Pt, Ot = Lesson2Data()


#ToDo - find max, which element is it in the lists?
def Viterbi(At, Bt, Pt, Ot):
    sequence = []
    maxStates = []
    for k in range(len(Ot)): #Use len(Ot)
        if k == 0:
            tk = elemWise(Pt[0], transpose(getCol(Bt, Ot[k]))[0], giveMatrixForm = True)[0]
        else:
            problist = [[i*getCol(Bt,Ot[k])[j][0] for i in elemWise(tk,
                    transpose(getCol(At,j))[0])] for j in range(len(At[0]))]
            
            d_list = [max(i) for i in problist]
            elemOfMaxProb = [problist[j].index(d_list[j]) for j in range(len(At[0]))]
            tk = d_list

            maxStates.append(elemOfMaxProb)

    lastState = d_list.index(max(d_list))
    
    seq = [lastState]
    for i in reversed(range(len(maxStates))):

        seq.append(maxStates[i][lastState])
        lastState = maxStates[i][lastState]
    #print(d_list)
    return list(reversed(seq))

seq = Viterbi(A,B,pi,O)
seqans = " ".join(str(i) for i in seq)

print(seqans)
