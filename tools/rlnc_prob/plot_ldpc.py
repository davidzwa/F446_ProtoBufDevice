#! /usr/bin/env python3
# -*- coding: utf-8 -*-
# =====================================================
# Imports
# =====================================================
import os
import sys
import logging
import socket
import binascii
import math
from datetime import datetime
from time import sleep
# =====================================================
# Global variables
# =====================================================
logger = logging.getLogger('__name__')
test_matlab = False
test_interop = True
fec_algo_version = 1
if test_interop:
    input_file = 'source_rlnc_600f_10b_fake_30g_60r_293934007rng.bin'
    fragment_size = 40
    redundancy = 25
else:
    input_file = 'LoRaWAN_End_Node.sfb'
    fragment_size = 120
    redundancy = 72
# =====================================================
# =====================================================


def prbs23(start):
    '''The prbs23() function implements a PRBS generator with 2^23 period.
    standard implementation of a 23bit prbs generator'''
    x = start
    b0 = x & 1
    b1 = int((x & 32) / 32)
    x = (x >> 1) | ((b0 ^ b1) << 22)
    return x
# =====================================================
# =====================================================


def matrix_line(N, M):
    '''the matrix_line function generating a parity check vector:
    this function returns line N of the MxM parity matrix'''
    nb_coeff = 0
    line = [0]*M
    # if M is a power of 2
    if (M & (M - 1) == 0) and M != 0:
        pow2 = 1
    else:
        pow2 = 0
    # initialize the seed differently for each line
    x = 1 + (1001 * (N + 1))
    # will generate a line with M / 2 bits set to 1 (50 % )
    while (((fec_algo_version == 2) and (line.count(1) < math.floor(M / 2))) or
           ((fec_algo_version == 1) and (nb_coeff < math.floor(M / 2)))):
        r = math.pow(2, 16)
        # this can happen if m=1, in that case just try again with a different random number
        while r >= M:
            x = prbs23(x)
            # bit number r of the current line will be switched to 1
            r = x % (M + pow2)

        # set to 1 the column which was randomly selected
        line[r] = 1
        nb_coeff += 1
    return line


# =====================================================
# =====================================================
if __name__ == '__main__':
    logging.basicConfig(format='%(asctime)s - [%(levelname)s] - %(message)s',
                        level=logging.DEBUG)
    output_file = os.path.splitext(
        input_file)[0] + '_coded' + os.path.splitext(input_file)[1]

    uncoded_frag = []
    # nb of bytes per fragment
    if test_matlab:
        fragment_size = 10
        nb_fragment = 32
        for i in range(nb_fragment):
            buffer = ''
            for j in range(fragment_size):
                buffer += '{:02X}'.format((i*fragment_size+j) % 256)
            logger.debug(buffer)
            uncoded_frag.append(buffer)

    else:
        # Read the binary file and convert into fragments list of size <fragment_size>
        try:
            with open(input_file, "rb") as f:
                while bytes_str := f.read(fragment_size):
                    uncoded_frag.extend([binascii.hexlify(bytes_str).decode()])
        except FileNotFoundError as e:
            logger.error(e)
            exit(1)

        # Get the number of fragments into the binary file
        nb_fragment = len(uncoded_frag)

        # 0-Padding of the last fragments
        uncoded_frag[-1] += '0'*(fragment_size*2-len(uncoded_frag[-1]))

        logger.info(('Input file: {} | Fragment size: {} bytes | Uncoded fragments: {} | '
                    'Redundancy fragments: {}').format(input_file, fragment_size,
                                                       nb_fragment, redundancy))

    # generate a coded array based on uncoded content
    coded_frag = []
    logger.debug('Matrix:')
    for y in range(nb_fragment):
        s = '0'*(2 * fragment_size)
        # line y of M x M matrix
        A = matrix_line(y, nb_fragment)
        logger.debug('{:03}: {} - {:03}'.format(y + 1, A, A.count(1)))

        for x in range(nb_fragment):
            # if bit x is set to 1 then xor the corresponding fragment
            if A[x] == 1:
                s = '{:X}'.format(int(s, 16) ^ int(uncoded_frag[x], 16))
        # prevent Odd-length string
        s = '0'*((fragment_size * 2) - len(s)) + s
        # save coded fragment
        coded_frag.extend([s])

    # write the ouput file containing uncoded + coded fragments
    with open(output_file, "wb") as f:
        logger.debug('Uncoded fragments:')
        for num, frag in enumerate(uncoded_frag, start=1):
            logger.debug('{:03}: {}'.format(num, frag.upper()))
            f.write(binascii.unhexlify(frag.encode()))
        logger.debug('Coded fragments:')
        for num, frag in enumerate(coded_frag, start=1):
            logger.debug('{:03}: {}'.format(num, frag.upper()))
            f.write(binascii.unhexlify(frag.encode()))

    logger.info('Output file: {} | File size: {}'.format(
        output_file, os.path.getsize(output_file)))
