# BREAKING-Merkle-Hellman-Crytosystem-BAD-Ass-i
Breaking Merkl-Hellmann cryptosystem - polynomial time C implementation based on [this](https://ieeexplore.ieee.org/document/4568386/)

Requirements
```
CFLAGS = -ansi -Wall -pedantic

COMPILER = gcc
IDIRS = -I /usr/include
LDIRS = -L /usr/lib
LDIRS = -L .

```

```
======= Test 1: Vanilla knapsack problem =====
SUM = 6; a = [ 1 2 3 4 ]
indices to include = [ 0 1 2 ]

======= Test 2: Knapsack with superincreasing series ======
SUM = 483; a = [ 1 3 6 14 27 60 150 300 ]
indices to include = [ 2 4 6 7 ]

======= Test 3: to_bin ======
dec = 88;  bin = 01011000
dec = 1000;  bin = 11101000

======= Test 4: Meckl-Hellmann encryption ======
message = XYZXYZXYZ
encryption =  3220 3487 4373 3220 3487 4373 3220 3487 4373
public key = [ 1000 961 1922 1766 493 869 1153 267 ]
private key = 9

======= Test 5: Meckl-Hellmann decrypt ======
coded message = [3220 3487 4373]
key generators: 2039, 1000
original A_si = [ 1 3 6 14 27 60 150 300 ]
original message = XYZXYZXYZ
decrypted = [ 48 49 48 49 49 48 48 48 ]

======= Test 6: Break Meckl-Hellmann encryption ======
coded message = [3220 3487 4373]
public key: [ 1000 961 1922 1766 493 869 1153 267 ]
Breaking encryption...
Message decoded: [ 48 48 48 48 49 49 49 49 48 48 48 48 49 49 49 49 48 49 48 48 49 49 49 49 ]
```
