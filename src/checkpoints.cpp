#include <boost/assign/list_of.hpp> // for 'map_list_of()'
#include <boost/foreach.hpp>

#include "checkpoints.h"

#include "db.h"
#include "main.h"
#include "uint256.h"

namespace Checkpoints
{
    typedef std::map<int, uint256> MapCheckpoints;

    //
    // What makes a good checkpoint block?
    // + Is surrounded by blocks with reasonable timestamps
    //   (no blocks before with a timestamp after, none after with
    //    timestamp before)
    // + Contains no strange transactions
    //
    static MapCheckpoints mapCheckpoints =
        boost::assign::map_list_of
        (     0, hashGenesisBlockOfficial )
	(10, uint256("0x0000074074af28e73189ae5767b706246be2e0827c46d97a61178394aec877cf"))
	(31781, uint256("0x42265210870957b8d37f91a0834c6cda65949b2ca805bb3a7d527a4cd585a090")) //official hyp fork
	(80987, uint256("0x6b943fa756e915ddd8b654844781e21090ae9ddfcb2147fba46cac529df5be08")) //not using even number because sync gets sticky
	(199999, uint256("0x084b314dfee7db9d311a5db4dc4b8880df36eb7e9bb90ec98dd0bab5af2a7df2"))
	(235691, uint256("0xf0f71ea7edf7457e611ee893cdbb6ff19499713f4dae935d6d21e073d96a7dc3"))
	(235999, uint256("0xafe60dd0ab56ef529db21ea648ea4fd8de758a11b6a8ac1fa5cd2d4959162106"))
	(399999, uint256("0x875356232916a420c100b83d87cc9ce3eb9a174750b48d2fd1eefba7292163b5"))
	(499999, uint256("0x8e370d8ab8bdb6e6a5a4882dda755b23b5f284f633e04c12e6f73f92de15e68e"))
    (1207950, uint256("0xbad0a0f14081129f34d42fdc617638756158fd7b1413f4d3a2916bed2c1a61d4"))
	;

    static MapCheckpoints mapCheckpointsTestnet =
        boost::assign::map_list_of
        ( 0, hashGenesisBlockTestNet )
		(70, uint256("0x97c81df9aab50f1bef2e09ec8d806c3cc7ec6b7b7f13c70f1b854d8e40ed77c9"))
        ;

    bool CheckHardened(int nHeight, const uint256& hash)
    {
        MapCheckpoints& checkpoints = (fTestNet ? mapCheckpointsTestnet : mapCheckpoints);

        MapCheckpoints::const_iterator i = checkpoints.find(nHeight);
        if (i == checkpoints.end()) return true;
        return hash == i->second;
    }

    int GetTotalBlocksEstimate()
    {
        MapCheckpoints& checkpoints = (fTestNet ? mapCheckpointsTestnet : mapCheckpoints);

        return checkpoints.rbegin()->first;
    }

    CBlockIndex* GetLastCheckpoint(const std::map<uint256, CBlockIndex*>& mapBlockIndex)
    {
        MapCheckpoints& checkpoints = (fTestNet ? mapCheckpointsTestnet : mapCheckpoints);

        BOOST_REVERSE_FOREACH(const MapCheckpoints::value_type& i, checkpoints)
        {
            const uint256& hash = i.second;
            std::map<uint256, CBlockIndex*>::const_iterator t = mapBlockIndex.find(hash);
            if (t != mapBlockIndex.end())
                return t->second;
        }
        return NULL;
    }
}