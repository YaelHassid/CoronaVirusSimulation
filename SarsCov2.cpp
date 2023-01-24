#pragma clang diagnostic push
#pragma clang diagnostic ignored "-Wunknown-pragmas"
#pragma ide diagnostic ignored "cppcoreguidelines-pro-type-member-init"
#include "SarsCov2.h"

SarsCov2::SarsCov2(const vector<string> &virusComb, char t, double p) : virusComb(virusComb), type(t), prob(p), refCount(1){}
SarsCov2::SarsCov2(SarsCov2* virus) : virusComb(virus->virusComb), type(virus->type), prob(virus->prob){
    ancestor = virus;
    fit = virus->fit;
    virus->refCount++;
}

SarsCov2::~SarsCov2() {
    if (ancestor != nullptr) ancestor->refCount--;
}
int SarsCov2::getRefCount() const {
    return refCount;
}
#pragma clang diagnostic pop