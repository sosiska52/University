class Curve:
    def __init__(self, a, b, p, gen_point):
        self.a = a
        self.b = b
        self.p = p
        self.G = gen_point
        self.alphabet = {'р': (243, 87),
                         'е': (234, 587),
                         'г': (229, 600),
                         'с': (243, 664),
                         'о': (240, 309)}

    def sum_points(self, point_A, point_B):
        if point_A is None:
            return point_B
        if point_B is None:
            return point_A

        lmb = self.lamb(point_A, point_B)
        x1, y1 = point_A
        x2, y2 = point_B
        x = (lmb ** 2 - x1 - x2) % self.p
        y = (lmb * (x1 - x) - y1) % self.p
        return (x, y)

    def lamb(self, point_A, point_B):
        x1, y1 = point_A
        x2, y2 = point_B
        if point_A == point_B:
            numerator = (3 * x1 ** 2 + self.a) % self.p
            denominator = (2 * y1) % self.p
        else:
            numerator = (y2 - y1) % self.p
            denominator = (x2 - x1) % self.p

        den_inv = pow(denominator, -1, self.p)
        return (numerator * den_inv) % self.p

    def scalar_prod_point(self, n: int, point: tuple):
        temp = point
        for i in range(n - 1):
            point = self.sum_points(point, temp)
        return point

    def subtract_points(self, point_A, point_B):
        x, y = point_B
        return self.sum_points(point_A, (x,-y))

    def encrypt(self, message, open_key, k_arr):
        cipher = []
        for ind, char in enumerate(message):
            Pm = self.alphabet.get(char, (None, None))
            kPb = self.scalar_prod_point(k_arr[ind], open_key)
            cipher.append((self.scalar_prod_point(k_arr[ind], self.G), self.sum_points(Pm, kPb)))
        return cipher

    def decrypt(self, cipher, key):
        decrypted_text = []
        for ind, cip_char in enumerate(cipher):
            kG, PmkPb = cip_char
            kG = self.scalar_prod_point(key, kG)
            decrypted_text.append(self.subtract_points(PmkPb, kG))
        return decrypted_text

    def extended_gcd(self, a, b):
        if b == 0:
            return a, 1, 0

        g, x, y = self.extended_gcd(b, a % b)
        return g, y, x - (a // b) * y

    def mod_inverse(self, a, p):
        g, x, y = self.extended_gcd(a, p)
        if g != 1:
            return None
        else:
            return x % p

    def DSA(self, e, d, k, n):
        x, y = self.scalar_prod_point(k, self.G)
        r = x % n
        s = (self.mod_inverse(k, n) * (e + d * r)) % n
        return (r, s)

    def verify_DSA(self, e, open_key, n, DSA) -> bool:
        r, s = DSA
        if r < 1 or r > n - 1:
            return False
        if s < 1 or s > n - 1:
            return False
        v = self.mod_inverse(s, n)
        u1 = (e * v) % n
        u2 = (r * v) % n
        x, y = self.sum_points(self.scalar_prod_point(u1, self.G), self.scalar_prod_point(u2, open_key))
        return r == x % n