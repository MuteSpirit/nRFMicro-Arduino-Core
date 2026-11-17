#!/usr/bin/env python3
# Generate SoftDevice-free (nosd) bootloader hex from the merged
# bootloader+SoftDevice hex in bootloader/<variant>/.
#
# The merged hex contains contiguous byte runs:
#   1. MBR            [0x0000 .. 0x1000)
#   2. SoftDevice     [0x1000 .. <sd end>)
#   3. Bootloader     [<bl base> .. ...)
# plus optional data blob and UICR records. The run starting at 0x1000 is
# the SoftDevice - drop it, re-emit everything else.
import glob
import os
import re
import sys

SD_START = 0x1000


def parse_hex(path):
    base = 0
    mem = {}
    for line in open(path):
        line = line.strip()
        if not line.startswith(':'):
            continue
        n = int(line[1:3], 16)
        addr = int(line[3:7], 16)
        typ = int(line[7:9], 16)
        data = bytes.fromhex(line[9:9 + 2 * n])
        if typ == 0:
            for i, b in enumerate(data):
                mem[base + addr + i] = b
        elif typ == 4:
            base = int.from_bytes(data, 'big') << 16
        elif typ == 2:
            base = int.from_bytes(data, 'big') << 16
        elif typ == 1:
            break
    return mem


def emit_hex(mem, path):
    ks = sorted(mem)
    with open(path, 'w') as f:
        i = 0
        while i < len(ks):
            chunk = []
            addr = ks[i]
            # split records at 16 bytes or when addresses are not contiguous
            while i < len(ks) and len(chunk) < 16 and (not chunk or ks[i] == addr + len(chunk)):
                chunk.append(mem[ks[i]])
                i += 1
            ext = addr >> 16
            f.write(':02000004{:04X}{:02X}\n'.format(ext, (~ext + 1) & 0xFF))
            data = bytes(chunk)
            rec = len(data).to_bytes(1, 'big') + (addr & 0xFFFF).to_bytes(2, 'big') + b'\x00' + data
            crc = (-sum(rec)) & 0xFF
            f.write(':' + rec.hex().upper() + '{:02X}\n'.format(crc))
        f.write(':00000001FF\n')


def main():
    root = os.path.join(os.path.dirname(__file__), '..', 'bootloader')
    changed = False
    for merged in sorted(glob.glob(os.path.join(root, '*', '*_s140_*.hex'))):
        out = re.sub(r'_s\d{3}_[0-9.]+\.hex$', '_nosd.hex', merged)
        if out == merged:
            print('unexpected name, skip {}'.format(os.path.basename(merged)))
            continue
        if os.path.exists(out):
            print('exists, skip {}'.format(os.path.basename(out)))
            continue

        mem = parse_hex(merged)
        ks = sorted(mem)

        # find the byte run starting at SD_START
        i0 = ks.index(SD_START)
        j = i0
        while j + 1 < len(ks) and ks[j + 1] == ks[j] + 1:
            j += 1
        sd_end = ks[j] + 1
        for a in range(SD_START, sd_end):
            del mem[a]

        emit_hex(mem, out)
        print('{}: dropped SoftDevice [0x{:X}..0x{:X}) -> {}'.format(
            os.path.basename(merged), SD_START, sd_end, os.path.basename(out)))
        changed = True

    return 0 if changed else 0


if __name__ == '__main__':
    sys.exit(main())
