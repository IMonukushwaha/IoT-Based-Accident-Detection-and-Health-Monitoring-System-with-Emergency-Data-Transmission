import serial
import csv
import time

ser = serial.Serial('COM8', 115200, timeout=1)

filename = "mpu6050_data_acceleration2.csv"

with open(filename, mode='w', newline='') as file:
    writer = csv.writer(file)
    writer.writerow(['timestamp', 'Ax', 'Ay', 'Az', 'Gx', 'Gy', 'Gz'])

    print("Logging MPU6050 data... Press Ctrl+C to stop.\n")

    try:
        while True:
            line = ser.readline().decode('utf-8', errors='ignore').strip()
            if line and ',' in line:
                print("LOG:", line)
                parts = line.split(',')

                if len(parts) == 6:
                    try:
                       
                        ax = float(parts[0])
                        ay = float(parts[1])
                        az = float(parts[2])
                        gx = float(parts[3])
                        gy = float(parts[4])
                        gz = float(parts[5])

                        
                        timestamp = time.strftime('%Y-%m-%d %H:%M:%S')
                        writer.writerow([timestamp, ax, ay, az, gx, gy, gz])
                        file.flush()
                    except ValueError:
                        print("Skipped invalid float conversion:", parts)
            time.sleep(0.05)  
    except KeyboardInterrupt:
        print("\n Data logging stopped. File saved as:", filename)
    finally:
        ser.close()
