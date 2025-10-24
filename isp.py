#!/usr/bin/env python3
"""
Simple ISP Exit for LPC11C24
Just sends ISP exit commands - clean and simple
"""

import serial
import time
import sys

def simple_isp_exit():
    """Simple ISP exit - just the commands that work"""
    
    try:
        # Open serial at ISP speed
        ser = serial.Serial('/dev/ttyUSB0', 115200, timeout=1)
        
        
        # Send the key ISP exit commands
        ser.write(b'G 0 A\r\n')    # Go to address 0, ARM mode
        time.sleep(0.5)
        
        ser.write(b'A 0\r\n')      # Execute at address 0  
        time.sleep(0.5)
        
        ser.close()
        
        return True
        
    except Exception as e:
        print(f"❌ ISP exit failed: {e}")
        return False

if __name__ == "__main__":
    if simple_isp_exit():
        print("🎉 ISP exit successful!")
    else:
        print("💥 ISP exit failed!")
        sys.exit(1)