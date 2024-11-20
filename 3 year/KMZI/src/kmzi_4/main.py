from ElCurve import Curve

if __name__ == '__main__':
    curve = Curve(-1,1,751)
    A = (0,1)
    print(curve.lamb(A,A))