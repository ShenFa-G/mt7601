/*ar: This file to call the driver functions and transmit custom beacon frames*/

#include <linux/kernel.h>
#include "linux/slab.h"
#include "rt_config.h"
#include "rtmp.h"
#include "rtmp_comm.h"
#define BUF_SIZE 48
#include <linux/module.h>
typedef struct PRTMP_Adapter pAd_swarm;
//struct sk_buff *skb_swarm;
static char swarmTxBuffer[BUF_SIZE];
static pAd_swarm; // ensure the right type and also the this is for the 
static int thread_flag = 0;


static swarm_sequence = 500 ;
extern void swarmTxPackets(void *pAd,int type);
extern void mlmeHelper(void *pAd,char * buf, int size);
extern int swarmInit(); // This method is defined in mlme.c
//EXPORT_SYMBOL(swarmTxPackets);
//EXPORT_SYMBOL(mlmeHelper);
/*Structure of the frame and ther fields defined*/

typedef struct frame_control
{
    unsigned int protoVer:2; /* protocol version*/
    unsigned int type:2; /*frame type field (Management,Control,Data)*/
    unsigned int subtype:4; /* frame subtype*/

    unsigned int toDS:1; /* frame coming from Distribution system */
    unsigned int fromDS:1; /*frame coming from Distribution system */
    unsigned int moreFrag:1; /* More fragments?*/
    unsigned int retry:1; /*was this frame retransmitted*/

    unsigned int powMgt:1; /*Power Management*/
    unsigned int moreDate:1; /*More Date*/
    unsigned int protectedData:1; /*Protected Data*/
    unsigned int order:1; /*Order*/
}frame_control;

struct ieee80211_radiotap_header{
    u_int8_t it_version;
    u_int8_t it_pad;
    u_int16_t it_len;
    u_int32_t it_present;
    u_int64_t MAC_timestamp;
    u_int8_t flags;
    u_int8_t dataRate;
    u_int16_t channelfrequency;
    u_int16_t channelType;
    int ssiSignal:8;
    int ssiNoise:8;
};

struct wi_frame {
    u_int16_t fc;
    u_int16_t wi_duration;
    u_int8_t wi_add1[6];
    u_int8_t wi_add2[6];
    u_int8_t wi_add3[6];
    u_int16_t wi_sequenceControl;
    // u_int8_t wi_add4[6];
    //unsigned int qosControl:2;
    //unsigned int frameBody[23124];
};

struct beacon_data {
    uint8_t timestamp[8];
    uint16_t interval;
    uint16_t capabilities;
};
