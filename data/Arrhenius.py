#! /usr/bin/env python3

import math

class Arrhenius:
    def __init__(self, A_i, alpha_i, T_i):
        self.A_i = A_i
        self.alpha_i = alpha_i
        self.T_i = T_i

    def calc(self, T_e):
        # unit: m^3 s^-1
        return self.A_i*math.pow(T_e, self.alpha_i)*math.exp(-self.T_i/T_e)

if __name__ == '__main__':
    arr = Arrhenius(1.23e-19, 1.511, 141480)

    T_e_min = 10000 # K
    T_e_max = 100000 # K
    dT = 1000
    T = T_e_min

    file_name = 'rate_constants.xml'

    with open(file_name, "w+") as file:
        file.write("<rate_constants>\n")

        while T <= T_e_max:
            r = arr.calc(T)

            file.write("<pair  temperature=\"" + str(T) + "\" rate_constant=\"" + str(r) + "\"/>\n")

            T += dT

        file.write("</rate_constants>\n")
