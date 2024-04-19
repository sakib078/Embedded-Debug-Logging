#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <thread>
#include <fstream>
#include <mutex>
#include <cstring>
#include "Logger.h"

#define BUF_LEN 1024

/* sakib sirajbhai mansuri 
 id : 122728223
 */

// Global variables
static int sockfd;
static sockaddr_in serverAddr;
static LOG_LEVEL filterLevel;
static std::mutex logMutex;
static bool isRunning = true;

// Function to handle receiving messages from the server
void ReceiveThread(int fd) {
    char buf[BUF_LEN];
    std::cout << "Hii" << std::endl;
    socklen_t addrLen = sizeof(serverAddr);
    while (isRunning) {
        // Non-blocking receive
        int len = recvfrom(fd, buf, BUF_LEN, MSG_DONTWAIT,(struct sockaddr *)&serverAddr, &addrLen);
        if (len > 0) {
            std::cout << "i am in" << std::endl;
            buf[len] = '\0';
            if (strstr(buf, "Set Log Level=") == buf) {
                int level;
                sscanf(buf, "Set Log Level=%d", &level);
                std::cout << "i am in 2" << std::endl;
                SetLogLevel((LOG_LEVEL)level);
                std::cout << "filter level set to: " << level << std::endl;
            }
            else 
            {
              std::cout << "invalid format" << std::endl;
            }
        }
        sleep(1); // Sleep for 1 second
    }
}

// Initialize logging
int InitializeLog() {
    // Create UDP socket
    sockfd = socket(AF_INET, SOCK_DGRAM, 0);
    if (sockfd < 0) {
        perror("Error creating socket");
        return -1;
    }

    // Configure server address
    serverAddr.sin_family = AF_INET;
    serverAddr.sin_addr.s_addr = inet_addr("192.168.247.132");
    serverAddr.sin_port = htons(12005);

    // Start receive thread
    std::thread recvThread(ReceiveThread, sockfd);
    recvThread.detach(); // Detach the thread

    return 0;
}

// Set the filter log level
void SetLogLevel(LOG_LEVEL level) {
    std::lock_guard<std::mutex> lock(logMutex);
    filterLevel = level;
}

// Log a message
void Log(LOG_LEVEL level, const char *file, const char *func, int line, const char *message) {
    //std::cout << "Received Log Message: " << message << std::endl; // Debugging output
    //std::cout << "Filter Level: " << filterLevel << ", Log Level: " << level << std::endl;
    
    if (level >= filterLevel) {
       // Log message processing continues if severity level meets the filter criteria
       char levelStr[][16] = {"DEBUG", "WARNING", "ERROR", "CRITICAL"};
       char buf[BUF_LEN];
       time_t now = time(0);
       char *dt = ctime(&now);
       snprintf(buf, BUF_LEN, "%s %s %s:%s:%d %s\n", dt, levelStr[level], file, func, line, message);

       // Send log message to the server
       std::lock_guard<std::mutex> lock(logMutex);
       sendto(sockfd, buf, strlen(buf), 0, (struct sockaddr *)&serverAddr, sizeof(serverAddr));
    
       std::ofstream logFile("server_log_compare.txt", std::ios::app); // Open file in append mode
       if (logFile.is_open()) {
                logFile << buf << std::endl; // Write log message to file
                logFile.flush(); // Flush the output buffer to ensure immediate writing to the file
       } else {
                std::cerr << "Error writing to log file (file not open)" << std::endl;
       }

    } else {
       std::cout << "Not sent due to low severity level" << std::endl;
       return;
    }
}

// Cleanup and exit logging
void ExitLog() {
    isRunning = false;
    close(sockfd);
}
