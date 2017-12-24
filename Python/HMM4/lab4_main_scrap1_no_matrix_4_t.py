from lab4_func import *
import math

#FOR KATTIS
#import sys
#file = sys.stdin

file = open("hmm4_01.in")

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

# HMM4 ----------------

# 1. Initialization:
A = getMat(raw_list, 0)
B = getMat(raw_list, 1)
pi = getMat(raw_list, 2)
O = [int(i) for i in getVect(raw_list, 3)]

maxIters = 5
iters = 0
oldProbLog = -(math.inf)

apass = EvalProb(A, B, pi, O)
bpass = Viterbi(A, B, pi, O)

# 2. compute a0
# N = len(pi[0])
c0 = 0

c0 = matCalc(pi, getCol(B, O[0]))[0][0]
a0_vect = elemWise(pi[0],transpose(getCol(B, O[0]))[0])
#print(c0)
#print(a0_vect)
# Scale the a0
a0_vect = [i*(1/c0) for i in a0_vect]
#print(a0_vect)
#--------------------

# compute a0(i)
c0 = 0
a0 = [0 for i in range(len(pi[0]))]
for i in range(len(pi[0])):
    a0[i] = pi[0][i]*B[i][O[0]]
    c0 = c0+a0[i]

# scale a0(i)
c0 = 1 / c0
for i in range(len(pi[0])):
    a0[i] = c0*a0[i]
    
# compute at(i)    
##for t in range(1,len(O)):
##    ct = 0
##    for i in range(len(pi[0])):
##        at = [0 for i in range(len(pi[0]))]
##        for j in range(len(pi[0])):
##            at[i] = at[i] + a0_vect[j]*A[j][i]
##        at[i] = at[i]*B[i][O[t]]
##        ct = ct + at[i]
##    #Scale at(i)
##    ct = 1/ct
##    for i in range(len(pi[0])):
##        at[i] = ct*at[i]

at = [0 for i in range(len(pi[0]))]
for t in range(1, len(O)):
    ct = 0
    at = [0 for i in range(len(pi[0]))] #1
    for i in range(len(pi[0])):
        #at[i] = 0 #2
        at_1 = a0
        for j in range(len(pi[0])):
            at[i] = at[i] + at_1[j]*A[j][i]
        #at_1 = at #

        at[i] = at[i]*B[i][O[t]]
        ct = ct + at[i]

    #scale at(i)

    ct = 1/ct
    for i in range(len(pi[0])):
        at[i] = ct*at[i]
        at_1 = at

# 3. B-pass

# Let B_T_1[i] = 1 scaled by C_T_1
B_T_1 = [0 for i in range(len(pi[0]))]
for i in range(len(pi[0])):
    B_T_1[i] = ct

# B-pass
for t in reversed(range(len(O)-1)):
    bt = [0 for i in range(len(pi[0]))]
    for i in range(len(pi[0])):
        bt_p1 = B_T_1
        for j in range(len(pi[0])):
            bt[i] = bt[i] + A[i][j]*B[j][O[t+1]]*bt_p1[j]
        # scale bt[i] with same scale factor as at[i]
        bt[i] = ct*bt[i]

### BAUM-WELCH bt here is large? should it be????

# 4. Compute gt[i][j] and gt[i]
gtij = [[0 for i in range(len(pi[0]))] for j in range(len(pi[0]))]
for t in range(len(O)-1):
    denom = 0 # error?
    print(at)
    for i in range(len(pi[0])):
        for j in range(len(pi[0])):
            denom = denom + at[i]*A[i][j]*B[j][O[t+1]]*bt_p1[j] # bt_p1??
    gt = [0 for i in range(len(pi[0]))]
    for i in range(len(pi[0])):
        for j in range(len(pi[0])):
            gtij[i][j] = (at[i]*A[i][j]*B[j][O[t+1]]*bt_p1[j])/denom
            gt[i] = gt[i] + gtij[i][j]

"""
NOTE - PERHAPS BETTER TO MAKE MATRIX FOR EACH t in at, so we can recall previous
t, now we are using same t all over - likely wrong
"""

# Special case for gT_1[i]
denom = 0
for i in range(len(pi[0])):
    denom = denom + at[i]
for i in range(len(pi[0])):
    gt[i] = at[i]/denom

        
            

        
         
    
        
        
