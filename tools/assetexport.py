#!/usr/bin/env python3
"""Asset exporter for Derpy2D"""

import argparse
import struct
import glob
import os.path

from PIL import Image


def bw_rgba(c):
    return (255, 255, 255, 255) if c else (0, 0, 0, 0)

def gray_rgba(c):
    return (c, ) * 3 + (255, )

def rgb_rgba(c):
    return c + (255, )

def cpy(c):
    return c

CONV_DICT = {'1': bw_rgba, 'L': gray_rgba, 'RGB': rgb_rgba, 'RGBA': cpy}

def convert_image(src, dst):
    img = Image.open(src)
    if img.mode not in CONV_DICT:
        raise RuntimeError(f'Image mode "{img.mode}" not supported')
    with open(dst, 'wb') as fhandler:
        fhandler.write(struct.pack('>II', *img.size))
        for c in img.getdata():
            fhandler.write(struct.pack('>BBBB', *CONV_DICT[img.mode](c)))


def run(src, dst):
    print(f'Exporting assets in {src} to {dst}')
    for pth in glob.glob(src + '/**', recursive=True):
        if os.path.isdir(pth):
            continue
        suffix = pth.split('.')[-1].lower()
        if suffix in ('png', 'jpg', 'jpeg', 'bmp'):
            dst_pth = os.path.join(dst, os.path.split(pth)[1][:-len(suffix)].replace(' ', '_') + 'raw')
            print(f'Converting {pth} -> {dst_pth}...', end='')
            convert_image(pth, dst_pth)
            print('Done')
    print('Finished export')


parser = argparse.ArgumentParser(description='Asset exporter for Derpy2D')
parser.add_argument('src', help='The source path, containing the assets '
                    'to be converted.')
parser.add_argument('dst', help='The destination path, where the '
                    'assets should be placed.')

args = parser.parse_args()

run(os.path.abspath(args.src), os.path.abspath(args.dst))
