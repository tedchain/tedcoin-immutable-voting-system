#ifndef TEDCOIN_VOTEPROPOSALMANAGER_H
#define TEDCOIN_VOTEPROPOSALMANAGER_H

#include <set>
#include "voteobject.h"

class CVoteProposal;

struct CProposalMetaData
{
    uint256 hash;
    VoteLocation location;
    unsigned int nHeightStart;
    unsigned int nHeightEnd;
};

class CVoteProposalManager
{
private:
    std::map<uint256, CProposalMetaData> mapProposalData;
public:
    bool Add(const CVoteProposal& proposal);
    void Remove(const uint256& hashProposal);
    std::map<uint256, VoteLocation> GetActive(int nHeight);
    bool GetNextLocation(int nBitCount, int nStartHeight, int nCheckSpan, VoteLocation& location);
    std::map<uint256, CProposalMetaData> GetAllProposals() const { return mapProposalData; };
    bool CheckProposal (const CVoteProposal& proposal);
};

#endif //TEDCOIN_VOTEPROPOSALMANAGER_H
