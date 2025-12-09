#!/usr/bin/env python3
"""
Simple ISP Exit for LPC11C24
Releases control lines and exits ISP mode
"""

import serial
import time
import sys

def simple_isp_exit():
    """Exit ISP mode and release RESET/DTR lines"""
    
    try:
        # Open serial at ISP speed
        ser = serial.Serial('/dev/ttyUSB1', 115200, timeout=1)
        
        # Release ISP mode (set RTS to deassert boot mode)
        ser.setRTS(False)  # Release boot mode
        time.sleep(0.1)
        
        # Send ISP exit commands
        ser.write(b'G 0 A\r\n')    # Go to address 0, ARM mode
        time.sleep(0.1)
        
        # Release RESET (set DTR to deassert reset)
        ser.setDTR(False)  # Release reset
        time.sleep(0.1)
        
        ser.close()
        
        print("✅ Control lines released")
        return True
        
    except Exception as e:
        print(f"⚠️  ISP exit: {e}")
        return False

if __name__ == "__main__":
    if simple_isp_exit():
        print("🎉 ISP exit successful!")
    else:
        print("💥 ISP exit failed - try manual power cycle")
        sys.exit(1)