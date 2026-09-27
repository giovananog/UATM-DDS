#include "../../model/UATMTraits.h"  
#include "ReaderListenerAA.h"  
#include <model/Sync.h>  
#include <ace/Log_Msg.h>  
#include <dds/DCPS/WaitSet.h>  

// Constructor initializes ReaderCondSync object
ReaderListenerAA::ReaderListenerAA(OpenDDS::Model::ReaderCondSync &rcs)
    : rcs_(rcs) {}  

void ReaderListenerAA::on_data_available(DDS::DataReader_ptr reader)
{
    ACE_Guard<ACE_Thread_Mutex> g(mutex_);  
    static bool signal_sent = false;  

    // Narrow the reader to the specific data type for flight assignment (flightAssignDataReader)
    UATM::airspaceAlertDataReader_var reader_i =
        UATM::airspaceAlertDataReader::_narrow(reader);

    // Check if the narrow operation was successful, exit if it failed
    if (CORBA::is_nil(reader_i.in()))
    {
        ACE_ERROR((LM_ERROR,
                   ACE_TEXT("ERROR: %N:%l: on_data_available() -")
                       ACE_TEXT(" _narrow failed!\n")));
        ACE_OS::exit(-1);  // Exit the program if narrowing the reader failed
    }

    UATM::airspaceAlert msg;  // Declare a message object to store data from the reader
    DDS::SampleInfo info;  // Declare a SampleInfo object to store metadata about the sample

    // Loop to process available data
    while (true)
    {
        // Take the next sample from the reader
        DDS::ReturnCode_t error = reader_i->take_next_sample(msg, info);
        if (error == DDS::RETCODE_OK)  
        {
            if (info.valid_data)  
            {
                // Print the details of the flight assignment to the console
                std::cout << "| airspaceAlert: "
                          << "type:" << msg.type
                          << ",affectedArea:" << msg.affectedArea
                          << ",severity:" << msg.severity
                          << ",alertId:" << msg.alertId.in()
                          << std::endl;
            }
            else  
            {
                if (!signal_sent)
                {
                    rcs_.signal();  
                    signal_sent = true;  
                }
                break;  
            }
        }
        else  
        {
            if (error != DDS::RETCODE_NO_DATA)  
            {
                ACE_ERROR((LM_ERROR,
                           ACE_TEXT("ERROR: %N:%l: on_data_available() -")
                               ACE_TEXT(" take_next_sample failed!\n")));  
            }
            break;  
        }
    }
};
