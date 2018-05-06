#include <SoundManager.h>

SoundManager::SoundManager(){
  timer = 0;
  tone = 0;
  tonePrev = 0;
}

int SoundManager::getID(){
  int id = effects.size();
  Sound newS = {id, 0, 0, 0, 0, 0, false};
  effects.push_back(newS);
  return id;
}

void SoundManager::setContTone(int ID, float priority, float frequency){
  if(ID >= effects.size() || ID < 0)
    return;
  effects[ID].start = timer;
  effects[ID].duration = -1;
  effects[ID].priority = priority;
  effects[ID].startF = frequency;
  effects[ID].alive = true;
}

void SoundManager::setEffect(int ID, float priority, float duration, float startFrequency, float endFrequency){
  if(ID >= effects.size() || ID < 0)
    return;
  effects[ID].start = timer;
  effects[ID].duration = duration;
  effects[ID].priority = priority;
  effects[ID].startF = startFrequency;
  effects[ID].endF = endFrequency;
  effects[ID].alive = true;
}

void SoundManager::stopContTone(int ID){
  if(ID >= effects.size() || ID < 0)
    return;
  effects[ID].alive = false;
}

void SoundManager::update(float dt, Controller &cont){
  timer += dt;
  int topID = -1;
  float topPriority = 0;
  for(unsigned int i = 0; i < effects.size(); i++){
    if(effects[i].alive && effects[i].duration != -1 && effects[i].start + effects[i].duration <= timer)
      effects[i].alive = false;
    if(effects[i].priority > topPriority && effects[i].alive){
      topID = effects[i].ID;
      topPriority = effects[i].priority;
    }
  }
  if(topID == -1)
  {
    tone = 0;
  }
  else if(effects[topID].duration != -1){
    float p = (timer - effects[topID].start) / effects[topID].duration;
    tone = (effects[topID].endF - effects[topID].startF) * p + effects[topID].startF;
  }
  else{
    tone = effects[topID].startF;
  }
  if(tone != tonePrev || tone == 0){
    cont.toneContinous(tone);
  }
  tone = tonePrev;
}
