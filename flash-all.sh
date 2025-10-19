#!/bin/bash

# TBSAR Flash Utility - All-in-One Flash Script
# Combines all flash functionality into a single comprehensive script
# Author: Auto-generated for TBSAR project
# Target: NXP LPC11C24 via CP2102 UART-USB bridge

set -e  # Exit on any error

# Configuration
TARGET_DEVICE="LPC11C24"
UART_PORT=""  # Auto-detect
DEFAULT_BAUD="115200"
CRYSTAL_FREQ="12000"
HEX_FILE="Build/tbsar.hex"
BIN_FILE="Build/tbsar.bin"
FLASH_FILE=""  # Will be set based on file type preference
FILE_TYPE=""   # "hex" or "bin"

# Colors for output
RED='\033[0;31m'
GREEN='\033[0;32m'
YELLOW='\033[1;33m'
BLUE='\033[0;34m'
CYAN='\033[0;36m'
WHITE='\033[1;37m'
NC='\033[0m' # No Color

# Function to print colored output
print_header() {
    echo -e "${CYAN}===================================================================================="
    echo -e "${WHITE}$1${NC}"
    echo -e "${CYAN}===================================================================================="
}

print_info() {
    echo -e "${BLUE}ℹ️  $1${NC}"
}

print_success() {
    echo -e "${GREEN}✅ $1${NC}"
}

print_warning() {
    echo -e "${YELLOW}⚠️  $1${NC}"
}

print_error() {
    echo -e "${RED}❌ $1${NC}"
}

# Function to check if any processes are using the UART port
check_port_usage() {
    if command -v lsof >/dev/null 2>&1; then
        local using_port=$(lsof "$UART_PORT" 2>/dev/null)
        if [ -n "$using_port" ]; then
            print_warning "Processes using $UART_PORT:"
            echo "$using_port"
            print_info "Kill these processes before flashing:"
            echo "   sudo fuser -k $UART_PORT"
            echo "   or manually kill the PIDs shown above"
        else
            print_success "No processes using $UART_PORT"
        fi
    elif command -v fuser >/dev/null 2>&1; then
        if fuser "$UART_PORT" >/dev/null 2>&1; then
            print_warning "Process(es) are using $UART_PORT"
            print_info "Kill with: sudo fuser -k $UART_PORT"
        else
            print_success "No processes using $UART_PORT"
        fi
    else
        print_info "Cannot check port usage (lsof/fuser not available)"
    fi
}

# Function to check device permissions
check_device_permissions() {
    if [ ! -r "$UART_PORT" ] || [ ! -w "$UART_PORT" ]; then
        print_warning "Permission denied accessing $UART_PORT"
        
        if [ "$EUID" -ne 0 ]; then
            print_info "Current user: $(whoami)"
            print_info "Device permissions: $(ls -la $UART_PORT | cut -d' ' -f1,3,4)"
            print_info "Add user to dialout group: sudo usermod -a -G dialout $(whoami)"
            print_info "Or run script with sudo: sudo $0"
            echo ""
            
            # Check if user is in dialout group
            if groups | grep -q dialout; then
                print_info "User is in dialout group - may need to log out/in for changes to take effect"
            else
                print_warning "User is not in dialout group"
            fi
        fi
        
        # Test actual access
        if ! timeout 1 cat "$UART_PORT" >/dev/null 2>&1; then
            if [ "$EUID" -ne 0 ]; then
                print_error "Cannot access device - try running with sudo"
                exit 1
            fi
        fi
    else
        print_success "Device permissions OK"
    fi
}

# Function to auto-detect UART device
detect_uart_device() {
    print_info "Auto-detecting UART device..."
    
    # Look for CP2102 by USB ID first
    if [ -d "/dev/serial/by-id" ]; then
        local cp2102_device=$(ls /dev/serial/by-id/ 2>/dev/null | grep -i "cp210\|silicon_labs" | head -1)
        if [ -n "$cp2102_device" ]; then
            UART_PORT="/dev/serial/by-id/$cp2102_device"
            print_success "Found CP2102 device: $UART_PORT"
            return 0
        fi
    fi
    
    # Fall back to USB/ACM device detection
    for device in /dev/ttyUSB* /dev/ttyACM*; do
        if [ -e "$device" ]; then
            UART_PORT="$device"
            print_success "Found UART device: $UART_PORT"
            return 0
        fi
    done
    
    return 1
}

# Function to check hardware connections
check_hardware() {
    print_header "🔌 HARDWARE CONNECTION CHECK"
    
    # Auto-detect device if not specified
    if [ -z "$UART_PORT" ]; then
        if ! detect_uart_device; then
            print_error "No UART device found!"
            echo -e "${WHITE}Please check:${NC}"
            echo "   1️⃣  CP2102 USB cable is connected"
            echo "   2️⃣  Board is powered on"
            echo "   3️⃣  Driver is installed (lsusb should show CP210x)"
            echo ""
            echo -e "${CYAN}Available serial ports:${NC}"
            ls -la /dev/ttyUSB* /dev/ttyACM* 2>/dev/null || echo "   No serial ports found"
            echo ""
            echo -e "${CYAN}USB devices (lsusb):${NC}"
            lsusb | grep -i "cp210\|silicon\|uart" || echo "   No CP210x devices found"
            exit 1
        fi
    else
        if [ ! -e "$UART_PORT" ]; then
            print_error "UART port $UART_PORT not found!"
            print_info "Attempting auto-detection..."
            if ! detect_uart_device; then
                exit 1
            fi
        fi
    fi
    
    print_success "UART port $UART_PORT found"
    
    # Check device permissions
    check_device_permissions
    
    # Check DTR/RTS control
    print_info "Testing DTR/RTS control signals..."
    if command -v stty >/dev/null 2>&1; then
        if stty -F $UART_PORT $DEFAULT_BAUD raw -echo 2>/dev/null; then
            print_success "DTR/RTS control available"
        else
            print_warning "DTR/RTS control may not be available (check permissions)"
        fi
    fi
    
    # Check lpc21isp availability
    if ! command -v lpc21isp >/dev/null 2>&1; then
        print_error "lpc21isp not found! Please install it:"
        echo "   Ubuntu/Debian: sudo apt install lpc21isp"
        echo "   Or download from: https://github.com/capiman/lpc21isp"
        exit 1
    fi
    
    print_success "lpc21isp programmer found"
    
    # Check for processes using the UART port
    check_port_usage
    
    echo ""
}

# Function to detect and choose flash file type
detect_flash_file() {
    print_header "📄 FLASH FILE DETECTION"
    
    local hex_exists=false
    local bin_exists=false
    local hex_size=0
    local bin_size=0
    local hex_date=""
    local bin_date=""
    
    # Check HEX file
    if [ -f "$HEX_FILE" ]; then
        hex_exists=true
        hex_size=$(stat -f%z "$HEX_FILE" 2>/dev/null || stat -c%s "$HEX_FILE" 2>/dev/null)
        hex_date=$(stat -f%Sm "$HEX_FILE" 2>/dev/null || stat -c%y "$HEX_FILE" 2>/dev/null | cut -d' ' -f1-2)
        print_info "HEX file found: $HEX_FILE (${hex_size} bytes, ${hex_date})"
    fi
    
    # Check BIN file  
    if [ -f "$BIN_FILE" ]; then
        bin_exists=true
        bin_size=$(stat -f%z "$BIN_FILE" 2>/dev/null || stat -c%s "$BIN_FILE" 2>/dev/null)
        bin_date=$(stat -f%Sm "$BIN_FILE" 2>/dev/null || stat -c%y "$BIN_FILE" 2>/dev/null | cut -d' ' -f1-2)
        print_info "BIN file found: $BIN_FILE (${bin_size} bytes, ${bin_date})"
    fi
    
    # Choose file type based on availability and preference
    if [ "$bin_exists" = true ]; then
        FLASH_FILE="$BIN_FILE"
        FILE_TYPE="bin"
        print_success "Using BIN file: $FLASH_FILE (faster, more reliable)"
    elif [ "$hex_exists" = true ]; then
        FLASH_FILE="$HEX_FILE" 
        FILE_TYPE="hex"
        print_success "Using HEX file: $FLASH_FILE"
    else
        print_error "No flash files found! Build the project first with 'make'"
        echo ""
        echo "Expected files:"
        echo "  🔹 $BIN_FILE (preferred)"
        echo "  🔹 $HEX_FILE (fallback)"
        return 1
    fi
    
    # Validate file format
    if [ "$FILE_TYPE" = "hex" ]; then
        if head -1 "$FLASH_FILE" | grep -q "^:.*[0-9A-F][0-9A-F]$"; then
            print_success "Valid Intel HEX format detected"
        else
            print_warning "HEX file format validation failed, proceeding anyway"
        fi
    elif [ "$FILE_TYPE" = "bin" ]; then
        if [ "$bin_size" -gt 100 ] && [ "$bin_size" -lt 40960 ]; then  # Reasonable size for LPC11C24
            print_success "Valid binary file size: ${bin_size} bytes"
        else
            print_warning "Binary file size seems unusual: ${bin_size} bytes"
        fi
    fi
    
    echo ""
    return 0
}

# Function to check hex file (legacy - now part of detect_flash_file)
check_hex_file() {
    print_header "📄 HEX FILE VERIFICATION"
    
    if [ ! -f "$HEX_FILE" ]; then
        print_error "HEX file not found: $HEX_FILE"
        print_info "Building project first..."
        make clean && make || {
            print_error "Build failed!"
            exit 1
        }
    fi
    
    if [ ! -f "$HEX_FILE" ]; then
        print_error "HEX file still not found after build!"
        exit 1
    fi
    
    local file_size=$(stat -f%z "$HEX_FILE" 2>/dev/null || stat -c%s "$HEX_FILE" 2>/dev/null)
    print_success "HEX file found: $HEX_FILE (${file_size} bytes)"
    
    # Show hex file info
    local line_count=$(wc -l < "$HEX_FILE")
    print_info "HEX file contains $line_count lines"
    
    # Verify hex file format
    if head -1 "$HEX_FILE" | grep -q "^:.*[0-9A-F][0-9A-F]$"; then
        print_success "HEX file format appears valid"
    else
        print_warning "HEX file format may be invalid"
    fi
    echo ""
}

# Function for automatic flash with DTR/RTS
flash_auto() {
    print_header "🚀 AUTOMATIC FLASH (DTR/RTS ISP)"
    
    print_info "Programming $TARGET_DEVICE via $UART_PORT..."
    print_info "Using automatic ISP entry (DTR/RTS control)"
    
    echo -e "${WHITE}Programming parameters:${NC}"
    echo "   📱 Target: $TARGET_DEVICE"
    echo "   🔌 Port: $UART_PORT"
    echo "   ⚡ Baud: $DEFAULT_BAUD"
    echo "   🔮 Crystal: ${CRYSTAL_FREQ} Hz"
    echo "   📄 File: $FLASH_FILE ($FILE_TYPE format)"
    echo ""
    
    print_info "Starting ISP programming..."
    
    # Build lpc21isp command with correct file type flag
    local lpc_cmd="lpc21isp -control"
    if [ "$FILE_TYPE" = "bin" ]; then
        lpc_cmd="$lpc_cmd -bin"
    fi
    lpc_cmd="$lpc_cmd \"$FLASH_FILE\" \"$UART_PORT\" \"$DEFAULT_BAUD\" \"$CRYSTAL_FREQ\""
    
    # Execute lpc21isp with verbose output
    local lpc_output=$(mktemp)
    if eval "$lpc_cmd" 2>&1 | tee "$lpc_output"; then
        print_success "Programming completed successfully!"
        
        print_header "✅ APPLICATION STARTED AUTOMATICALLY"
        echo "   🚀 Firmware automatically launched after programming"
        echo "   💡 No power cycle required - LED should be flashing now!"
        echo "   🔌 If LED is not flashing, try a manual power cycle:"
        echo "      1️⃣  Unplug USB cable → Wait 2 seconds → Plug back in"
        echo ""
        print_success "Development cycle complete!"
        rm -f "$lpc_output"
        
    else
        print_error "Programming failed!"
        echo ""
        
        # Analyze error output
        print_info "Analyzing error..."
        if grep -q "not implemented" "$lpc_output"; then
            print_warning "DTR/RTS not supported - try manual mode"
            echo "   Solution: $0 manual"
        fi
        
        if grep -q "Permission denied\|Device or resource busy" "$lpc_output"; then
            print_warning "Device access issue detected"
            echo "   Solutions:"
            echo "   • Run with sudo: sudo $0"
            echo "   • Add user to dialout: sudo usermod -a -G dialout \$(whoami)"
            echo "   • Kill competing processes: sudo fuser -k $UART_PORT"
        fi
        
        if grep -q "Synchronizing" "$lpc_output" && grep -q "timeout\|failed" "$lpc_output"; then
            print_warning "Board not in ISP mode"
            echo "   Solutions:"
            echo "   • Try manual mode: $0 manual"
            echo "   • Power cycle board and retry"
            echo "   • Check ISP/RESET button sequence"
        fi
        
        echo ""
        print_info "General troubleshooting tips:"
        echo "   • Check hardware connections"
        echo "   • Verify board is powered"
        echo "   • Try different baud rate: $0 57600"
        echo "   • Check for competing processes using $UART_PORT"
        
        rm -f "$lpc_output"
        exit 1
    fi
}

# Function for manual flash (user controls ISP)
flash_manual() {
    print_header "🔧 MANUAL FLASH (USER ISP CONTROL)"
    
    print_warning "Manual ISP mode selected"
    echo -e "${WHITE}Instructions:${NC}"
    echo "   1️⃣  Hold the ISP button on the board"
    echo "   2️⃣  Press and release the RESET button (while holding ISP)"
    echo "   3️⃣  Release the ISP button"
    echo "   4️⃣  Board should now be in ISP mode"
    echo ""
    
    echo -e "${YELLOW}Press Enter when board is in ISP mode, or Ctrl+C to cancel...${NC}"
    read -r
    
    print_info "Programming $TARGET_DEVICE via $UART_PORT..."
    
    # Build lpc21isp command with correct file type flag
    local lpc_cmd="lpc21isp"
    if [ "$FILE_TYPE" = "bin" ]; then
        lpc_cmd="$lpc_cmd -bin"
    fi
    lpc_cmd="$lpc_cmd \"$FLASH_FILE\" \"$UART_PORT\" \"$DEFAULT_BAUD\" \"$CRYSTAL_FREQ\""
    
    # Execute lpc21isp without DTR/RTS control
    if eval "$lpc_cmd"; then
        print_success "Programming completed successfully!"
        print_info "Press RESET button to start application"
    else
        print_error "Programming failed!"
        exit 1
    fi
}

# Function for alternative baud rates
flash_57600() {
    print_header "🔄 FLASH WITH 57600 BAUD"
    
    print_info "Using slower baud rate for problematic connections..."
    
    # Build lpc21isp command with correct file type flag
    local lpc_cmd="lpc21isp -control"
    if [ "$FILE_TYPE" = "bin" ]; then
        lpc_cmd="$lpc_cmd -bin"
    fi
    lpc_cmd="$lpc_cmd \"$FLASH_FILE\" \"$UART_PORT\" 57600 \"$CRYSTAL_FREQ\""
    
    if eval "$lpc_cmd"; then
        print_success "Programming completed successfully!"
        power_cycle_instructions
    else
        print_error "Programming failed at 57600 baud!"
        exit 1
    fi
}

# Function to show power cycle instructions
power_cycle_instructions() {
    print_header "✅ APPLICATION STARTED AUTOMATICALLY"
    echo "   🚀 Firmware automatically launched after programming"
    echo "   💡 No power cycle required - LED should be flashing now!"
    echo "   🔌 If LED is not flashing, try a manual power cycle:"
    echo "      1️⃣  Unplug USB cable → Wait 2 seconds → Plug back in"
    echo ""
    print_success "Development cycle complete!"
}

# Function to reset board (attempt DTR reset)
reset_board() {
    print_header "🔄 BOARD RESET ATTEMPT"
    
    print_info "Attempting reset via DTR signal..."
    
    if command -v stty >/dev/null 2>&1; then
        # Toggle DTR line
        stty -F $UART_PORT hupcl
        sleep 0.1
        stty -F $UART_PORT -hupcl
        print_info "DTR reset signal sent"
        
        print_warning "Note: Many boards require manual power cycle"
        print_info "If application doesn't start, perform manual power cycle"
    else
        print_error "stty command not available for reset"
        print_info "Please perform manual power cycle"
    fi
}

# Function to show usage
show_usage() {
    echo -e "${WHITE}TBSAR Flash Utility - Usage:${NC}"
    echo ""
    echo -e "${CYAN}$0 [COMMAND]${NC}"
    echo ""
    echo -e "${WHITE}File Format Support:${NC}"
    echo "  📄 Automatically detects BIN (preferred) or HEX files"
    echo "  🚀 BIN format: Faster, more reliable flashing"
    echo "  📝 HEX format: Standard Intel HEX fallback"
    echo ""
    echo -e "${WHITE}Commands:${NC}"
    echo "  auto           🚀 Automatic flash with DTR/RTS ISP (default)"
    echo "  manual         🔧 Manual flash (user controls ISP button)"
    echo "  57600          🔄 Flash with 57600 baud rate"
    echo "  check          🔌 Check hardware connections only"
    echo "  reset          🔄 Attempt board reset via DTR"
    echo "  build          🔨 Build project and flash automatically"
    echo "  monitor [baud] 📊 Monitor serial output (default: 57600)"
    echo "  flashmon [baud] 🚀📊 Flash then monitor (default: 57600)"
    echo "  flashterm      🚀📺 Flash with built-in terminal (for UART firmware)"
    echo "  help           ❓ Show this help message"
    echo ""
    echo -e "${WHITE}Examples:${NC}"
    echo "  $0                    # Automatic flash"
    echo "  $0 auto               # Same as above"
    echo "  $0 manual             # Manual ISP control"
    echo "  $0 check              # Check connections only"
    echo "  $0 build              # Clean build and flash"
    echo "  $0 monitor            # Monitor serial at 57600 baud"
    echo "  $0 monitor 115200     # Monitor serial at 115200 baud"
    echo "  $0 flashmon           # Flash then monitor at 57600"
    echo "  $0 flashmon 9600      # Flash then monitor at 9600"
    echo "  $0 flashterm          # Flash with terminal (for UART output)"
    echo ""
    echo -e "${WHITE}Hardware Requirements:${NC}"
    echo "  • NXP LPC11C24 board"
    echo "  • CP2102 UART-USB bridge"
    echo "  • lpc21isp programmer installed"
    echo ""
}

# Function to monitor serial output
monitor_serial() {
    local baud_rate=${1:-57600}
    local duration=${2:-10}
    
    print_header "📊 SERIAL MONITOR"
    
    check_hardware
    
    print_info "Monitoring $UART_PORT at $baud_rate baud for $duration seconds"
    print_info "Press Ctrl+C to stop monitoring early"
    echo ""
    
    # Configure serial port
    if ! stty -F "$UART_PORT" $baud_rate cs8 -cstopb -parenb raw -echo 2>/dev/null; then
        print_error "Failed to configure serial port"
        exit 1
    fi
    
    print_success "Serial port configured - starting capture..."
    echo -e "${YELLOW}--- Serial Output Start ---${NC}"
    
    # Monitor with timeout
    timeout $duration cat "$UART_PORT" || {
        local exit_code=$?
        echo ""
        if [ $exit_code -eq 124 ]; then
            print_info "Monitoring timeout reached ($duration seconds)"
        else
            print_warning "Monitoring stopped (Ctrl+C or error)"
        fi
    }
    
    echo -e "${YELLOW}--- Serial Output End ---${NC}"
    echo ""
}

# Function to flash and monitor
flash_and_monitor() {
    local baud_rate=${1:-57600}
    
    print_header "🚀📊 FLASH AND MONITOR"
    
    # Flash first
    check_hardware
    detect_flash_file || exit 1
    flash_auto
    
    echo ""
    print_info "Waiting 3 seconds for board to restart..."
    sleep 3
    
    # Then monitor
    monitor_serial $baud_rate 15
}

# Function to flash with built-in terminal (for firmware with UART output)
flash_with_terminal() {
    print_header "🚀📺 FLASH WITH TERMINAL"
    
    check_hardware
    detect_flash_file || exit 1
    
    print_info "Programming with built-in terminal monitoring..."
    print_info "Press ESC to exit terminal mode after flashing"
    echo ""
    
    # Build lpc21isp command with correct file type flag
    local lpc_cmd="lpc21isp -control -term"
    if [ "$FILE_TYPE" = "bin" ]; then
        lpc_cmd="$lpc_cmd -bin"
    fi
    lpc_cmd="$lpc_cmd \"$FLASH_FILE\" \"$UART_PORT\" \"$DEFAULT_BAUD\" \"$CRYSTAL_FREQ\""
    
    # Flash with terminal mode enabled
    if eval "$lpc_cmd"; then
        print_success "Programming completed!"
    else
        print_error "Programming failed!"
        exit 1
    fi
}

# Main script logic
main() {
    local command=${1:-auto}
    
    case "$command" in
        "auto"|"")
            check_hardware
            detect_flash_file || exit 1
            flash_auto
            ;;
        "manual")
            check_hardware
            detect_flash_file || exit 1
            flash_manual
            ;;
        "57600")
            check_hardware
            detect_flash_file || exit 1
            flash_57600
            ;;
        "check")
            check_hardware
            ;;
        "reset")
            reset_board
            ;;
        "build")
            print_header "🔨 BUILD AND FLASH"
            print_info "Cleaning and building project..."
            make clean && make
            check_hardware
            detect_flash_file || exit 1
            flash_auto
            ;;
        "monitor")
            local baud_rate=${2:-57600}
            monitor_serial $baud_rate
            ;;
        "flashmon")
            local baud_rate=${2:-57600}
            flash_and_monitor $baud_rate
            ;;
        "flashterm")
            flash_with_terminal
            ;;
        "help"|"-h"|"--help")
            show_usage
            ;;
        *)
            print_error "Unknown command: $command"
            echo ""
            show_usage
            exit 1
            ;;
    esac
}

# Execute main function with all arguments
main "$@"