#ifndef UATM_T_H
#define UATM_T_H

#include "uatm_export.h"

#include "model/Exceptions.h"

#include "dds/DdsDcpsInfrastructureC.h" // For QoS Policy types.
#include "dds/DCPS/transport/framework/TransportDefs.h"

namespace DDS {
  class DomainParticipant; // For type registration
} // End of namespace DDS

namespace OpenDDS { namespace DCPS {
  class TransportConfiguration;
} } // End of namespace OpenDDS::DCPS

namespace OpenDDS { namespace Model {

  using namespace OpenDDS::DCPS;
  using namespace DDS;

namespace UATM {
namespace uatmDiagram {
 
  class Elements {
    public:
      class Participants {
        public: enum Values {
          evtolVehicleDP,
          weatherSystemDP,
          fleetOperatorDP,
          uaspDP,
          skyportOperatorDP,
          LAST_INDEX
        };
      };

      class Types {
        public: enum Values {
          vehicleState,
          tacticalCommand,
          flightStatus,
          airspaceAlert,
          fleetDirectives,
          weatherUpdate,
          tolPadStatus,
          trafficFlowsInfo,
          LAST_INDEX
        };
      };
      class Topics {
        public: enum Values {
          UATM__uatmDiagram__vehicleState,
          UATM__uatmDiagram__tacticalCommand,
          UATM__uatmDiagram__airspaceAlert,
          UATM__uatmDiagram__weatherUpdate,
          UATM__uatmDiagram__flightStatus,
          UATM__uatmDiagram__fleetDirectives,
          UATM__uatmDiagram__tolPadStatus,
          UATM__uatmDiagram__trafficFlowsInfo,
          LAST_INDEX
        };
      };
      class ContentFilteredTopics {
        public: enum Values {
          LAST_INDEX
        };
      };
      class MultiTopics {
        public: enum Values {
          LAST_INDEX
        };
      };
      class Publishers {
        public: enum Values {
          evtolVehiclePb,
          weatherSystemPB,
          fleetOperatorPb,
          uaspPB,
          skyportOperatorPB,
          LAST_INDEX
        };
      };

      class Subscribers {
        public: enum Values {
          evtolVehicleSb,
          fleetOperatorSb,
          uaspSB,
          skyportOperatorSB,
          LAST_INDEX
        };
      };

      class DataWriters {
        public: enum Values {
          vehicleStateDW,
          flightStatusDW,
          weatherUpdateDW,
          fleetDirectivesFoDW,
          tacticalCommandDW,
          airspaceAlertDW,
          fleetDirectivesUaspDW,
          tolPadStatusDW,
          trafficFlowsDW,
          LAST_INDEX
        };
      };

      class DataReaders {
        public: enum Values {
          tacticalCommandEvtolDR,
          airspaceAlertDR,
          fleetDirectivesDR,
          vehicleStateFoDR,
          flightStatusDR,
          vehicleStateUaspDR,
          trafficFlowsDR,
          weatherUpdateDR,
          vehicleStateSkpDR,
          tacticalCommandSkpDR,
          LAST_INDEX
        };
      };

      class Data {
        public:
          Data();
          ~Data();

          ///{ @name Qos Policy values
          DDS::DomainParticipantQos qos(Participants::Values which);
          DDS::TopicQos             qos(Topics::Values which);
          DDS::PublisherQos         qos(Publishers::Values which);
          DDS::SubscriberQos        qos(Subscribers::Values which);
          DDS::DataWriterQos        qos(DataWriters::Values which);
          DDS::DataReaderQos        qos(DataReaders::Values which);

          bool copyTopicQos(DataWriters::Values which);
          bool copyTopicQos(DataReaders::Values which);

          void copyPublicationQos(DataWriters::Values which, DDS::DataWriterQos& writerQos);
          void copySubscriptionQos(DataReaders::Values which, DDS::DataReaderQos& readerQos);
          ///}

          ///{ @name Other configuration values
          long        mask(Participants::Values which);
          long        mask(Publishers::Values which);
          long        mask(Subscribers::Values which);
          long        mask(Topics::Values which);
          long        mask(DataWriters::Values which);
          long        mask(DataReaders::Values which);
          long        domain(Participants::Values which);
          const char* typeName(Types::Values which);
          const char* topicName(Topics::Values which);
          ///}

          /// Type registration.
          void registerType(Types::Values type, DDS::DomainParticipant* participant);

          ///{ @name Containment Relationships
          Participants::Values participant(Publishers::Values which);
          Participants::Values participant(Subscribers::Values which);
          Types::Values        type(Topics::Values which);
          Topics::Values       topic(DataWriters::Values which);
          Topics::Values       topic(DataReaders::Values which);
          ContentFilteredTopics::Values contentFilteredTopic(Topics::Values which);
          const char*          filterExpression(ContentFilteredTopics::Values which);
          const char*          topicExpression(MultiTopics::Values which);
          MultiTopics::Values  multiTopic(Topics::Values which);
          Topics::Values       relatedTopic(ContentFilteredTopics::Values which);
          Publishers::Values   publisher(DataWriters::Values which);
          Subscribers::Values  subscriber(DataReaders::Values which);
          std::string          transportConfigName(Participants::Values which);
          std::string          transportConfigName(Publishers::Values which);
          std::string          transportConfigName(Subscribers::Values which);
          std::string          transportConfigName(DataWriters::Values which);
          std::string          transportConfigName(DataReaders::Values which);
          ///}

        private:

          // Initialization.
          void loadDomains();
          void loadTopics();
          void loadMaps();
          void loadTransportConfigNames();

          void buildParticipantsQos();
          void buildTopicsQos();
          void buildPublishersQos();
          void buildSubscribersQos();
          void buildPublicationsQos();
          void buildSubscriptionsQos();

          // Basic array containers since we only allow access using the
          // defined enumeration values.

          unsigned long             domains_[                Participants::LAST_INDEX];
          DDS::DomainParticipantQos participantsQos_[        Participants::LAST_INDEX];
          std::string               participantTxCfgNames_[  Participants::LAST_INDEX];

          Participants::Values      publisherParticipants_[   Publishers::LAST_INDEX];
          DDS::PublisherQos         publishersQos_[           Publishers::LAST_INDEX];
          std::string               publisherTxCfgNames_[     Publishers::LAST_INDEX];

          Participants::Values      subscriberParticipants_[   Subscribers::LAST_INDEX];
          DDS::SubscriberQos        subscribersQos_[           Subscribers::LAST_INDEX];
          std::string               subscriberTxCfgNames_[     Subscribers::LAST_INDEX];

          Topics::Values            writerTopics_[           DataWriters::LAST_INDEX];
          Publishers::Values        publishers_[             DataWriters::LAST_INDEX];
          DDS::DataWriterQos        writersQos_[             DataWriters::LAST_INDEX];
          bool                      writerCopyTopicQos_[     DataWriters::LAST_INDEX];
          std::string               writerTxCfgNames_[       DataWriters::LAST_INDEX];

          Topics::Values            readerTopics_[           DataReaders::LAST_INDEX];
          Subscribers::Values       subscribers_[            DataReaders::LAST_INDEX];
          DDS::DataReaderQos        readersQos_[             DataReaders::LAST_INDEX];
          bool                      readerCopyTopicQos_[     DataReaders::LAST_INDEX];
          std::string               readerTxCfgNames_[       DataReaders::LAST_INDEX];

          Types::Values                 types_[      Topics::LAST_INDEX];
          const char*                   topicNames_[ Topics::LAST_INDEX];
          DDS::TopicQos                 topicsQos_[  Topics::LAST_INDEX];
          char*                         typeNames_[   Types::LAST_INDEX];
          ContentFilteredTopics::Values cfTopics_[   Topics::LAST_INDEX];
          MultiTopics::Values           multiTopics_[Topics::LAST_INDEX];

      }; // End class Data
  }; // End class Elements
} // End namespace uatmDiagram
} // End namespace UATM

} // End namespace Model
} // End namespace OpenDDS

// The template implementation.

inline
DDS::DomainParticipantQos
OpenDDS::Model::UATM::uatmDiagram::Elements::Data::qos(Participants::Values which)
{
  if(which < 0 || which >= Participants::LAST_INDEX) {
    throw OutOfBoundsException();
  }
  return this->participantsQos_[ which];
}

inline
DDS::TopicQos
OpenDDS::Model::UATM::uatmDiagram::Elements::Data::qos(Topics::Values which)
{
  if (which < 0 || which >= Topics::LAST_INDEX) {
    throw OutOfBoundsException();
  }
  return this->topicsQos_[ which];
}

inline
DDS::PublisherQos
OpenDDS::Model::UATM::uatmDiagram::Elements::Data::qos(Publishers::Values which)
{
  if (which < 0 || which >= Publishers::LAST_INDEX) {
    throw OutOfBoundsException();
  }
  return this->publishersQos_[ which];
}

inline
DDS::SubscriberQos
OpenDDS::Model::UATM::uatmDiagram::Elements::Data::qos(Subscribers::Values which)
{
  if (which < 0 || which >= Subscribers::LAST_INDEX) {
    throw OutOfBoundsException();
  }
  return this->subscribersQos_[ which];
}

inline
DDS::DataWriterQos
OpenDDS::Model::UATM::uatmDiagram::Elements::Data::qos(DataWriters::Values which)
{
  if (which < 0 || which >= DataWriters::LAST_INDEX) {
    throw OutOfBoundsException();
  }
  return this->writersQos_[ which];
}

inline
DDS::DataReaderQos
OpenDDS::Model::UATM::uatmDiagram::Elements::Data::qos(DataReaders::Values which)
{
  if (which < 0 || which >= DataReaders::LAST_INDEX) {
    throw OutOfBoundsException();
  }
  return this->readersQos_[ which];
}

inline
bool
OpenDDS::Model::UATM::uatmDiagram::Elements::Data::copyTopicQos(DataWriters::Values which)
{
  if (which < 0 || which >= DataWriters::LAST_INDEX) {
    throw OutOfBoundsException();
  }
  return this->writerCopyTopicQos_[which];
}

inline
bool
OpenDDS::Model::UATM::uatmDiagram::Elements::Data::copyTopicQos(DataReaders::Values which)
{
  if (which < 0 || which >= DataReaders::LAST_INDEX) {
    throw OutOfBoundsException();
  }
  return this->readerCopyTopicQos_[which];
}

inline
long
OpenDDS::Model::UATM::uatmDiagram::Elements::Data::mask(Participants::Values which)
{
  if (which < 0 || which >= Participants::LAST_INDEX) {
    throw OutOfBoundsException();
  }
  return DEFAULT_STATUS_MASK;
}

inline
long
OpenDDS::Model::UATM::uatmDiagram::Elements::Data::mask( Publishers::Values which)
{
  if( which < 0 || which >= Publishers::LAST_INDEX) {
    throw OutOfBoundsException();
  }
  return DEFAULT_STATUS_MASK;
}

inline
long
OpenDDS::Model::UATM::uatmDiagram::Elements::Data::mask( Subscribers::Values which)
{
  if( which < 0 || which >= Subscribers::LAST_INDEX) {
    throw OutOfBoundsException();
  }
  return DEFAULT_STATUS_MASK;
}

inline
long
OpenDDS::Model::UATM::uatmDiagram::Elements::Data::mask( Topics::Values which)
{
  if( which < 0 || which >= Topics::LAST_INDEX) {
    throw OutOfBoundsException();
  }
  return DEFAULT_STATUS_MASK;
}

inline
long
OpenDDS::Model::UATM::uatmDiagram::Elements::Data::mask( DataWriters::Values which)
{
  if( which < 0 || which >= DataWriters::LAST_INDEX) {
    throw OutOfBoundsException();
  }
  return DEFAULT_STATUS_MASK;
}

inline
long
OpenDDS::Model::UATM::uatmDiagram::Elements::Data::mask( DataReaders::Values which)
{
  if( which < 0 || which >= DataReaders::LAST_INDEX) {
    throw OutOfBoundsException();
  }
  return DEFAULT_STATUS_MASK;
}

inline
long
OpenDDS::Model::UATM::uatmDiagram::Elements::Data::domain( Participants::Values which)
{
  if( which < 0 || which >= Participants::LAST_INDEX) {
    throw OutOfBoundsException();
  }
  return this->domains_[ which];
}

inline
const char*
OpenDDS::Model::UATM::uatmDiagram::Elements::Data::typeName( Types::Values which)
{
  if( which < 0 || which >= Types::LAST_INDEX) {
    throw OutOfBoundsException();
  }
  return this->typeNames_[ which];
}

inline
const char*
OpenDDS::Model::UATM::uatmDiagram::Elements::Data::topicName( Topics::Values which)
{
  if( which < 0 || which >= Topics::LAST_INDEX) {
    throw OutOfBoundsException();
  }
  return this->topicNames_[ which];
}

inline
OpenDDS::Model::UATM::uatmDiagram::Elements::Participants::Values
OpenDDS::Model::UATM::uatmDiagram::Elements::Data::participant(Publishers::Values which)
{
  if(which < 0 || which >= Publishers::LAST_INDEX) {
    throw OutOfBoundsException();
  }
  return this->publisherParticipants_[ which];
}

inline
OpenDDS::Model::UATM::uatmDiagram::Elements::Participants::Values
OpenDDS::Model::UATM::uatmDiagram::Elements::Data::participant(Subscribers::Values which)
{
  if(which < 0 || which >= Subscribers::LAST_INDEX) {
    throw OutOfBoundsException();
  }
  return this->subscriberParticipants_[ which];
}

inline
OpenDDS::Model::UATM::uatmDiagram::Elements::Types::Values
OpenDDS::Model::UATM::uatmDiagram::Elements::Data::type(Topics::Values which)
{
  if(which < 0 || which >= Topics::LAST_INDEX) {
    throw OutOfBoundsException();
  }
  return this->types_[ which];
}

inline
OpenDDS::Model::UATM::uatmDiagram::Elements::Topics::Values
OpenDDS::Model::UATM::uatmDiagram::Elements::Data::topic(DataWriters::Values which)
{
  if(which < 0 || which >= DataWriters::LAST_INDEX) {
    throw OutOfBoundsException();
  }
  return this->writerTopics_[ which];
}

inline
OpenDDS::Model::UATM::uatmDiagram::Elements::Topics::Values
OpenDDS::Model::UATM::uatmDiagram::Elements::Data::topic(DataReaders::Values which)
{
  if(which < 0 || which >= DataReaders::LAST_INDEX) {
    throw OutOfBoundsException();
  }
  return this->readerTopics_[ which];
}

inline
OpenDDS::Model::UATM::uatmDiagram::Elements::ContentFilteredTopics::Values
OpenDDS::Model::UATM::uatmDiagram::Elements::Data::contentFilteredTopic(Topics::Values which)
{
  if(which < 0 || which >= Topics::LAST_INDEX) {
    throw OutOfBoundsException();
  }
  return this->cfTopics_[which];
}

inline
OpenDDS::Model::UATM::uatmDiagram::Elements::MultiTopics::Values
OpenDDS::Model::UATM::uatmDiagram::Elements::Data::multiTopic(Topics::Values which)
{
  if(which < 0 || which >= Topics::LAST_INDEX) {
    throw OutOfBoundsException();
  }
  return this->multiTopics_[which];
}

inline
OpenDDS::Model::UATM::uatmDiagram::Elements::Topics::Values
OpenDDS::Model::UATM::uatmDiagram::Elements::Data::relatedTopic(ContentFilteredTopics::Values which)
{
  if(which < 0 || which >= ContentFilteredTopics::LAST_INDEX) {
    throw OutOfBoundsException();
  }
  return Topics::LAST_INDEX; // not valid when no CF topics defined
}

inline
const char* 
OpenDDS::Model::UATM::uatmDiagram::Elements::Data::filterExpression(ContentFilteredTopics::Values which)
{
  if(which < 0 || which >= ContentFilteredTopics::LAST_INDEX) {
    throw OutOfBoundsException();
  }
  return 0; // not valid when no CF topics defined
}

inline
const char* 
OpenDDS::Model::UATM::uatmDiagram::Elements::Data::topicExpression(MultiTopics::Values which)
{
  if(which < 0 || which >= MultiTopics::LAST_INDEX) {
    throw OutOfBoundsException();
  }
  return 0; // not valid when no multitopics defined
}

inline
OpenDDS::Model::UATM::uatmDiagram::Elements::Publishers::Values
OpenDDS::Model::UATM::uatmDiagram::Elements::Data::publisher(DataWriters::Values which)
{
  if(which < 0 || which >= DataWriters::LAST_INDEX) {
    throw OutOfBoundsException();
  }
  return this->publishers_[ which];
}

inline
OpenDDS::Model::UATM::uatmDiagram::Elements::Subscribers::Values
OpenDDS::Model::UATM::uatmDiagram::Elements::Data::subscriber(DataReaders::Values which)
{
  if(which < 0 || which >= DataReaders::LAST_INDEX) {
    throw OutOfBoundsException();
  }
  return this->subscribers_[ which];
}


#if defined (ACE_TEMPLATES_REQUIRE_SOURCE)
#include "uatm_T.cpp"
#endif /* ACE_TEMPLATES_REQUIRE_SOURCE */

#if defined (ACE_TEMPLATES_REQUIRE_PRAGMA)
#pragma implementation ("uatm_T.cpp")
#endif /* ACE_TEMPLATES_REQUIRE_PRAGMA */

// Establish the model interfaces for use by the application.

#include "uatmTypeSupportImpl.h"

#include "model/Service_T.h"

#endif /* UATM_T_H */

