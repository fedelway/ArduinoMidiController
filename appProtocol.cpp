#include "appProtocol.h"

Packet InfoMessage::makePacket() {
    Packet ret;

    ret.packetUnion.info.id = 'I';
    ret.packetUnion.info.mode = mode;

    char volBuf[4] = {0};
    sprintf(volBuf, "%03.3u", volume );
    memcpy(ret.packetUnion.info.volume,volBuf,3);

    char noteBuf[4] = {0};
    sprintf(noteBuf, "%03.3u", note );
    memcpy(ret.packetUnion.info.note,noteBuf,3);

    ret.packetUnion.info.scale = scale - '0';

    return ret;
}

Packet ModeChangeMessage::makePacket() {
    Packet ret;

    ret.packetUnion.modeChange.id = 'M';
    ret.packetUnion.modeChange.mode = mode;

    return ret;
}

Packet VolumeChangeMessage::makePacket() {
    Packet ret;

    ret.packetUnion.volumeChange.id = 'V';
    
    char volBuf[4] = {0};
    sprintf(volBuf, "%03.3u", volume );
    memcpy(ret.packetUnion.volumeChange.volume,volBuf,3);

    return ret;
}