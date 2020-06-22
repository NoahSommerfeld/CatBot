from tkinter import *
import serial
#import syslog
import time

#The following line is for serial over GPIO
port = 'COM4'
ard = serial.Serial(port,9600,timeout=5)
time.sleep(3)

class Window(Frame):
    def __init__(self, master=None):
        Frame.__init__(self, master)                 
        self.master = master
        self.init_window()

    #Creation of init_window
    def init_window(self):

        # changing the title of o ur master widget      
        self.master.title("GUI")

        # allowing the widget to take the full space of the root window
        self.pack(fill=BOTH, expand=1)

        # creating a button instance
        GoLeft = Button(self, text="GoLeft")
        GoLeft.bind("<ButtonPress>",  lambda e: setCommand(e,"GoLeft Pressed"))
        GoLeft.bind("<ButtonRelease>", lambda e: setCommand(e,"GoLeft Released"))  
        GoLeft.place(x=0, y=0)
        
        GoStraight = Button(self, text="GoStraight")
        GoStraight.bind("<ButtonPress>",  lambda e: setCommand(e,"GoStraight Pressed"))
        GoStraight.bind("<ButtonRelease>", lambda e: setCommand(e,"GoStraight Released"))  
        GoStraight.place(x=75, y=0)

        GoRight = Button(self, text="GoRight")
        GoRight.bind("<ButtonPress>",  lambda e: setCommand(e,"GoRight Pressed"))
        GoRight.bind("<ButtonRelease>", lambda e: setCommand(e,"GoRight Released"))   
        GoRight.place(x=150, y=0)

        #Backup
        BackLeft = Button(self, text="BackLeft")
        BackLeft.bind("<ButtonPress>",  lambda e: setCommand(e,"BackLeft Pressed"))
        BackLeft.bind("<ButtonRelease>", lambda e: setCommand(e,"BackLeft Released"))       
        BackLeft.place(x=0, y=25)

        BackStraight = Button(self, text="BackStraight")
        BackStraight.bind("<ButtonPress>",  lambda e: setCommand(e,"BackStraight Pressed"))
        BackStraight.bind("<ButtonRelease>", lambda e: setCommand(e,"BackStraight Released"))
        BackStraight.place(x=75, y=25)

        
        BackRight = Button(self, text="BackRight")
        BackRight.bind("<ButtonPress>",  lambda e: setCommand(e,"backRight Pressed"))
        BackRight.bind("<ButtonRelease>", lambda e: setCommand(e,"backRight Released"))
        BackRight.place(x=150, y=25)


    def client_exit(self):
        exit()

#command= lambda: setCommand("BackRight")
def on_press(self, test):
    print(test)

def on_release(self):
    print("button was released")

def setCommand(self, command):
    print(command)

    
root = Tk()

#size of the window
root.geometry("400x300")

app = Window(root)
root.mainloop()  


i = 0


print ("Python value sent: ")
ard.write("|test+".encode())

while (i < 1):
    # Serial write section

    time.sleep(1)

    # Serial read section
    msg = ard.read(ard.inWaiting())
    print ("Message from arduino: ")
    print (msg)
    i = i + 1
else:
    print ("Exiting")

exit()
