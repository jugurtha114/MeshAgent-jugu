#ifndef OPUS_STUB
#define OPUS_STUB
#include <stdint.h>
typedef struct OpusEncoder OpusEncoder;
#define OPUS_OK 0
#define OPUS_APPLICATION_VOIP 2048
#define OPUS_APPLICATION_AUDIO 2049
#define OPUS_APPLICATION_RESTRICTED_LOWDELAY 2051
#define OPUS_BANDWIDTH_NARROWBAND 1101
#define OPUS_BANDWIDTH_MEDIUMBAND 1102
#define OPUS_BANDWIDTH_WIDEBAND 1103
#define OPUS_BANDWIDTH_SUPERWIDEBAND 1104
#define OPUS_BANDWIDTH_FULLBAND 1105
#define OPUS_AUTO -1000
#define OPUS_SET_BITRATE(x) 4002,(x)
#define OPUS_SET_VBR(x) 4006,(x)
#define OPUS_SET_VBR_CONSTRAINT(x) 4020,(x)
#define OPUS_SET_BANDWIDTH(x) 4008,(x)
#define OPUS_SET_INBAND_FEC(x) 4012,(x)
#define OPUS_SET_PACKET_LOSS_PERC(x) 4014,(x)
#define OPUS_SET_DTX(x) 4016,(x)
#define OPUS_SET_COMPLEXITY(x) 4010,(x)
OpusEncoder* opus_encoder_create(int32_t,int,int,int*);
int opus_encoder_ctl(OpusEncoder*,int,...);
int opus_encode(OpusEncoder*,const int16_t*,int,unsigned char*,int32_t);
void opus_encoder_destroy(OpusEncoder*);
#endif
