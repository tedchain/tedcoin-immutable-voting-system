#include "voteobject.h"
#include "main.h"

using namespace std;

int CVoteObject::GetCombinedVotes(const std::vector<CVoteObject>& votes) {
    int nCombinedVotes = 0;

    for(CVoteObject vote: votes){
        nCombinedVotes |= vote.GetFormattedVote();
    }

    return nCombinedVotes;
}

bool CVoteObject::Vote(int nVotersChoice)
{
    nChoice = static_cast<uint32_t>(nVotersChoice);
    return true;
}

