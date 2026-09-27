#include "../../model/UATMTraits.h"
#include <tools/modeling/codegen/model/NullReaderListener.h>

#include <model/Sync.h>
#include <ace/Log_Msg.h>

#include <dds/DCPS/WaitSet.h>
#include "ReaderListenerTC.h"
#include "ReaderListenerVS.h"

// Security configurations
#if OPENDDS_CONFIG_SECURITY
#  include <dds/DCPS/security/framework/Properties.h>
#endif
#include <dds/DCPS/StaticIncludes.h>
#if OPENDDS_DO_MANUAL_STATIC_INCLUDES
#  ifndef OPENDDS_SAFETY_PROFILE
#    include <dds/DCPS/transport/udp/Udp.h>
#    include <dds/DCPS/transport/multicast/Multicast.h>
#    include <dds/DCPS/RTPS/RtpsDiscovery.h>
#    include <dds/DCPS/transport/shmem/Shmem.h>
#    if OPENDDS_CONFIG_SECURITY
#      include <dds/DCPS/security/BuiltInPlugins.h>
#    endif
#  endif
#  include <dds/DCPS/transport/rtps_udp/RtpsUdp.h>
#endif
#include <ace/Log_Msg.h>

// Main function
int ACE_TMAIN(int argc, ACE_TCHAR* argv[])
{
  try {
    // Set security for participant
    TheServiceParticipant->set_security(true); ///

    // Initialize the application and models for UATM
    OpenDDS::Model::Application application(argc, argv);
    UATM::uatmDiagram::DefaultuatmType model(application, argc, argv);

    // Define a shorthand for the Elements type in UATM
    using OpenDDS::Model::UATM::uatmDiagram::Elements;

    // Create a synchronization mechanism
    ACE_SYNCH_MUTEX lock;
    ACE_Condition<ACE_SYNCH_MUTEX> condition(lock);

    // Setup DataReaders and their listeners for different topics

    DDS::DataReader_var reader_rest = model.reader(Elements::DataReaders::vehicleStateSkpDR);
    OpenDDS::Model::ReaderCondSync rcsVS(reader_rest, condition);
    DDS::DataReaderListener_var listenerVS(new ReaderListenerVS(rcsVS));
    reader_rest->set_listener(listenerVS, OpenDDS::DCPS::DEFAULT_STATUS_MASK);

    DDS::DataReader_var reader_request = model.reader(Elements::DataReaders::tacticalCommandSkpDR);
    OpenDDS::Model::ReaderCondSync rcsTC(reader_request, condition);
    DDS::DataReaderListener_var listenerTC(new ReaderListenerTC(rcsTC));
    reader_request->set_listener(listenerTC, OpenDDS::DCPS::DEFAULT_STATUS_MASK);

  } catch (const CORBA::Exception& e) {
    // Exception handling for CORBA exceptions
    e._tao_print_exception("Exception caught in main():");
    return -1;

  } catch( const std::exception& ex) {
    // Exception handling for standard C++ exceptions
    ACE_ERROR_RETURN((LM_ERROR,
                      ACE_TEXT("(%P|%t) ERROR: %N:%l: main() -")
                      ACE_TEXT(" Exception caught: %C\n"),
                      ex.what()),
                     -1);
  }
  return 0;
}
