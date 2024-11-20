class Curve:
    def __init__(self, a, b, p):
        self.a = a
        self.b = b
        self.p = p

    def sum_points(self, point_A, point_B):
        if point_A is None:
            return point_B
        if point_B is None:
            return point_A
        lmb = self.lamb(point_A, point_B)
        x1,y1 = point_A
        x2,y2 = point_B
        x3 = lmb**2 - x1 - x2
        y3 = lmb * (x1 - x3) - y1
        return (x3 % self.p, y3 % self.p)


    def lamb(self, point_A, point_B) -> int:
        x1, y1 = point_A
        if point_A == point_B:
            divisible = (3 * x1 * x1 + self.a)
            print(divisible % self.p)
            return (divisible / 2 * y1 * y1)%self.p
        else:
            x2 , y2 = point_B
            return ((y2-y1)/(x2-x1))%self.p