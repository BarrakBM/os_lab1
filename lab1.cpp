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
        ifstream infile;
        double btime;
        double uptime;
        double stat;
        char time_information[200];
        char time_information2[200];
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
                //cout << line << endl;
            }
        
            if(line.find("uptime") == 0){
                sscanf(line.c_str(), "uptime %lf", &uptime);
            }
            if(line.find("cpu" == 0)){
                //get first line
                getline(infile,test);
                break;
                
                }
            }

        

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
        cout << "Time since system last booted (yyyy-mm-dd hh:mm:ss): " << time_information << endl;

        
        /*
            amount of time since system last booted
        */

        time_t time2 = (time_t)uptime;
        struct tm *real_time2 = gmtime(&time2);
        strftime(time_information2, 200, "%d:%H:%M:%S", real_time2); // format the time
        cout << "Amount of time since system last booted (dd:hh:mm:ss): " << time_information2 << endl;
        
        
        // cout << test << endl;

        // istringstream iss(test);
        // string s;
        // while(getline(iss, s,' ')){
        //     printf( "`%s'\n", s.c_str());
        // }

        //cout << s[3] << endl;
    }
