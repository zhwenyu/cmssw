#ifndef CSC_CHAMBER_MAP_SRC_IMPL_H
#define CSC_CHAMBER_MAP_SRC_IMPL_H

#include <vector>
#include <string>
#include <iostream>
#include <typeinfo>

#include "CondCore/PopCon/interface/PopConSourceHandler.h"
#include "CondCore/PopCon/interface/LogReader.h"
#include "CondFormats/CSCObjects/interface/CSCobject.h"
#include "CondFormats/DataRecord/interface/CSCChamberMapRcd.h"
#include "FWCore/Framework/interface/ESHandle.h"
#include "FWCore/Framework/interface/Event.h"
#include "DataFormats/Common/interface/Handle.h"
#include "FWCore/Framework/interface/EventSetup.h"
#include "CSCChamberMapValues.h"

namespace popcon
{
	class CSCChamberMapImpl : public popcon::PopConSourceHandler<CSCChamberMap>
	{

		public:
			void getNewObjects();
			~CSCChamberMapImpl(); 
			CSCChamberMapImpl(const std::string&,
					    const std::string&, 
					    const edm::Event& evt, 
					    const edm::EventSetup& est, 
					    std::string&);
		

		private:
			std::string m_pop_connect; //connect string to popcon metaschema
			std::string m_name;
			std::string m_cs;
			const CSCChamberMap * mycham_map;
			LogReader* lgrdr;
	};
}
#endif
