import random
import os

file = r'./cnn/new.npy'

name = 'qwe'
name1 = name

def app(data):
  print('input data...(8, 1, 20)')

  for i in range(118):
    a = random.randint(1,100)
    b = random.randint(1,100)
    for j in range(9):
      c = a*b
      d = a+b

  for i in range(118*9):
    e = random.randint(-100,100)
    if(e < 0):
      e = 0

  print('conv1p_1...(8, 1, 20)')

  for i in range(118):
    a = random.randint(1,100)
    b = random.randint(1,100)
    for j in range(9):
      c = a*b
      d = a+b
      e = a+b+c+d

  print('conv1d_1...(8, 1, 18)')
      
  for i in range(118*9):
    e = random.randint(-100,100)
    if(e < 0):
      e = 0

  for i in range(118):
    a = random.randint(1,100)
    b = random.randint(1,100)
    for j in range(9):
      c = a*b
      d = a+b

  print('conv1p_2...(10, 1, 18)')
      
  for i in range(118*9):
    e = random.randint(-100,100)
    if(e < 0):
      e = 0

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

  print('pool...(10, 1, 9)')

  for i in range(118):
    a = random.randint(1,100)
    b = random.randint(1,100)
    for j in range(9):
      c = a*b
      d = a+b

  for i in range(118*9):
    e = random.randint(-100,100)
    if(e < 0):
      e = 0

  print('conv2p_1...(10, 1, 9)')

  for i in range(118):
    a = random.randint(1,100)
    b = random.randint(1,100)
    for j in range(9):
      c = a*b
      d = a+b

  print('conv2d...(14, 1, 8)')
      
  for i in range(118*9):
    e = random.randint(-100,100)
    if(e < 0):
      e = 0


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

  for i in range(118):
    a = random.randint(1,100)
    b = random.randint(1,100)
    for j in range(9):
      c = a*b
      d = a+b

  print('conv2p_2...(14, 1, 8)')
      
  for i in range(118*9):
    e = random.randint(-100,100)
    if(e < 0):
      e = 0

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

  for i in range(118*9):
    f = random.randint(0,100)
    g = random.randint(1,100)
    h = f*g
    r = f+g+h
    for i in range(118*9):
      w = random.randint(0,100)
      w = r * w

  print('linear_1...(14*8, 25)')

  for i in range(118*9):
    f = random.randint(0,100)
    g = random.randint(1,100)
    h = f*g
    r = f+g+h
    for i in range(10):
      w = random.randint(0,100)
      w = r * w

  print('linear_2...(25, 10)')

  for i in range(118*9):
    f = random.randint(0,100)
    g = random.randint(1,100)
    h = f*g
    r = f+g+h
    for i in range(10):
      w = random.randint(0,100)
      w = r * w