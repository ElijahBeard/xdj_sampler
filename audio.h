#define MINIAUDIO_IMPLEMENTATION
#include "soundfont/miniaudio_io.h"
#define TSF_IMPLEMENTATION
#include "soundfont/tsf.h"

static tsf* g_sf;
static ma_mutex g_mutex;
ma_device device;
ma_device_config device_config;

static void AudioCallback(ma_device* pDevice, void* pOutput, const void* pInput, ma_uint32 frameCount) {
    ma_mutex_lock(&g_mutex);
    tsf_render_float(g_sf,(float*)pOutput,(int)frameCount,0);
    ma_mutex_unlock(&g_mutex);
}

int init_audio() {
    /* Mini Audio Init */
    device_config = ma_device_config_init(ma_device_type_playback);
    device_config.playback.format = ma_format_f32;
    device_config.playback.channels = 2;
    device_config.sampleRate = 44100;
    device_config.dataCallback = AudioCallback;
    if (ma_device_init(NULL,&device_config,&device) != 0) {perror("Couldn't Init Audio Driver\n");return 1;}

    /* SoundFont Init */
    g_sf = tsf_load_filename("assets/audio/ac.sf2");
    if (!g_sf) {perror("Couldn't Load SoundFont\n");return 1;}
    tsf_set_output(g_sf,TSF_STEREO_INTERLEAVED,(int)device_config.sampleRate,0);

    ma_mutex_init(&g_mutex);

    if(ma_device_start(&device) != 0) {
        perror("Failed to start playback device\n");
        ma_device_uninit(&device);
        return 1;
    }

    return 0;
}

void free_audio() {
    ma_device_uninit(&device);
}

void note_on(int note) {
    ma_mutex_lock(&g_mutex);
    tsf_note_on(g_sf,50,note,1.0f);
    ma_mutex_unlock(&g_mutex);
}

void note_off(int note) {
    ma_mutex_lock(&g_mutex);
    tsf_note_off(g_sf,50,note);
    ma_mutex_unlock(&g_mutex);
}