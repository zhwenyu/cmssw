#include "OnlineDB/CSCCondDB/interface/CSCDDUMapHandler.h"
#include "CondCore/DBOutputService/interface/PoolDBOutputService.h"
#include "FWCore/ServiceRegistry/interface/Service.h"

popcon::CSCDDUMapImpl::CSCDDUMapImpl(const std::string& name, 
						 const std::string& cstring,
						 const edm::Event& evt, 
						 const edm::EventSetup& est, 
						 std::string& pconnect) : popcon::PopConSourceHandler<CSCDDUMap>(name,cstring,evt,est), m_pop_connect(pconnect)
{
	m_name = name;
	m_cs = cstring;
	lgrdr = new LogReader(m_pop_connect);
	
}

popcon::CSCDDUMapImpl::~CSCDDUMapImpl()
{
}

void popcon::CSCDDUMapImpl::getNewObjects()
{

	std::cout << "------- CSC src - > getNewObjects\n";
	
	//check whats already inside of database
	
	std::map<std::string, popcon::PayloadIOV> mp = getOfflineInfo();

	for(std::map<std::string, popcon::PayloadIOV>::iterator it = mp.begin(); it != mp.end();it++)
	{
		std::cout << it->first << " , last object valid since " << it->second.last_since << std::endl;

	}

	coral::TimeStamp ts = lgrdr->lastRun(m_name, m_cs);
	
	unsigned int snc,tll;
	/*
	std::cerr << "Source implementation test ::getNewObjects : enter since ? \n";
	std::cin >> snc;
	std::cerr << "getNewObjects : enter till ? \n";
	std::cin >> tll;
	*/

	//the following code works, however since 1.6.0_pre7 it causes glibc 
	//double free error (inside CSC specific code) - commented 
	//
	//Using ES to get the data:

	edm::ESHandle<CSCDDUMap> dd_map;
	esetup.get<CSCDDUMapRcd>().get(dd_map);
	myddu_map = dd_map.product();
	std::cout << "size " << dd_map->ddu_map.size() << std::endl;

	snc = edm::IOVSyncValue::beginOfTime().eventID().run();
	tll = edm::IOVSyncValue::endOfTime().eventID().run();//infinite
	//snc =1;
	//tll =10;

	popcon::IOVPair iop = {snc,tll};
	//popcon::IOVPair iop2 = {snc+20,tll};
	//popcon::IOVPair iop3 = {snc+10,tll};

	//CSCDDUMap * p1 = new CSCDDUMap(*myddu_map);
	//CSCDDUMap * p2 = new CSCDDUMap(*myddu_map);


	m_to_transfer->push_back(std::make_pair((CSCDDUMap*)myddu_map,iop));
	//m_to_transfer->push_back(std::make_pair((CSCDDUMap*)p1,iop2));
	//m_to_transfer->push_back(std::make_pair((CSCDDUMap*)p2,iop3));

	std::cout << "CSC src - > getNewObjects -----------\n";
}
