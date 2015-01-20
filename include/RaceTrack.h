#ifndef _RACETRACK_H_
#define _RACETRACK_H_

#include <vector>
#include <algorithm>

#include "Cache.h"
#include "Timer.h"

typedef int RTPortPos;
typedef int RTPos;
typedef enum {
    ReadPort,
    WritePort,
    ReadWritePort
} RTPortType;

using namespace std;

struct RTGroup {
    RTPos head; // current position
    vector<RTPortPos> r; // ports list
    vector<RTPortPos> w;
    vector<RTPortPos> rw;

    RTGroup(vector<RTPortPos> r, 
            vector<RTPortPos> w,
            vector<RTPortPos> rw);

    RTPos toTrackPos(RTPos stdPos) { return stdPos - head; }
    RTPos toStdPos(RTPos trackPos) { return trackPos + head; }
    RTPortPos findPort(RTPos pos, RTPortType type);
    RTPortPos findMinDis(RTPos pos, vector<RTPortPos> ports);
};

struct RTCoord {
    RTPos pos;
    int gid;
    RTCoord(RTPos pos, int gid): pos(pos), gid(gid) {}
};

class RaceTrack {
public:
    RaceTrack() {};
    RaceTrack(int numDomain,
              int numTrack,
              int size,
              TimeType shiftTime,
              vector<RTPortPos> r,
              vector<RTPortPos> w,
              vector<RTPortPos> rw);

    Timer read(RTPos pos, int gid, Timer timer);
    Timer write(RTPos pos, int gid, Timer timer);
    Timer access(RTPos pos, int gid, RTPortType type, Timer timer);
    Timer move(RTPos src, RTPos dst, int gid, Timer timer);

    int numDomain;
    int numTrack;
    int numGroup;
    int size;

    TimeType shiftTime;

private:
    vector<RTGroup> groups;
};

#endif
