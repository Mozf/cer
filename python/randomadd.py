import random

print('input data')
for i in range(118):
  a = random.randint(1,100)
  b = random.randint(1,100)
  for j in range(9):
    c = a*b
    d = a+b

print('conv2d_1...')
    
for i in range(118*9):
  e = random.randint(-100,100)
  if(e < 0):
    e = 0

print('activation function_1...') 

for i in range(118*9):
  f = random.randint(0,100)
  g = random.randint(1,100)
  h = random.randint(0,100)
  if(f > g):
    k = f
  else:
    k = g
  if(f > h):
    k = f
  else:
    k = h
  if(g > h):
    k = g
  else:
    k = h

print('pool_1...')
