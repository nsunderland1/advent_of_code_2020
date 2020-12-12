import re
import numpy as np

def parse(s):
  pattern = re.compile(r"(?P<instr>[A-Z])(?P<num>[0-9]+)")
  match = pattern.match(s)
  instr = match.group("instr")
  num = int(match.group("num"))
  return (instr, num)

input = open('input', 'r')
lines = input.readlines()
lines = filter(lambda line : line != '', lines)
instrs = list(map(lambda line : parse(line), lines))

start = np.array([[0], [0], [1]])
pos = start
way = np.array([[10], [1], [1]])

def txmat(x, y):
  return np.array([
    [1, 0, x],
    [0, 1, y],
    [0, 0, 1]
  ])

def rotmat(dir):
  return np.array([
    [0, -dir, 0],
    [dir, 0, 0],
    [0, 0, 1]
  ])

for instr in instrs:
  op, num = instr
  if op == 'F':
    delta = np.subtract(way, pos)
    mat = txmat(delta[0][0], delta[1][0])
    pos = np.dot(np.linalg.matrix_power(mat, num), pos)
    way = np.dot(np.linalg.matrix_power(mat, num), way)
    continue
  elif op == 'N':
    mat = txmat(0, 1)
  elif op == 'S':
    mat = txmat(0, -1)
  elif op == 'E':
    mat = txmat(1, 0)
  elif op == 'W':
    mat = txmat(-1, 0)
  elif op == 'L':
    to_orig = np.negative(pos)
    premat = txmat(to_orig[0][0], to_orig[1][0])
    postmat = txmat(pos[0][0], pos[1][0])
    mat = np.dot(postmat, np.dot(rotmat(1), premat))
    num = num // 90
  elif op == 'R':
    to_orig = np.negative(pos)
    premat = txmat(to_orig[0][0], to_orig[1][0])
    postmat = txmat(pos[0][0], pos[1][0])
    mat = np.dot(postmat, np.dot(rotmat(-1), premat))
    num = num // 90
  way = np.dot(np.linalg.matrix_power(mat, num), way)

print(abs(pos[0][0]) + abs(pos[1][0]))
