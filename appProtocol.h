#ifndef _PACKET_PARSER_DEFINED_
#define _PACKET_PARSER_DEFINED_

#include <stdio.h>
#include <cstring>

struct Packet{
    union union_tag{
        char id;
        struct info_tag {
            char id;
            char mode;
            char volume[3];
            char note[3];
            char scale;
        } info;
        struct mode_tag {
            char id;
            char mode;
        } modeChange;
        struct vol_tag {
            char id;
            char volume[3];
        } volumeChange;
    } packetUnion;
};

struct InfoMessage{
    char mode;
    unsigned short volume;
    unsigned short note;
    unsigned short scale;

    InfoMessage(char mode, unsigned short volume, unsigned short note, unsigned short scale) :
        mode(mode), volume(volume), note(note), scale(scale) {}

    Packet makePacket();
};

struct ModeChangeMessage{
    char mode;

    ModeChangeMessage(char mode) : mode(mode) {}

    Packet makePacket();
};

struct VolumeChangeMessage{
    unsigned short volume;

    VolumeChangeMessage(unsigned short volume) : volume(volume) {}

    Packet makePacket();
};

#endif //_PACKET_PARSER_DEFINED_