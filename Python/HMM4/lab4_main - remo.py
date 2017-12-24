from lab4_func import *
import math
#import cProfile

#FOR KATTIS
import sys
#file = sys.stdin

##file1 = open("hmm4_01.in")
##file2 = open("hmm4_02.in")
##file3 = open("hmm4_03.in")



#########  MAIN  ##########
# Append the raw data to list
def data(file):
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
    return raw_list

#raw_list = data(file1)

# HMM4 ----------------

# 1. Initialization:
def genDat(raw_list):
    A = getMat(raw_list, 0)
    B = getMat(raw_list, 1)
    pi = getMat(raw_list, 2)
    O = [int(i) for i in getVect(raw_list, 3)]
    return A, B, pi, O
#A,B,pi,O = genDat(raw_list)

def BaumWelch(A,B,pi,O):
    maxIters = 100
    iters = 0
    oldLogProb = -(math.inf)

    # 2. a-pass
    # compute a0[i]
    while True:
        
        c0 = 0
        a0 = [0 for i in range(len(pi[0]))]
        for i in range(len(pi[0])):
            a0[i] = pi[0][i]*B[i][O[0]]
            c0 = c0 + a0[i]
        
        # scale a0[i]
        c0 = 1/c0
        for i in range(len(pi[0])):
            a0[i] = c0*a0[i]

        # Compute a[t][i]
        a = [[0 for i in range(len(pi[0]))] for j in range(len(O))]
        a[0] = a0
        c = [0 for i in range(len(O))]
        c[0] = c0
        #print(c[0])
        for t in range(1, len(O)):
            c[t] = 0
            #a[t] = [0 for i in range(len(pi[0]))] #perhaps unneccessary step
            for i in range(len(pi[0])):
                a[t][i] = 0
                for j in range(len(pi[0])):
                    a[t][i] = a[t][i] + a[t-1][j]*A[j][i]
                a[t][i] = a[t][i] * B[i][O[t]]
                c[t] = c[t] + a[t][i]
            # scale a[t][i]
            c[t] = 1/c[t]
            for i in range(len(pi[0])):
                a[t][i] = c[t]*a[t][i]


        # 3. b-pass
        # Let b[T-1][i] = 1, scaled by c[T-1]
        b = [[0 for i in range(len(pi[0]))] for j in range(len(O))]
        for i in range(len(pi[0])):
            b[-1][i] = c[-1]

        # b-pass
        for t in reversed(range(len(O)-1)):
            for i in range(len(pi[0])):
                b[t][i] = 0
                for j in range(len(pi[0])):
                    b[t][i] = b[t][i] + A[i][j]*B[j][O[t+1]]*b[t+1][j]
                # scale b[t][i] with same scale factor as a[t][i]
                b[t][i] = c[t]*b[t][i]
        
        # 4. Compute g
        g = [[[0 for i in range(len(pi[0]))] for j in range(len(pi[0]))]
             for t in range(len(O))]
        g_sum = [[sum(j) for j in i] for i in g]
        #g[i] = sum_j{g[i][j]}

        for t in range(len(O)-1):
            denom = 0
            for i in range(len(pi[0])):
                for j in range(len(pi[0])):
                    denom = denom + a[t][i]*A[i][j]*B[j][O[t+1]]*b[t+1][j]
            for i in range(len(pi[0])):
                #g_sum[t][i] = 0?
                for j in range(len(pi[0])):
                    g[t][i][j] = (a[t][i]*A[i][j]*B[j][O[t+1]]*b[t+1][j])/denom
                    g_sum[t][i] = g_sum[t][i] + g[t][i][j]
        
        
        # Special cases for g_sum[T-1][i]
        denom = 0
        for i in range(len(pi[0])):
            denom = denom + a[-1][i]
        for i in range(len(pi[0])):
            g_sum[-1][i] = a[-1][i]/denom
        
        # 5. Re-estimate A, B, and pi

        # Re-estimate pi
        for i in range(len(pi[0])):
            pi[0][i] = g_sum[0][i]
        
        # Re-estimate A
        for i in range(len(pi[0])):
            for j in range(len(pi[0])):
                numer = 0
                denom = 0
                for t in range(len(O)-1):
                    numer = numer + g[t][i][j]
                    denom = denom + g_sum[t][i]
                A[i][j] = numer/denom
        
        # Re-estimate B
        for i in range(len(pi[0])):
            for j in range(len(getRow(B,0))):
                numer = 0
                denom = 0
                for t in range(len(O)):
                    if O[t] == j:
                        numer = numer + g_sum[t][i]
                    denom = denom + g_sum[t][i]
                B[i][j] = numer / denom

        # 6. Compute log[P(O|lambda)]
        logProb = 0
        for i in range(len(O)):
            logProb = logProb + math.log(c[i])
            ##print(c[i])
        logProb = -logProb

        # 7. To iterate or not to iterate, that is the question...
        iters = iters + 1
        if (iters < maxIters and logProb > oldLogProb):
            oldLogProb = logProb
            #continue
        else:
            L = [pi, A, B] #Buggar............
            return L

###
#file1 = open("hmm4_01.in")
def main():
    #file1 = sys.stdin
    file1 = open("hmm4_01.in")
    raw_list = data(file1)
    A,B,pi,O = genDat(raw_list)

    #printMat(A)
    #printMat(B)
    #printMat(pi)

    L = BaumWelch(A,B,pi,O)

    A = L[1]
    B = L[2]
    #pi = L[0]

    #printMat(A)
    #print("--------------")
    #printMat(B)
    #print("--------------")
    #printMat(pi)
    #print("Output 1")
    print(ansFormat(A, mkstr = True, trunc = 8))
    print(ansFormat(B, mkstr = True, trunc = 8))
    #print(ansFormat(pi, mkstr = True, trunc = 8))
    
#cProfile.run('main()')
main()

"""
###
file2 = open("hmm4_02.in")
#file2 = sys.stdin
raw_list = data(file2)
A,B,pi,O = genDat(raw_list)

L = BaumWelch(A,B,pi,O)

A = L[1]
B = L[2]

#print("Output 2")
print(ansFormat(A, mkstr = True, trunc = 6))
print(ansFormat(B, mkstr = True, trunc = 6))


###
file3 = open("hmm4_03.in")
#file3 = sys.stdin
raw_list = data(file3)
A,B,pi,O = genDat(raw_list)

L = BaumWelch(A,B,pi,O)

A = L[1]
B = L[2]

#print("Output 3")
print(ansFormat(A, mkstr = True, trunc = 6))
print(ansFormat(B, mkstr = True, trunc = 6))


"""
