import serial
import MySQLdb

DB = MySQLdb.connect(host = "localhost", user = "root", passwd = "toor", db = "STEAMRnE")
cur = DB.cursor()
ser = serial.Serial('/dev/ttyUSB0', 9600)

name = raw_input("Please input your name(with no spaces): ")
while 1:
    data = ser.readline()
    print data
    try:
        cur.execute("insert into TEST values ('"+str(name)+"', "+str(data)+")")
        DB.commit()
    except:
        DB.rollback()
    f = open("/home/rhkgkrwk0831/Desktop/data_test.txt", 'a')
    f.write(str(data)+"\n")
    f.close()
    
