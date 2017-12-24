import math
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


def ansFormat(A, mkstr = False):
    m = len(A)
    n = len(A[0])

    str_list = []

    str_list.append(m)
    str_list.append(n)

    for i in range(m):
        for j in range(n):
            str_list.append(float(truncate(A[i][j],1)))
            #str_list.append(A[i][j])

    if mkstr == True:
        return (" ".join(str(i) for i in str_list)+"\n")
    return str_list

