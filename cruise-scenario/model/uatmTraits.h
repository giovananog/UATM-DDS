#ifndef UATM_TRAITS_H
#define UATM_TRAITS_H
#include "uatm_T.h"
#include <model/TransportDirectives.h>

namespace UATM {
namespace uatmDiagram {

  struct uatm_Export DefaultuatmTraits {
    DefaultuatmTraits();
    virtual ~DefaultuatmTraits();
    std::string configName(const std::string& modeledName) const;
  };

  typedef OpenDDS::Model::Service< OpenDDS::Model::UATM::uatmDiagram::Elements, DefaultuatmTraits> DefaultuatmType;
}
}

#endif
