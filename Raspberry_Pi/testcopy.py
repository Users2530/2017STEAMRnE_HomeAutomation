import serial
#import MySQLdb

#DB = MySQLdb.connect(host = "localhost", user = "root", passwd = "toor", db = "STEAMRnE")
#cur = DB.cursor()
ser = serial.Serial('/dev/ttyACM0', 9600)

while 1:
    data = ser.readline()
    print data
