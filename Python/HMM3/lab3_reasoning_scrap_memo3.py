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


t1 = elemWise(Pt[0], transpose(getCol(Bt, Ot[0]))[0], giveMatrixForm = True)[0]

#theAnsw
problist1 = [i*getCol(Bt,0)[0][0] for i in elemWise(t1,
                                              transpose(getCol(At,0))[0])]
dprob1 = max(problist1)
eprob1 = problist1.index(dprob1)

problist2 = [i*getCol(Bt,0)[1][0] for i in elemWise(t1,
                                              transpose(getCol(At,1))[0])]
dprob2 = max(problist2)
eprob2 = problist2.index(dprob2)

problist3 = [i*getCol(Bt,0)[2][0] for i in elemWise(t1,
                                              transpose(getCol(At,2))[0])]
dprob3 = max(problist3)
eprob3 = problist3.index(dprob3)

problist4 = [i*getCol(Bt,0)[3][0] for i in elemWise(t1,
                                              transpose(getCol(At,3))[0])]
dprob4 = max(problist4)
eprob4 = problist4.index(dprob4)

t2 = [dprob1, dprob2, dprob3, dprob4]
e2 = [eprob1, eprob2, eprob3, eprob4]

ddprob1 = max([i*getCol(Bt,3)[0][0] for i in elemWise(t2,
                                              transpose(getCol(At,0))[0])])
ddprob2 = max([i*getCol(Bt,3)[1][0] for i in elemWise(t2,
                                              transpose(getCol(At,1))[0])])
ddprob3 = max([i*getCol(Bt,3)[2][0] for i in elemWise(t2,
                                              transpose(getCol(At,2))[0])])
ddprob4 = max([i*getCol(Bt,3)[3][0] for i in elemWise(t2,
                                              transpose(getCol(At,3))[0])])
t3 = [ddprob1, ddprob2, ddprob3, ddprob4]


#-------------------------------

for k in range(len(Ot)): #Use len(Ot)
    if k == 0:
        tk = elemWise(Pt[0], transpose(getCol(Bt, Ot[k]))[0], giveMatrixForm = True)[0]
    else:
        problist1 = [i*getCol(Bt,Ot[k])[0][0] for i in elemWise(tk,
                                        transpose(getCol(At,0))[0])]
        dprob1 = max(problist1)
        eprob1 = problist1.index(dprob1)
        
        problist2 = [i*getCol(Bt,Ot[k])[1][0] for i in elemWise(tk,
                                        transpose(getCol(At,1))[0])]
        dprob2 = max(problist2)
        eprob2 = problist2.index(dprob2)
        
        problist3 = [i*getCol(Bt,Ot[k])[2][0] for i in elemWise(tk,
                                        transpose(getCol(At,2))[0])]
        dprob3 = max(problist3)
        eprob3 = problist3.index(dprob3)
        
        problist4 = [i*getCol(Bt,Ot[k])[3][0] for i in elemWise(tk,
                                        transpose(getCol(At,3))[0])]
        dprob4 = max(problist4)
        eprob4 = problist4.index(dprob4)
        tk = [dprob1, dprob2, dprob3, dprob4]
    #print(tk)

#ToDo - find max, which element is it in the lists?

for k in range(len(Ot)): #Use len(Ot)
    if k == 0:
        tk = elemWise(Pt[0], transpose(getCol(Bt, Ot[k]))[0], giveMatrixForm = True)[0]
    else:
        problist = [[i*getCol(Bt,Ot[k])[j][0] for i in elemWise(tk,
                transpose(getCol(At,j))[0])] for j in range(len(At[0]))]
        
        d_list = [max(i) for i in problist]
        elemOfMax_list = [problist[j].index(d_list[j]) for j in range(len(At[0]))]
        tk = d_list
        print(d_list)
        print(elemOfMax_list)
        """
        problist1 = [i*getCol(Bt,Ot[k])[0][0] for i in elemWise(tk,
                                        transpose(getCol(At,0))[0])]
        dprob1 = max(problist1)
        eprob1 = problist1.index(dprob1)
        
        problist2 = [i*getCol(Bt,Ot[k])[1][0] for i in elemWise(tk,
                                        transpose(getCol(At,1))[0])]
        dprob2 = max(problist2)
        eprob2 = problist2.index(dprob2)
        
        problist3 = [i*getCol(Bt,Ot[k])[2][0] for i in elemWise(tk,
                                        transpose(getCol(At,2))[0])]
        dprob3 = max(problist3)
        eprob3 = problist3.index(dprob3)
        
        problist4 = [i*getCol(Bt,Ot[k])[3][0] for i in elemWise(tk,
                                        transpose(getCol(At,3))[0])]
        dprob4 = max(problist4)
        eprob4 = problist4.index(dprob4)
        tk = [dprob1, dprob2, dprob3, dprob4]"""
    #print(tk)


