
#include "uatm_T.h"

#include "uatmTypeSupportImpl.h"


// For transport configuration
#include "dds/DCPS/transport/tcp/TcpInst.h"
#include "dds/DCPS/transport/udp/UdpInst.h"
#include "dds/DCPS/transport/multicast/MulticastInst.h"

#include <dds/DCPS/security/framework/Properties.h>

#include "dds/DCPS/Service_Participant.h"
#include "model/Utilities.h"

namespace OpenDDS { namespace Model { 
namespace UATM {
namespace uatmDiagram {

inline
Elements::Data::Data()
{ 
  for( int index = 0;
       index < Elements::Types::LAST_INDEX;
       ++index) {
    this->typeNames_[index] = 0;
  }
  this->loadDomains();
  this->loadTopics();
  this->loadMaps(); /// MUST precede the QoS loading.
  this->loadTransportConfigNames();

  this->buildParticipantsQos();
  this->buildTopicsQos();
  this->buildPublishersQos();
  this->buildSubscribersQos();
  this->buildPublicationsQos();
  this->buildSubscriptionsQos();
}

inline
Elements::Data::~Data()
{
  for(int index = 0;
      index < Elements::Types::LAST_INDEX;
      ++index) {
    if(this->typeNames_[index]) {
      CORBA::string_free(this->typeNames_[index]); // Created by CORBA::string_dup()
      this->typeNames_[index] = 0;
    }
  }
}

inline
void
Elements::Data::registerType(
  Types::Values      type,
  DomainParticipant* participant)
{
  switch(type) {
    case Types::vehicleState:
      {
        typedef ::UATM::vehicleStateTypeSupportImpl TypeSupport;

        TypeSupport* typeSupport = new TypeSupport();
        if( RETCODE_OK != typeSupport->register_type( participant, 0)) {
          throw BadRegisterException();
        }

        if( this->typeNames_[ type]) {
          CORBA::string_free( this->typeNames_[ type]); // Was created by CORBA::string_dup()
        }
        this->typeNames_[ type] = typeSupport->get_type_name();
      }
      break;

    case Types::tacticalCommand:
      {
        typedef ::UATM::tacticalCommandTypeSupportImpl TypeSupport;

        TypeSupport* typeSupport = new TypeSupport();
        if( RETCODE_OK != typeSupport->register_type( participant, 0)) {
          throw BadRegisterException();
        }

        if( this->typeNames_[ type]) {
          CORBA::string_free( this->typeNames_[ type]); // Was created by CORBA::string_dup()
        }
        this->typeNames_[ type] = typeSupport->get_type_name();
      }
      break;

    case Types::flightStatus:
      {
        typedef ::UATM::flightStatusTypeSupportImpl TypeSupport;

        TypeSupport* typeSupport = new TypeSupport();
        if( RETCODE_OK != typeSupport->register_type( participant, 0)) {
          throw BadRegisterException();
        }

        if( this->typeNames_[ type]) {
          CORBA::string_free( this->typeNames_[ type]); // Was created by CORBA::string_dup()
        }
        this->typeNames_[ type] = typeSupport->get_type_name();
      }
      break;

    case Types::airspaceAlert:
      {
        typedef ::UATM::airspaceAlertTypeSupportImpl TypeSupport;

        TypeSupport* typeSupport = new TypeSupport();
        if( RETCODE_OK != typeSupport->register_type( participant, 0)) {
          throw BadRegisterException();
        }

        if( this->typeNames_[ type]) {
          CORBA::string_free( this->typeNames_[ type]); // Was created by CORBA::string_dup()
        }
        this->typeNames_[ type] = typeSupport->get_type_name();
      }
      break;

    case Types::fleetDirectives:
      {
        typedef ::UATM::fleetDirectivesTypeSupportImpl TypeSupport;

        TypeSupport* typeSupport = new TypeSupport();
        if( RETCODE_OK != typeSupport->register_type( participant, 0)) {
          throw BadRegisterException();
        }

        if( this->typeNames_[ type]) {
          CORBA::string_free( this->typeNames_[ type]); // Was created by CORBA::string_dup()
        }
        this->typeNames_[ type] = typeSupport->get_type_name();
      }
      break;

    case Types::weatherUpdate:
      {
        typedef ::UATM::weatherUpdateTypeSupportImpl TypeSupport;

        TypeSupport* typeSupport = new TypeSupport();
        if( RETCODE_OK != typeSupport->register_type( participant, 0)) {
          throw BadRegisterException();
        }

        if( this->typeNames_[ type]) {
          CORBA::string_free( this->typeNames_[ type]); // Was created by CORBA::string_dup()
        }
        this->typeNames_[ type] = typeSupport->get_type_name();
      }
      break;

    case Types::tolPadStatus:
      {
        typedef ::UATM::tolPadStatusTypeSupportImpl TypeSupport;

        TypeSupport* typeSupport = new TypeSupport();
        if( RETCODE_OK != typeSupport->register_type( participant, 0)) {
          throw BadRegisterException();
        }

        if( this->typeNames_[ type]) {
          CORBA::string_free( this->typeNames_[ type]); // Was created by CORBA::string_dup()
        }
        this->typeNames_[ type] = typeSupport->get_type_name();
      }
      break;

    case Types::trafficFlowsInfo:
      {
        typedef ::UATM::trafficFlowsInfoTypeSupportImpl TypeSupport;

        TypeSupport* typeSupport = new TypeSupport();
        if( RETCODE_OK != typeSupport->register_type( participant, 0)) {
          throw BadRegisterException();
        }

        if( this->typeNames_[ type]) {
          CORBA::string_free( this->typeNames_[ type]); // Was created by CORBA::string_dup()
        }
        this->typeNames_[ type] = typeSupport->get_type_name();
      }
      break;

  default:
    throw NoTypeException();
    break;
  }
}

inline
void
Elements::Data::loadDomains()
{
  this->domains_[ Participants::evtolVehicleDP] = 0;
  this->domains_[ Participants::weatherSystemDP] = 0;
  this->domains_[ Participants::fleetOperatorDP] = 0;
  this->domains_[ Participants::uaspDP] = 0;
  this->domains_[ Participants::skyportOperatorDP] = 0;
}

inline
void
Elements::Data::loadTopics()
{
  this->topicNames_[Topics::UATM__uatmDiagram__vehicleState] = "vehicleState";
  this->cfTopics_[Topics::UATM__uatmDiagram__vehicleState] = ContentFilteredTopics::LAST_INDEX;
  this->multiTopics_[Topics::UATM__uatmDiagram__vehicleState] = MultiTopics::LAST_INDEX;
  this->topicNames_[Topics::UATM__uatmDiagram__tacticalCommand] = "tacticalCommand";
  this->cfTopics_[Topics::UATM__uatmDiagram__tacticalCommand] = ContentFilteredTopics::LAST_INDEX;
  this->multiTopics_[Topics::UATM__uatmDiagram__tacticalCommand] = MultiTopics::LAST_INDEX;
  this->topicNames_[Topics::UATM__uatmDiagram__airspaceAlert] = "airspaceAlert";
  this->cfTopics_[Topics::UATM__uatmDiagram__airspaceAlert] = ContentFilteredTopics::LAST_INDEX;
  this->multiTopics_[Topics::UATM__uatmDiagram__airspaceAlert] = MultiTopics::LAST_INDEX;
  this->topicNames_[Topics::UATM__uatmDiagram__weatherUpdate] = "weatherUpdate";
  this->cfTopics_[Topics::UATM__uatmDiagram__weatherUpdate] = ContentFilteredTopics::LAST_INDEX;
  this->multiTopics_[Topics::UATM__uatmDiagram__weatherUpdate] = MultiTopics::LAST_INDEX;
  this->topicNames_[Topics::UATM__uatmDiagram__flightStatus] = "flightStatus";
  this->cfTopics_[Topics::UATM__uatmDiagram__flightStatus] = ContentFilteredTopics::LAST_INDEX;
  this->multiTopics_[Topics::UATM__uatmDiagram__flightStatus] = MultiTopics::LAST_INDEX;
  this->topicNames_[Topics::UATM__uatmDiagram__fleetDirectives] = "fleetDirectives";
  this->cfTopics_[Topics::UATM__uatmDiagram__fleetDirectives] = ContentFilteredTopics::LAST_INDEX;
  this->multiTopics_[Topics::UATM__uatmDiagram__fleetDirectives] = MultiTopics::LAST_INDEX;
  this->topicNames_[Topics::UATM__uatmDiagram__tolPadStatus] = "tolPadStatus";
  this->cfTopics_[Topics::UATM__uatmDiagram__tolPadStatus] = ContentFilteredTopics::LAST_INDEX;
  this->multiTopics_[Topics::UATM__uatmDiagram__tolPadStatus] = MultiTopics::LAST_INDEX;
  this->topicNames_[Topics::UATM__uatmDiagram__trafficFlowsInfo] = "trafficFlowsInfo";
  this->cfTopics_[Topics::UATM__uatmDiagram__trafficFlowsInfo] = ContentFilteredTopics::LAST_INDEX;
  this->multiTopics_[Topics::UATM__uatmDiagram__trafficFlowsInfo] = MultiTopics::LAST_INDEX;
}

inline
std::string
Elements::Data::transportConfigName(Participants::Values which)
{
  return participantTxCfgNames_[which];
}

inline
std::string
Elements::Data::transportConfigName(Publishers::Values which)
{
  return publisherTxCfgNames_[which];
}

inline
std::string
Elements::Data::transportConfigName(Subscribers::Values which)
{
  return subscriberTxCfgNames_[which];
}

inline
std::string
Elements::Data::transportConfigName(DataWriters::Values which)
{
  return writerTxCfgNames_[which];
}

inline
std::string
Elements::Data::transportConfigName(DataReaders::Values which)
{
  return readerTxCfgNames_[which];
}

inline
void
Elements::Data::loadTransportConfigNames()
{
}

inline
void
Elements::Data::loadMaps()
{
  this->publisherParticipants_[ Publishers::evtolVehiclePb] = Participants::evtolVehicleDP;
  this->publisherParticipants_[ Publishers::weatherSystemPB] = Participants::weatherSystemDP;
  this->publisherParticipants_[ Publishers::fleetOperatorPb] = Participants::fleetOperatorDP;
  this->publisherParticipants_[ Publishers::uaspPB] = Participants::uaspDP;
  this->publisherParticipants_[ Publishers::skyportOperatorPB] = Participants::skyportOperatorDP;

  this->subscriberParticipants_[ Subscribers::evtolVehicleSb] = Participants::evtolVehicleDP;
  this->subscriberParticipants_[ Subscribers::fleetOperatorSb] = Participants::fleetOperatorDP;
  this->subscriberParticipants_[ Subscribers::uaspSB] = Participants::uaspDP;
  this->subscriberParticipants_[ Subscribers::skyportOperatorSB] = Participants::skyportOperatorDP;

  this->types_[ Topics::UATM__uatmDiagram__vehicleState] = Types::vehicleState;
  this->types_[ Topics::UATM__uatmDiagram__tacticalCommand] = Types::tacticalCommand;
  this->types_[ Topics::UATM__uatmDiagram__airspaceAlert] = Types::airspaceAlert;
  this->types_[ Topics::UATM__uatmDiagram__weatherUpdate] = Types::weatherUpdate;
  this->types_[ Topics::UATM__uatmDiagram__flightStatus] = Types::flightStatus;
  this->types_[ Topics::UATM__uatmDiagram__fleetDirectives] = Types::fleetDirectives;
  this->types_[ Topics::UATM__uatmDiagram__tolPadStatus] = Types::tolPadStatus;
  this->types_[ Topics::UATM__uatmDiagram__trafficFlowsInfo] = Types::trafficFlowsInfo;

  this->writerTopics_[ DataWriters::vehicleStateDW] = Topics::UATM__uatmDiagram__vehicleState;
  this->writerTopics_[ DataWriters::flightStatusDW] = Topics::UATM__uatmDiagram__flightStatus;
  this->writerTopics_[ DataWriters::weatherUpdateDW] = Topics::UATM__uatmDiagram__weatherUpdate;
  this->writerTopics_[ DataWriters::fleetDirectivesFoDW] = Topics::UATM__uatmDiagram__fleetDirectives;
  this->writerTopics_[ DataWriters::tacticalCommandDW] = Topics::UATM__uatmDiagram__tacticalCommand;
  this->writerTopics_[ DataWriters::airspaceAlertDW] = Topics::UATM__uatmDiagram__airspaceAlert;
  this->writerTopics_[ DataWriters::fleetDirectivesUaspDW] = Topics::UATM__uatmDiagram__fleetDirectives;
  this->writerTopics_[ DataWriters::tolPadStatusDW] = Topics::UATM__uatmDiagram__tolPadStatus;
  this->writerTopics_[ DataWriters::trafficFlowsDW] = Topics::UATM__uatmDiagram__trafficFlowsInfo;

  this->readerTopics_[ DataReaders::tacticalCommandEvtolDR] = Topics::UATM__uatmDiagram__tacticalCommand;
  this->readerTopics_[ DataReaders::airspaceAlertDR] = Topics::UATM__uatmDiagram__airspaceAlert;
  this->readerTopics_[ DataReaders::fleetDirectivesDR] = Topics::UATM__uatmDiagram__fleetDirectives;
  this->readerTopics_[ DataReaders::vehicleStateFoDR] = Topics::UATM__uatmDiagram__vehicleState;
  this->readerTopics_[ DataReaders::flightStatusDR] = Topics::UATM__uatmDiagram__flightStatus;
  this->readerTopics_[ DataReaders::vehicleStateUaspDR] = Topics::UATM__uatmDiagram__vehicleState;
  this->readerTopics_[ DataReaders::trafficFlowsDR] = Topics::UATM__uatmDiagram__trafficFlowsInfo;
  this->readerTopics_[ DataReaders::weatherUpdateDR] = Topics::UATM__uatmDiagram__weatherUpdate;
  this->readerTopics_[ DataReaders::vehicleStateSkpDR] = Topics::UATM__uatmDiagram__vehicleState;
  this->readerTopics_[ DataReaders::tacticalCommandSkpDR] = Topics::UATM__uatmDiagram__tacticalCommand;

  this->publishers_[ DataWriters::vehicleStateDW] = Publishers::evtolVehiclePb;
  this->publishers_[ DataWriters::flightStatusDW] = Publishers::evtolVehiclePb;
  this->publishers_[ DataWriters::weatherUpdateDW] = Publishers::weatherSystemPB;
  this->publishers_[ DataWriters::fleetDirectivesFoDW] = Publishers::fleetOperatorPb;
  this->publishers_[ DataWriters::tacticalCommandDW] = Publishers::uaspPB;
  this->publishers_[ DataWriters::airspaceAlertDW] = Publishers::uaspPB;
  this->publishers_[ DataWriters::fleetDirectivesUaspDW] = Publishers::uaspPB;
  this->publishers_[ DataWriters::tolPadStatusDW] = Publishers::skyportOperatorPB;
  this->publishers_[ DataWriters::trafficFlowsDW] = Publishers::skyportOperatorPB;

  this->subscribers_[ DataReaders::tacticalCommandEvtolDR] = Subscribers::evtolVehicleSb;
  this->subscribers_[ DataReaders::airspaceAlertDR] = Subscribers::evtolVehicleSb;
  this->subscribers_[ DataReaders::fleetDirectivesDR] = Subscribers::evtolVehicleSb;
  this->subscribers_[ DataReaders::vehicleStateFoDR] = Subscribers::fleetOperatorSb;
  this->subscribers_[ DataReaders::flightStatusDR] = Subscribers::fleetOperatorSb;
  this->subscribers_[ DataReaders::vehicleStateUaspDR] = Subscribers::uaspSB;
  this->subscribers_[ DataReaders::trafficFlowsDR] = Subscribers::uaspSB;
  this->subscribers_[ DataReaders::weatherUpdateDR] = Subscribers::uaspSB;
  this->subscribers_[ DataReaders::vehicleStateSkpDR] = Subscribers::skyportOperatorSB;
  this->subscribers_[ DataReaders::tacticalCommandSkpDR] = Subscribers::skyportOperatorSB;

}

inline
void
Elements::Data::buildParticipantsQos()
{
  DomainParticipantQos participantQos;
  Participants::Values participant;
    
  participant = Participants::evtolVehicleDP;
  participantQos = TheServiceParticipant->initial_DomainParticipantQos();

  DDS::PropertySeq& propsEV = participantQos.property.value;
  CORBA::ULong lengthEV = propsEV.length();
  propsEV.length(lengthEV + 6);
  propsEV[lengthEV].name = CORBA::string_dup(DDS::Security::Properties::AuthIdentityCA);
  propsEV[lengthEV].value = (("file:security1/certs/identity/ca_cert.pem"));
  propsEV[lengthEV].propagate = false;
  propsEV[lengthEV + 1].name = CORBA::string_dup(DDS::Security::Properties::AuthIdentityCertificate);
  propsEV[lengthEV + 1].value = (("file:security1/certs/identity/evtol_cert.pem"));
  propsEV[lengthEV + 1].propagate = false;
  propsEV[lengthEV + 2].name = CORBA::string_dup(DDS::Security::Properties::AuthPrivateKey);
  propsEV[lengthEV + 2].value = (("file:security1/certs/identity/evtol_key.pem"));
  propsEV[lengthEV + 2].propagate = false;
  propsEV[lengthEV + 3].name = CORBA::string_dup(DDS::Security::Properties::AccessPermissionsCA);
  propsEV[lengthEV + 3].value = (("file:security1/certs/permissions/permissions_ca_cert.pem"));
  propsEV[lengthEV + 3].propagate = false;
  propsEV[lengthEV + 4].name = CORBA::string_dup(DDS::Security::Properties::AccessGovernance);
  propsEV[lengthEV + 4].value = (("file:security1/governance/governance_signed.p7s"));
  propsEV[lengthEV + 4].propagate = false;
  propsEV[lengthEV + 5].name = CORBA::string_dup(DDS::Security::Properties::AccessPermissions);
  propsEV[lengthEV + 5].value = ("file:security1/permissions/evtol_permissions.p7s");
  propsEV[lengthEV + 5].propagate = false;

  this->participantsQos_[ participant] = participantQos;



  participant = Participants::weatherSystemDP;
  participantQos = TheServiceParticipant->initial_DomainParticipantQos();

  DDS::PropertySeq& propsWS = participantQos.property.value;
  CORBA::ULong lengthWS = propsWS.length();
  propsWS.length(lengthWS + 6);
  propsWS[lengthWS].name = CORBA::string_dup(DDS::Security::Properties::AuthIdentityCA);
  propsWS[lengthWS].value = (("file:security1/certs/identity/ca_cert.pem"));
  propsWS[lengthWS].propagate = false;
  propsWS[lengthWS + 1].name = CORBA::string_dup(DDS::Security::Properties::AuthIdentityCertificate);
  propsWS[lengthWS + 1].value = (("file:security1/certs/identity/weather_cert.pem"));
  propsWS[lengthWS + 1].propagate = false;
  propsWS[lengthWS + 2].name = CORBA::string_dup(DDS::Security::Properties::AuthPrivateKey);
  propsWS[lengthWS + 2].value = (("file:security1/certs/identity/weather_key.pem"));
  propsWS[lengthWS + 2].propagate = false;
  propsWS[lengthWS + 3].name = CORBA::string_dup(DDS::Security::Properties::AccessPermissionsCA);
  propsWS[lengthWS + 3].value = (("file:security1/certs/permissions/permissions_ca_cert.pem"));
  propsWS[lengthWS + 3].propagate = false;
  propsWS[lengthWS + 4].name = CORBA::string_dup(DDS::Security::Properties::AccessGovernance);
  propsWS[lengthWS + 4].value = (("file:security1/governance/governance_signed.p7s"));
  propsWS[lengthWS + 4].propagate = false;
  propsWS[lengthWS + 5].name = CORBA::string_dup(DDS::Security::Properties::AccessPermissions);
  propsWS[lengthWS + 5].value = ("file:security1/permissions/weather_permissions.p7s");
  propsWS[lengthWS + 5].propagate = false;

  this->participantsQos_[ participant] = participantQos;



  participant = Participants::fleetOperatorDP;
  participantQos = TheServiceParticipant->initial_DomainParticipantQos();

  DDS::PropertySeq& propsFO = participantQos.property.value;
  CORBA::ULong lengthFO = propsFO.length();
  propsFO.length(lengthFO + 6);
  propsFO[lengthFO].name = CORBA::string_dup(DDS::Security::Properties::AuthIdentityCA);
  propsFO[lengthFO].value = (("file:security1/certs/identity/ca_cert.pem"));
  propsFO[lengthFO].propagate = false;
  propsFO[lengthFO + 1].name = CORBA::string_dup(DDS::Security::Properties::AuthIdentityCertificate);
  propsFO[lengthFO + 1].value = (("file:security1/certs/identity/fleet_cert.pem"));
  propsFO[lengthFO + 1].propagate = false;
  propsFO[lengthFO + 2].name = CORBA::string_dup(DDS::Security::Properties::AuthPrivateKey);
  propsFO[lengthFO + 2].value = (("file:security1/certs/identity/fleet_key.pem"));
  propsFO[lengthFO + 2].propagate = false;
  propsFO[lengthFO + 3].name = CORBA::string_dup(DDS::Security::Properties::AccessPermissionsCA);
  propsFO[lengthFO + 3].value = (("file:security1/certs/permissions/permissions_ca_cert.pem"));
  propsFO[lengthFO + 3].propagate = false;
  propsFO[lengthFO + 4].name = CORBA::string_dup(DDS::Security::Properties::AccessGovernance);
  propsFO[lengthFO + 4].value = (("file:security1/governance/governance_signed.p7s"));
  propsFO[lengthFO + 4].propagate = false;
  propsFO[lengthFO + 5].name = CORBA::string_dup(DDS::Security::Properties::AccessPermissions);
  propsFO[lengthFO + 5].value = ("file:security1/permissions/fleet_permissions.p7s");
  propsFO[lengthFO + 5].propagate = false;

  this->participantsQos_[ participant] = participantQos;



  participant = Participants::uaspDP;
  participantQos = TheServiceParticipant->initial_DomainParticipantQos();

  DDS::PropertySeq& propsUS = participantQos.property.value;
  CORBA::ULong lengthUS = propsUS.length();
  propsUS.length(lengthUS + 6);
  propsUS[lengthUS].name = CORBA::string_dup(DDS::Security::Properties::AuthIdentityCA);
  propsUS[lengthUS].value = (("file:security1/certs/identity/ca_cert.pem"));
  propsUS[lengthUS].propagate = false;
  propsUS[lengthUS + 1].name = CORBA::string_dup(DDS::Security::Properties::AuthIdentityCertificate);
  propsUS[lengthUS + 1].value = (("file:security1/certs/identity/uasp_cert.pem"));
  propsUS[lengthUS + 1].propagate = false;
  propsUS[lengthUS + 2].name = CORBA::string_dup(DDS::Security::Properties::AuthPrivateKey);
  propsUS[lengthUS + 2].value = (("file:security1/certs/identity/uasp_key.pem"));
  propsUS[lengthUS + 2].propagate = false;
  propsUS[lengthUS + 3].name = CORBA::string_dup(DDS::Security::Properties::AccessPermissionsCA);
  propsUS[lengthUS + 3].value = (("file:security1/certs/permissions/permissions_ca_cert.pem"));
  propsUS[lengthUS + 3].propagate = false;
  propsUS[lengthUS + 4].name = CORBA::string_dup(DDS::Security::Properties::AccessGovernance);
  propsUS[lengthUS + 4].value = (("file:security1/governance/governance_signed.p7s"));
  propsUS[lengthUS + 4].propagate = false;
  propsUS[lengthUS + 5].name = CORBA::string_dup(DDS::Security::Properties::AccessPermissions);
  propsUS[lengthUS + 5].value = ("file:security1/permissions/uasp_permissions.p7s");
  propsUS[lengthUS + 5].propagate = false;
  
  this->participantsQos_[ participant] = participantQos;



  participant = Participants::skyportOperatorDP;
  participantQos = TheServiceParticipant->initial_DomainParticipantQos();

  DDS::PropertySeq& propsSO = participantQos.property.value;
  CORBA::ULong lengthSO = propsSO.length();
  propsSO.length(lengthSO + 6);
  propsSO[lengthSO].name = CORBA::string_dup(DDS::Security::Properties::AuthIdentityCA);
  propsSO[lengthSO].value = (("file:security1/certs/identity/ca_cert.pem"));
  propsSO[lengthSO].propagate = false;
  propsSO[lengthSO + 1].name = CORBA::string_dup(DDS::Security::Properties::AuthIdentityCertificate);
  propsSO[lengthSO + 1].value = (("file:security1/certs/identity/skyport_cert.pem"));
  propsSO[lengthSO + 1].propagate = false;
  propsSO[lengthSO + 2].name = CORBA::string_dup(DDS::Security::Properties::AuthPrivateKey);
  propsSO[lengthSO + 2].value = (("file:security1/certs/identity/skyport_key.pem"));
  propsSO[lengthSO + 2].propagate = false;
  propsSO[lengthSO + 3].name = CORBA::string_dup(DDS::Security::Properties::AccessPermissionsCA);
  propsSO[lengthSO + 3].value = (("file:security1/certs/permissions/permissions_ca_cert.pem"));
  propsSO[lengthSO + 3].propagate = false;
  propsSO[lengthSO + 4].name = CORBA::string_dup(DDS::Security::Properties::AccessGovernance);
  propsSO[lengthSO + 4].value = (("file:security1/governance/governance_signed.p7s"));
  propsSO[lengthSO + 4].propagate = false;
  propsSO[lengthSO + 5].name = CORBA::string_dup(DDS::Security::Properties::AccessPermissions);
  propsSO[lengthSO + 5].value = ("file:security1/permissions/skyport_permissions.p7s");
  propsSO[lengthSO + 5].propagate = false;

  this->participantsQos_[ participant] = participantQos;
}


inline
void
Elements::Data::buildTopicsQos()
{
  TopicQos       topicQos;
  Topics::Values topic;
    
  topic    = Topics::UATM__uatmDiagram__vehicleState;
  topicQos = TheServiceParticipant->initial_TopicQos();
    
  topicQos.deadline.period.sec = 0;
  topicQos.deadline.period.nanosec = 200000000;
  topicQos.history.depth = 1;
  topicQos.history.kind = KEEP_LAST_HISTORY_QOS;
  topicQos.reliability.kind = BEST_EFFORT_RELIABILITY_QOS;
  topicQos.reliability.max_blocking_time.sec = 2147483647;
  topicQos.reliability.max_blocking_time.nanosec = 2147483647;
  topicQos.durability.kind = VOLATILE_DURABILITY_QOS;
  this->topicsQos_[ topic] = topicQos;

  topic    = Topics::UATM__uatmDiagram__tacticalCommand;
  topicQos = TheServiceParticipant->initial_TopicQos();
    
  topicQos.durability.kind = TRANSIENT_LOCAL_DURABILITY_QOS;
  topicQos.history.depth = 1;
  topicQos.history.kind = KEEP_ALL_HISTORY_QOS;
  topicQos.reliability.kind = RELIABLE_RELIABILITY_QOS;
  topicQos.reliability.max_blocking_time.sec = 2147483647;
  topicQos.reliability.max_blocking_time.nanosec = 2147483647;
  this->topicsQos_[ topic] = topicQos;

  topic    = Topics::UATM__uatmDiagram__airspaceAlert;
  topicQos = TheServiceParticipant->initial_TopicQos();
    
  topicQos.durability.kind = TRANSIENT_LOCAL_DURABILITY_QOS;
  topicQos.history.depth = 1;
  topicQos.history.kind = KEEP_LAST_HISTORY_QOS;
  topicQos.reliability.kind = RELIABLE_RELIABILITY_QOS;
  topicQos.reliability.max_blocking_time.sec = 2147483647;
  topicQos.reliability.max_blocking_time.nanosec = 2147483647;
  this->topicsQos_[ topic] = topicQos;

  topic    = Topics::UATM__uatmDiagram__weatherUpdate;
  topicQos = TheServiceParticipant->initial_TopicQos();
    
  topicQos.durability.kind = TRANSIENT_LOCAL_DURABILITY_QOS;
  topicQos.history.depth = 1;
  topicQos.history.kind = KEEP_LAST_HISTORY_QOS;
  topicQos.reliability.kind = RELIABLE_RELIABILITY_QOS;
  topicQos.reliability.max_blocking_time.sec = 2147483647;
  topicQos.reliability.max_blocking_time.nanosec = 2147483647;
  this->topicsQos_[ topic] = topicQos;

  topic    = Topics::UATM__uatmDiagram__flightStatus;
  topicQos = TheServiceParticipant->initial_TopicQos();
    
  topicQos.deadline.period.sec = 0;
  topicQos.deadline.period.nanosec = 200000000;
  topicQos.history.depth = 1;
  topicQos.history.kind = KEEP_LAST_HISTORY_QOS;
  topicQos.reliability.kind = BEST_EFFORT_RELIABILITY_QOS;
  topicQos.reliability.max_blocking_time.sec = 2147483647;
  topicQos.reliability.max_blocking_time.nanosec = 2147483647;
  topicQos.durability.kind = VOLATILE_DURABILITY_QOS;
  this->topicsQos_[ topic] = topicQos;

  topic    = Topics::UATM__uatmDiagram__fleetDirectives;
  topicQos = TheServiceParticipant->initial_TopicQos();
    
  topicQos.durability.kind = TRANSIENT_LOCAL_DURABILITY_QOS;
  topicQos.history.depth = 1;
  topicQos.history.kind = KEEP_ALL_HISTORY_QOS;
  topicQos.reliability.kind = RELIABLE_RELIABILITY_QOS;
  topicQos.reliability.max_blocking_time.sec = 2147483647;
  topicQos.reliability.max_blocking_time.nanosec = 2147483647;
  this->topicsQos_[ topic] = topicQos;

  topic    = Topics::UATM__uatmDiagram__tolPadStatus;
  topicQos = TheServiceParticipant->initial_TopicQos();
    
  topicQos.durability.kind = TRANSIENT_LOCAL_DURABILITY_QOS;
  topicQos.history.depth = 1;
  topicQos.history.kind = KEEP_LAST_HISTORY_QOS;
  topicQos.reliability.kind = RELIABLE_RELIABILITY_QOS;
  topicQos.reliability.max_blocking_time.sec = 2147483647;
  topicQos.reliability.max_blocking_time.nanosec = 2147483647;
  this->topicsQos_[ topic] = topicQos;

  topic    = Topics::UATM__uatmDiagram__trafficFlowsInfo;
  topicQos = TheServiceParticipant->initial_TopicQos();
    
  topicQos.durability.kind = TRANSIENT_LOCAL_DURABILITY_QOS;
  topicQos.history.depth = 1;
  topicQos.history.kind = KEEP_LAST_HISTORY_QOS;
  topicQos.reliability.kind = RELIABLE_RELIABILITY_QOS;
  topicQos.reliability.max_blocking_time.sec = 2147483647;
  topicQos.reliability.max_blocking_time.nanosec = 2147483647;
  this->topicsQos_[ topic] = topicQos;
}

inline
void
Elements::Data::buildPublishersQos()
{
  PublisherQos       publisherQos;
  Publishers::Values publisher;

  publisher    = Publishers::evtolVehiclePb;
  publisherQos = TheServiceParticipant->initial_PublisherQos();
  this->publishersQos_[ publisher] = publisherQos;

  publisher    = Publishers::weatherSystemPB;
  publisherQos = TheServiceParticipant->initial_PublisherQos();
  this->publishersQos_[ publisher] = publisherQos;

  publisher    = Publishers::fleetOperatorPb;
  publisherQos = TheServiceParticipant->initial_PublisherQos();
  this->publishersQos_[ publisher] = publisherQos;

  publisher    = Publishers::uaspPB;
  publisherQos = TheServiceParticipant->initial_PublisherQos();
  this->publishersQos_[ publisher] = publisherQos;

  publisher    = Publishers::skyportOperatorPB;
  publisherQos = TheServiceParticipant->initial_PublisherQos();
  this->publishersQos_[ publisher] = publisherQos;
}

inline
void
Elements::Data::buildSubscribersQos()
{
  SubscriberQos       subscriberQos;
  Subscribers::Values subscriber;

  subscriber    = Subscribers::evtolVehicleSb;
  subscriberQos = TheServiceParticipant->initial_SubscriberQos();
  this->subscribersQos_[ subscriber] = subscriberQos;

  subscriber    = Subscribers::fleetOperatorSb;
  subscriberQos = TheServiceParticipant->initial_SubscriberQos();
  this->subscribersQos_[ subscriber] = subscriberQos;

  subscriber    = Subscribers::uaspSB;
  subscriberQos = TheServiceParticipant->initial_SubscriberQos();
  this->subscribersQos_[ subscriber] = subscriberQos;

  subscriber    = Subscribers::skyportOperatorSB;
  subscriberQos = TheServiceParticipant->initial_SubscriberQos();
  this->subscribersQos_[ subscriber] = subscriberQos;
}

inline
void
Elements::Data::buildPublicationsQos()
{
  DataWriters::Values  writer;
  DataWriterQos        writerQos;

  writer    = DataWriters::vehicleStateDW;
  writerQos = TheServiceParticipant->initial_DataWriterQos();
  this->writersQos_[ writer] = writerQos;
  this->writerCopyTopicQos_[writer] = true;

  writer    = DataWriters::flightStatusDW;
  writerQos = TheServiceParticipant->initial_DataWriterQos();
  this->writersQos_[ writer] = writerQos;
  this->writerCopyTopicQos_[writer] = true;

  writer    = DataWriters::weatherUpdateDW;
  writerQos = TheServiceParticipant->initial_DataWriterQos();
  this->writersQos_[ writer] = writerQos;
  this->writerCopyTopicQos_[writer] = true;

  writer    = DataWriters::fleetDirectivesFoDW;
  writerQos = TheServiceParticipant->initial_DataWriterQos();
  this->writersQos_[ writer] = writerQos;
  this->writerCopyTopicQos_[writer] = true;

  writer    = DataWriters::tacticalCommandDW;
  writerQos = TheServiceParticipant->initial_DataWriterQos();
  this->writersQos_[ writer] = writerQos;
  this->writerCopyTopicQos_[writer] = true;

  writer    = DataWriters::airspaceAlertDW;
  writerQos = TheServiceParticipant->initial_DataWriterQos();
  this->writersQos_[ writer] = writerQos;
  this->writerCopyTopicQos_[writer] = true;

  writer    = DataWriters::fleetDirectivesUaspDW;
  writerQos = TheServiceParticipant->initial_DataWriterQos();
  this->writersQos_[ writer] = writerQos;
  this->writerCopyTopicQos_[writer] = true;

  writer    = DataWriters::tolPadStatusDW;
  writerQos = TheServiceParticipant->initial_DataWriterQos();
  this->writersQos_[ writer] = writerQos;
  this->writerCopyTopicQos_[writer] = true;

  writer    = DataWriters::trafficFlowsDW;
  writerQos = TheServiceParticipant->initial_DataWriterQos();
  this->writersQos_[ writer] = writerQos;
  this->writerCopyTopicQos_[writer] = true;
}

inline
void
Elements::Data::buildSubscriptionsQos()
{
  DataReaders::Values  reader;
  DataReaderQos        readerQos;

  reader    = DataReaders::tacticalCommandEvtolDR;
  readerQos = TheServiceParticipant->initial_DataReaderQos();
  this->readersQos_[ reader] = readerQos;
  this->readerCopyTopicQos_[reader] = true;

  reader    = DataReaders::airspaceAlertDR;
  readerQos = TheServiceParticipant->initial_DataReaderQos();
  this->readersQos_[ reader] = readerQos;
  this->readerCopyTopicQos_[reader] = true;

  reader    = DataReaders::fleetDirectivesDR;
  readerQos = TheServiceParticipant->initial_DataReaderQos();
  this->readersQos_[ reader] = readerQos;
  this->readerCopyTopicQos_[reader] = true;

  reader    = DataReaders::vehicleStateFoDR;
  readerQos = TheServiceParticipant->initial_DataReaderQos();
  this->readersQos_[ reader] = readerQos;
  this->readerCopyTopicQos_[reader] = true;

  reader    = DataReaders::flightStatusDR;
  readerQos = TheServiceParticipant->initial_DataReaderQos();
  this->readersQos_[ reader] = readerQos;
  this->readerCopyTopicQos_[reader] = true;

  reader    = DataReaders::vehicleStateUaspDR;
  readerQos = TheServiceParticipant->initial_DataReaderQos();
  this->readersQos_[ reader] = readerQos;
  this->readerCopyTopicQos_[reader] = true;

  reader    = DataReaders::trafficFlowsDR;
  readerQos = TheServiceParticipant->initial_DataReaderQos();
  this->readersQos_[ reader] = readerQos;
  this->readerCopyTopicQos_[reader] = true;

  reader    = DataReaders::weatherUpdateDR;
  readerQos = TheServiceParticipant->initial_DataReaderQos();
  this->readersQos_[ reader] = readerQos;
  this->readerCopyTopicQos_[reader] = true;

  reader    = DataReaders::vehicleStateSkpDR;
  readerQos = TheServiceParticipant->initial_DataReaderQos();
  this->readersQos_[ reader] = readerQos;
  this->readerCopyTopicQos_[reader] = true;

  reader    = DataReaders::tacticalCommandSkpDR;
  readerQos = TheServiceParticipant->initial_DataReaderQos();
  this->readersQos_[ reader] = readerQos;
  this->readerCopyTopicQos_[reader] = true;
}


inline
void
Elements::Data::copyPublicationQos(
  DataWriters::Values which,
  DataWriterQos&  
)
{
  switch(which) {
    case DataWriters::vehicleStateDW:
      break;

    case DataWriters::flightStatusDW:
      break;

    case DataWriters::weatherUpdateDW:
      break;

    case DataWriters::fleetDirectivesFoDW:
      break;

    case DataWriters::tacticalCommandDW:
      break;

    case DataWriters::airspaceAlertDW:
      break;

    case DataWriters::fleetDirectivesUaspDW:
      break;

    case DataWriters::tolPadStatusDW:
      break;

    case DataWriters::trafficFlowsDW:
      break;

    default:
      throw NoWriterException();
  }
}

inline
void
Elements::Data::copySubscriptionQos(
  DataReaders::Values which,
  DataReaderQos&  
)
{
  switch(which) {
    case DataReaders::tacticalCommandEvtolDR:
      break;

    case DataReaders::airspaceAlertDR:
      break;

    case DataReaders::fleetDirectivesDR:
      break;

    case DataReaders::vehicleStateFoDR:
      break;

    case DataReaders::flightStatusDR:
      break;

    case DataReaders::vehicleStateUaspDR:
      break;

    case DataReaders::trafficFlowsDR:
      break;

    case DataReaders::weatherUpdateDR:
      break;

    case DataReaders::vehicleStateSkpDR:
      break;

    case DataReaders::tacticalCommandSkpDR:
      break;

    default:
      throw NoReaderException();
  }
}
} // End namespace uatmDiagram
} // End namespace UATM

} // End namespace Model
} // End namespace OpenDDS
