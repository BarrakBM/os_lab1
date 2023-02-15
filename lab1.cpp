    //Barrak Mandani
    //Due 2/21/2023
    #include <iostream>
    #include <string> 
    #include <errno.h>
    #include <sys/utsname.h>
    #include <cstdio>
    #include <fstream>
    #include <ctime>
    #include <iomanip> 
    #include <sstream>
    #include <vector> 
    #include <string.h>
    #include <stdio.h>

    using namespace std;


    int main(){

        /*
        PART A
        */

        // create a usname struct
        struct utsname myuname; 

        //check if something went wrong
        errno = 0;
        if (uname(&myuname) < 0) {
        perror("uname");
        exit(EXIT_FAILURE);
        }

        
        //print information
        printf("System name - %s\n", myuname.sysname);
        printf("Node name - %s\n", myuname.nodename);
        printf("Release - %s\n", myuname.release);
        printf("Version  - %s\n", myuname.version);


        printf("\n\n*******************************************\n\n");
        /*
        PART B
        */

    // Use the proc filesystem to provide information about the system

        string line;
        string line1;
        string line2;
        string line3;
        ifstream infile;
        ifstream onfile;
        ifstream xfile; 
        ifstream afile;
        double btime;
        //string uptime;
        double stat;
        char time_information[200];
        char time_information2[200];
        char time_information3[200];
        string ignore1,ignore2, ignore3;
        string cpu;
        string test;
        char strings[300];
        char *ptr;
        string memory;
        string memory2;


         /*


            1.    Time since system last booted


        */
        // double now = std::chrono::duration_cast<std::chrono::seconds>(std::chrono::system_clock::now().time_since_epoch()).count()
        //open the file
        infile.open("/proc/stat");

       
        while (getline(infile, line)) {
            if(line.find("btime") == 0){
                
                /*
                take line as an input and return it with a null terminator
                %lf to format the numbers withour a decimal point
                store them in btime
                */
                sscanf(line.c_str(), "btime %lf", &btime);
               
            }
            
            }
            
        infile.close();
       
        // convert btime into time values 
        time_t time = (time_t)btime;
        //  use struct of type tm to store broken down time values
        struct tm *real_time = gmtime(&time);
        //use strftime to format the time
        strftime(time_information, 200, "%Y-%m-%d %H:%M:%S", real_time);
        // print the time
        cout << "The time when system was last booted (yyyy-mm-dd hh:mm:ss): " << time_information << endl;
        //cout << test << endl;


         /*


            2.   The amount of time since system was last booted 


        */
        //uptime
        onfile.open("/proc/uptime");
        while (getline(onfile, line1)) {
            break;
        }
        onfile.close();

        /*
            separate the string by space and put the into vector
        */
        istringstream is(line1);
        vector<string> uptime_vector;
        string v;
        while ( getline( is, v,' ') ) {
            uptime_vector.push_back(v);
        } 
        //convert to double
        double uptime = stod(uptime_vector[0]);//uptime of the system in seconds
        double idle = stod(uptime_vector[1]);//amount of time spent in idle process in seconds

        //extract days
        int days = (int)uptime/86400;
        
        time_t time_seconds = (time_t)uptime;//system 
        struct tm* second_time =gmtime(&time_seconds);
        char seconds[100];
        strftime(seconds, 100,"%H:%M:%S", second_time );
        cout << "The amount of time since system was last booted in the form (dd:hh:mm:ss): "<<days<<":" << seconds<< endl;


        /*


            3.   Amount of time that the CPU has spent in user mode and system mode


        */

        //cpu
        xfile.open("/proc/stat");
        while (getline(xfile, line2)) {
        
            if(line2.find("cpu") == 0){
                getline(xfile,test);
                break;
            }
        }
        xfile.close();
        // separte it by space into vectors
        istringstream ss(test);
        vector<string> cpu_vector;
        string s;
        while ( getline( ss, s,' ') ) {
            cpu_vector.push_back(s);
            
            
        } 
        
        double user_mode = stod(cpu_vector[1]);//uptime of the system in seconds
        double system_mode = stod(cpu_vector[3]);//amount of time spent in idle process in seconds

        // int user_mode = stoi(cpu_vector[1]);
        cout << "Amount of time that the CPU has spent in user mode: " << cpu_vector[1]<< " Seconds" << endl;
        cout << "Amount of time that the CPU has spent in system mode: " << cpu_vector[3] << " Seconds" << endl;

        /*


            4.   The total amount of memory in the system and the amount of memory currently available


        */

       afile.open("/proc/meminfo");
        while (getline(afile, line3)) {
        
            if(line3.find("MemTotal:") == 0){
                
                cout << line3 << endl;
            }
            if(line3.find("MemAvailable") == 0){
                
                cout << line3 << endl;
            }
        }
        afile.close();
        
    }      