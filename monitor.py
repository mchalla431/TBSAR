#!/usr/bin/env python3
"""
TBSAR Serial Monitor - Simple UART monitoring for printf debugging

Usage:
    python3 monitor.py          # Start monitoring
    
Note: Use 'make flash' to program the MCU before monitoring
"""
import serial
import time
import sys
import os

def start_monitor():
    """Start UART monitoring with proper reset timing"""
    print("\x1b[1;37m\x1b[44m  SYSTEM MONITOR  \x1b[0m")
    print("=" * 25)
    
    try:
        # Kill any interfering processes
        os.system('sudo pkill -f ttyUSB1 2>/dev/null || true')
        time.sleep(0.5)
        
        # Open serial connection
        ser = serial.Serial(
            port='/dev/ttyUSB1',
            baudrate=57600,
            bytesize=serial.EIGHTBITS,
            parity=serial.PARITY_NONE,
            stopbits=serial.STOPBITS_ONE,
            timeout=0.1,
            xonxoff=False,
            rtscts=False,
            dsrdtr=True     # Enable DTR control
        )
        
        # Reset sequence (FlashMagic-style)
        ser.setDTR(True)   # Assert reset (hold MCU in reset)
        ser.setRTS(False)  # Clear RTS
        time.sleep(0.3)    # Hold reset
        
        # Release reset to start MCU
        ser.setDTR(False)  # Release reset
        time.sleep(0.2)    # Wait for MCU startup
        
        ser.reset_input_buffer()
        
        # Monitor loop
        try:
            while True:
                if ser.in_waiting > 0:
                    data = ser.read(ser.in_waiting)
                    try:
                        text = data.decode('utf-8', errors='ignore')
                        print(text, end='', flush=True)
                    except UnicodeDecodeError:
                        print(f"[BINARY: {data.hex()}]", flush=True)
                
                time.sleep(0.01)
                
        except KeyboardInterrupt:
            print("\n")
            return True
            
    except serial.SerialException as e:
        print(f"❌ Serial port error: {e}")
        print("💡 Make sure MCU is connected and no other programs are using the port")
        return False
        
    except Exception as e:
        print(f"❌ Monitor error: {e}")
        return False
        
    finally:
        try:
            ser.close()
        except:
            pass

def main():
    """Main entry point"""
    
    if len(sys.argv) > 1 and sys.argv[1] == "--help":
        print("Usage:")
        print("  python3 monitor.py          # Start monitoring")
        print("")
        print("Prerequisites:")
        print("  1. Flash MCU first: make flash")
        print("  2. Then run monitor to see printf output")
        return
    
    if not start_monitor():
        sys.exit(1)

if __name__ == "__main__":
    main()
