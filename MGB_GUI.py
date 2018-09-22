# Undo/Redo Demo

from tkinter import *
import copy
import time
import string
import serial
ser = serial.Serial('COM11', 9600, timeout=0)

def drawFrame(canvas,data):
    canvas.create_rectangle(data.originX - (data.frameWidth/2) + data.frameSideWidth,
        data.originY + (data.frameHeight/2),
        data.originX + (data.frameWidth/2) - data.frameSideWidth, 
        data.originY + (data.frameHeight/2 ) - data.frameBottomHeight, 
        fill= "black")
    canvas.create_rectangle(data.originX - (data.frameWidth/2),
        data.originY + (data.frameHeight/2),
        data.originX - (data.frameWidth/2) + data.frameSideWidth, 
        data.originY - (data.frameHeight/2 ) + data.frameSideWidth, 
        fill= "grey")
    canvas.create_rectangle(data.originX + (data.frameWidth/2) - data.frameSideWidth,
        data.originY + (data.frameHeight/2),
        data.originX + (data.frameWidth/2), 
        data.originY - (data.frameHeight/2 ) + data.frameSideWidth, 
        fill= "grey")
    canvas.create_rectangle(data.originX - (data.frameWidth/2) + data.frameSideWidth,
        data.originY - (data.frameHeight/2) + data.frameSideWidth,
        data.originX + (data.frameWidth/2) - data.frameSideWidth, 
        data.originY - (data.frameHeight/2), 
        fill= "grey")

def drawZCarriage(canvas,data):
    canvas.create_rectangle(data.originX - data.zCarriageWidth/2,
        data.zCoord + data.zCarriageHeight/2,
        data.originX + data.zCarriageWidth/2, 
        data.zCoord - data.zCarriageHeight/2, 
        fill= "green")

def drawXCarriage(canvas,data):
    canvas.create_rectangle(data.xCoord - data.xCarriageWidth/2,
        data.zCoord + data.zCarriageHeight/2,
        data.xCoord + data.xCarriageWidth/2, 
        data.zCoord + data.zCarriageHeight/2 + data.xCarriageHeight, 
        fill= "red")

def init(data):
    data.direction = "none"
    data.originX = data.width/2
    data.originY = data.height/2
    data.frameHeight = 450
    data.frameWidth = 770
    data.frameSideWidth = 45
    data.frameBottomHeight = 55
    data.zCarriageWidth = 670
    data.zCarriageHeight = 20
    data.xCarriageWidth = 25
    data.xCarriageHeight = 30
    data.zCoord = data.height/2 - data.frameHeight/2 + data.frameSideWidth + 135 + data.zCarriageHeight/2
    data.xCoord = data.width/2 - data.zCarriageWidth/2 + 62.5 + data.xCarriageWidth/2

def mousePressed(event, data):
    pass

def keyPressed(event, data):
    if (event.keysym == "Up"):
        command = "up"
        data.zCoord -= 25
        ser.write(command.encode())
    elif (event.keysym == "Down"):
        command = "down"
        data.zCoord += 25
        ser.write(command.encode())
    elif (event.keysym == "Left"):
        command = "left"
        data.xCoord -= 125
        ser.write(command.encode())
    elif (event.keysym == "Right"):
        command = "right"
        data.xCoord += 125
        ser.write(command.encode())

    data.direction = command


def timerFired(data):
    data.direction = ""

def drawGantry(canvas, data):
    drawFrame(canvas,data)
    drawZCarriage(canvas,data)
    drawXCarriage(canvas,data)

def redrawAll(canvas, data):
    drawGantry(canvas, data)

####################################
# use the run function as-is
####################################

def run(width=900, height=600):
    def redrawAllWrapper(canvas, data):
        canvas.delete(ALL)
        canvas.create_rectangle(0, 0, data.width, data.height,
                                fill='white', width=0)
        redrawAll(canvas, data)
        canvas.update()    

    def mousePressedWrapper(event, canvas, data):
        mousePressed(event, data)
        redrawAllWrapper(canvas, data)

    def keyPressedWrapper(event, canvas, data):
        keyPressed(event, data)
        redrawAllWrapper(canvas, data)

    def timerFiredWrapper(canvas, data):
        timerFired(data)
        redrawAllWrapper(canvas, data)
        # pause, then call timerFired again
        canvas.after(data.timerDelay, timerFiredWrapper, canvas, data)
    # Set up data and call init
    class Struct(object): pass
    data = Struct()
    data.width = width
    data.height = height
    data.timerDelay = 100 # milliseconds
    root = Tk()
    root.resizable(width=False, height=False) # prevents resizing window
    init(data)
    # create the root and the canvas
    canvas = Canvas(root, width=data.width, height=data.height)
    canvas.configure(bd=0, highlightthickness=0)
    canvas.pack()
    # set up events
    root.bind("<Button-1>", lambda event:
                            mousePressedWrapper(event, canvas, data))
    root.bind("<Key>", lambda event:
                            keyPressedWrapper(event, canvas, data))
    timerFiredWrapper(canvas, data)
    # and launch the app
    root.mainloop()  # blocks until window is closed
    print("bye!")

run()