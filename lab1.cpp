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
        double btime;
        string uptime;
        double stat;
        char time_information[200];
        char time_information2[200];
        char time_information3[200];
        string ignore1,ignore2, ignore3;
        string cpu;
        string test;
        char strings[300];
        char *ptr;
        // double now = std::chrono::duration_cast<std::chrono::seconds>(std::chrono::system_clock::now().time_since_epoch()).count()
        //open the fikle
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


        //uptime
        onfile.open("/proc/uptime");
        while (getline(onfile, line1)) {
            getline(onfile,uptime);
            cout << line1<< endl;
            break;
            
        }
        onfile.close();

        //cpu
        xfile.open("/proc/stat");
        while (getline(xfile, line2)) {
        
            if(line2.find("cpu") == 0){
                getline(xfile,test);
                break;
            }
        }
        xfile.close();


        cout << "numbers" <<line1 <<endl;
        /*
                Time since system last booted
        */
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
            amount of time since system last booted
        */

        // time_t time2 = (time_t)uptime;
        // struct tm *real_time2 = gmtime(&time2);
        // strftime(time_information2, 200, "%m-%d:%H:%M:%S", real_time2); // format the time
        // cout << "Amount of time since system last booted (dd:hh:mm:ss): " << time_information2 << endl;
       
        istringstream iss(test);
        vector<string> cpu_vector;
        string s;
        while ( getline( iss, s,' ') ) {
            cpu_vector.push_back(s);
        } 

        //Amount of time that the CPU has spent in user mode and system mode
        double cpu3 = stod(cpu_vector[3]);//system mode
        double cpu1 = stod(cpu_vector[1]);//user mode
        //cout << cpu3 << endl;

        time_t time3 = (time_t)cpu3;//system 
        struct tm *real_time3 = gmtime(&time3);
        strftime(time_information2, 200, "%Y-%m-%d %H:%M:%S", real_time3); // format the time
        cout << "Amount of time that the CPU has spent in system mode (yyyy-mm-dd hh:mm:ss): " << time_information2 << endl;

        //user mode
        time_t time4 = (time_t)cpu1;//user
        struct tm *real_time4 = gmtime(&time4);//user
        strftime(time_information3, 200, "%Y-%m-%d %H:%M:%S", real_time4); 
        cout << "Amount of time that the CPU has spent in user mode (yyyy-mm-dd hh:mm:ss): " << time_information3 << endl;
       

    }
