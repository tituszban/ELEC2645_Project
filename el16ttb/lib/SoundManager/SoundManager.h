#ifndef LIB_SOUNDMANAGER_H_
#define LIB_SOUNDMANAGER_H_

using namespace std;
#include <vector>
#include <Controller.h>

struct Sound{
  int ID;
  float start;
  float duration;
  float priority;
  float startF;
  float endF;
  bool alive;
};

class SoundManager{
public:
  SoundManager();
  int getID();
  void setContTone(int ID, float priority, float frequency);
  void setEffect(int ID, float priority, float duration, float startFrequency, float endFrequency);
  void stopContTone(int ID);
  void update(float dt, Controller &cont);

private:
  vector<Sound> effects;
  float timer;
  float tone;
  float tonePrev;
};

#endif
