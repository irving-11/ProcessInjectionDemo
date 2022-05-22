#include <stdio.h>
#include <stdlib.h>

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

int dummy_cve_2018_14395_mov_write_audio_tag(void *s, void *pb, void *mov, MOVTrack *track) {
    unsigned int tag = track->tag;
    int version = 0;
    if (track->mode == MODE_MOV) {
        if (track->timescale > 0x7fff || !track->par->channels) {
            // if (mov_get_lpcm_flags(track->par->codec_id))
            //     tag = AV_RL32("lpcm");
            tag = 11;
            track->tag = 11;
            version = 2;
        } else if (track->audio_vbr) {
            version = 1;
        }
    }
    return 0;
}

int main() {
    MOVTrack *track; int ret = 0;
    track = (MOVTrack *)malloc(sizeof(MOVTrack));
    track->tag = 0; track->mode = 2; track->timescale = 1; 
    AVCodecParameters *par;
    par = (AVCodecParameters *)malloc(sizeof(AVCodecParameters));
    par->channels = 0;
    track->par = par;
    //track->par->channels = 0;

    ret = dummy_cve_2018_14395_mov_write_audio_tag((void *)0, (void *)0, (void *)0, track);
    if (track->tag == 11) {
		printf("after patch\n");}
	else if (ret == 0){
		printf("before patch\n");}

    return 0;
}

