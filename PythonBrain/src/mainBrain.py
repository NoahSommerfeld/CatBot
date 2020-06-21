from tkinter import *
import serial
#import syslog
import time
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
        quitButton = Button(self, text="Quit", command=self.client_exit)

        # placing the button on my window
        quitButton.place(x=0, y=0)

    def client_exit(self):
        exit()



#The following line is for serial over GPIO
port = 'COM4'


ard = serial.Serial(port,9600,timeout=5)
time.sleep(3)
i = 0


print ("Python value sent: ")
ard.write("|test+".encode())

while (i < 10):
    # Serial write section

    time.sleep(1)

    # Serial read section
    msg = ard.read(ard.inWaiting())
    print ("Message from arduino: ")
    print (msg)
    i = i + 1
else:
    print ("Exiting")

        
root = Tk()

#size of the window
root.geometry("400x300")

app = Window(root)
root.mainloop()  

exit()
