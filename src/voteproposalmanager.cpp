#include "voteproposalmanager.h"
#include "voteproposal.h"

using namespace std;

bool CVoteProposalManager::CheckProposal(const CVoteProposal &proposal)
{
    // If the proposal is already in the blockchain then it's guaranteed to be valid
    if (mapProposalData.count(proposal.GetHash()) != 0) {
        return true;
    }

    // Proposal name length must be between 1 and MAX_CHAR_NAME (inclusive)
    if (proposal.GetName().empty() || proposal.GetName().size() > MAX_CHAR_NAME) {
        return false;
    }

    // Proposal description length must be between 1 and MAX_CHAR_ABSTRACT (inclusive)
    if (proposal.GetDescription().empty() || proposal.GetDescription().size() > MAX_CHAR_ABSTRACT) {
        return false;
    }

    // Proposal voting period cannot start before or at the current height or after MAX_BLOCKS_IN_FUTURE
    if (proposal.GetStartHeight() <= nBestHeight || proposal.GetStartHeight() > nBestHeight + MAX_BLOCKS_IN_FUTURE) {
        return false;
    }

    // Proposal voting period length must be between 1 and MAX_CHECKSPAN (inclusive)
    if (!proposal.GetCheckSpan() || proposal.GetCheckSpan() > MAX_CHECKSPAN) {
        return false;
    }

    // Check to see if there is room on the blockchain for this proposal
    VoteLocation location;
    if (!GetNextLocation(proposal.GetBitCount(), proposal.GetStartHeight(), proposal.GetCheckSpan(), location)) {
        return false;
    }

    return true;
}

//! Add a proposal to the manager. Note that it must not have conflicts in its scheduling.
bool CVoteProposalManager::Add(const CVoteProposal& proposal)
{
    CProposalMetaData newProposal;
    newProposal.location = proposal.GetLocation();
    newProposal.hash = proposal.GetHash();
    newProposal.nHeightStart = proposal.GetStartHeight();
    newProposal.nHeightEnd = newProposal.nHeightStart + proposal.GetCheckSpan();

    //Check if any of the existing proposals are using the same bits during the same time
    for (auto it : mapProposalData) {
        CProposalMetaData existingProposal = it.second;
        //Clear of any conflicts, starts after the existing proposal ends
        if (newProposal.location.nMostSignificantBit < existingProposal.location.nLeastSignificantBit)
            continue;
        //Clear of any conflicts, ends before the existing proposal starts
        if (newProposal.location.nLeastSignificantBit > existingProposal.location.nMostSignificantBit)
            continue;
        //Clear of any conflicts, there is not overlap in the voting period
        if (newProposal.nHeightStart > existingProposal.nHeightEnd || newProposal.nHeightEnd < existingProposal.nHeightStart)
            continue;

        return error("%s: Proposal position is already occupied during the block span requested", __func__);
    }

    mapProposalData.insert(make_pair(newProposal.hash, newProposal));
    printf("%s: added proposal %s\n", __func__, newProposal.hash.GetHex().c_str());
    return true;
}

//! Remove a proposal from the proposal manager
void CVoteProposalManager::Remove(const uint256& hashProposal)
{
    auto it = mapProposalData.find(hashProposal);
    if (it != mapProposalData.end())
        mapProposalData.erase(it);
}

//! Get proposals that are actively being voted on
map<uint256, VoteLocation> CVoteProposalManager::GetActive(int nHeight)
{
    map<uint256, VoteLocation> mapActive;
    for (auto it : mapProposalData) {
        CProposalMetaData data = it.second;
        if ((int)data.nHeightStart <= nHeight && (int)data.nHeightEnd >= nHeight)
            mapActive.insert(make_pair(data.hash, data.location));
    }

    return mapActive;
}

bool CVoteProposalManager::GetNextLocation(int nBitCount, int nStartHeight, int nCheckSpan, VoteLocation& location)
{
    //Conflicts for block range
    vector<CProposalMetaData> vConflictingTime;
    for (auto it : mapProposalData) {
        CProposalMetaData data = it.second;
        int nEndHeight = nStartHeight + nCheckSpan;
        if ((int)data.nHeightEnd < nStartHeight)
            continue;
        if ((int)data.nHeightStart > nEndHeight)
            continue;
        vConflictingTime.emplace_back(data);
    }

    //Find an open location for the new proposal, return left most bits
    if (vConflictingTime.empty()) {
        location.nMostSignificantBit = 27;
        location.nLeastSignificantBit = (uint8_t)(location.nMostSignificantBit - nBitCount + 1);
        return true;
    }

    //create a vector tracking available spots
    vector<int> vAvailable(28, 1);

    //remove spots that are already taken
    for (auto data : vConflictingTime) {
        for (int i = data.location.nMostSignificantBit; i >= data.location.nLeastSignificantBit; i--) {
            vAvailable.at(i) = 0;
        }
    }

    //find an available sequence of bits that fit the proposal
    vector<int> vRange;
    int nSequential = 0;
    for (int i = 27; i >= 0; i--) {
        uint8_t n = static_cast<uint8_t>(i);
        nSequential = vAvailable.at(n) == 1 ? nSequential + 1 : 0;
        if (nSequential == nBitCount) {
            location.nLeastSignificantBit = n;
            location.nMostSignificantBit = static_cast<uint8_t>(n + nBitCount - 1);
            return true;
        }
    }
    return false;
}