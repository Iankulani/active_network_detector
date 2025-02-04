#include <iostream>
#include <string>
#include <cstdlib>
#include <cstring>
#include <vector>
#include <thread>
#include <chrono>

using namespace std;

// Function to check if the host is active by pinging the given IP address
bool is_host_active(const string& ip_address) {
    // The command string to execute the ping
    string command = "ping -c 1 -W 1 " + ip_address + " > /dev/null 2>&1"; // Linux/Mac format

    // If you're on Windows, use the following instead:
    // string command = "ping -n 1 -w 1000 " + ip_address + " > nul";

    int result = system(command.c_str());
    return result == 0;  // If ping is successful, return true
}

// Function to validate IP format
bool is_valid_ip(const string& ip) {
    int a, b, c, d;
    return sscanf(ip.c_str(), "%d.%d.%d.%d", &a, &b, &c, &d) == 4 && a >= 0 && a <= 255 && b >= 0 && b <= 255 && c >= 0 && c <= 255 && d >= 0 && d <= 255;
}

// Function to scan a range of IP addresses
void scan_ip_range(const string& base_ip, int start, int end) {
    vector<string> active_hosts;

    // Scan each IP in the range
    for (int i = start; i <= end; ++i) {
        string ip_address = base_ip + "." + to_string(i);

        if (is_host_active(ip_address)) {
            active_hosts.push_back(ip_address);  // Add to the list of active hosts
        }
    }

    // Display active hosts
    if (active_hosts.empty()) {
        cout << "No active hosts found in the specified range." << endl;
    } else {
        cout << "Active hosts detected: " << endl;
        for (const auto& ip : active_hosts) {
            cout << ip << endl;
        }
    }
}

int main() {
    string base_ip;
    int start, end;
    
    cout<<"========================= Active Host Detector =========================\n\n";
    

    // Get user input for the IP range
    cout << "Enter the base IP address:";
    cin >> base_ip;

    // Validate IP format
    if (!is_valid_ip(base_ip)) {
        cerr << "Invalid IP address format. Please enter a valid base IP (e.g., 192.168.1)." << endl;
        return 1;
    }

    // Get user input for the range of the last octet (from 1 to 255)
    cout << "Enter the starting IP (1-255):";
    cin >> start;
    cout << "Enter the ending IP (1-255):";
    cin >> end;

    if (start < 1 || start > 255 || end < 1 || end > 255 || start > end) {
        cerr << "Invalid range. Please enter values between 1 and 255, with start <= end." << endl;
        return 1;
    }

    // Scan the range and detect active hosts
    cout << "\nScanning the network..." << endl;
    scan_ip_range(base_ip, start, end);

    return 0;
}
