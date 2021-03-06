import serial
import time

def verify_checksum(received_string):
    result_list = received_string.split(",")
    checksum_value = int(result_list[-1].strip())
    total = 0
    return_string = ""
    for values in result_list[0:len(result_list)-1]:
        total = total + int(values)
        return_string = return_string + values + ","
    return_string = return_string[0:len(return_string)-1] + "\n"
    return total == checksum_value, return_string

def main():
    ser = serial.Serial('/dev/ttyAMA0', 57600, timeout=2.0)
    handshake_flag = 1
    read_sensor_flag = 0

    try: 
        print("Initialising handshake sequence")
        while handshake_flag:
            ser.write("1".encode(encoding='utf_8'))
            response = ser.readline() # this is blocking
            if response.rstrip() == "2":
                print("Received ACK2, sending confirmation ACK3")
                ser.write("3".encode(encoding='utf_8'))
                handshake_flag = 0
                read_sensor_flag = 1

        # use sys clock to get time frame
        timestr = time.strftime("%Y%m%d%H%M%S")
        filename = "datarec_" + timestr + ".csv"
        data_file = open(filename, "a")
        data_file.write("ax0,ay0,az0,gx0,gy0,gz0,ax1,ay1,az1,gx1,gy1,gz1\n")
        while read_sensor_flag:
            received_string = ser.readline()
            is_verified, processed_string = verify_checksum(received_string)
            print(is_verified)
            if (is_verified):
                if (len(processed_string)>10):
                    data_file.write(processed_string)
                    print(processed_string)
                    ser.write("A".encode(encoding='utf_8'))


    except KeyboardInterrupt:
        print("\nClosing port /dev/ttyAMA0")
        ser.write("4".encode(encoding='utf_8'))
        time.sleep(2)
        data_file.close()
        ser.close()

main()