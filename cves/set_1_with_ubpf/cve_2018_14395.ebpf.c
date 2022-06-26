/*
note: "allows attackers to cause a denial of service (application crash caused by a divide-by-zero error) with a user crafted audio file when converting to the MOV audio format."
cve link: https://cve.mitre.org/cgi-bin/cvename.cgi?name=CVE_2018_14395
commit link: https://github.com/FFmpeg/FFmpeg/commit/2c0e98a0b478284bdff6d7a4062522605a8beae5
*/

#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>

typedef struct stack_frame {
	uint64_t a1;
	uint64_t a2;
	uint64_t a3;
	uint64_t a4;
} __attribute__ ((__packed__, aligned(4))) stack_frame;

typedef struct AVCodecParameters {
    unsigned int         codec_tag;
    // enum AVCodecID   codec_id;
    int channels;
}AVCodecParameters;

typedef struct MOVTrack {
    int         mode;
    int         tag;
    int         audio_vbr;
    unsigned    timescale;
    AVCodecParameters *par;
} MOVTrack;

#define MODE_MOV  0x02

//int dummy_cve_2018_14395_mov_write_audio_tag(void *s, void *pb, void *mov, MOVTrack *track) {
int dummy_cve_2018_14395_mov_write_audio_tag(void *mem) {
	stack_frame *frame = (stack_frame *)mem;
	MOVTrack *track = (MOVTrack *)(frame->a4);
	
    //unsigned int tag = track->tag;
    int version = 0;
    if (track->mode == MODE_MOV) {
    	//if (track->timescale > 0x7fff) {
    	// patch
        if (track->timescale > 0x7fff || !track->par->channels) {
            // if (mov_get_lpcm_flags(track->par->codec_id))
            //     tag = AV_RL32("lpcm");
            //tag = 11;
            //track->tag = 11;
            version = 2;
        } else if (track->audio_vbr) {
            version = 1;
        }
    }
    return version;
}

