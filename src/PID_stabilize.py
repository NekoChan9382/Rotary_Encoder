import tkinter as tk
import serial

class PID_stabilize:

    def __init__(self,master,ser):
        self.master = master
        self.serial=ser
        self.gain=[0,0,0]

        self.entry_kp=tk.Entry(master)
        self.entry_ki=tk.Entry(master)
        self.entry_kd=tk.Entry(master)
        self.entry_kp.place(x=0,y=0)
        self.entry_ki.place(x=100,y=0)
        self.entry_kd.place(x=200,y=0)

        self.entry_goal=tk.Entry(master)
        self.entry_goal.place(x=0,y=60)

        self.submit_gain=tk.Button(master,text="ゲイン設定",command=self.set_gain)
        self.submit_gain.place(x=115,y=30)

        self.submit_goal=tk.Button(master,text="目標値設定",command=self.set_goal)
        self.submit_goal.place(x=100,y=90)

    def set_gain(self):
        self.gain[0]=float(self.entry_kp.get())
        self.gain[1]=float(self.entry_ki.get())
        self.gain[2]=float(self.entry_kd.get())

    def set_goal(self):
        goal=float(self.entry_goal.get())
        self.serial.write(goal)



root = tk.Tk()
root.geometry("300x200")
#ser=serial.Serial('COM3',115200,timeout=2)
ser=2
gui=PID_stabilize(root,ser)
root.mainloop()