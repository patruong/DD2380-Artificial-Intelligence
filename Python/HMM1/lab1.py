import math
import sys

########  FUNCTIONS  #######

# File Length
def file_len(fname):
    with open(fname) as f:
        for i, l in enumerate(f):
            pass
        return i+1

def getMat(rawDat, var):
    Mat = [rawDat[var][x+2:x+2+(rawDat[var][1])]
           for x in range(0, len(rawDat[var])-2, rawDat[var][1])]
    return Mat


def printMat(Mat):
    for i in Mat:
        for j in i:
            print(j, end = " " )
        print("\n")

# MATRIX MULTIPLICATOR
def MatCalc(A,B):
    m = len(A)
    n = len(A[0])
    p = len(B)
    q = len(B[0])
    
    c = [[0 for j in range(q)] for i in range(m)]
    if n == p:
        for i in range(m):
            for j in range(q):
                for k in range(n):
                    c[i][j] = c[i][j]+(A[i][k]*B[k][j]);
    else:
        print("Dimension error")
        return
    return c

# MATRIX TRANSPOSE
def Transpose(A):
    trans = [[A[row][col] for row in range(0,len(A)) ] for col in range(0,len(A[0]))]
    return trans

# TRUNCATE
def truncate(number, digits) -> float:
    stepper = pow(10.0, digits)
    return math.trunc(stepper * number) / stepper

file = open("sample_00.in")
#file = sys.stdin
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

#ESTIMATE OF CURRENT EMISSIONS
#print(MatCalc(pi, B))

#ESTIMATE OF CURRENT STATES
#print(MatCalc(pi, A))

CE = MatCalc(pi, A)
EPD = MatCalc(CE, B)

#TODO Define function to return i in requested format
#t1 = [[1,2,3],[4,5,6]]

def ansFormat(A, mkstr = False):
    m = len(A)
    n = len(A[0])

    str_list = []

    str_list.append(m)
    str_list.append(n)

    for i in range(m):
        for j in range(n):
            str_list.append(float(truncate(A[i][j],1)))

    if mkstr == True:
        return (" ".join(str(i) for i in str_list)+"\n")
    return str_list

#print(ansFormat(t1))
#print(" ".join(str(i) for i in ansFormat(t1)))
#print(ansFormat(t1, mkstr = True))

ans = ansFormat(EPD, mkstr=False)
print(ansFormat(EPD, mkstr= True))

"""
ans = ansFormat(EPD, mkstr=True)

f = open('file.ans', 'w')
f.write(ans)
f.close()
"""
"""
f = open('sample_00.ans')
print(f.read())
"""
