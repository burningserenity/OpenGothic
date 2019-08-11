#pragma once

#include <cstdint>

#include <daedalus/DaedalusStdlib.h>

class Npc;
class GameScript;
class Serialize;

class FightAlgo final {
  public:
    FightAlgo();

    void load(Serialize& fin);
    void save(Serialize& fout);

    enum Action : uint8_t {
      MV_NULL     = 0,
      MV_MOVEG    = 1,
      MV_MOVEA    = 2,
      MV_JUMPBACK = 3,
      MV_ATACK    = 4,
      MV_ATACKL   = 5,
      MV_ATACKR   = 6,
      MV_STRAFEL  = 7,
      MV_STRAFER  = 8,
      MV_BLOCK    = 8,
      MV_WAIT     = 10,
      MV_WAITLONG = 11,
      MV_TURN2HIT = 12,

      MV_MAX      = 6
      };

    Action nextFromQueue(Npc &npc, Npc &tg, GameScript& owner);
    void   consumeAction();
    void   onClearTarget();
    void   onTakeHit();

    bool   hasInstructions() const;
    bool   fetchInstructions(Npc &npc, Npc &tg, GameScript& owner);

    float  prefferedAtackDistance(const Npc &npc, const Npc &tg, GameScript &owner) const;
    float  prefferedGDistance    (const Npc &npc, const Npc &tg, GameScript &owner) const;

    bool   isInAtackRange        (const Npc &npc, const Npc &tg, GameScript &owner);
    bool   isInGRange            (const Npc &npc, const Npc &tg, GameScript &owner);
    bool   isInFocusAngle        (const Npc &npc, const Npc &tg);

  private:
    void   fillQueue(Npc &npc, Npc &tg, GameScript& owner);
    void   fillQueue(GameScript& owner,const Daedalus::GEngineClasses::C_FightAI& src);

    static float  gRange         (GameScript &owner,const Npc &npc);
    static float  weaponRange    (GameScript &owner,const Npc &npc);
    static float  weaponOnlyRange(GameScript &owner,const Npc &npc);

    Daedalus::GEngineClasses::Move queueId=Daedalus::GEngineClasses::Move(0);
    Action                         tr   [MV_MAX]={};
    bool                           hitFlg=false;
  };
