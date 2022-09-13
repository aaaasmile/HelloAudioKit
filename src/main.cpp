// /* @brief AUDIOKIT_BOARD selects a specic board:
//  * 1) lyrat_v4_3
//  * 2) lyrat_v4_2 - DRAFT Not Tested
//  * 3) lyrat_mini_v1_1 - DRAFT Not Tested
//  * 4) esp32_s2_kaluga_1_v1_2 - DRAFT Not Tested
//  * 5) ai_thinker (ES8388) 2957 3478 A149
//  * 6) ai_thinker (AC101) 2762 2957
//  * 7) ai_thinker (ES8388) 2957
//  * 10) generic_es8388
//  */
// #define AUDIOKIT_BOARD 5
// #define SD_FAT_TYPE 2 // 1 for FAT16/FAT32, 2 for exFAT, 3 for FAT16/FAT32 and exFAT.
// #define AI_THINKER_ES8388_VOLUME_HACK 1
// #define LED_GPIO 19

// #define WIFI_SSID ""
// #define WIFI_PASSWORD ""

// // ------------------------------------------------------

// //#define USE_SDFAT
// //#define USE_HELIX // #define USE_MAD
// #include "AudioTools.h"
// //#include "AudioCodecs/CodecMP3Helix.h" 
// #include "AudioCodecs/CodecMP3MAD.h"
// #include "AudioLibs/AudioKit.h"

// #include <WiFi.h>
// #include <WiFiClient.h>

// // WiFi
// WiFiClient net;

// AudioKitStream kit;
// //EncodedAudioStream dec(&kit, new MP3DecoderHelix()); 
// EncodedAudioStream dec(&kit, new MP3DecoderMAD());

// // URL streaming
// URLStream urlStream(WIFI_SSID, WIFI_PASSWORD);
// StreamCopy copierUrl(dec, urlStream);

// // SD card
// // const char *startFilePath = "/";
// // const char* ext = "mp3";
// // int speedMz = 10;

// //AudioSourceSdFat source(startFilePath, ext, PIN_AUDIO_KIT_SD_CARD_CS, speedMz);
// //StreamCopy copierSd;

// void playUrl(const char* url) {
//   dec.begin();
//   urlStream.begin(url, "audio/mp3");
//   copierUrl.copyAll(5, 1000);

//   urlStream.end();
//   dec.end();
// }

// // void playSdIndex(int index) {
// //   dec.begin();
// //   source.begin(); // Init SD

// //   Stream* inputStream = source.selectStream(index);

// //   copierSd.begin(dec, *inputStream);
// //   copierSd.copyAll();

// //   dec.end();
// // }


// void setup() {
//   Serial.begin(115200);
//   AudioLogger::instance().begin(Serial, AudioLogger::Warning);

//   AudioKitStreamConfig cfg = kit.defaultConfig(TX_MODE);
//   cfg.sample_rate = 24000;
//   cfg.channels = 1;
//   // cfg.bits_per_sample = 16

//   kit.begin(cfg);
//   kit.setVolume(50);

//   // We start by connecting to a WiFi network
//   Serial.println();
//   Serial.print("Connecting to SSID: ");
//   Serial.println(WIFI_SSID);

//   WiFi.begin(WIFI_SSID, WIFI_PASSWORD);

//   while (WiFi.status() != WL_CONNECTED) {
//     delay(500);
//     Serial.print(".");
//   }

//   Serial.println("WiFi connected");
//   Serial.println("IP address: ");
//   Serial.println(WiFi.localIP());

//   pinMode(LED_GPIO, OUTPUT);
//   digitalWrite(LED_GPIO, HIGH);
//   delay(1000);
//   playUrl("http://stream.srg-ssr.ch/m/rsj/mp3_128");
// }

// void loop() {
//   kit.processActions();
// }

///////////////////////////////////////////
// Il mio radio player, che funziona con lo speaker
//#define AUDIOKIT_BOARD 7 
#define USE_HELIX 
#include <Arduino.h>
#include "AudioTools.h"
#include "AudioLibs/AudioKit.h"
#include "AudioCodecs/CodecMP3Helix.h"

const char *urls[] = {
  "http://stream.srg-ssr.ch/m/rsj/mp3_128",
  "http://stream.srg-ssr.ch/m/drs3/mp3_128",
  "http://stream.srg-ssr.ch/m/rr/mp3_128",
  "http://sunshineradio.ice.infomaniak.ch/sunshineradio-128.mp3",
  "http://streaming.swisstxt.ch/m/drsvirus/mp3_128"
};

const char *wifi = "";
const char *password = "";

AudioKitStream kit;
URLStream urlStream(wifi, password);
AudioSourceURL source(urlStream, urls, "audio/mp3");
MP3DecoderHelix decoder;
AudioPlayer player(source, kit, decoder);

void setup() {
  Serial.begin(115200);
  AudioLogger::instance().begin(Serial, AudioLogger::Warning);
  AudioKitStreamConfig cfg = kit.defaultConfig(RxTxMode::TX_MODE);
  cfg.default_actions_active = true;
  kit.begin(cfg);

  player.begin();
  player.setVolume(0.0); // range (0.0 -1.0)
  //selfAudioKit->setSpeakerActive(false); // headphone sembra non funzionare
}

void loop() {
  kit.processActions();
  player.copy();
}

///////////////// Example Out (funziona con lo speaker)
// #include <Arduino.h>
// #include "AudioKitHAL.h"
// #include "SineWaveGenerator.h"

// AudioKit kit;
// MySineWaveGenerator wave;
// const int BUFFER_SIZE = 1024;
// uint8_t buffer[BUFFER_SIZE];

// void setup() {
//   LOGLEVEL_AUDIOKIT = AudioKitInfo; 
//   Serial.begin(115200);
//   // open in write mode
//   auto cfg = kit.defaultConfig(AudioOutput);
//   kit.begin(cfg);

//   // 1000 hz
//   wave.setFrequency(1000);
//   wave.setSampleRate(cfg.sampleRate());

// }

// void loop() {
//   size_t l = wave.read(buffer, BUFFER_SIZE);
//   kit.write(buffer, l);
// }

//////////////////////////////////// Example Input

//#include <Arduino.h>
// #include "AudioKitHAL.h"

// AudioKit kit;
// const int BUFFER_SIZE = 1024;
// uint8_t buffer[BUFFER_SIZE];

// void printBuffer(int len){
//   // by default we get int16_t values on 2 channels = 4 bytes per frame
//   int16_t *value_ptr = (int16_t*) buffer;
//   for (int j=0;j<len/4;j++){
//     Serial.print(*value_ptr++);
//     Serial.print(", ");
//     Serial.println(*value_ptr++);
//   }
// }

// void setup() {
//   Serial.begin(115200);
//   // open in read mode
//   auto cfg = kit.defaultConfig(AudioInput);
//   cfg.adc_input = AUDIO_HAL_ADC_INPUT_LINE1; // microphone
//   cfg.sample_rate = AUDIO_HAL_16K_SAMPLES;
//   kit.begin(cfg);
// }

// void loop() {
//   size_t len = kit.read(buffer, BUFFER_SIZE);
//   printBuffer(len);
// }

/////////////////////////////////

// #define USE_HELIX 
// #include <Arduino.h>
// #include "AudioTools.h"
// #include "AudioCodecs/CodecMP3Helix.h"



// const char *urls[] = {
//   "http://stream.srg-ssr.ch/m/rsj/mp3_128",
//   "http://stream.srg-ssr.ch/m/drs3/mp3_128",
//   "http://stream.srg-ssr.ch/m/rr/mp3_128",
//   "http://sunshineradio.ice.infomaniak.ch/sunshineradio-128.mp3",
//   "http://streaming.swisstxt.ch/m/drsvirus/mp3_128"
// };
// const char *wifi = "";
// const char *password = "";

// // #define WIFI_SSID ""
// // #define WIFI_PASSWORD ""

// URLStream urlStream(wifi, password);
// AudioSourceURL source(urlStream, urls, "audio/mp3");
// I2SStream i2s;
// MP3DecoderHelix decoder;
// AudioPlayer player(source, i2s, decoder);

// // additional controls
// const int volumePin = A0;
// Debouncer nextButtonDebouncer(2000);
// const int nextButtonPin = 13;

// void setup() {
//   Serial.begin(115200);
//   AudioLogger::instance().begin(Serial, AudioLogger::Info);

//   // setup output
//   auto cfg = i2s.defaultConfig(TX_MODE);
//   i2s.begin(cfg);

//   // setup player
//   player.begin();

//   player.setVolume(50);
// }

// // Sets the volume control from a linear potentiometer input
// void updateVolume() {
//   // Reading potentiometer value (range is 0 - 4095)
//   float vol = static_cast<float>(analogRead(volumePin));
//   // min in 0 - max is 1.0
//   player.setVolume(vol/4095.0);
// }


// // Moves to the next url when we touch the pin
// void updatePosition() {
//    if (digitalRead(nextButtonPin)) {
//       Serial.println("Moving to next url");
//       if (nextButtonDebouncer.debounce()){
//         player.next();
//       }
//   }
// }


// void loop() {
//   //updateVolume(); // remove comments to activate volume control
//   //updatePosition();  // remove comments to activate position control
//   player.copy();
// }
