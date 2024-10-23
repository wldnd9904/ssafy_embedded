from sense_hat import SenseHat
from time import sleep
from collections import deque

sense = SenseHat()
red = (255,0,0)
green = (0,255,0)
blue = (0,0,255)
white = (255,255,255)
black = (0,0,0)
yellow = (255,255,0)

sense.set_pixel(0,0, red)
sense.set_pixel(0,7, green)
sense.set_pixel(7,0, blue)
sense.set_pixel(7,7, white)

board = [[1, 1, 1, 1, 1, 1, 1, 1, 1, 1],
         [1, 0, 0, 0, 0, 0, 0, 0, 0, 1],
         [1, 0, 1, 1, 1, 1, 1, 1, 0, 1],
         [1, 0, 0, 0, 0, 0, 0, 1, 0, 1],
         [1, 0, 1, 1, 1, 1, 0, 1, 0, 1],
         [1, 0, 0, 1, 0, 0, 0, 0, 0, 1],
         [1, 0, 0, 1, 0, 1, 1, 0, 1, 1],
         [1, 0, 1, 1, 0, 0, 0, 0, 0, 1],
         [1, 0, 0, 0, 0, 1, 1, 1, 0, 1],
         [1, 1, 1, 1, 1, 1, 1, 1, 1, 1]]

dy = [-1,1,0,0]
dx = [0,0,-1,1]


py = 0
px = 0

y = 1
x = 1

ey = 8
ex = 8

path = [[False for _ in range(10)] for _ in range(10)]

def dfs(current, goal, dist, maxDist):
    if dist > maxDist:
        return
    if current == goal:
        yield current
    y, x = current
    for dir in range(4):
        ny, nx = y+dy[dir], x+dx[dir]
        if board[ny][nx] == 1:
            continue
        if path[ny][nx]:
            continue
        path[ny][nx] = True
        yield from dfs((ny, nx), goal, dist+1, maxDist)
        path[ny][nx] = False



def shortestPath():
    global y, x, ey, ex
    #bfs한번 돌려서 최단거리 찾기
    visited = [[False for _ in range(10)] for _ in range(10)]
    q = deque([(y, x)])
    visited[y][x] = True
    
    found = False
    dist = 0
    qSize = len(q)
  
    while qSize > 0:
        for _ in range(qSize):
            (cy, cx) = q.popleft()
            if cy==ey and cx==ex:
                found = True
                break
            for dir in range(4):
                (ny, nx) = (cy+dy[dir], cx+dx[dir])
                if board[ny][nx] == 1:
                    continue
                if visited[ny][nx]:
                    continue
                visited[ny][nx] = True
                q.append((ny,nx))
        if found:
            break
        dist += 1
        qSize = len(q)
   

    #이제 그 최단거리 제한으로 dfs 돌리는데 yield하기
    while True:
        global path
        path = [[False for _ in range(10)] for _ in range(10)]
        cur = (y,x)
        yield from dfs(cur, (ey, ex), 0, dist)

   
   
finder = shortestPath()
next(finder)

while True:
    #화면에 띄우기
    for i in range(1,9):
        for j in range(1,9):
            if board[i][j] == 1:
                sense.set_pixel(i-1,j-1,blue)
            elif path[i][j] == True:
                sense.set_pixel(i-1, j-1, yellow)
            elif board[i][j] == 0:
                sense.set_pixel(i-1,j-1,black)
    sense.set_pixel(ey-1, ex-1, red)
    sense.set_pixel(y-1, x-1, green)
    #기울임 감지 후 xy적용
    ori = sense.get_orientation_degrees()
    pitch = ori['pitch']
    roll = ori['roll']
    #yaw = ori['yaw']
    #print(f"Degree : X:{pitch}, Y:{roll}, Z:{yaw} ")
    ddx = 0
    ddy = 0
    if pitch > 180 and pitch < 352:
        ddy = 1
    elif pitch > 8 and pitch < 180: 
        ddy = -1
    if roll > 180 and roll < 352:
        ddx = -1
    elif roll > 8 and roll < 180:
        ddx = 1

    py = y
    px = x

    if (board[y+ddy][x] == 0 or board[y][x+ddx] == 0):
        if board[y+ddy][x+ddx] == 0:
            y += ddy
            x += ddx
        elif board[y+ddy][x] == 0:
            y += ddy
        else:
            x += ddx

    if py != y or px != x:
        finder = shortestPath()
        next(finder)

    #클릭이벤트 감지
    for event in sense.stick.get_events():
        if event.action == "pressed":
            next(finder)
