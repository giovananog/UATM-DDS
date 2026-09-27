#include <fstream>
#include <string>
#include <vector>
#include <thread>
#include <chrono>
#include "../../model/uatmTraits.h"
#include <model/Sync.h>
#include <unordered_set>
#include <dds/DCPS/WaitSet.h>

// Security configurations
#if OPENDDS_CONFIG_SECURITY
#include <dds/DCPS/security/framework/Properties.h>
#endif
#include <dds/DCPS/StaticIncludes.h>
#if OPENDDS_DO_MANUAL_STATIC_INCLUDES
#ifndef OPENDDS_SAFETY_PROFILE
#include <dds/DCPS/transport/udp/Udp.h>
#include <dds/DCPS/transport/multicast/Multicast.h>
#include <dds/DCPS/RTPS/RtpsDiscovery.h>
#include <dds/DCPS/transport/shmem/Shmem.h>
#if OPENDDS_CONFIG_SECURITY
#include <dds/DCPS/security/BuiltInPlugins.h>
#endif
#endif
#include <dds/DCPS/transport/rtps_udp/RtpsUdp.h>
#endif
#include <ace/Log_Msg.h>

int ACE_TMAIN(int argc, ACE_TCHAR **argv)
{
  try
  {
    // Set security for participant
    TheServiceParticipant->set_security(true);

    // Initialize OpenDDS application
    OpenDDS::Model::Application application(argc, argv);
    UATM::uatmDiagram::DefaultuatmType model(application, argc, argv);

    // Define elements and obtain DataWriter for eVTOL data
    using OpenDDS::Model::UATM::uatmDiagram::Elements;

    DDS::DataWriter_var fleetDirectivesWriter = model.writer(Elements::DataWriters::fleetDirectivesFoDW);
    UATM::fleetDirectivesDataWriter_var writer_var = UATM::fleetDirectivesDataWriter::_narrow(fleetDirectivesWriter.in());

    // Check if narrowing succeeded
    if (CORBA::is_nil(writer_var.in()))
    {
      ACE_ERROR_RETURN((LM_ERROR,
                        ACE_TEXT("(%P|%t) ERROR: %N:%l: main() -")
                            ACE_TEXT(" _narrow failed!\n")),
                       -1);
    }

    // Set start time and duration for main loop
    auto startTime = std::chrono::steady_clock::now();
    double duration = 100.0;

    // Main loop to process eVTOL data
    while (true)
    {
      auto currentTime = std::chrono::steady_clock::now();
      std::chrono::duration<double> elapsedTime = currentTime - startTime;

      if (elapsedTime.count() >= duration)
      {
        break;
      }

      // Acquire lock and process each eVTOL's availability
      OpenDDS::Model::WriterSync ws(fleetDirectivesWriter);
      {
        UATM::fleetDirectives bfr;

        // Missão alvo
        bfr.missionId = CORBA::string_dup("MISSION_32A");

        // Instrução geral
        bfr.instruction = CORBA::string_dup("HOLD_POSITION");

        // ETA de execução (epoch seconds)
        bfr.scheduleETA = 1738582800.0L; // +1h do exemplo anterior

        // Write data to DDS
        DDS::ReturnCode_t error = writer_var->write(bfr, DDS::HANDLE_NIL);

        // Error handling for failed write
        if (error != DDS::RETCODE_OK)
        {
          ACE_ERROR((LM_ERROR,
                     ACE_TEXT("(%P|%t) ERROR: %N:%l: main() -")
                         ACE_TEXT(" write returned %d!\n"),
                     error));
        }
      }

      // Wait for a defined period before processing the next batch
      std::this_thread::sleep_for(std::chrono::seconds(3));
    }
  }
  catch (const CORBA::Exception &e)
  {
    e._tao_print_exception("Exception caught in main():");
    return -1;
  }
  catch (const std::exception &ex)
  {
    ACE_ERROR_RETURN((LM_ERROR,
                      ACE_TEXT("(%P|%t) ERROR: %N:%l: main() -")
                          ACE_TEXT(" Exception caught: %C\n"),
                      ex.what()),
                     -1);
  }
  return 0;
}
