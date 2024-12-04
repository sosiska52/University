from ElCurve import Curve

if __name__ == '__main__':
    curve = Curve(-1,1,751, (0,1))
    message = "регрессор"
    k_arr = [6,12,16,4,9,4,19,9,18]
    open_key = (425,663)
    print(curve.encrypt(message, open_key, k_arr))
    ######################################
    curve = Curve(-1, 1, 751, (-1, 1))
    cipher = [((183,93),(573,583)),
              ((188,93),(128,79)),
              ((425,663),(703,125)),
              ((489,486),(109,200)),
              ((568,355),(348,27)),
              ((377,456),(323,657)),
              ((72,254),(399,65)),
              ((16,416),(660,275)),
              ((179,275),(267,270)),
              ((568,355),(642,53))]
    print(curve.decrypt(cipher, 40))
    #####################################
    P = (62,372)
    Q = (70,195)
    R = (67,84)
    P = curve.scalar_prod_point(2,P)
    Q = curve.scalar_prod_point(3,Q)
    print(curve.subtract_points(curve.sum_points(P,Q), R))
    ###################################
    print(curve.scalar_prod_point(110, (39,171)))
    ###################################
    curve = Curve(-1, 1, 751, (416, 55))
    print(curve.DSA(12,9,3,13))
    ###################################
    curve = Curve(-1, 1, 751, (562,89))
    print(curve.verify_DSA(6,(135,669), 13, (5,7)))
