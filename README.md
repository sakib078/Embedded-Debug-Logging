# Embedded-Debug-Logging
Welcome to the Embedded Debug Logger repository! This project aims to Revolutionize embedded systems debugging with our lightweight logging system. Real-time monitoring, dynamic filtering, and centralized server. Effortless integration, scalable for single or multiple applications. Join us in building more robust embedded solutions!

// let's talk about the features
Features:

1. Embedded Logging: Our logging system is designed to be lightweight and efficient, ensuring minimal impact on the performance of your product. Each log entry contains essential information such as severity level, file name, function name, line number, and a concise message, providing invaluable insights into the state of your application.
2. Centralized Server: Logs are transmitted to a central server via UDP for fast and reliable delivery. The server aggregates log messages from multiple processes, allowing for comprehensive monitoring and analysis of system behaviour.
3. Dynamic Log Filtering: Customize the severity level at runtime to filter log messages according to your specific requirements. Whether you need to focus on debugging critical errors or monitoring general system activity, our logging system adapts to your needs with ease.
4. Record-based log system: According to the filter level that you have chosen all those log messages will be dumped down in server_log.txt.
6. Scalability: Designed to accommodate a single application or multiple applications across different machines, our logging system scales seamlessly to meet the demands of your project. Whether you're debugging a small-scale prototype or a distributed network of embedded devices, our solution adapts to your evolving needs with flexibility and reliability.

Setup: 
Clone the repository into your local machine. You need a Linux-based operating system, to download the required components such as GCC compiler, and other libraries to successfully run the project. The Makefile is given, execute those to create a binary file that can be executable.

Integration: 
The program has integrated logger files in an existing codebase, capturing essential data like severity level, file name, and line number. You will find the logger code in the logger.h, logger.cpp and logserver.cpp.

Testing and Debugging:
Deploy your application alongside the central server. Monitor log messages in real-time, adjust filtering settings as needed, and analyze system behaviour to identify and resolve issues efficiently.

Scalability: 
As your project grows, deploy additional instances of the central server to accommodate multiple applications across various machines. Customize server configurations to meet the specific requirements of each application, ensuring seamless integration and optimal performance.

Contributing:
We welcome contributions from the community to enhance and expand the capabilities of our embedded debug logging system. Whether you're interested in adding new features, improving documentation, or fixing bugs, your contributions are invaluable in advancing the reliability and effectiveness of embedded systems development. Hint: The log system(server side) is not that fast in receiving the data bcuz of the of the usage of UDP or issues with the sento() or receiveFrom() function.
