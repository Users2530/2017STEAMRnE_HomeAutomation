import serial
import MySQLdb

DB = MySQLdb.connect(host = "localhost", user = "root", passwd = "toor", db = "STEAMRnE")
cur = DB.cursor()
ser = serial.Serial('/dev/ttyACM0', 115200)
time = 1;
while 1:
    data = ser.readline()
    print "insert into testnew values ('test', "+str(time)+", "+str(data)+")"
    try:
        cur.execute("insert into testnew values ('test', "+str(time)+", "+str(data)+")")
        DB.commit()
        time = time + 1
    except:
        DB.rollback()
    f = open("/home/rhkgkrwk0831/Desktop/data_test.txt", 'a')
    f.write(str(data)+"\n")
    f.close()
    
